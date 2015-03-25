#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H

#include <vector>
#include <string>

#include "script_object_source.h"

namespace rs {
namespace scriptobject {
namespace test {
    
typedef std::vector<std::tuple<std::string, rs::scriptobject::ScriptObjectType, std::string>> VectorObject;

class VectorObjectSource : public rs::scriptobject::ScriptObjectSource {
public:
    VectorObjectSource(const VectorObject& source) : source(source) {}
    
    virtual unsigned count() const override { return source.size(); }
    virtual const char* name(int index) const override { return std::get<0>(source[index]).c_str(); }
    virtual unsigned length(int index) const override { return std::get<0>(source[index]).length(); }
    virtual rs::scriptobject::ScriptObjectType type(int index) const override { return std::get<1>(source[index]); }
    
    virtual bool getBoolean(int index) const { return std::get<2>(source[index]) == "true"; }
    virtual int32_t getInt32(int index) const { return std::stoi(std::get<2>(source[index])); }
    virtual double getDouble(int index) const override { return std::stod(std::get<2>(source[index])); }
    virtual const char* getString(int index) const override { return std::get<2>(source[index]).c_str(); }
    virtual int getStringLength(int index) const override { return std::get<2>(source[index]).length(); }
        
private:
    VectorObject source;
};

}}}
    
#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H */

