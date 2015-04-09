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

namespace rs {
namespace scriptobject {

class ScriptArrayFactory final {
public:
    ScriptArrayFactory() = delete;
    ScriptArrayFactory(const ScriptArrayFactory& orig) = delete;
    
    static ScriptArrayPtr CreateArray(const ScriptArraySource& source);
    
private:

};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H */

