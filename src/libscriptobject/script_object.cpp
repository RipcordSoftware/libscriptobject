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

#include "exceptions.h"
#include "script_object_source.h"
#include "script_object_vector_source.h"
#include "script_object_factory.h"

#include <cstring>

void rs::scriptobject::ScriptObject::ScriptObjectDeleter(ScriptObject* ptr) {
    // destroy all child object/array references
    auto valueStart = getValueStart(*ptr);
    for (int i = 0; i < ptr->keys->count; ++i) {
        auto index = ptr->keys->keys[i].index;

        switch (static_cast<rs::scriptobject::ScriptObjectType>(ptr->keys->keys[i].type)) {
            case ScriptObjectType::Object: {
                auto child = reinterpret_cast<ScriptObjectPtr*>(valueStart + ptr->valueOffsets[index]);
                child->~ScriptObjectPtr();
                break;
            }
            case ScriptObjectType::Array: {
                auto child = reinterpret_cast<ScriptArrayPtr*>(valueStart + ptr->valueOffsets[index]);
                child->~ScriptArrayPtr();
                break;
            }
        }
    }

    // destroy the key reference
    ptr->keys.~ScriptObjectKeysPtr();

    delete[] reinterpret_cast<unsigned char*>(ptr); 
}

const unsigned char* rs::scriptobject::ScriptObject::getValueStart() const {
    auto fieldCount = keys->count;
    auto start = reinterpret_cast<const unsigned char*>(&(valueOffsets[fieldCount]));
    return start;
}

unsigned char* rs::scriptobject::ScriptObject::getValueStart(ScriptObject& object) {
    auto fieldCount = object.keys->count;
    auto start = reinterpret_cast<unsigned char*>(&(object.valueOffsets[fieldCount]));
    return start;
}

unsigned rs::scriptobject::ScriptObject::CalculateSize(const ScriptObjectSource& source) {
    unsigned fieldCount = source.count();
    unsigned size = sizeof(ScriptObject) + (fieldCount * sizeof(ScriptObject::valueOffsets[0]));
    
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
            case ScriptObjectType::Null:
                size += 0;
                break;
            case ScriptObjectType::Object:
                size += sizeof(ScriptObjectPtr);
                break;
            case ScriptObjectType::Array:
                size += sizeof(ScriptArrayPtr);
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
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    return getStringFieldLength(key);
}

unsigned rs::scriptobject::ScriptObject::getStringFieldLength(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
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
        if (keys->getKey(i, nextKey) && nextKey.type == (unsigned)ScriptObjectType::String) {
            nextIndex = nextKey.index;
            break;
        }
    }

    unsigned length = 0;
    if (nextIndex < key.index) {
        length = valueOffsets[nextIndex] - valueOffsets[key.index];
    } else {
        auto end = reinterpret_cast<const unsigned char*>(this) + size;
        
        auto start = reinterpret_cast<const unsigned char*>(getValueStart());
        start += valueOffsets[key.index];
        
        length = end - start;
    }
    
    return length;
}

unsigned rs::scriptobject::ScriptObject::getCount() const { 
    return keys->count; 
}

const char* rs::scriptobject::ScriptObject::getName(int index) const {
    return keys->getKeyName(index);
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObject::getType(int index) const {
    ScriptObjectKey key;
    if (keys->getKey(index, key)) {
        return static_cast<ScriptObjectType>(key.type);
    } else {
        return ScriptObjectType::Unknown;
    }
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObject::getType(const char* name) const {
    ScriptObjectKey key;
    if (keys->getKey(name, key)) {
        return static_cast<ScriptObjectType>(key.type);
    } else {
        return ScriptObjectType::Unknown;
    }
}

const char* rs::scriptobject::ScriptObject::getString(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::String) {
        throw TypeCastException();
    }
    
    auto str = reinterpret_cast<const char*>(getValueStart());
    str += valueOffsets[key.index];
    return str;
}

const char* rs::scriptobject::ScriptObject::getString(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::String) {
        throw TypeCastException();
    }
    
    auto str = reinterpret_cast<const char*>(getValueStart());
    str += valueOffsets[key.index];
    return str;
}

