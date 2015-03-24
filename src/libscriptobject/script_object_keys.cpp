#include "script_object_keys.h"

#include <algorithm>
#include <cstring>

void rs::scriptobject::ScriptObjectKeysFactory::ScriptObjectKeysDeleter(ScriptObjectKeys* ptr) { 
    delete[] reinterpret_cast<char*>(ptr); 
}

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(const ScriptObjectDefinition& defn) {
    int fieldCount = defn.count();
    
    // calculate the total size required for the header, indexes and strings
    int size = sizeof(ScriptObjectKeys) + (fieldCount * sizeof(ScriptObjectKey)) + (fieldCount * sizeof(unsigned short));    
    for (int i = 0; i < fieldCount; ++i) {
        size += defn.length(i) + 1;
    }
    
    // allocate the memory we need
    auto objectKeysPtr = new char[size];
#ifdef DEBUG_SCRIPT_OBJECT_KEYS
    // in debug mode fill the memory with ? chars
    std::fill(objectKeysPtr, objectKeysPtr + size, '?');
#endif
    // cast to the real keys object
    auto objectKeys = reinterpret_cast<ScriptObjectKeys*>(objectKeysPtr);
    
    // populate the size and count fields
    objectKeys->size = size;
    objectKeys->count = fieldCount;
    
    // get the start of the indexes reqion
    auto indexes = ScriptObjectKeys::getIndexesStart(*objectKeys);
    
    // get a pointer to the first key name
    auto keyNameStart = ScriptObjectKeys::getKeyNameStart(*objectKeys);
    unsigned offset = 0;
    for (int i = 0; i < fieldCount; ++i) {
        // populate the indexes and key entry
        indexes[i] = i;
        objectKeys->keys[i].index = i;
        objectKeys->keys[i].offset = offset;
        objectKeys->keys[i].type = (unsigned)defn.type(i);
        
        auto name = defn.name(i);
        auto nameLength = defn.length(i);
        
        // copy the string and add a null
        std::copy(name, name + nameLength, keyNameStart + offset);
        *(keyNameStart + nameLength + offset) = '\0';
        
        // move the offset to the next key
        offset += nameLength + 1;
    }
    
    // sort the keys so we can locate them quickly
    std::sort(&objectKeys->keys[0], &objectKeys->keys[fieldCount], [&](const ScriptObjectKey& a, const ScriptObjectKey& b) {
        auto keyA = ScriptObjectKeys::getKeyName(*objectKeys, a.index);
        auto keyB = ScriptObjectKeys::getKeyName(*objectKeys, b.index);
        return ::strcmp(keyA, keyB) < 0;
    });
    
    // the keys array is now sorted, take the original index from the key and
    // store in the index lookup so we can easily recover the original key order
    for (int i = 0; i < fieldCount; ++i) {
        indexes[objectKeys->keys[i].index] = i;
    }

    // allocate the smart pointer and return it
    return ScriptObjectKeysPtr(objectKeys, ScriptObjectKeysDeleter);
}

char* rs::scriptobject::ScriptObjectKeys::getKeyNameStart(ScriptObjectKeys& keys) {
    char* start = reinterpret_cast<char*>(&keys);
    start += sizeof(ScriptObjectKeys) + (keys.count * sizeof(ScriptObjectKey)) + (keys.count * sizeof(unsigned short));
    return start;
}

char* rs::scriptobject::ScriptObjectKeys::getKeyName(ScriptObjectKeys& keys, int index) {
    if (index >= 0) {
        // if the index is non-negative then it needs to be mapped to the new index position
        auto indexes = ScriptObjectKeys::getIndexesStart(keys);
        index = indexes[index];
    } else {
        // a negative index denotes a raw (non-mapped) index
        index = ~index;
    }
                
    char* name = nullptr;
    if (index >= 0 && index < keys.count) {        
        name = getKeyNameStart(keys) + keys.keys[index].offset;
    }        
    
    return name;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObjectKeys::getKeyType(ScriptObjectKeys& keys, int index) {
    if (index >= 0) {
        // if the index is non-negative then it needs to be mapped to the new index position
        auto indexes = ScriptObjectKeys::getIndexesStart(keys);
        index = indexes[index];
    } else {
        // a negative index denotes a raw (non-mapped) index
        index = ~index;
    }
    
    auto type = rs::scriptobject::ScriptObjectType::Unknown;
    if (index >= 0 && index < keys.count) {
        type = static_cast<rs::scriptobject::ScriptObjectType>(keys.keys[index].type);
    }
    return type;
}

unsigned short* rs::scriptobject::ScriptObjectKeys::getIndexesStart(ScriptObjectKeys& keys) {
    return reinterpret_cast<unsigned short*>(&keys.keys[keys.count]);
}

bool rs::scriptobject::ScriptObjectKeys::getKey(ScriptObjectKeys& keys, const char* name, ScriptObjectKey& key) {
    auto index = -1;
    
    if (name != nullptr) {
        if (keys.count == 1) {
            // if there is only 1 key then just compare it here
            index = ::strcmp(name, getKeyName(keys, 0)) == 0 ? 0 : -1;
        } else if (keys.count > 1) {
            // do a binary search on the keys to find a match
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