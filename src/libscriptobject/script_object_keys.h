#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H

#include <memory>

#include "script_object_type.h"

namespace rs {
namespace scriptobject {
    
struct ScriptObjectKey {
    unsigned type : 4;                  /// < The type of the key
    unsigned index : 12;                /// < The original key index
    unsigned offset : 16;               /// < The key string offset
};

struct ScriptObjectKeys {
    unsigned short size;                /// < The size of the entire key structure
    unsigned short count;               /// < The number of keys
    unsigned char hash[16];             /// < The MD5 hash generated from key+type
    ScriptObjectKey keys[/*count*/];    /// < The key definitions
    // unsigned short index[count];     // a map of original index position to sorted position
    // char names[count];               // the null terminated field names
    
    static bool getKey(ScriptObjectKeys& keys, const char* name, ScriptObjectKey& key);
    static char* getKeyName(ScriptObjectKeys& keys, int index);
    static ScriptObjectType getKeyType(ScriptObjectKeys& keys, int index);
    
private:    
    friend class ScriptObjectKeysFactory;
    
    static unsigned short* getIndexes(ScriptObjectKeys& keys);
    static int FindKey(ScriptObjectKeys& keys, const char* name, int min, int max);
} __attribute__ ((aligned (2)));

class ScriptObjectDefinition {
public:
    virtual unsigned count() const = 0;
    virtual ScriptObjectType type(int index) const = 0;
    virtual const char* name(int index) const = 0;    
    virtual unsigned length(int index) const = 0;
};

class ScriptObjectKeysFactory final {
public:
    ScriptObjectKeysFactory() = delete;
    
    typedef std::shared_ptr<ScriptObjectKeys> ScriptObjectKeysPtr;
    static ScriptObjectKeysPtr CreateKeys(const ScriptObjectDefinition& defn);
    
private:       
    static void ScriptObjectKeysDeleter(ScriptObjectKeys* ptr);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H */

