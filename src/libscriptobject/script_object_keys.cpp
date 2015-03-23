#include "script_object_keys.h"

#include <algorithm>

void rs::scriptobject::ScriptObjectKeysFactory::ScriptObjectKeysDeleter(ScriptObjectKeys* ptr) { 
    delete[] reinterpret_cast<char*>(ptr); 
}

rs::scriptobject::ScriptObjectKeysFactory::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(const ScriptObjectDefinition& defn) {
    int fieldCount = defn.count();
    int size = sizeof(ScriptObjectKeys) + (fieldCount * sizeof(ScriptObjectKey));
    
    for (int i = 0; i < fieldCount; ++i) {
        size += defn.length(i) + 1;
    }
    
    auto objectKeysPtr = new char[size];
#ifdef DEBUG_SCRIPT_OBJECT_KEYS
    std::fill(objectKeysPtr, objectKeysPtr + size, '?');
#endif
    auto objectKeys = reinterpret_cast<ScriptObjectKeys*>(objectKeysPtr);
    
    objectKeys->size = size;
    objectKeys->count = fieldCount;
    
    objectKeys->keys[0].offset = 0;
    auto keyNameStart = ScriptObjectKeys::getKeyName(*objectKeys, 0);
    
    unsigned offset = 0;
    for (int i = 0; i < fieldCount; ++i) {                
        objectKeys->keys[i].index = i;
        objectKeys->keys[i].offset = offset;
        objectKeys->keys[i].type = (unsigned)defn.type(i);
        
        auto name = defn.name(i);
        auto nameLength = defn.length(i);
        
        std::copy(name, name + nameLength, keyNameStart + offset);
        *(keyNameStart + nameLength + offset) = '\0';
        
        offset += nameLength + 1;
    }
    
    return ScriptObjectKeysPtr(objectKeys, ScriptObjectKeysDeleter);
}

char* rs::scriptobject::ScriptObjectKeys::getKeyName(ScriptObjectKeys& keys, int index) {
    char* name = reinterpret_cast<char*>(&keys);
    name += sizeof(ScriptObjectKeys) + (keys.count * sizeof(ScriptObjectKey));
    name += keys.keys[index].offset;
    return name;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObjectKeys::getKeyType(ScriptObjectKeys& keys, int index) {
    return static_cast<rs::scriptobject::ScriptObjectType>(keys.keys[index].type);
}