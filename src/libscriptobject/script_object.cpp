/*
 *  This file is part of libscriptobject.
 *
 *  libscriptobject is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libscriptobject is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libscriptobject.  If not, see <http://www.gnu.org/licenses/>.
**/

#include "script_object.h"

#include <cstring>

#include "md5.h"

#include "exceptions.h"
#include "script_object_source.h"
#include "script_object_vector_source.h"
#include "script_object_factory.h"

rs::scriptobject::ScriptObject::ScriptObject(unsigned size) : size_(size) {
    
}

rs::scriptobject::ScriptObject::~ScriptObject() {
    // destroy all child object/array references
    auto valueStart = getValueStart(*this);
    for (int i = 0; i < keys_->count; ++i) {
        auto index = keys_->keys[i].index;

        switch (static_cast<rs::scriptobject::ScriptObjectType>(keys_->keys[i].type)) {
            case ScriptObjectType::Object: {
                auto child = reinterpret_cast<ScriptObjectPtr*>(valueStart + valueOffsets_[index]);
                child->~ScriptObjectPtr();
                break;
            }
            case ScriptObjectType::Array: {
                auto child = reinterpret_cast<ScriptArrayPtr*>(valueStart + valueOffsets_[index]);
                child->~ScriptArrayPtr();
                break;
            }
        }
    }
}

const unsigned char* rs::scriptobject::ScriptObject::getValueStart() const {
    auto fieldCount = keys_->count;
    auto start = reinterpret_cast<const unsigned char*>(&(valueOffsets_[fieldCount]));
    return start;
}

unsigned char* rs::scriptobject::ScriptObject::getValueStart(ScriptObject& object) {
    auto fieldCount = object.keys_->count;
    auto start = reinterpret_cast<unsigned char*>(&(object.valueOffsets_[fieldCount]));
    return start;
}

unsigned rs::scriptobject::ScriptObject::CalculateSizeOverhead(unsigned fieldCount) {
    return sizeof(ScriptObject) + (fieldCount * sizeof(ScriptObject::valueOffsets_[0]));
}

unsigned rs::scriptobject::ScriptObject::CalculateSize(const ScriptObjectSource& source) {
    unsigned fieldCount = source.count();
    unsigned size = CalculateSizeOverhead(fieldCount);
    
    for (int i = 0; i < fieldCount; ++i) {
        auto type = source.type(i);
        
        switch (type) {
            case ScriptObjectType::String:
                size += source.getStringLength(i) + 1;
                break;
            case ScriptObjectType::Boolean:
                // booleans store their state in their valueOffset[] field
                size += 0;
                break;
            case ScriptObjectType::Double:
                size += sizeof(double);
                break;
            case ScriptObjectType::Int32:
                size += sizeof(std::int32_t);
                break;
            case ScriptObjectType::UInt32:
                size += sizeof(std::uint32_t);
                break;
            case ScriptObjectType::Int64:
                size += sizeof(std::int64_t);
                break;                
            case ScriptObjectType::UInt64:
                size += sizeof(std::uint64_t);
                break;                
            case ScriptObjectType::Null:
                size += 0;
                break;
            case ScriptObjectType::Object:
                size += sizeof(ScriptObjectPtr);
                break;
            case ScriptObjectType::Array:
                size += sizeof(ScriptArrayPtr);
                break;
            case ScriptObjectType::Undefined:
                size += 0;
                break;
            default:
                throw UnknownSourceFieldTypeException();
                break;
        }
    }
    
    return size;
}

unsigned rs::scriptobject::ScriptObject::getStringFieldLength(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    return getStringFieldLength(key);
}

unsigned rs::scriptobject::ScriptObject::getStringFieldLength(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    return getStringFieldLength(key);
}

