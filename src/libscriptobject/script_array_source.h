#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H

#include <cstdint>

#include "script_array.h"
#include "script_object.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource {
public:
    virtual unsigned count() const = 0;
    virtual ScriptObjectType type(int index) const = 0;
    virtual bool getBoolean(int index) const = 0;
    virtual std::int32_t getInt32(int index) const = 0;
    virtual double getDouble(int index) const = 0;
    virtual const char* getString(int index) const = 0;
    virtual int getStringLength(int index) const = 0;
    virtual const ScriptObjectPtr getObject(int index) const = 0;
    virtual const ScriptArrayPtr getArray(int index) const = 0;
};

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_SOURCE_H */

