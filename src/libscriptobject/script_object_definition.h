#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H

#include "script_object_type.h"

namespace rs {
namespace scriptobject {

class ScriptObjectDefinition {
public:
    virtual unsigned count() const = 0;
    virtual ScriptObjectType type(int index) const = 0;
    virtual const char* name(int index) const = 0;    
    virtual unsigned length(int index) const = 0;
    
    void CalculateHash(unsigned char digest[16]);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_DEFINITION_H */