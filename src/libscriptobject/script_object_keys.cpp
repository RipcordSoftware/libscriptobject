#include "script_object_keys.h"

#include <algorithm>
#include <cstring>

void rs::scriptobject::ScriptObjectKeysFactory::ScriptObjectKeysDeleter(ScriptObjectKeys* ptr) { 
    delete[] reinterpret_cast<char*>(ptr); 
}

rs::scriptobject::ScriptObjectKeysFactory::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(const ScriptObjectDefinition& defn) {
    int fieldCount = defn.count();
    int size = sizeof(ScriptObjectKeys) + (fieldCount * sizeof(ScriptObjectKey)) + (fieldCount * sizeof(unsigned short));
    
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
    
    auto indexes = ScriptObjectKeys::getIndexes(*objectKeys);
    indexes[0] = 0;    
    objectKeys->keys[0].offset = 0;
    
    auto keyNameStart = ScriptObjectKeys::getKeyName(*objectKeys, 0);        
    unsigned offset = 0;
    for (int i = 0; i < fieldCount; ++i) {
        indexes[i] = i;
        objectKeys->keys[i].index = i;
        objectKeys->keys[i].offset = offset;
        objectKeys->keys[i].type = (unsigned)defn.type(i);
        
        auto name = defn.name(i);
        auto nameLength = defn.length(i);
        
        std::copy(name, name + nameLength, keyNameStart + offset);
        *(keyNameStart + nameLength + offset) = '\0';
        
        offset += nameLength + 1;
    }
    
    std::sort(&objectKeys->keys[0], &objectKeys->keys[0] + fieldCount, [&](const ScriptObjectKey& a, const ScriptObjectKey& b) {
        auto keyA = ScriptObjectKeys::getKeyName(*objectKeys, a.index);
        auto keyB = ScriptObjectKeys::getKeyName(*objectKeys, b.index);
        return ::strcmp(keyA, keyB) < 0;
    });
    
    // reorder the original position lookup
    for (int i = 0; i < fieldCount; ++i) {
        indexes[objectKeys->keys[i].index] = i;
    }
            
    return ScriptObjectKeysPtr(objectKeys, ScriptObjectKeysDeleter);
}

char* rs::scriptobject::ScriptObjectKeys::getKeyName(ScriptObjectKeys& keys, int index) {
    if (index >= 0) {
        auto indexes = ScriptObjectKeys::getIndexes(keys);
        index = indexes[index];
    } else {
        index = ~index;
    }
    
    if (index < 0 || index >= keys.count) {
        return nullptr;
    }
    
    char* name = reinterpret_cast<char*>(&keys);
    name += sizeof(ScriptObjectKeys) + (keys.count * sizeof(ScriptObjectKey)) + (keys.count * sizeof(unsigned short));

    name += keys.keys[index].offset;
    return name;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObjectKeys::getKeyType(ScriptObjectKeys& keys, int index) {
    if (index >= 0) {
        auto indexes = ScriptObjectKeys::getIndexes(keys);
        index = indexes[index];
    } else {
        index = ~index;
    }
    
    if (index < 0 || index >= keys.count) {
        return rs::scriptobject::ScriptObjectType::Unknown;
    } else {
        return static_cast<rs::scriptobject::ScriptObjectType>(keys.keys[index].type);
    }
}

unsigned short* rs::scriptobject::ScriptObjectKeys::getIndexes(ScriptObjectKeys& keys) {
    return reinterpret_cast<unsigned short*>(&keys.keys[keys.count]);
}

bool rs::scriptobject::ScriptObjectKeys::getKey(ScriptObjectKeys& keys, const char* name, ScriptObjectKey& key) {
    auto index = -1;
    
    if (name != nullptr) {
        if (keys.count == 1) {
            index = ::strcmp(name, getKeyName(keys, 0)) == 0 ? 0 : -1;
        } else if (keys.count > 1) {
            index = FindKey(keys, name, 0, keys.count - 1);
        }
    }
    
    if (index >= 0) {
        key = keys.keys[index];
    }
    
    return index >= 0;
}

int rs::scriptobject::ScriptObjectKeys::FindKey(ScriptObjectKeys& keys, const char* name, int min, int max) {
    while (max >= min) {
        int mid = ((max - min) / 2) + min;
        
        auto diff = ::strcmp(name, ScriptObjectKeys::getKeyName(keys, ~mid));
        if (diff == 0) {
            return mid;
        } else if (diff < 0) {
            max = mid - 1;
        } else {
            min = mid + 1;
        }
    }
    
    return -1;
}