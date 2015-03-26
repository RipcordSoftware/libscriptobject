#include "script_array_factory.h"

#include <algorithm>

rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptArrayFactory::CreateArray(const rs::scriptobject::ScriptArraySource& source) {
    int size = ScriptArray::CalculateSize(source);
    
    // allocate the memory we need
    auto arrayPtr = new unsigned char[size];
#ifdef DEBUG_SCRIPT_OBJECT
    // in debug mode fill the memory with ? chars
    std::fill_n(arrayPtr, size, '?');
#endif        
    
    // create the real array
    auto array = new (arrayPtr) ScriptArray(size, source.count());
    
    auto valueStart = ScriptArray::getValueStart(*array);
    auto types = ScriptArray::getTypeStart(*array);
    unsigned offset = 0, stringOffset = size - (valueStart - arrayPtr);
    for (int i = 0; i < array->count; ++i) {
        const auto type = source.type(i);
        switch (type) {
            case ScriptObjectType::Int32:
                *reinterpret_cast<std::int32_t*>(valueStart + offset) = source.getInt32(i);
                array->offsets[i] = offset;
                offset += sizeof(std::int32_t);                
                break;
            case ScriptObjectType::Double:
                *reinterpret_cast<double*>(valueStart + offset) = source.getDouble(i);
                array->offsets[i] = offset;
                offset += sizeof(double);
                break;
            case ScriptObjectType::Boolean:
                array->offsets[i] = source.getBoolean(i);
                offset += 0;
                break;
            case ScriptObjectType::Object: {
                auto child = source.getObject(i);
                new (static_cast<void*>(valueStart + offset)) ScriptObjectPtr(child);
                array->offsets[i] = offset;
                offset += sizeof(ScriptObjectPtr);
                break;
            }
            case ScriptObjectType::Array: {
                auto child = source.getArray(i);
                new (static_cast<void*>(valueStart + offset)) ScriptArrayPtr(child);
                array->offsets[i] = offset;
                offset += sizeof(ScriptArrayPtr);
                break;
            }
            case ScriptObjectType::String: {
                auto stringLength = source.getStringLength(i);
                stringOffset -= stringLength + 1;
                std::copy_n(source.getString(i), stringLength, valueStart + stringOffset);
                *(valueStart + stringOffset + stringLength) = '\0';
                array->offsets[i] = stringOffset;
                break;
            }
            case ScriptObjectType::Null:
                array->offsets[i] = 0;
                break;
        }
        
        types[i] = type;
    }
    
    return ScriptArrayPtr(array, ScriptArray::ScriptArrayDeleter);
}