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

#include "script_object_keys.h"

#include <cstring>
#include <algorithm>

void rs::scriptobject::ScriptObjectKeys::ScriptObjectKeysDeleter(ScriptObjectKeys* ptr) { 
    delete[] reinterpret_cast<char*>(ptr); 
}

rs::scriptobject::ScriptObjectKeys::ScriptObjectKeys(size_t s, size_t c, const ScriptObjectHash h) : size(s), count(c) {
    std::copy_n(h, sizeof(hash), hash);
}

const char* rs::scriptobject::ScriptObjectKeys::getKeyNameStart() const {
    auto start = reinterpret_cast<const char*>(this);
    start += sizeof(ScriptObjectKeys) + (count * sizeof(ScriptObjectKey)) + (count * sizeof(Index));
    return start;
}

char* rs::scriptobject::ScriptObjectKeys::getKeyNameStart(ScriptObjectKeys& keys) {
    auto start = reinterpret_cast<char*>(&keys);
    start += sizeof(ScriptObjectKeys) + (keys.count * sizeof(ScriptObjectKey)) + (keys.count * sizeof(Index));
    return start;
}

const char* rs::scriptobject::ScriptObjectKeys::getKeyNameByOffset(unsigned offset) const {
    const char* name = getKeyNameStart() + offset;
    return name;
}

const char* rs::scriptobject::ScriptObjectKeys::getKeyName(int index) const {
    if (index >= 0) {
        // if the index is non-negative then it needs to be mapped to the new index position
        auto indexes = getIndexesStart();
        index = index >= 0 && index < count ? indexes[index] : -1;
    } else {
        // a negative index denotes a raw (non-mapped) index
        index = ~index;
    }
                
    const char* name = nullptr;
    if (index >= 0 && index < count) {        
        name = getKeyNameStart() + keys[index].offset;
    }        
    
    return name;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObjectKeys::getKeyType(int index) const {
    if (index >= 0) {
        // if the index is non-negative then it needs to be mapped to the new index position
        auto indexes = getIndexesStart();
        index = index >= 0 && index < count ? indexes[index] : -1;
    } else {
        // a negative index denotes a raw (non-mapped) index
        index = ~index;
    }
    
    auto type = rs::scriptobject::ScriptObjectType::Unknown;
    if (index >= 0 && index < count) {
        type = static_cast<rs::scriptobject::ScriptObjectType>(keys[index].type);
    }
    return type;
}

const rs::scriptobject::ScriptObjectKeys::Index* rs::scriptobject::ScriptObjectKeys::getIndexesStart() const {
    return reinterpret_cast<const ScriptObjectKeys::Index*>(&keys[count]);
}

rs::scriptobject::ScriptObjectKeys::Index* rs::scriptobject::ScriptObjectKeys::getIndexesStart(ScriptObjectKeys& keys) {
    return reinterpret_cast<ScriptObjectKeys::Index*>(&keys.keys[keys.count]);
}

bool rs::scriptobject::ScriptObjectKeys::getKey(int index, ScriptObjectKey& key) const {
    if (index >= 0) {
        // if the index is non-negative then it needs to be mapped to the new index position
        auto indexes = getIndexesStart();
        index = index >= 0 && index < count ? indexes[index] : -1;
    } else {
        // a negative index denotes a raw (non-mapped) index
        index = ~index;
    }
    
    // check the bounds
    if (index < 0 || index >= count) {
        index = -1;
    }
    
    if (index >= 0) {
        key = keys[index];
    }
    
    return index >= 0;
}

bool rs::scriptobject::ScriptObjectKeys::getKey(const char* name, ScriptObjectKey& key) const {
    auto index = -1;
    
    if (name != nullptr) {
        if (count == 1) {
            // if there is only 1 key then just compare it here
            index = ::strcmp(name, getKeyName(0)) == 0 ? 0 : -1;
        } else if (count > 1) {
            // do a binary search on the keys to find a match
            index = ScriptObjectKeys::FindKey(name);
        }
    }
    
    if (index >= 0) {
        key = keys[index];
    }
    
    return index >= 0;
}

int rs::scriptobject::ScriptObjectKeys::FindKey(const char* name) const {
    int min = 0;
    int max = count - 1;

    while (max >= min) {
        int mid = ((max - min) / 2) + min;
        
        auto keyName = ScriptObjectKeys::getKeyName(~mid);
        auto diff = ::strcmp(name, keyName);
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