double rs::scriptobject::ScriptObject::getDouble(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Double) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const double*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

double rs::scriptobject::ScriptObject::getDouble(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Double) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const double*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

bool rs::scriptobject::ScriptObject::getBoolean(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Boolean) {
        throw TypeCastException();
    }
    
    return (bool)valueOffsets[key.index];
}

bool rs::scriptobject::ScriptObject::getBoolean(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Boolean) {
        throw TypeCastException();
    }
    
    return (bool)valueOffsets[key.index];    
}

std::int32_t rs::scriptobject::ScriptObject::getInt32(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int32_t*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

std::int32_t rs::scriptobject::ScriptObject::getInt32(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Int32) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const std::int32_t*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::getObject(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Object) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptObjectPtr*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::getObject(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Object) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptObjectPtr*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptObject::getArray(int index) const {
    ScriptObjectKey key;
    if (!keys->getKey(index, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Array) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptArrayPtr*>(getValueStart() + valueOffsets[key.index]);
    return *ptr;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptObject::getArray(const char* name) const {
    ScriptObjectKey key;
    if (!keys->getKey(name, key)) {
        throw UnknownScriptObjectFieldException();
    }
    
    if (key.type != (unsigned)ScriptObjectType::Array) {
        throw TypeCastException();
    }
    
    auto ptr = reinterpret_cast<const ScriptArrayPtr*>(getValueStart() + valueOffsets[key.index]);
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

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::merge(const ScriptObjectPtr left, const ScriptObjectPtr right, MergeStrategy strategy) {
    if (left.get() == right.get()) {
        return left;
    } else {
        switch (strategy) {
            case MergeStrategy::Fast: return mergeFast(left, right);
            default: return mergePosition(left, right, strategy);
        }
    }
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::mergeFast(const ScriptObjectPtr left, const ScriptObjectPtr right) {
    utils::ObjectVector mergedObject;

    auto l = 0, r = 0;
    auto lMax = left->getCount();
    auto rMax = right->getCount();
    while (l < lMax && r < rMax) {
        auto leftName = left->getName(~l);
        auto rightName = right->getName(~r);
        auto diff = std::strcmp(leftName, rightName);

        if (diff < 0) {
            appendValue(mergedObject, left, leftName, ~l);
            ++l;
        } else if (diff > 0) {
            appendValue(mergedObject, right, rightName, ~r);
            ++r;
        } else {
            appendValue(mergedObject, right, rightName, ~r);
            ++l;
            ++r;
        }
    }

    for (; l < lMax; ++l) {
        auto name = left->getName(~l);
        appendValue(mergedObject, left, name, ~l);
    }

    for (; r < rMax; ++r) {
        auto name = right->getName(~r);
        appendValue(mergedObject, right, name, ~r);
    }

    utils::ScriptObjectVectorSource mergedSource{mergedObject};
    return ScriptObjectFactory::CreateObject(mergedSource);
}

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObject::mergePosition(const ScriptObjectPtr left, const ScriptObjectPtr right, MergeStrategy strategy) {
    utils::ObjectVector mergedObject;

    const auto leftCount = left->getCount();
    const auto rightCount = right->getCount();

    if (strategy == MergeStrategy::Front) {
        for (int i = 0; i < rightCount; ++i) {
            auto name = right->getName(i);
            appendValue(mergedObject, right, name, i);
        }
    }

    for (int i = 0; i < leftCount; ++i) {
        auto name = left->getName(i);

        ScriptObjectKey key;
        if (!right->keys->getKey(name, key)) {
            appendValue(mergedObject, left, name, i);
        }
    }

    if (strategy == MergeStrategy::Back) {
        for (int i = 0; i < rightCount; ++i) {
            auto name = right->getName(i);
            appendValue(mergedObject, right, name, i);
        }        
    }

    utils::ScriptObjectVectorSource mergedSource{mergedObject};
    return ScriptObjectFactory::CreateObject(mergedSource);
}