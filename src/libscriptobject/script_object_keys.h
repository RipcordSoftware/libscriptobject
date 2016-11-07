/**
 * @file
 * Declares ScriptObjectKey and ScriptObjectKeys
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_H

#include <memory>

#include "script_object_type.h"
#include "script_object_definition.h"

namespace rs {
namespace scriptobject {

/**
 * A key which contains the field type, raw index and offset
 * @see ScriptObjectKeys
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
 * @see ScriptObjectKey
 * @see ScriptObjectKeysCache
 */
struct ScriptObjectKeys {
    using size_t = unsigned short;

    size_t size;                        ///< The size of the entire key structure
    size_t count;                       ///< The number of keys
    ScriptObjectHash hash;              ///< The MD5 hash generated from key+type
    ScriptObjectKey keys[/*count*/];    ///< The key definitions
    // Index index[count];              // a map of original index position to sorted position
    // char names[count];               // the null terminated field names
    
    /**
     * Gets the key descriptor at the specified index
     * @param index The index to get
     * @param key A key object which is populated on success
     * @return True if successful
     */
    bool getKey(int index, ScriptObjectKey& key) const;
    
    /**
     * Gets the key descriptor of the specified field name
     * @param name The name of the field
     * @param key A key object which is populated on success
     * @return True if successful
     */
    bool getKey(const char* name, ScriptObjectKey& key) const;
    
    /**
     * Gets the name of the key at the specified index
     * @param index The index to get
     * @return The key name or nullptr if the index is not known
     */
    const char* getKeyName(int index) const;
    
    /**
     * Gets the type of the key at the specified index
     * @param index The index to get
     * @return The type of the key at the given index
     */
    ScriptObjectType getKeyType(int index) const;
    
private:    
    friend class ScriptObjectKeysFactory;
    
    ScriptObjectKeys(size_t size, size_t count, const ScriptObjectHash hash);            
    
    using Index = size_t;
    
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