unsigned rs::scriptobject::ScriptObject::getStringFieldLength(const ScriptObjectKey& key) const {
    if (key.type != (unsigned)ScriptObjectType::String) {
        throw TypeCastException();
    }
    
    unsigned nextIndex = key.index;    
    for (int i = key.index - 1; i >= 0; --i) {
        ScriptObjectKey nextKey;
        if (keys_->getKey(i, nextKey) && nextKey.type == (unsigned)ScriptObjectType::String) {
            nextIndex = nextKey.index;
            break;
        }
    }

    unsigned length = 0;
    if (nextIndex < key.index) {
        length = valueOffsets_[nextIndex] - valueOffsets_[key.index];
    } else {
        auto end = reinterpret_cast<const unsigned char*>(this) + size_;
        
        auto start = reinterpret_cast<const unsigned char*>(getValueStart());
        start += valueOffsets_[key.index];
        
        length = end - start;
    }
    
    return length;
}

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObject::getKeys() const {
    return keys_;
}

std::uint64_t rs::scriptobject::ScriptObject::getSize(bool includeChildren) const {
    if (!includeChildren) {
        return size_;
    } else {
        std::uint64_t size = size_;
        
        for (auto count = keys_->count, i = decltype(count)(0); i < count; ++i) {
            switch (getType(i)) {
                case ScriptObjectType::Object: size += getObject(i)->getSize(true); break;
                case ScriptObjectType::Array: size += getArray(i)->getSize(true); break;
            }
        }
        
        return size;
    }    
}

rs::scriptobject::ScriptObjectKeys::size_t rs::scriptobject::ScriptObject::getCount() const { 
    return keys_->count; 
}

const char* rs::scriptobject::ScriptObject::getName(int index) const {
    return keys_->getKeyName(index);
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObject::getType(int index) const {
    ScriptObjectKey key;
    if (keys_->getKey(index, key)) {
        return static_cast<ScriptObjectType>(key.type);
    } else {
        return ScriptObjectType::Unknown;
    }
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObject::getType(const char* name) const {
    ScriptObjectKey key;
    if (keys_->getKey(name, key)) {
        return static_cast<ScriptObjectType>(key.type);
    } else {
        return ScriptObjectType::Unknown;
    }
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObject::getType(const char* name, int& index) const {
    ScriptObjectKey key;
    if (keys_->getKey(name, key)) {
        index = key.index;
        return static_cast<ScriptObjectType>(key.type);
    } else {
        return ScriptObjectType::Unknown;
    }
}

const char* rs::scriptobject::ScriptObject::getString(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException{};
    }
    
    if (key.type != (unsigned)ScriptObjectType::String) {
        throw TypeCastException{};
    }
    
    auto str = reinterpret_cast<const char*>(getValueStart());
    str += valueOffsets_[key.index];
    return str;
}

const char* rs::scriptobject::ScriptObject::getString(const char* name, bool throwOnError) const {
    const char* str = nullptr;

    ScriptObjectKey key;
    if (keys_->getKey(name, key)) {            
        if (key.type == (unsigned)ScriptObjectType::String) {
            str = reinterpret_cast<const char*>(getValueStart());
            str += valueOffsets_[key.index];
        } else if (throwOnError) {
            throw TypeCastException{};
        }
    } else if (throwOnError) {
        throw UnknownScriptObjectFieldException();
    }
        
    return str;
}

bool rs::scriptobject::ScriptObject::setString(int index, const char* value) {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    return setString(key, value);
}

bool rs::scriptobject::ScriptObject::setString(const char* name, const char* value) {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    return setString(key, value);
}

bool rs::scriptobject::ScriptObject::setString(const ScriptObjectKey& key, const char* value) {
    if (key.type != (unsigned)ScriptObjectType::String) {
        throw TypeCastException();
    }
    
    auto fieldLength = getStringFieldLength(key);
    if (std::strlen(value) + 1 > fieldLength) {
        return false;
    } else {                        
        auto str = const_cast<char*>(reinterpret_cast<const char*>(getValueStart()));
        str += valueOffsets_[key.index];
        std::strcpy(str, value);
        return true;
    }
}

double rs::scriptobject::ScriptObject::getDouble(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Double) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const double*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

double rs::scriptobject::ScriptObject::getDouble(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Double) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const double*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

bool rs::scriptobject::ScriptObject::getBoolean(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Boolean) {
        throw TypeCastException();
    }
    
    return (bool)valueOffsets_[key.index];
}

bool rs::scriptobject::ScriptObject::getBoolean(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Boolean) {
        throw TypeCastException();
    }
    
    return (bool)valueOffsets_[key.index];    
}

