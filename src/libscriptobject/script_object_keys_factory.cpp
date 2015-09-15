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

#include "script_object_keys_factory.h"

#include <algorithm>
#include <cstring>

#include "script_object_keys_cache.h"

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(const ScriptObjectDefinition& defn, bool useCache) {    
    int fieldCount = defn.count();
    
    ScriptObjectHash hash;
    defn.CalculateHash(hash);    
    
    // TODO: this lookup is horrible
    ScriptObjectKeys tempKeys(0, fieldCount, hash);
    auto newKeys = useCache ? ScriptObjectKeysCache::GetObjectKeys(ScriptObjectKeysPtr(&tempKeys, [](ScriptObjectKeys*){})) : nullptr;
    if (!newKeys) {
        // calculate the total size required for the header, indexes and strings
        int size = sizeof(ScriptObjectKeys) + (fieldCount * sizeof(ScriptObjectKey)) + (fieldCount * sizeof(ScriptObjectKeys::Index));    
        for (int i = 0; i < fieldCount; ++i) {
            size += defn.length(i) + 1;
        }

        // allocate the memory we need
        auto objectKeysPtr = new char[size];
#ifdef DEBUG_SCRIPT_OBJECT
        // in debug mode fill the memory with ? chars
        std::fill_n(objectKeysPtr, size, '?');
#endif

        auto objectKeys = new(objectKeysPtr) ScriptObjectKeys(size, fieldCount, hash);

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
            std::copy_n(name, nameLength, keyNameStart + offset);
            *(keyNameStart + nameLength + offset) = '\0';

            // move the offset to the next key
            offset += nameLength + 1;
        }

        // sort the keys so we can locate them quickly
        std::sort(&objectKeys->keys[0], &objectKeys->keys[fieldCount], [&](const ScriptObjectKey& a, const ScriptObjectKey& b) {
            auto keyA = objectKeys->getKeyNameByOffset(a.offset);
            auto keyB = objectKeys->getKeyNameByOffset(b.offset);
            return std::strcmp(keyA, keyB) < 0;
        });

        // the keys array is now sorted, take the original index from the key and
        // store in the index lookup so we can easily recover the original key order
        for (int i = 0; i < fieldCount; ++i) {
            indexes[objectKeys->keys[i].index] = i;
        }

        // allocate the smart pointer
        newKeys = ScriptObjectKeysPtr(objectKeys, ScriptObjectKeys::ScriptObjectKeysDeleter);
        
        // add the keys to the cache
        if (useCache) {
            newKeys = ScriptObjectKeysCache::AddObjectKeys(newKeys);
        }
    }
    
    return newKeys;
}