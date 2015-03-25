#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H

#include <cstdio>

#include <vector>
#include <string>
#include <algorithm>

#include "script_object_source.h"

namespace rs {
namespace scriptobject {
namespace test {
    
class VectorObjectValue {
public: 
    VectorObjectValue(const VectorObjectValue& other) {
        type_ = other.type_;
        
        if (type_ == rs::scriptobject::ScriptObjectType::String) {
            value_.s = CopyString(other.value_.s);    
        } else {
            value_ = other.value_;
        }
    }
    
    VectorObjectValue(VectorObjectValue&& other) {
        type_ = other.type_;
        value_ = other.value_;
        other.type_ = rs::scriptobject::ScriptObjectType::Null;
    }
    
    VectorObjectValue() :
        type_(rs::scriptobject::ScriptObjectType::Null) {
    }
    
    VectorObjectValue(rs::scriptobject::ScriptObjectType type) :
        type_(type) {
    }
    
    VectorObjectValue(double value) :
        type_(rs::scriptobject::ScriptObjectType::Double) {
        value_.d = value;
        }
        
    VectorObjectValue(std::int32_t value) :
        type_(rs::scriptobject::ScriptObjectType::Int32) {
        value_.i = value;
    }
    
    VectorObjectValue(bool value) :
        type_(rs::scriptobject::ScriptObjectType::Boolean) {
        value_.b = value;
    }
    
    VectorObjectValue(const char* value) :
        type_(rs::scriptobject::ScriptObjectType::String) {
        value_.s = CopyString(value);
    }
    
    ~VectorObjectValue() {
        if (type_ == rs::scriptobject::ScriptObjectType::String) {
            delete[] value_.s;
        }
    }
    
    rs::scriptobject::ScriptObjectType getType() const {
        return type_;
    }
    
    double getDouble() const {
        return value_.d;
    }
    
    std::int32_t getInt32() const {
        return value_.i;
    }
    
    bool getBoolean() const {
        return value_.b;
    }
    
    const char* getString() const {
        return value_.s;
    }
    
private:
    char* CopyString(const char* source) const {
        auto length = ::strlen(source);
        auto value = new char[length + 1];
        std::copy_n(source, length, value);
        value[length] = '\0';
        return value;
    }
    
    rs::scriptobject::ScriptObjectType type_;
    union Value {
        double d;
        std::int32_t i;
        bool b;
        char* s;
    } value_;
};
    
typedef std::vector<std::tuple<std::string, VectorObjectValue>> VectorObject;

class VectorObjectSource : public rs::scriptobject::ScriptObjectSource {
public:
    VectorObjectSource(const VectorObject& source) : source_(std::move(source)) {}
    
    virtual unsigned count() const override { return source_.size(); }
    virtual const char* name(int index) const override { return std::get<0>(source_[index]).c_str(); }
    virtual unsigned length(int index) const override { return std::get<0>(source_[index]).length(); }
    virtual rs::scriptobject::ScriptObjectType type(int index) const override { return std::get<1>(source_[index]).getType(); }
    
    virtual bool getBoolean(int index) const { return std::get<1>(source_[index]).getBoolean(); }
    virtual int32_t getInt32(int index) const { return std::get<1>(source_[index]).getInt32(); }
    virtual double getDouble(int index) const override { return std::get<1>(source_[index]).getDouble(); }
    virtual const char* getString(int index) const override { return std::get<1>(source_[index]).getString(); }
    virtual int getStringLength(int index) const override { return ::strlen(getString(index)); }
    
    virtual const VectorObjectSource& getObject(int index) const override { throw "not_implemented"; }
        
private:
    VectorObject source_;
};

}}}
    
#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H */

