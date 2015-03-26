#include "script_object_vector_source.h"

#include <cstring>

#include <algorithm>

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(const VectorObjectValue& other) {
    type_ = other.type_;

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

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(VectorObjectValue&& other) {
    type_ = other.type_;
    value_ = other.value_;
    other.type_ = rs::scriptobject::ScriptObjectType::Null;
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue() :
    type_(rs::scriptobject::ScriptObjectType::Null) {
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(rs::scriptobject::ScriptObjectType type) :
    type_(type) {
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(double value) :
    type_(rs::scriptobject::ScriptObjectType::Double) {
    value_.d_ = value;
    }

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(std::int32_t value) :
    type_(rs::scriptobject::ScriptObjectType::Int32) {
    value_.i_ = value;
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(bool value) :
    type_(rs::scriptobject::ScriptObjectType::Boolean) {
    value_.b_ = value;
}
    
rs::scriptobject::test::VectorObjectValue::VectorObjectValue(const char* value) :
    type_(rs::scriptobject::ScriptObjectType::String) {
    value_.s_ = CopyString(value);
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(const ScriptObjectPtr value) :
    type_(rs::scriptobject::ScriptObjectType::Object) {
    value_.obj_ = new ScriptObjectPtr(value);
}

rs::scriptobject::test::VectorObjectValue::VectorObjectValue(const ScriptArrayPtr value) :
    type_(rs::scriptobject::ScriptObjectType::Array) {
    value_.arr_ = new ScriptArrayPtr(value);
}

rs::scriptobject::test::VectorObjectValue::~VectorObjectValue() {
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

rs::scriptobject::ScriptObjectType rs::scriptobject::test::VectorObjectValue::getType() const {
    return type_;
}

double rs::scriptobject::test::VectorObjectValue::getDouble() const {
    return value_.d_;
}

std::int32_t rs::scriptobject::test::VectorObjectValue::getInt32() const {
    return value_.i_;
}

bool rs::scriptobject::test::VectorObjectValue::getBoolean() const {
    return value_.b_;
}

const char* rs::scriptobject::test::VectorObjectValue::getString() const {
    return value_.s_;
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::test::VectorObjectValue::getObject() const {
    return *value_.obj_;
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::test::VectorObjectValue::getArray() const {
    return *value_.arr_;
}

char* rs::scriptobject::test::VectorObjectValue::CopyString(const char* source) {
    auto length = ::strlen(source);
    auto value = new char[length + 1];
    std::copy_n(source, length, value);
    value[length] = '\0';
    return value;
}

rs::scriptobject::test::VectorObjectSource::VectorObjectSource(const VectorObject& source) : source_(source) {
}
    
unsigned rs::scriptobject::test::VectorObjectSource::count() const { 
    return source_.size(); 
}

const char* rs::scriptobject::test::VectorObjectSource::name(int index) const { 
    return std::get<0>(source_[index]).c_str(); 
}

unsigned rs::scriptobject::test::VectorObjectSource::length(int index) const { 
    return std::get<0>(source_[index]).length(); 
}

rs::scriptobject::ScriptObjectType rs::scriptobject::test::VectorObjectSource::type(int index) const { 
    return std::get<1>(source_[index]).getType(); 
}

bool rs::scriptobject::test::VectorObjectSource::getBoolean(int index) const { 
    return std::get<1>(source_[index]).getBoolean(); 
}

int32_t rs::scriptobject::test::VectorObjectSource::getInt32(int index) const { 
    return std::get<1>(source_[index]).getInt32(); 
}

double rs::scriptobject::test::VectorObjectSource::getDouble(int index) const { 
    return std::get<1>(source_[index]).getDouble(); 
}

const char* rs::scriptobject::test::VectorObjectSource::getString(int index) const { 
    return std::get<1>(source_[index]).getString(); 
}

int rs::scriptobject::test::VectorObjectSource::getStringLength(int index) const { 
    return ::strlen(getString(index));
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::test::VectorObjectSource::getObject(int index) const { 
    return std::get<1>(source_[index]).getObject();
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::test::VectorObjectSource::getArray(int index) const {
    return std::get<1>(source_[index]).getArray();
}