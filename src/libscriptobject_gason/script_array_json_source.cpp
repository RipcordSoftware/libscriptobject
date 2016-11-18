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

#include "script_array_json_source.h"

#include <cstring>

#include "script_object_factory.h"
#include "script_array_factory.h"

#include "script_object_json_source.h"

rs::scriptobject::ScriptArrayJsonSource::ScriptArrayJsonSource(char* json) {
    char* endPtr;
    JsonValue value;
    auto status = jsonParse(json, &endPtr, &value, allocator_);
    if (status != 0) {
        throw jsonStrError(status);
    }
      
    members_ = GetMembers(value);
}

rs::scriptobject::ScriptArrayJsonSource::ScriptArrayJsonSource(const char* json) : 
    ScriptArrayJsonSource(json != nullptr ? std::vector<char>{&json[0], &json[strlen(json)]}.data() : nullptr) {
}

rs::scriptobject::ScriptArrayJsonSource::ScriptArrayJsonSource(JsonValue& value) : members_(GetMembers(value)) {    
}

unsigned rs::scriptobject::ScriptArrayJsonSource::count() const {
    return members_.size();
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptArrayJsonSource::type(int index) const {
        if (index < 0 && index >= count()) {
        throw UnknownScriptArrayIndexException();
    }    
        
    return getType(members_[index]->value.getTag());
}

bool rs::scriptobject::ScriptArrayJsonSource::getBoolean(int index) const {
    if (index < 0 && index >= count()) {
        throw TypeCastException();
    }

    return members_[index]->value.getTag() == JSON_TRUE;
}

std::int32_t rs::scriptobject::ScriptArrayJsonSource::getInt32(int index) const { 
    throw UnknownScriptArrayIndexException();
}

std::uint32_t rs::scriptobject::ScriptArrayJsonSource::getUInt32(int index) const { 
    throw UnknownScriptArrayIndexException();
}

std::int64_t rs::scriptobject::ScriptArrayJsonSource::getInt64(int index) const { 
    throw UnknownScriptArrayIndexException();
}

std::uint64_t rs::scriptobject::ScriptArrayJsonSource::getUInt64(int index) const { 
    throw UnknownScriptArrayIndexException();
}

double rs::scriptobject::ScriptArrayJsonSource::getDouble(int index) const {
    if (type(index) != ScriptObjectType::Double) {
        throw TypeCastException();
    }
    
    return members_[index]->value.fval;
}

const char* rs::scriptobject::ScriptArrayJsonSource::getString(int index) const {
    if (type(index) != ScriptObjectType::String) {
        throw TypeCastException();
    }
    
    return members_[index]->value.toString();
}

int rs::scriptobject::ScriptArrayJsonSource::getStringLength(int index) const {
    return std::strlen(getString(index));
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::ScriptArrayJsonSource::getObject(int index) const {
    if (type(index) != ScriptObjectType::Object) {
        throw TypeCastException();
    }
    
    ScriptObjectJsonSource objectSource(members_[index]->value);
    return ScriptObjectFactory::CreateObject(objectSource);
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptArrayJsonSource::getArray(int index) const {
    if (type(index) != ScriptObjectType::Array) {
        throw TypeCastException();
    }
    
    ScriptArrayJsonSource arraySource(members_[index]->value);
    return ScriptArrayFactory::CreateArray(arraySource);
}

rs::scriptobject::ScriptObjectType rs::scriptobject::ScriptArrayJsonSource::getType(JsonTag tag) {
    switch (tag) {
        case JSON_NULL:
            return ScriptObjectType::Null;
        case JSON_NUMBER:
            return ScriptObjectType::Double;
        case JSON_TRUE:
        case JSON_FALSE:
            return ScriptObjectType::Boolean;
        case JSON_OBJECT:
            return ScriptObjectType::Object;
        case JSON_ARRAY:
            return ScriptObjectType::Array;
        case JSON_STRING:
            return ScriptObjectType::String;
        default:
            return ScriptObjectType::Unknown;
    }
}

std::vector<JsonNode*> rs::scriptobject::ScriptArrayJsonSource::GetMembers(JsonValue& value) {
    std::vector<JsonNode*> members;
    for (auto i : value) {
        members.push_back(i);
    }
    return members;
}