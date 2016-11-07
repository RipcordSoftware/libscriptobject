/**
 * @file
 * Declares ScriptObjectKeysCache
 * 
 * @internal
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_CACHE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_CACHE_H

#include <unordered_set>
#include <cstring>
#include <mutex>

#include "script_object_keys.h"
#include "script_object_definition.h"

namespace rs {
namespace scriptobject {

/**
 * A type which caches script object keys based on their hashes
 * @see ScriptObjectKeys
 * @see ScriptObjectKey
 * @see ScriptObjectHash
 */
class ScriptObjectKeysCache final {
public:
    ScriptObjectKeysCache() = delete;
    ScriptObjectKeysCache(const ScriptObjectKeysCache& orig) = delete;
    
    /**
     * Adds an object keys instance to the cache
     * @param keys A keys instance to add
     * @return The added instance
     */
    static ScriptObjectKeysPtr AddObjectKeys(const ScriptObjectKeysPtr& keys);

    /**
     * Gets an matching keys instance if it already exists in the cache
     */
    static ScriptObjectKeysPtr GetObjectKeys(const ScriptObjectKeysPtr& keys);
    
    /**
     * Gets the number of keys in the cache
     * @return The number of keys in the cache
     */
    static std::size_t getCount();
    
    /**
     * Flushes (clears) the contents of the cache
     */
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

