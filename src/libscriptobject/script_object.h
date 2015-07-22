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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H

#include <memory>

#include "script_object_keys.h"

namespace rs {
namespace scriptobject {
    
class ScriptObjectSource;

struct ScriptObject;
typedef std::shared_ptr<ScriptObject> ScriptObjectPtr;

struct ScriptArray;
typedef std::shared_ptr<ScriptArray> ScriptArrayPtr;

struct ScriptObject {
    ScriptObject() = delete;
    
    unsigned size;
    ScriptObjectKeysPtr keys;
    unsigned valueOffsets[];

    unsigned getCount() const;
    
    ScriptObjectType getType(int index) const;
    ScriptObjectType getType(const char* name) const;
    
    const char* getName(int index) const;
    
    const char* getString(int index) const;
    const char* getString(const char* name) const;
    bool setString(int index, const char* value);
    bool setString(const char* name, const char* value);
    
    std::int32_t getInt32(int index) const;
    std::int32_t getInt32(const char* name) const;
    
    double getDouble(int index) const;
    double getDouble(const char* name) const;
    
    bool getBoolean(int index) const;
    bool getBoolean(const char* name) const;
    
    const ScriptObjectPtr getObject(int index) const;
    const ScriptObjectPtr getObject(const char* name) const;
    
    const ScriptArrayPtr getArray(int index) const;
    const ScriptArrayPtr getArray(const char* name) const;
    
    unsigned getStringFieldLength(int index) const;
    unsigned getStringFieldLength(const char* name) const;
    
    enum class MergeStrategy : unsigned {
        Fast = 0,
        Front = 1,
        Back = 2
    };

    static ScriptObjectPtr merge(const ScriptObjectPtr, const ScriptObjectPtr, MergeStrategy = MergeStrategy::Fast);
    
private:
    static unsigned CalculateSize(const ScriptObjectSource& source);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptObject&);
    
    static ScriptObjectPtr mergeFast(const ScriptObjectPtr, const ScriptObjectPtr);
    static ScriptObjectPtr mergePosition(const ScriptObjectPtr, const ScriptObjectPtr, MergeStrategy);
    
    unsigned getStringFieldLength(const ScriptObjectKey&) const;
    
    bool setString(const ScriptObjectKey&, const char*);
    
    static void ScriptObjectDeleter(ScriptObject* ptr);
    
    friend class ScriptObjectFactory;
} __attribute__ ((aligned (4)));

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H */

