#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H

namespace rs {
namespace scriptobject {
    
enum class ScriptObjectType : unsigned char {    
    Unknown = 0,
    Int32 = 1,
    Double = 2,
    String = 3,
    Object = 4,
    Array = 5,
    Null = 6,
    MAX = 16
};
    
}}

#endif /* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_TYPE_H */