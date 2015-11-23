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

#include "script_object_msgpack_source.h"
#include "script_array_msgpack_source.h"

#include "exceptions.h"
#include "script_object_factory.h"
#include "script_array_factory.h"

rs::scriptobject::ScriptObjectMsgpackSource::ScriptObjectMsgpackSource(const char* data, std::size_t length) : result_(msgpack::unpack(data, length)) {
    auto obj = result_.get();
    
    if (obj.type != msgpack::type::object_type::MAP) {
        throw ScriptObjectMsgpackSourceParseException{"Bad source object type"};
    }
    
    map_ = obj.via.map.ptr;
    count_ = obj.via.map.size;
}

rs::scriptobject::ScriptObjectMsgpackSource::ScriptObjectMsgpackSource(msgpack::object_kv* obj, unsigned count) : map_(obj), count_(count) {

}

unsigned rs::scriptobject::ScriptObjectMsgpackSource::count() const {
    return count_;
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptObjectMsgpackSource::type(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }  
 
    switch (map_[index].val.type) {
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

const char* rs::scriptobject::ScriptObjectMsgpackSource::name(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].key.type != msgpack::type::object_type::STR) {
        throw ScriptObjectMsgpackSourceParseException{"Bad source field name"};
    }
    
    return map_[index].key.via.str.ptr;
}

unsigned rs::scriptobject::ScriptObjectMsgpackSource::length(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].key.type != msgpack::type::object_type::STR) {
        throw ScriptObjectMsgpackSourceParseException{"Bad source field name"};
    }
    
    return map_[index].key.via.str.size;
}

bool rs::scriptobject::ScriptObjectMsgpackSource::getBoolean(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].val.type != msgpack::type::object_type::BOOLEAN) {
        throw TypeCastException{};
    }
    
    return map_[index].val.via.boolean;
}

std::int32_t rs::scriptobject::ScriptObjectMsgpackSource::getInt32(int index) const {
    throw TypeCastException{};
}

std::uint32_t rs::scriptobject::ScriptObjectMsgpackSource::getUInt32(int index) const {
    throw TypeCastException{};
}

std::int64_t rs::scriptobject::ScriptObjectMsgpackSource::getInt64(int index) const {
    throw TypeCastException{};
}

std::uint64_t rs::scriptobject::ScriptObjectMsgpackSource::getUInt64(int index) const {
    throw TypeCastException{};
}

double rs::scriptobject::ScriptObjectMsgpackSource::getDouble(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
    
    switch (map_[index].val.type) {
        case msgpack::type::object_type::FLOAT: return map_[index].val.via.f64;
        case msgpack::type::object_type::NEGATIVE_INTEGER: return map_[index].val.via.i64;
        case msgpack::type::object_type::POSITIVE_INTEGER: return map_[index].val.via.u64;
        default: throw TypeCastException{};
    }
}

const char* rs::scriptobject::ScriptObjectMsgpackSource::getString(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].val.type != msgpack::type::object_type::STR) {
        throw TypeCastException{};
    }
    
    return map_[index].val.via.str.ptr;
}

int rs::scriptobject::ScriptObjectMsgpackSource::getStringLength(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].val.type != msgpack::type::object_type::STR) {
        throw TypeCastException{};
    }
    
    return map_[index].val.via.str.size;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptObjectMsgpackSource::getObject(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].val.type != msgpack::type::object_type::MAP) {
        throw TypeCastException{};
    }    
    
    ScriptObjectMsgpackSource source{map_[index].val.via.map.ptr, map_[index].val.via.map.size};
    return ScriptObjectFactory::CreateObject(source);
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptObjectMsgpackSource::getArray(int index) const {
    if (index >= count_) {
        throw UnknownScriptObjectFieldException{};
    }
                
    if (map_[index].val.type != msgpack::type::object_type::ARRAY) {
        throw TypeCastException{};
    }    
    
    ScriptArrayMsgpackSource source{map_[index].val.via.array.ptr, map_[index].val.via.array.size};
    return ScriptArrayFactory::CreateArray(source);
}