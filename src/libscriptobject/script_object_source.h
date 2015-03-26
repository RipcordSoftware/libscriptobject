#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_SOURCE_H

#include "script_object_definition.h"
#include "script_object.h"
#include "script_array.h"

#include <cstdint>

namespace rs {
namespace scriptobject {

class ScriptObjectSource : public ScriptObjectDefinition {
public:
    virtual bool getBoolean(int index) const = 0;
    virtual std::int32_t getInt32(int index) const = 0;
    virtual double getDouble(int index) const = 0;
    virtual const char* getString(int index) const = 0;
    virtual int getStringLength(int index) const = 0;
    virtual const ScriptObjectPtr getObject(int index) const = 0;
    virtual const ScriptArrayPtr getArray(int index) const = 0;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_SOURCE_H */

