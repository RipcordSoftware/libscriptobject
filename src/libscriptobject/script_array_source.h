/**
 * @file
 * Declares the ScriptArraySource class
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H

#include <cstdint>

#include "script_array.h"
#include "script_object.h"

namespace rs {
namespace scriptobject {

/**
 * An abstract (pure-virtual) type which acts as the base class for scriptable array sources
 * @see ScriptArrayFactory
 * @see ScriptArray
 */
class ScriptArraySource {
public:
    /**
     * Gets the size (extent) of the source describing the array
     * @return The number of items that should be in the new array instance
     */
    virtual unsigned count() const = 0;
    
    /**
     * Gets the type of the item at the specified index in the array source
     * @param index The index to query
     * @return The type of the item at the specified index
     */
    virtual ScriptObjectType type(int index) const = 0;
    
    /**
     * Gets the value as a boolean at the specified index in the array source
     * @param index The index in the source
     * @return The value from the specified index
     */
    virtual bool getBoolean(int index) const = 0;
        
    /**
     * Gets the value as an int32_t at the specified index in the array source
     * @param index The index in the source
     * @return The value from the specified index
     */
    virtual std::int32_t getInt32(int index) const = 0;
    
    /**
     * Gets the value as a uint32_t at the specified index in the array source
     * @param index The index in the source
     * @return The value from the specified index
     */
    virtual std::uint32_t getUInt32(int index) const = 0;
    
    /**
     * Gets the value as an int64_t at the specified index in the array source
     * @param index The index in the source
     * @return The value from the specified index
     */
    virtual std::int64_t getInt64(int index) const = 0;
    
    /**
     * Gets the value as a uint64_t at the specified index in the array source
     * @param index The index in the array
     * @return The value from the specified index
     */
    virtual std::uint64_t getUInt64(int index) const = 0;
    
    /**
     * Gets the value as a double at the specified index in the array source
     * @param index The index in the source
     * @return The value from the specified index
     */
    virtual double getDouble(int index) const = 0;
    
    /**
     * Gets the string at the specified index in the array source
     * @param index The index in the source
     * @return A pointer to the string entry in the array
     */
    virtual const char* getString(int index) const = 0;
    
    /**
     * Gets the length of the string at the specified index in the array source
     * @param index The index in the source
     * @return The length of the string at the specified index
     */
    virtual int getStringLength(int index) const = 0;
    
    /**
     * Gets the object at the specified index in the array in the array source
     * @param index The index in the source
     * @return The object instance from the specified index
     */
    virtual const ScriptObjectPtr getObject(int index) const = 0;
    
    /**
     * Gets the child array at the specified index in the array in the array source
     * @param index The index in the source
     * @return The child array instance from the specified index
     */
    virtual const ScriptArrayPtr getArray(int index) const = 0;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H */
