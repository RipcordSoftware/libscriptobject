#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HEADER_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HEADER_H

namespace rs {
namespace scriptobject {

struct ScriptObjectHeader {
    unsigned size;
    unsigned short count;
    unsigned short flags;
    unsigned valueOffsets[];
} __attribute__ ((aligned (2)));
    
}}    
    
#endif	/* #ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_HEADER_H */

