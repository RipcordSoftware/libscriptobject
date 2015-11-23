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

#include "script_array_msgpack_source.h"

#include "script_object_msgpack_source.h"

#include "exceptions.h"
#include "script_object_factory.h"
#include "script_array_factory.h"

rs::scriptobject::ScriptArrayMsgpackSource::ScriptArrayMsgpackSource(const char* data, std::size_t length) : result_(msgpack::unpack(data, length)) {
    auto arr = result_.get();
    
    if (arr.type != msgpack::type::object_type::ARRAY) {
        throw ScriptObjectMsgpackSourceParseException{"Bad source object type"};
    }
    
    arr_ = arr.via.array.ptr;
    count_ = arr.via.array.size;
}

rs::scriptobject::ScriptArrayMsgpackSource::ScriptArrayMsgpackSource(msgpack::object* arr, unsigned count) : arr_(arr), count_(count) {
    
}

unsigned rs::scriptobject::ScriptArrayMsgpackSource::count() const {
    return count_;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptArrayMsgpackSource::type(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }  
 
    switch (arr_[index].type) {
        case msgpack::type::object_type::ARRAY: return ScriptObjectType::Array; break;
        case msgpack::type::object_type::BOOLEAN: return ScriptObjectType::Boolean; break;
        case msgpack::type::object_type::FLOAT: return ScriptObjectType::Double; break;
        case msgpack::type::object_type::MAP: return ScriptObjectType::Object; break;
        case msgpack::type::object_type::NEGATIVE_INTEGER: return ScriptObjectType::Double; break;        
        case msgpack::type::object_type::NIL: return ScriptObjectType::Null; break;
        case msgpack::type::object_type::POSITIVE_INTEGER: return ScriptObjectType::Double; break;
        case msgpack::type::object_type::STR: return ScriptObjectType::String; break;
        default: return ScriptObjectType::Undefined; break;
    }
}

bool rs::scriptobject::ScriptArrayMsgpackSource::getBoolean(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (arr_[index].type != msgpack::type::object_type::BOOLEAN) {
        throw TypeCastException{};
    }
    
    return arr_[index].via.boolean;
}

std::int32_t rs::scriptobject::ScriptArrayMsgpackSource::getInt32(int index) const {
    throw TypeCastException{};
}

std::uint32_t rs::scriptobject::ScriptArrayMsgpackSource::getUInt32(int index) const {
    throw TypeCastException{};
}

std::int64_t rs::scriptobject::ScriptArrayMsgpackSource::getInt64(int index) const {
    throw TypeCastException{};
}

std::uint64_t rs::scriptobject::ScriptArrayMsgpackSource::getUInt64(int index) const {
    throw TypeCastException{};
}

double rs::scriptobject::ScriptArrayMsgpackSource::getDouble(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
    
    switch (arr_[index].type) {
        case msgpack::type::object_type::FLOAT: return arr_[index].via.f64;
        case msgpack::type::object_type::NEGATIVE_INTEGER: return arr_[index].via.i64;
        case msgpack::type::object_type::POSITIVE_INTEGER: return arr_[index].via.u64;
        default: throw TypeCastException{};
    }
}

const char* rs::scriptobject::ScriptArrayMsgpackSource::getString(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (arr_[index].type != msgpack::type::object_type::STR) {
        throw TypeCastException{};
    }
    
    return arr_[index].via.str.ptr;
}

int rs::scriptobject::ScriptArrayMsgpackSource::getStringLength(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (arr_[index].type != msgpack::type::object_type::STR) {
        throw TypeCastException{};
    }
    
    return arr_[index].via.str.size;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptArrayMsgpackSource::getObject(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (arr_[index].type != msgpack::type::object_type::MAP) {
        throw TypeCastException{};
    }    
    
    ScriptObjectMsgpackSource source{arr_[index].via.map.ptr, arr_[index].via.map.size};
    return ScriptObjectFactory::CreateObject(source);
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptArrayMsgpackSource::getArray(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (arr_[index].type != msgpack::type::object_type::ARRAY) {
        throw TypeCastException{};
    }    
    
    ScriptArrayMsgpackSource source{arr_[index].via.array.ptr, arr_[index].via.array.size};
    return ScriptArrayFactory::CreateArray(source);
}