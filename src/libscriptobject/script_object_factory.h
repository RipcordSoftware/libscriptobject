#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H

#include "script_object_source.h"
#include "script_object.h"

namespace rs {
namespace scriptobject {

class ScriptObjectFactory final {
public:
    ScriptObjectFactory() = delete;
    ScriptObjectFactory(const ScriptObjectFactory& orig) = delete;
    
    static ScriptObjectPtr CreateObject(const ScriptObjectSource& source);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_FACTORY_H */

