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

#include "exceptions.h"
#include "script_object_factory.h"
#include "script_array_factory.h"

#include "script_object_json_source.h"

ScriptArrayJsonSource::ScriptArrayJsonSource(char* json) {
    char* endPtr;
    JsonValue value;
    auto status = jsonParse(json, &endPtr, &value, allocator_);
    if (status != 0) {
        throw jsonStrError(status);
    }
      
    members_ = GetMembers(value);
}

ScriptArrayJsonSource::ScriptArrayJsonSource(JsonValue& value) : members_(GetMembers(value)) {    
}

unsigned ScriptArrayJsonSource::count() const {
    return members_.size();
}

rs::scriptobject::ScriptObjectType ScriptArrayJsonSource::type(int index) const {
        if (index < 0 && index >= count()) {
        throw rs::scriptobject::UnknownScriptArrayIndexException();
    }    
        
    return getType(members_[index]->value.getTag());
}

bool ScriptArrayJsonSource::getBoolean(int index) const {
    if (index < 0 && index >= count()) {
        throw rs::scriptobject::TypeCastException();
    }

    return members_[index]->key;
}

std::int32_t ScriptArrayJsonSource::getInt32(int index) const { 
    throw rs::scriptobject::UnknownScriptArrayIndexException();
}

double ScriptArrayJsonSource::getDouble(int index) const {
    if (type(index) != rs::scriptobject::ScriptObjectType::Double) {
        throw rs::scriptobject::TypeCastException();
    }
    
    return members_[index]->value.fval;
}

const char* ScriptArrayJsonSource::getString(int index) const {
    if (type(index) != rs::scriptobject::ScriptObjectType::String) {
        throw rs::scriptobject::TypeCastException();
    }
    
    return members_[index]->value.toString();
}

int ScriptArrayJsonSource::getStringLength(int index) const {
    return std::strlen(getString(index));
}

const rs::scriptobject::ScriptObjectPtr ScriptArrayJsonSource::getObject(int index) const {
    if (type(index) != rs::scriptobject::ScriptObjectType::Object) {
        throw rs::scriptobject::TypeCastException();
    }
    
    ScriptObjectJsonSource objectSource(members_[index]->value);
    return rs::scriptobject::ScriptObjectFactory::CreateObject(objectSource);
}

const rs::scriptobject::ScriptArrayPtr ScriptArrayJsonSource::getArray(int index) const {
    if (type(index) != rs::scriptobject::ScriptObjectType::Array) {
        throw rs::scriptobject::TypeCastException();
    }
    
    ScriptArrayJsonSource arraySource(members_[index]->value);
    return rs::scriptobject::ScriptArrayFactory::CreateArray(arraySource);
}

rs::scriptobject::ScriptObjectType ScriptArrayJsonSource::getType(JsonTag tag) {
    switch (tag) {
        case JSON_NULL:
            return rs::scriptobject::ScriptObjectType::Null;
        case JSON_NUMBER:
            return rs::scriptobject::ScriptObjectType::Double;
        case JSON_TRUE:
        case JSON_FALSE:
            return rs::scriptobject::ScriptObjectType::Boolean;
        case JSON_OBJECT:
            return rs::scriptobject::ScriptObjectType::Object;
        case JSON_ARRAY:
            return rs::scriptobject::ScriptObjectType::Array;
        case JSON_STRING:
            return rs::scriptobject::ScriptObjectType::String;
        default:
            return rs::scriptobject::ScriptObjectType::Unknown;
    }
}

std::vector<JsonNode*> ScriptArrayJsonSource::GetMembers(JsonValue& value) {
    std::vector<JsonNode*> members;
    for (auto i : value) {
        members.push_back(i);
    }
    return members;
}