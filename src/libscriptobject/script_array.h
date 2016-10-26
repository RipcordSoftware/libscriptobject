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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H

#include <memory>

#include "script_object_type.h"
#include "script_object_hash.h"
#include "script_item_ptr.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource;

class ScriptArray;
using ScriptArrayPtr = ScriptItemPtr<ScriptArray>;

class ScriptObject;
using ScriptObjectPtr = ScriptItemPtr<ScriptObject>;

/**
 * A type which describes a scriptable array
 */
class ScriptArray final : public ScriptItemPtrBase<ScriptArray> {
private:
    const unsigned size_;
    ScriptItemPtrBase<ScriptArray>::atomic_count_type refCount_{0};
    struct {
        unsigned singleTypeFlag_ : 1;
        unsigned spareFlag1_ : 1;
        unsigned spareFlag2_ : 1;
        unsigned spareFlag3_ : 1;
        unsigned count_ : 28;
    };
    unsigned offsets_[/*count*/];
    //unsigned char values[];
    //ScriptObjectType types[count];

public:
    /**
     * Gets the size of the array instance and optionally all its children
     * @param includeChildren When true the size will include all the children of the array (i.e. child arrays, child objects)
     * @return 
     */
    std::uint64_t getSize(bool includeChildren = false) const;
    
    /**
     * Gets the size of the array
     * @return The number of items in the array
     */
    unsigned getCount() const;
    
    /**
     * Gets the type of the item at the specified index
     * @param index The index to query
     * @return The type of the item at the specified index
     */
    ScriptObjectType getType(int index) const;
    
    /**
     * Gets the string at the specified index
     * @param index The index in the array
     * @return A pointer to the string entry in the array
     */
    const char* getString(int index) const;
    
    /**
     * Gets the value as an int32_t at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    std::int32_t getInt32(int index) const;
    
    /**
     * Gets the value as a uint32_t at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    std::uint32_t getUInt32(int index) const;
    
    /**
     * Gets the value as an int64_t at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    std::int64_t getInt64(int index) const;
    
    /**
     * Gets the value as a uint64_t at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    std::uint64_t getUInt64(int index) const;
    
    /**
     * Gets the value as a double at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    double getDouble(int index) const;
    
    /**
     * Gets the value as a boolean at the specified index
     * @param index The index in the array
     * @return The value from the specified index
     */
    bool getBoolean(int index) const;
    
    /**
     * Gets the object at the specified index in the array
     * @param index The index in the array
     * @return The object instance from the specified index
     */
    const ScriptObjectPtr getObject(int index) const;
    
    /**
     * Gets the child array at the specified index in the array
     * @param index The index in the array
     * @return The child array instance from the specified index
     */
    const ScriptArrayPtr getArray(int index) const;
    
    /**
     * Calculates the hash of the current array
     * @param digest on return contains the hash of the array
     * @param validateFieldFunc a function predicate which should return true if the child object field is to be included in the hash calculation, can be nullptr to include all fields
     */
    void CalculateHash(ScriptObjectHash& digest, bool (*validateFieldFunc)(const char* name) = nullptr);
    
    /**
     * Calculates the size overhead of the 'management' data of the array object.
     * The overhead is the data portion of the script array which is not the actual field data itself. For example field offsets and indexes.
     * @param fieldCount the number of fields to use in the calculation
     * @return The overhead size in bytes
     */
    static unsigned CalculateSizeOverhead(unsigned fieldCount);
    
private:
    friend class ScriptItemPtrBase<ScriptArray>;
    friend ScriptArrayPtr make_sized_script_item_ptr<ScriptArrayPtr::element_type>(size_t, unsigned&, unsigned&);
    friend class ScriptArrayFactory;
    
    ScriptArray(unsigned size, unsigned count);
    ~ScriptArray();
    
    static unsigned CalculateSize(const ScriptArraySource& source);
    static unsigned CalculateTypesSize(unsigned fieldCount);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptArray& array);
    const ScriptObjectType* getTypeStart() const;
    static ScriptObjectType* getTypeStart(ScriptArray& array);    

} __attribute__ ((aligned (4)));;

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H */
