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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H

#include <cstdint>

#include "script_array.h"
#include "script_object.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource {
public:
    virtual unsigned count() const = 0;
    virtual ScriptObjectType type(int index) const = 0;
    virtual bool getBoolean(int index) const = 0;
    virtual std::int32_t getInt32(int index) const = 0;
    virtual double getDouble(int index) const = 0;
    virtual const char* getString(int index) const = 0;
    virtual int getStringLength(int index) const = 0;
    virtual const ScriptObjectPtr getObject(int index) const = 0;
    virtual const ScriptArrayPtr getArray(int index) const = 0;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H */

