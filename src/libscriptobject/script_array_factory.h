#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H

#include "script_array.h"
#include "script_array_source.h"

namespace rs {
namespace scriptobject {

class ScriptArrayFactory final {
public:
    ScriptArrayFactory() = delete;
    ScriptArrayFactory(const ScriptArrayFactory& orig) = delete;
    
    static ScriptArrayPtr CreateArray(const ScriptArraySource& source);
    
private:

};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_FACTORY_H */

