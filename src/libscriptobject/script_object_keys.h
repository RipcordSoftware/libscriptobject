#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H

#include <memory>

#include "script_object_type.h"

namespace rs {
namespace scriptobject {

/**
 * A key which contains the field type, raw index and offset
 */    
struct ScriptObjectKey {
    unsigned type : 4;                  /// < The type of the key
    unsigned index : 12;                /// < The original key index
    unsigned offset : 16;               /// < The key string offset
};

/**
 * A collection of keys, allocated from a single memory block
 * @ note
 * This structure is designed to be very efficient with memory. Only a single
 * block is allocated to contain the field names, types and other associated data.
 */
struct ScriptObjectKeys {        
    unsigned short size;                /// < The size of the entire key structure
    unsigned short count;               /// < The number of keys
    unsigned char hash[16];             /// < The MD5 hash generated from key+type
    ScriptObjectKey keys[/*count*/];    /// < The key definitions
    // Index index[count];              // a map of original index position to sorted position
    // char names[count];               // the null terminated field names
    
    bool getKey(int index, ScriptObjectKey& key) const;
    bool getKey(const char* name, ScriptObjectKey& key) const;
    const char* getKeyName(int index) const;
    ScriptObjectType getKeyType(int index) const;
    
private:    
    friend class ScriptObjectKeysFactory;
    
    ScriptObjectKeys(unsigned short size, unsigned short count, const unsigned char hash[16]);            
    
    typedef unsigned short Index;
    
    static void ScriptObjectKeysDeleter(ScriptObjectKeys* ptr);
    
    const char* getKeyNameByOffset(unsigned offset) const;
    const char* getKeyNameStart() const;
    static char* getKeyNameStart(ScriptObjectKeys& keys);
    const Index* getIndexesStart() const;
    static Index* getIndexesStart(ScriptObjectKeys& keys);
    int FindKey(const char* name) const;
} __attribute__ ((aligned (2)));

typedef std::shared_ptr<ScriptObjectKeys> ScriptObjectKeysPtr;

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H */

