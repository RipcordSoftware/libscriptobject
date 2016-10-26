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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H

#include "script_array.h"
#include "script_array_source.h"

#include <atomic>

namespace rs {
namespace scriptobject {

/**
 * A factory for creating ScriptArrays
 */
class ScriptArrayFactory final {
public:
    ScriptArrayFactory() = delete;
    ScriptArrayFactory(const ScriptArrayFactory& orig) = delete;
    
    /**
     * Creates a ScriptArray from the specified source
     * @param source The source of the new ScriptArray object
     * @return The new ScriptArrayPtr
     */
    static ScriptArrayPtr CreateArray(const ScriptArraySource& source);
    
    /**
     * Gets the total number of array objects created
     * @return The total number of array objects created
     */
    static unsigned getCount();
    
    /**
     * Gets the total number of bytes allocated by the created array objects
     * @return The total number of bytes allocated to store the created array objects
     */
    static unsigned long getTotalBytesAllocated();
    
private:
    static std::atomic<unsigned> count_;
    static std::atomic<unsigned long> totalBytes_;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H */

