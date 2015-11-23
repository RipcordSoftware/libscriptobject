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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H

#include <memory>

#include "script_object_keys.h"
#include "script_object_hash.h"
#include "script_item_ptr.h"

namespace rs {
namespace scriptobject {
    
class ScriptObjectSource;

class ScriptObject;
using ScriptObjectPtr = ScriptItemPtr<ScriptObject>;

class ScriptArray;
using ScriptArrayPtr = ScriptItemPtr<ScriptArray>;

class ScriptObject final : public ScriptItemPtrBase<ScriptObject> {    

private:    
    const unsigned size_;
    ScriptItemPtrBase<ScriptObject>::atomic_count_type refCount_{0};
    ScriptObjectKeysPtr keys_;
    unsigned valueOffsets_[];

public:
    /**
     * Gets the size of the object with an option to include child objects or arrays
     * @param includeChildren when true will include the size of child objects and arrays
     * @return the size of the object
     */
    std::uint64_t getSize(bool includeChildren = false) const;
    
    /**
     * Gets the keys object associated with the object
     * @return the keys object
     */
    ScriptObjectKeysPtr getKeys() const;
    
    /**
     * Gets the number of fields in the object
     * @return the number of fields in the object
     */
    ScriptObjectKeys::size_t getCount() const;
    
    /**
     * Gets the type of the field at the specified index
     * @param index the field index to query for its type
     * @return the field type or ScriptObjectType::Unknown if the field was not found
     */
    ScriptObjectType getType(int index) const;
    
    /**
     * Gets the type of the field with the specified name
     * @param name the name of the field to query
     * @return the field type or ScriptObjectType::Unknown if the field was not found
     */
    ScriptObjectType getType(const char* name) const;
    
    /**
     * Gets the type and index of the field with the specified name
     * @param name the name of the field to query
     * @param index returns the index of the field in the object
     * @return the field type or ScriptObjectType::Unknown if the field was not found
     */
    ScriptObjectType getType(const char* name, int& index) const;
    
    /**
     * Gets the name of the field at the specified index
     * @param index the index to query
     * @return the name of the field or nullptr if the field does not exist
     */
    const char* getName(int index) const;
    
    /**
     * Gets the string value from the specified index
     * @param index the index to query
     * @return the string value
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not a string
     */
    const char* getString(int index) const;
    
    /**
     * Gets the string value from the specified field name
     * @param name the name of the field to query
     * @param throwOnError when false the method will suppress lookup/type errors
     * @return the string value
     * @throws UnknownScriptObjectFieldException if the name was not known (when throwOnError is true)
     * @throws TypeCastException if the field was not a string (when throwOnError is true)
     */
    const char* getString(const char* name, bool throwOnError = true) const;
    
    /**
     * Sets the value of a string field in the object.
     * The string will only be updated if the new length <= old length. 
     * The script object will not be resized.
     * The length of the string report by ScriptObject is always the original allocated length.
     * @param index the index to update
     * @param value the new string value
     * @return true if the value was updated
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not a string type
     */
    bool setString(int index, const char* value);
    
    /**
     * Sets the value of a string field in the object
     * The string will only be updated if the new length <= old length.
     * The script object will not be resized.
     * The length of the string report by ScriptObject is always the original allocated length.
     * @param name the name of the field to update
     * @param value the new string value
     * @return true if the value was updated
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not a string type
     */
    bool setString(const char* name, const char* value);
    
    /**
     * Gets the integer value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an integer type
     */
    std::int32_t getInt32(int index) const;
    
    /**
     * Gets the unsigned integer value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an integer type
     */
    std::uint32_t getUInt32(int index) const;
    
    /**
     * Gets the integer value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an integer type
     */
    std::int64_t getInt64(int index) const;
    
    /**
     * Gets the unsigned integer value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an integer type
     */
    std::uint64_t getUInt64(int index) const;
    
    /**
     * Gets the integer value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an integer type
     */
    std::int32_t getInt32(const char* name) const;
    
    /**
     * Gets the unsigned integer value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an integer type
     */
    std::uint32_t getUInt32(const char* name) const;
    
    /**
     * Gets the integer value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an integer type
     */
    std::int64_t getInt64(const char* name) const;
    
    /**
     * Gets the unsigned integer value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an integer type
     */
    std::uint64_t getUInt64(const char* name) const;
    
