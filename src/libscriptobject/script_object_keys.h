#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H

#include <memory>

#include "script_object_type.h"

namespace rs {
namespace scriptobject {
    
struct ScriptObjectKey {
    unsigned type : 4;              /// < The type of the key
    unsigned index : 12;            /// < The original key index
    unsigned offset : 16;           /// < The key string offset
} __attribute__ ((aligned (1)));

struct ScriptObjectKeys {
    unsigned short size;            /// < The size of the entire key structure
    unsigned short count;           /// < The number of keys
    unsigned char hash[16];         /// < The MD5 hash generated from key+type
    ScriptObjectKey keys[];         /// < The key definitions
    
    static char* getKeyName(ScriptObjectKeys& keys, int index);
    static ScriptObjectType getKeyType(ScriptObjectKeys& keys, int index);
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
    ScriptObjectKeysFactory(const ScriptObjectKeysFactory&) = delete;                
    
    typedef std::shared_ptr<ScriptObjectKeys> ScriptObjectKeysPtr;
    static ScriptObjectKeysPtr CreateKeys(const ScriptObjectDefinition& defn);
    
private:   
    
    static void ScriptObjectKeysDeleter(ScriptObjectKeys* ptr);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H */

