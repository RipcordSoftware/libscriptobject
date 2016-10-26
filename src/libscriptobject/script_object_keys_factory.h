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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H

#include "script_object_keys.h"
#include "script_object_definition.h"

namespace rs {
namespace scriptobject {   

/**
 * A factory for creating ScriptObjectKeys
 */
class ScriptObjectKeysFactory final {
public:
    ScriptObjectKeysFactory() = delete;

    /**
     * Creates a ScriptObjectKeys smart pointer instance
     * @param defn The source object definition
     * @param useCache Set to true to use the object key cache
     * @return A smart pointer containing the new object
     */    
    static ScriptObjectKeysPtr CreateKeys(const ScriptObjectDefinition& defn, bool useCache = true);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H */

