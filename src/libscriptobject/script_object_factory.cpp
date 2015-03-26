#include "script_object_factory.h"
#include "script_object_keys_factory.h"

#include <algorithm>

rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObjectFactory::CreateObject(const ScriptObjectSource& source) {
    int size = ScriptObject::CalculateSize(source);
    
    // allocate the memory we need
    auto objectPtr = new unsigned char[size];
#ifdef DEBUG_SCRIPT_OBJECT_KEYS
    // in debug mode fill the memory with ? chars
    std::fill_n(objectPtr, size, '?');
#endif        
    
    // cast to the real object
    auto object = reinterpret_cast<ScriptObject*>(objectPtr);
    
    // construct the keys pointer
    // TODO: use a cached keys object
    new (&object->keys) ScriptObjectKeysPtr(ScriptObjectKeysFactory::CreateKeys(source));
    
    auto valueStart = ScriptObject::getValueStart(*object);
    int fieldCount = source.count();
    unsigned offset = 0, stringOffset = size - (valueStart - objectPtr);
    for (int i = 0; i < fieldCount; ++i) {
        switch (source.type(i)) {
            case ScriptObjectType::Int32:
                *reinterpret_cast<std::int32_t*>(valueStart + offset) = source.getInt32(i);
                object->valueOffsets[i] = offset;
                offset += sizeof(std::int32_t);
                break;
            case ScriptObjectType::Double:
                *reinterpret_cast<double*>(valueStart + offset) = source.getDouble(i);
                object->valueOffsets[i] = offset;
                offset += sizeof(double);
                break;
            case ScriptObjectType::Boolean:
                object->valueOffsets[i] = source.getBoolean(i);
                offset += 0;
                break;
            case ScriptObjectType::Object: {
                auto child = source.getObject(i);
                new (static_cast<void*>(valueStart + offset)) ScriptObjectPtr(child);
                object->valueOffsets[i] = offset;
                offset += sizeof(ScriptObjectPtr);
                break;
            }
            case ScriptObjectType::Array: {
                auto child = source.getArray(i);
                new (static_cast<void*>(valueStart + offset)) ScriptArrayPtr(child);
                object->valueOffsets[i] = offset;
                offset += sizeof(ScriptArrayPtr);
                break;
            }
            case ScriptObjectType::String: {
                auto stringLength = source.getStringLength(i);
                stringOffset -= stringLength + 1;
                std::copy_n(source.getString(i), stringLength, valueStart + stringOffset);
                *(valueStart + stringOffset + stringLength) = '\0';
                object->valueOffsets[i] = stringOffset;
                break;
            }
        }
    }
    
    return ScriptObjectPtr(object, ScriptObject::ScriptObjectDeleter);
}