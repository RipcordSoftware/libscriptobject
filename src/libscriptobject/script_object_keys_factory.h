#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H

#include "script_object_keys.h"
#include "script_object_definition.h"

namespace rs {
namespace scriptobject {   

/**
 * A factory for creating ScriptObjectKeys
 */
class ScriptObjectKeysFactory final {
public:
    ScriptObjectKeysFactory() = delete;

    /**
     * Creates a ScriptObjectKeys smart pointer instance
     * @param defn The source object definition
     * @return A smart pointer containing the new object
     */    
    static ScriptObjectKeysPtr CreateKeys(const ScriptObjectDefinition& defn);
    
private:       
    static void ScriptObjectKeysDeleter(ScriptObjectKeys* ptr);
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_KEYS_FACTORY_H */

