#include "script_object_keys.h"

#include <cstring>

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