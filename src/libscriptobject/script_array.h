#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H

#include <memory>

#include "script_object_type.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource;

struct ScriptArray;
typedef std::shared_ptr<ScriptArray> ScriptArrayPtr;

struct ScriptArray {        
    const unsigned size;    
    struct {
        unsigned singleTypeFlag : 1;
        unsigned spareFlag1 : 1;
        unsigned spareFlag2 : 1;
        unsigned spareFlag3 : 1;
        unsigned count : 28;
    };
    unsigned offsets[/*count*/];
    //unsigned char values[];
    //ScriptObjectType types[count];
private:    
    friend class ScriptArrayFactory;
    
    ScriptArray(unsigned size, unsigned count);
    
    static unsigned CalculateSize(const ScriptArraySource& source);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptArray& array);
    const ScriptObjectType* getTypeStart() const;
    static ScriptObjectType* getTypeStart(ScriptArray& array);
    
    static void ScriptArrayDeleter(ScriptArray* ptr);

} __attribute__ ((aligned (4)));;

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H */

