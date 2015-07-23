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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H

#include <memory>

#include "script_object_type.h"
#include "script_object_hash.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource;

struct ScriptArray;
typedef std::shared_ptr<ScriptArray> ScriptArrayPtr;

struct ScriptObject;
typedef std::shared_ptr<ScriptObject> ScriptObjectPtr;

struct ScriptArray {        
    const unsigned size;    
    struct {
        unsigned singleTypeFlag : 1;
        unsigned spareFlag1 : 1;
        unsigned spareFlag2 : 1;
        unsigned spareFlag3 : 1;
        unsigned count : 28;
    };
    unsigned offsets[/*count*/];
    //unsigned char values[];
    //ScriptObjectType types[count];
    
    unsigned getCount() const;
    ScriptObjectType getType(int index) const;
    const char* getString(int index) const;
    std::int32_t getInt32(int index) const;
    double getDouble(int index) const;
    bool getBoolean(int index) const;
    const ScriptObjectPtr getObject(int index) const;
    const ScriptArrayPtr getArray(int index) const;
    
    void CalculateHash(ScriptObjectHash&, bool (*)(const char*) = nullptr);
    
private:    
    friend class ScriptArrayFactory;
    
    ScriptArray(unsigned size, unsigned count);
    
    static unsigned CalculateSize(const ScriptArraySource& source);
    static unsigned CalculateTypesSize(unsigned fieldCount);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptArray& array);
    const ScriptObjectType* getTypeStart() const;
    static ScriptObjectType* getTypeStart(ScriptArray& array);
    
    static void ScriptArrayDeleter(ScriptArray* ptr);

} __attribute__ ((aligned (4)));;

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H */