    /**
     * Gets the double value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not a double type
     */
    double getDouble(int index) const;
    
    /**
     * Gets the double value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not a double type
     */
    double getDouble(const char* name) const;
    
    /**
     * Gets the boolean value of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not a boolean type
     */    
    bool getBoolean(int index) const;
    
    /**
     * Gets the boolean value of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not a boolean type
     */
    bool getBoolean(const char* name) const;
    
    /**
     * Gets the child object of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an object type
     */ 
    const ScriptObjectPtr getObject(int index) const;
    
    /**
     * Gets the child object of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an object type
     */
    const ScriptObjectPtr getObject(const char* name) const;
    
    /**
     * Gets the child array of the field with the specified index
     * @param index the index to query
     * @return the value of the field
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not an array type
     */ 
    const ScriptArrayPtr getArray(int index) const;
    
    /**
     * Gets the child array of the field with the specified name
     * @param name the name of the field to query
     * @return the field value
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not an array type
     */
    const ScriptArrayPtr getArray(const char* name) const;
    
    /**
     * Gets the allocated length of the string field at the specified index.
     * If the string was modified by a call to setString then the string data will not match the allocated size.
     * @param index the index to query
     * @return the length of the string in characters
     * @throws UnknownScriptObjectFieldException if the index is not in bounds
     * @throws TypeCastException if the field was not a string type
     */
    unsigned getStringFieldLength(int index) const;

    /**
     * Gets the allocated length of the string field with the specified name.
     * If the string was modified by a call to setString then the string data will not match the allocated size.
     * @param name the field to query
     * @return the length of the string in characters
     * @throws UnknownScriptObjectFieldException if the name was not known
     * @throws TypeCastException if the field was not a string type
     */
    unsigned getStringFieldLength(const char* name) const;
    
    /**
     * Calculates the hash of the current object
     * @param on return contains the hash of the object
     * @param a function predicate which should return true if the field is to be included in the hash calculation, can be nullptr to include all fields
     */
    void CalculateHash(ScriptObjectHash&, bool (*)(const char*) = nullptr);
    
    /**
     * A enumeration which controls the behaviour of the Merge method
     */
    enum class MergeStrategy : unsigned {
        Fast = 0,   /// the default strategy, compares each field in turn in the source objects
        Front = 1,  /// the rhs object fields are placed at the front of the new object after merge
        Back = 2    /// the rhs object fields are placed at the end of the new object after merge
    };

    /**
     * Merges two objects into a new object
     * @param lhs an object to merge
     * @param rhs and object to merge, if the field names match the lhs object then this object wins
     * @param strategy the strategy to apply when merging
     * @return the new object
     */
    static ScriptObjectPtr Merge(const ScriptObjectPtr lhs, const ScriptObjectPtr rhs, MergeStrategy strategy = MergeStrategy::Fast);
    
    /**
     * Deletes a field by name from an object.
     * Does not modify the source object and preserves the original field order.
     * @param obj the source object
     * @param fieldName the name of the field to remove
     * @return the new object without the deleted field
     */
    static ScriptObjectPtr DeleteField(const ScriptObjectPtr obj, const char* fieldName);
    
    /**
     * Calculates the size overhead of the 'management' data of the script object.
     * The overhead is the data portion of the script object which is not the actual field data itself. For example field offsets, indexes and key references.
     * @param fieldCount the number of fields to use in the calculation
     * @return The overhead size in bytes
     */
    static unsigned CalculateSizeOverhead(unsigned fieldCount);
    
private:
    friend class ScriptItemPtrBase<ScriptObject>;
    friend ScriptObjectPtr make_sized_script_item_ptr<ScriptObjectPtr::element_type>(size_t, unsigned&);
    friend class ScriptObjectFactory;
    
    ScriptObject(unsigned size);
    ~ScriptObject();
    
    static unsigned CalculateSize(const ScriptObjectSource& source);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptObject&);
    
    static ScriptObjectPtr MergeFast(const ScriptObjectPtr, const ScriptObjectPtr);
    static ScriptObjectPtr MergePosition(const ScriptObjectPtr, const ScriptObjectPtr, MergeStrategy);
    
    unsigned getStringFieldLength(const ScriptObjectKey&) const;
    
    bool setString(const ScriptObjectKey&, const char*);    
    
} __attribute__ ((aligned (4)));

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H */

