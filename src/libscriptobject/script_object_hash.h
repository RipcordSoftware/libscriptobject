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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HASH_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HASH_H

/** 
 * @file 
 * Declares ScriptObjectHash and CompareScriptObjectHash, a simple comparison function
 */

namespace rs {
namespace scriptobject {
    
/**
 * An alias type containing a hash for a script object
 */
using ScriptObjectHash = unsigned char[16];

/**
 * Compares two script object hashes
 * @param x The first hash to compare
 * @param y The second hash to compare
 * @return 0 if equal, -1 is x is less than y and 1 if x is greater than y
 */
int CompareScriptObjectHash(const ScriptObjectHash& x, ScriptObjectHash& y);

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HASH_H */
