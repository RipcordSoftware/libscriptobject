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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_JSON_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_JSON_SOURCE_H

#include <vector>

#include "gason.h"

#include "script_object_source.h"

class ScriptObjectJsonSource : public rs::scriptobject::ScriptObjectSource {
public:
    ScriptObjectJsonSource(char* json);
    
    virtual unsigned count() const override;
    virtual rs::scriptobject::ScriptObjectType type(int index) const override;
    virtual const char* name(int index) const override;    
    virtual unsigned length(int index) const override;
    
    virtual bool getBoolean(int index) const override;
    virtual std::int32_t getInt32(int index) const override;
    virtual double getDouble(int index) const override;
    virtual const char* getString(int index) const override;
    virtual int getStringLength(int index) const override;
    virtual const rs::scriptobject::ScriptObjectPtr getObject(int index) const override;
    virtual const rs::scriptobject::ScriptArrayPtr getArray(int index) const override;
    
private:
    friend class ScriptArrayJsonSource;
    
    ScriptObjectJsonSource(JsonValue value);
    
    JsonAllocator allocator_;
    std::vector<JsonNode*> members_;
    
    static rs::scriptobject::ScriptObjectType getType(JsonTag tag);
    
    static std::vector<JsonNode*> GetMembers(JsonValue& value);
};

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_JSON_SOURCE_H */
