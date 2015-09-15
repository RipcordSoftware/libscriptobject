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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H

#include "script_object_source.h"
#include "script_object.h"

#include <atomic>

namespace rs {
namespace scriptobject {

class ScriptObjectFactory final {
public:
    ScriptObjectFactory() = delete;
    ScriptObjectFactory(const ScriptObjectFactory& orig) = delete;
    
    static ScriptObjectPtr CreateObject(const ScriptObjectSource& source, bool useKeyCache = true);
    
    static unsigned getCount();
    static unsigned long getTotalBytesAllocated();
    
private:
    static std::atomic<unsigned> count_;
    static std::atomic<unsigned long> totalBytes_;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H */

