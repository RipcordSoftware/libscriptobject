/**
 * @file
 * Declares ScriptArrayMsgpackSource
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_MSGPACK_SOURCE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_MSGPACK_SOURCE_H

#include "script_array_source.h"

#include "msgpack.hpp"

namespace rs {
namespace scriptobject {

/**
 * A source for a scriptable array, read from a msgpack character stream
 * @see ScriptArraySource
 * @see ScriptArrayFactory
 */
class ScriptArrayMsgpackSource final : public rs::scriptobject::ScriptArraySource {
public:
    
    ScriptArrayMsgpackSource(const char* data, std::size_t length);
    ScriptArrayMsgpackSource(msgpack::object* arr, unsigned count);
    
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

    msgpack::unpacked result_;
    msgpack::object* arr_;
    unsigned count_;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_MSGPACK_SOURCE_H */

