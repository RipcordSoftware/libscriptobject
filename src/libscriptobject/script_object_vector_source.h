#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H

#include <vector>
#include <string>

#include "script_object_source.h"

namespace rs {
namespace scriptobject {
namespace test {

class VectorObjectValue {
public: 
    VectorObjectValue();
    VectorObjectValue(const VectorObjectValue& other);    
    VectorObjectValue(VectorObjectValue&& other);        
    VectorObjectValue(rs::scriptobject::ScriptObjectType type);    
    VectorObjectValue(double value);
    VectorObjectValue(std::int32_t value);    
    VectorObjectValue(bool value);    
    VectorObjectValue(const char* value);    
    VectorObjectValue(const ScriptObjectPtr value);
    VectorObjectValue(const ScriptArrayPtr value);
    ~VectorObjectValue();
    
    rs::scriptobject::ScriptObjectType getType() const;
    double getDouble() const;    
    std::int32_t getInt32() const;    
    bool getBoolean() const;    
    const char* getString() const;
    const ScriptObjectPtr getObject() const;
    const ScriptArrayPtr getArray() const;
    
private:
    static char* CopyString(const char* source);
    
    rs::scriptobject::ScriptObjectType type_;
    union Value {
        double d_;
        std::int32_t i_;
        bool b_;
        char* s_;
        ScriptObjectPtr* obj_;
        ScriptArrayPtr* arr_;
    } value_;
};
    
typedef std::vector<std::tuple<std::string, VectorObjectValue>> VectorObject;

class VectorObjectSource : public rs::scriptobject::ScriptObjectSource {
public:
    VectorObjectSource(const VectorObject& source);
    
    virtual unsigned count() const override;
    virtual const char* name(int index) const override;
    virtual unsigned length(int index) const override;
    virtual rs::scriptobject::ScriptObjectType type(int index) const override;
    
    virtual bool getBoolean(int index) const override;
    virtual int32_t getInt32(int index) const override;
    virtual double getDouble(int index) const override;
    virtual const char* getString(int index) const override;
    virtual int getStringLength(int index) const override;
    
    virtual const ScriptObjectPtr getObject(int index) const override;
    virtual const ScriptArrayPtr getArray(int index) const override;
        
private:
    VectorObject source_;
};

}}}
    
#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H */

