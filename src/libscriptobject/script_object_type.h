/**
 * @file
 * Contains ScriptObjectType defining all the field types supported by libscriptobject
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H

namespace rs {
namespace scriptobject {
    
/**
 * An enumeration containing all the possible script object and array field types
 */
enum class ScriptObjectType : unsigned char {    
    Unknown = 0,
    Boolean = 1,
    UInt32 = 2,
    Int32 = 3,
    UInt64 = 4,
    Int64 = 5,
    Double = 6,
    String = 7,
    Object = 8,
    Array = 9,
    Null = 10,
    Undefined = 11,
    MAX = 16
};
    
}}

#endif /* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H */