std::int32_t rs::scriptobject::ScriptObject::getInt32(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int32_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::uint32_t rs::scriptobject::ScriptObject::getUInt32(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::UInt32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::uint32_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::int64_t rs::scriptobject::ScriptObject::getInt64(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int64) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int64_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::uint64_t rs::scriptobject::ScriptObject::getUInt64(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::UInt64) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::uint64_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::int32_t rs::scriptobject::ScriptObject::getInt32(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int32_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::uint32_t rs::scriptobject::ScriptObject::getUInt32(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::UInt32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::uint32_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::int64_t rs::scriptobject::ScriptObject::getInt64(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int64) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int64_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

std::uint64_t rs::scriptobject::ScriptObject::getUInt64(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::UInt64) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::uint64_t*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::getObject(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Object) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptObjectPtr*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::getObject(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Object) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptObjectPtr*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptObject::getArray(int index) const {
    ScriptObjectKey key;
    if (!keys_->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Array) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptArrayPtr*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptObject::getArray(const char* name) const {
    ScriptObjectKey key;
    if (!keys_->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Array) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptArrayPtr*>(getValueStart() + valueOffsets_[key.index]);
    return *ptr;
}

static void appendValue(rs::scriptobject::utils::ObjectVector& objVector, const rs::scriptobject::ScriptObjectPtr obj, const char* name, int index) {    
    auto type = obj->getType(index);
    switch (type) {
        case rs::scriptobject::ScriptObjectType::Array: {
            rs::scriptobject::utils::VectorValue v{obj->getArray(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Boolean: {
            rs::scriptobject::utils::VectorValue v{obj->getBoolean(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Double: {
            rs::scriptobject::utils::VectorValue v{obj->getDouble(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Int32: {
            rs::scriptobject::utils::VectorValue v{obj->getInt32(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::UInt32: {
            rs::scriptobject::utils::VectorValue v{obj->getUInt32(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Int64: {
            rs::scriptobject::utils::VectorValue v{obj->getInt64(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::UInt64: {
            rs::scriptobject::utils::VectorValue v{obj->getUInt64(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Null: {
            rs::scriptobject::utils::VectorValue v{rs::scriptobject::ScriptObjectType::Null};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::Object: {
            rs::scriptobject::utils::VectorValue v{obj->getObject(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
        case rs::scriptobject::ScriptObjectType::String: {
            rs::scriptobject::utils::VectorValue v{obj->getString(index)};
            objVector.push_back(std::make_pair(name, v));
            break;
        }
    }
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::DeleteField(const ScriptObjectPtr obj, const char* fieldName) {
    ScriptObjectKey fieldKey;
    if (!obj->getKeys()->getKey(fieldName, fieldKey)) {
        return obj;
    } else {
        auto fieldCount = obj->getCount();
        
        utils::ObjectVector newObject;
        newObject.reserve(fieldCount - 1);
        
        for (decltype(fieldKey.index) i = 0; i < fieldKey.index; ++i) {
            auto name = obj->getName(i);
            appendValue(newObject, obj, name, i);
        }
        
        for (decltype(fieldKey.index) i = fieldKey.index + 1; i < fieldCount; ++i) {
            auto name = obj->getName(i);
            appendValue(newObject, obj, name, i);
        }
        
        utils::ScriptObjectVectorSource newSource{newObject};
        return ScriptObjectFactory::CreateObject(newSource);
    }
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::Merge(const ScriptObjectPtr lhs, const ScriptObjectPtr rhs, MergeStrategy strategy) {
    if (lhs.get() == rhs.get()) {
        return lhs;
    } else {
        switch (strategy) {
            case MergeStrategy::Fast: return MergeFast(lhs, rhs);
            default: return MergePosition(lhs, rhs, strategy);
        }
    }
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::MergeFast(const ScriptObjectPtr lhs, const ScriptObjectPtr rhs) {
    utils::ObjectVector mergedObject;

    auto l = 0, r = 0;
    auto lMax = lhs->getCount();
    auto rMax = rhs->getCount();
    while (l < lMax && r < rMax) {
        auto leftName = lhs->getName(~l);
        auto rightName = rhs->getName(~r);
        auto diff = std::strcmp(leftName, rightName);

        if (diff < 0) {
            appendValue(mergedObject, lhs, leftName, ~l);
            ++l;
        } else if (diff > 0) {
            appendValue(mergedObject, rhs, rightName, ~r);
            ++r;
        } else {
            appendValue(mergedObject, rhs, rightName, ~r);
            ++l;
            ++r;
        }
    }

    for (; l < lMax; ++l) {
        auto name = lhs->getName(~l);
        appendValue(mergedObject, lhs, name, ~l);
    }

    for (; r < rMax; ++r) {
        auto name = rhs->getName(~r);
        appendValue(mergedObject, rhs, name, ~r);
    }

    utils::ScriptObjectVectorSource mergedSource{mergedObject};
    return ScriptObjectFactory::CreateObject(mergedSource);
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::MergePosition(const ScriptObjectPtr lhs, const ScriptObjectPtr rhs, MergeStrategy strategy) {
    utils::ObjectVector mergedObject;

    const auto leftCount = lhs->getCount();
    const auto rightCount = rhs->getCount();

    if (strategy == MergeStrategy::Front) {
        for (int i = 0; i < rightCount; ++i) {
            auto name = rhs->getName(i);
            appendValue(mergedObject, rhs, name, i);
        }
    }

    for (int i = 0; i < leftCount; ++i) {
        auto name = lhs->getName(i);

        ScriptObjectKey key;
        if (!rhs->keys_->getKey(name, key)) {
            appendValue(mergedObject, lhs, name, i);
        }
    }

    if (strategy == MergeStrategy::Back) {
        for (int i = 0; i < rightCount; ++i) {
            auto name = rhs->getName(i);
            appendValue(mergedObject, rhs, name, i);
        }        
    }

    utils::ScriptObjectVectorSource mergedSource{mergedObject};
    return ScriptObjectFactory::CreateObject(mergedSource);
}

void rs::scriptobject::ScriptObject::CalculateHash(ScriptObjectHash& digest, bool (*validateFieldFunc)(const char* name)) {    
    MD5 md5;
    const auto count = getCount();
    
    for (int i = 0; i < count; ++i) {
        const auto name = getName(i);
        
        if (validateFieldFunc == nullptr || validateFieldFunc(name)) {
            md5.update(name, std::strlen(name));
            
            const auto type = getType(i);
            
            switch (type) {
                case ScriptObjectType::Array: {
                    ScriptObjectHash childDigest;
                    auto value = getArray(i);
                    if (!!value) {
                        value->CalculateHash(childDigest, validateFieldFunc);
                        md5.update(reinterpret_cast<const unsigned char*>(&childDigest), sizeof(childDigest));
                    }
                    break;
                }
                case ScriptObjectType::Boolean: {
                    auto value = getBoolean(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::Double: {
                    auto value = getDouble(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::Int32: {
                    auto value = getInt32(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::UInt32: {
                    auto value = getUInt32(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::Int64: {
                    auto value = getInt64(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::UInt64: {
                    auto value = getUInt64(i);
                    md5.update(reinterpret_cast<const unsigned char*>(&value), sizeof(value));
                    break;
                }
                case ScriptObjectType::Null: {
                    md5.update("null", 4);
                    break;
                }
                case ScriptObjectType::String: {
                    auto value = getString(i);
                    md5.update(value, std::strlen(value));
                    break;
                }
                case ScriptObjectType::Object: {
                    ScriptObjectHash childDigest;
                    auto value = getObject(i);
                    if (!!value) {
                        value->CalculateHash(childDigest, validateFieldFunc);
                        md5.update(reinterpret_cast<const unsigned char*>(&childDigest), sizeof(childDigest));
                    }
                    break;
                }
                case ScriptObjectType::Undefined: {
                    md5.update("undefined", 9);
                    break;
                }
            }
        }
    }
    
    md5.finalize();
    md5.bindigest(digest);
}