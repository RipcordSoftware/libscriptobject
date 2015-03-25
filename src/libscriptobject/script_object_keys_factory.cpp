#include "script_object_keys_factory.h"

#include <algorithm>
#include <cstring>

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(const ScriptObjectDefinition& defn) {    
    int fieldCount = defn.count();
    
    // calculate the total size required for the header, indexes and strings
    int size = sizeof(ScriptObjectKeys) + (fieldCount * sizeof(ScriptObjectKey)) + (fieldCount * sizeof(ScriptObjectKeys::Index));    
    for (int i = 0; i < fieldCount; ++i) {
        size += defn.length(i) + 1;        
    }
    
    // allocate the memory we need
    auto objectKeysPtr = new char[size];
#ifdef DEBUG_SCRIPT_OBJECT_KEYS
    // in debug mode fill the memory with ? chars
    std::fill_n(objectKeysPtr, size, '?');
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
        std::copy_n(name, nameLength, keyNameStart + offset);
        *(keyNameStart + nameLength + offset) = '\0';
        
        // move the offset to the next key
        offset += nameLength + 1;
    }
    
    // sort the keys so we can locate them quickly
    std::sort(&objectKeys->keys[0], &objectKeys->keys[fieldCount], [&](const ScriptObjectKey& a, const ScriptObjectKey& b) {
        auto keyA = objectKeys->getKeyNameByOffset(a.offset);
        auto keyB = objectKeys->getKeyNameByOffset(b.offset);
        return ::strcmp(keyA, keyB) < 0;
    });
    
    // the keys array is now sorted, take the original index from the key and
    // store in the index lookup so we can easily recover the original key order
    for (int i = 0; i < fieldCount; ++i) {
        indexes[objectKeys->keys[i].index] = i;
    }

    // allocate the smart pointer and return it
    return ScriptObjectKeysPtr(objectKeys, ScriptObjectKeys::ScriptObjectKeysDeleter);
}