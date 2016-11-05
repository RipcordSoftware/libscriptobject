/**
 * @file
 * Declares ScriptObjectDefinition the abstract class used to query object metadata
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H

#include "script_object_type.h"
#include "script_object_hash.h"

namespace rs {
namespace scriptobject {   

/**
 * An abstract type which describes the object definition (metadata) of a scriptable object.
 * The metadata includes the number of fields, their names and their types.
 */
class ScriptObjectDefinition {
public:
    /**
     * Gets a count of the number of fields in the object definition
     * @return The number of fields in the object definition
     */
    virtual unsigned count() const = 0;
    
    /**
     * Gets the type of the field at the specified index
     * @param index The index to query
     * @return The type of the field at the index
     * @see ScriptObjectType
     */
    virtual ScriptObjectType type(int index) const = 0;
    
    /**
     * Gets the name of the field at the specified index
     * @param index The index to query
     * @return The name of the field at the index
     */
    virtual const char* name(int index) const = 0;    
    
    /**
     * Gets the length of the name of the field at the specified index
     * @param index The index to query
     * @return The length of the name of the field at the index
     */
    virtual unsigned length(int index) const = 0;
    
    /**
     * Calculates a digest (hash) based on the field names and types
     * of the object definition. The hash can be compared with other
     * hashes to determine equality (i.e. the compared object instances 
     * have the same object definition).
     * @param digest On return contains the hash of the object definition
     * @see ScriptObjectHash
     */
    void CalculateHash(ScriptObjectHash digest) const;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H */