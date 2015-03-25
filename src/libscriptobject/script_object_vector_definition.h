#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H

#include <vector>
#include <string>

#include "script_object_definition.h"

namespace rs {
namespace scriptobject {
namespace test {

typedef std::vector<std::pair<std::string, rs::scriptobject::ScriptObjectType>> VectorDefn;

class VectorKeysDefn : public rs::scriptobject::ScriptObjectDefinition {
public:
    VectorKeysDefn(const VectorDefn& keys) : keys_(keys) {}
    
    virtual unsigned count() const override { return keys_.size(); }
    virtual const char* name(int index) const override { return keys_[index].first.c_str(); }
    virtual unsigned length(int index) const override { return keys_[index].first.length(); }
    virtual rs::scriptobject::ScriptObjectType type(int index) const override { return keys_[index].second; }
        
private:
    VectorDefn keys_;
};
    
}}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H */

