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

#include "script_object_vector_source.h"

#include <cstring>
#include <algorithm>

rs::scriptobject::utils::VectorValue::VectorValue(const VectorValue& other) : type_(other.type_) {
    switch (type_) {
        case rs::scriptobject::ScriptObjectType::String:
            value_.s_ = CopyString(other.value_.s_);
            break;
        case rs::scriptobject::ScriptObjectType::Object:
            value_.obj_ = new ScriptObjectPtr(*other.value_.obj_);
            break;
        case rs::scriptobject::ScriptObjectType::Array:
            value_.arr_ = new ScriptArrayPtr(*other.value_.arr_);
            break;
        default:
            value_ = other.value_;
            break;
    }
}

rs::scriptobject::utils::VectorValue::VectorValue(VectorValue&& other) {
    type_ = other.type_;
    value_ = other.value_;
    other.type_ = rs::scriptobject::ScriptObjectType::Null;
}

rs::scriptobject::utils::VectorValue::VectorValue() :
    type_(rs::scriptobject::ScriptObjectType::Null) {
}

rs::scriptobject::utils::VectorValue::VectorValue(rs::scriptobject::ScriptObjectType type) :
    type_(type) {
}

rs::scriptobject::utils::VectorValue::VectorValue(const ScriptObjectPtr value) :
    type_(rs::scriptobject::ScriptObjectType::Object) {
    value_.obj_ = new ScriptObjectPtr(value);
}

rs::scriptobject::utils::VectorValue::VectorValue(const ScriptArrayPtr value) :
    type_(rs::scriptobject::ScriptObjectType::Array) {
    value_.arr_ = new ScriptArrayPtr(value);
}

rs::scriptobject::utils::VectorValue::~VectorValue() {
    switch (type_) {
        case rs::scriptobject::ScriptObjectType::String:
            delete[] value_.s_;
            break;
        case rs::scriptobject::ScriptObjectType::Object:
            delete value_.obj_;
            break;
        case rs::scriptobject::ScriptObjectType::Array:
            delete value_.arr_;
            break;
    }
}

rs::scriptobject::ScriptObjectType rs::scriptobject::utils::VectorValue::getType() const {
    return type_;
}

double rs::scriptobject::utils::VectorValue::getDouble() const {
    return value_.d_;
}

std::int32_t rs::scriptobject::utils::VectorValue::getInt32() const {
    return value_.i32_;
}

std::uint32_t rs::scriptobject::utils::VectorValue::getUInt32() const {
    return value_.ui32_;
}

std::int64_t rs::scriptobject::utils::VectorValue::getInt64() const {
    return value_.i64_;
}

std::uint64_t rs::scriptobject::utils::VectorValue::getUInt64() const {
    return value_.ui64_;
}

bool rs::scriptobject::utils::VectorValue::getBoolean() const {
    return value_.b_;
}

const char* rs::scriptobject::utils::VectorValue::getString() const {
    return value_.s_;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::utils::VectorValue::getObject() const {
    return *value_.obj_;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::utils::VectorValue::getArray() const {
    return *value_.arr_;
}

char* rs::scriptobject::utils::VectorValue::CopyString(const char* source) {
    auto length = ::strlen(source);
    auto value = new char[length + 1];
    std::copy_n(source, length, value);
    value[length] = '\0';
    return value;
}

rs::scriptobject::utils::ScriptObjectVectorSource::ScriptObjectVectorSource(const ObjectVector& source) : source_(source) {
}
    
unsigned rs::scriptobject::utils::ScriptObjectVectorSource::count() const { 
    return source_.size(); 
}

const char* rs::scriptobject::utils::ScriptObjectVectorSource::name(int index) const { 
    return std::get<0>(source_[index]).c_str(); 
}

unsigned rs::scriptobject::utils::ScriptObjectVectorSource::length(int index) const { 
    return std::get<0>(source_[index]).length(); 
}

rs::scriptobject::ScriptObjectType rs::scriptobject::utils::ScriptObjectVectorSource::type(int index) const { 
    return std::get<1>(source_[index]).getType(); 
}

bool rs::scriptobject::utils::ScriptObjectVectorSource::getBoolean(int index) const { 
    return std::get<1>(source_[index]).getBoolean(); 
}

std::int32_t rs::scriptobject::utils::ScriptObjectVectorSource::getInt32(int index) const { 
    return std::get<1>(source_[index]).getInt32(); 
}

std::uint32_t rs::scriptobject::utils::ScriptObjectVectorSource::getUInt32(int index) const { 
    return std::get<1>(source_[index]).getUInt32(); 
}

std::int64_t rs::scriptobject::utils::ScriptObjectVectorSource::getInt64(int index) const { 
    return std::get<1>(source_[index]).getInt64(); 
}

std::uint64_t rs::scriptobject::utils::ScriptObjectVectorSource::getUInt64(int index) const { 
    return std::get<1>(source_[index]).getUInt64(); 
}

double rs::scriptobject::utils::ScriptObjectVectorSource::getDouble(int index) const { 
    return std::get<1>(source_[index]).getDouble(); 
}

const char* rs::scriptobject::utils::ScriptObjectVectorSource::getString(int index) const { 
    return std::get<1>(source_[index]).getString(); 
}

int rs::scriptobject::utils::ScriptObjectVectorSource::getStringLength(int index) const { 
    return ::strlen(getString(index));
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::utils::ScriptObjectVectorSource::getObject(int index) const { 
    return std::get<1>(source_[index]).getObject();
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::utils::ScriptObjectVectorSource::getArray(int index) const {
    return std::get<1>(source_[index]).getArray();
}