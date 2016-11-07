/**
 * @file
 * Declares ScriptArrayJsonSource
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_JSON_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_JSON_SOURCE_H

#include <vector>

#include "../../externals/gason/src/gason.h"

#include "script_array_source.h"

namespace rs {
namespace scriptobject {

/**
 * A source for a scriptable array, read from a JSON character stream
 * @see ScriptArraySource
 * @see ScriptArrayFactory
 */
class ScriptArrayJsonSource : public rs::scriptobject::ScriptArraySource {
public:
    ScriptArrayJsonSource(char* json);    
    
    virtual unsigned count() const override;
    virtual rs::scriptobject::ScriptObjectType type(int index) const override;
    virtual bool getBoolean(int index) const override;
    virtual std::int32_t getInt32(int index) const override;
    virtual std::uint32_t getUInt32(int index) const override;
    virtual std::int64_t getInt64(int index) const override;
    virtual std::uint64_t getUInt64(int index) const override;
    virtual double getDouble(int index) const override;
    virtual const char* getString(int index) const override;
    virtual int getStringLength(int index) const override;
    virtual const rs::scriptobject::ScriptObjectPtr getObject(int index) const override;
    virtual const rs::scriptobject::ScriptArrayPtr getArray(int index) const override;

private:    
    friend class ScriptObjectJsonSource;
    
    ScriptArrayJsonSource(JsonValue& value);
    
    std::vector<JsonNode*> members_;
    JsonAllocator allocator_;
    
    static rs::scriptobject::ScriptObjectType getType(JsonTag tag);
    
    static std::vector<JsonNode*> GetMembers(JsonValue& value);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_JSON_SOURCE_H */

