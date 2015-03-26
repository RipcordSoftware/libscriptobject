#include "script_object.h"

#include "exceptions.h"
#include "script_object_source.h"

void rs::scriptobject::ScriptObject::ScriptObjectDeleter(ScriptObject* ptr) {
    // destroy all child object references
    auto valueStart = getValueStart(*ptr);
    for (int i = 0; i < ptr->keys->count; ++i) {
        if (ptr->keys->keys[i].type == (unsigned)ScriptObjectType::Object) {
            auto index = ptr->keys->keys[i].index;
            auto child = reinterpret_cast<ScriptObjectPtr*>(valueStart + ptr->valueOffsets[index]);
            child->~ScriptObjectPtr();
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
                // TODO: implement
                break;
            default:
                throw UnknownSourceFieldTypeException();
                break;
        }
    }
    
    return size;
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