#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_CACHE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_CACHE_H

#include <unordered_set>
#include <cstring>
#include <mutex>

#include "script_object_keys.h"
#include "script_object_definition.h"

namespace rs {
namespace scriptobject {

class ScriptObjectKeysCache final {
public:
    ScriptObjectKeysCache() = delete;
    ScriptObjectKeysCache(const ScriptObjectKeysCache& orig) = delete;
    
    static ScriptObjectKeysPtr AddObjectKeys(const ScriptObjectKeysPtr& keys);
    
    static ScriptObjectKeysPtr GetObjectKeys(const ScriptObjectKeysPtr& keys);
    
    static std::size_t getCount();
    
    static void Flush();
    
private:
    class KeyHash {
    public:
        std::size_t operator()(const ScriptObjectKeysPtr& key) const {
            auto hash = reinterpret_cast<std::size_t*>(key->hash);
            return *hash;
        }
    };
    
    class KeyEqual {
    public:
        bool operator()(const ScriptObjectKeysPtr& x, const ScriptObjectKeysPtr& y) const {
            return x->count == y->count && std::memcmp(x->hash, y->hash, sizeof(x->hash)) == 0;
        }
    };
    
    static unsigned getCacheIndex(const ScriptObjectKeysPtr& keys);
        
    static const unsigned NUM_CACHES = 16;
    static std::unordered_set<ScriptObjectKeysPtr, KeyHash, KeyEqual> cache_[NUM_CACHES];
    static std::recursive_mutex cacheLock_[NUM_CACHES];
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_CACHE_H */

