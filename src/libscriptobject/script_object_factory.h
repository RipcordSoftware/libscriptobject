/**
 * @file
 * Declares ScriptObjectFactory
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H

#include "script_object_source.h"
#include "script_object.h"

#include <atomic>

namespace rs {
namespace scriptobject {

/**
 * A factory for creating ScriptObjects
 * @see ScriptObject
 * @see ScriptObjectSource
 */
class ScriptObjectFactory final {
public:
    ScriptObjectFactory() = delete;
    ScriptObjectFactory(const ScriptObjectFactory& orig) = delete;
    
    /**
     * Creates a ScriptObject from a ScriptObjectSource
     * @param source The source object used to populate the new ScriptObject
     * @param useKeyCache When true libscriptobject will re-use a matching key object, otherwise a new one is created
     * @return A new ScriptObjectPtr instance
     */
    static ScriptObjectPtr CreateObject(const ScriptObjectSource& source, bool useKeyCache = true);
    
    /**
     * Gets the total number of ScriptObjects that have been created
     * @return The total number of ScriptObjects allocated
     */
    static unsigned getCount();
    
    /**
     * Gets the total number of bytes allocated by all the ScriptObjects
     * @return The total number of bytes allocated by all the ScriptObjects
     */
    static unsigned long getTotalBytesAllocated();
    
private:
    static std::atomic<unsigned> count_;
    static std::atomic<unsigned long> totalBytes_;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H */

