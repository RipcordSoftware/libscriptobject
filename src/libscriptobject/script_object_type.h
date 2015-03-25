#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H

namespace rs {
namespace scriptobject {
    
enum class ScriptObjectType : unsigned char {    
    Unknown = 0,
    Boolean = 1,
    Int32 = 2,
    Double = 3,
    String = 4,
    Object = 5,
    Array = 6,
    Null = 7,
    MAX = 16
};
    
}}

#endif /* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H */