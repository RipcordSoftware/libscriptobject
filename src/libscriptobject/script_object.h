#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H

#include <memory>

#include "script_object_keys.h"

namespace rs {
namespace scriptobject {
    
class ScriptObjectSource;

class ScriptObject;
typedef std::shared_ptr<ScriptObject> ScriptObjectPtr;

class ScriptArray;
typedef std::shared_ptr<ScriptArray> ScriptArrayPtr;

struct ScriptObject {
    unsigned size;
    ScriptObjectKeysPtr keys;
    unsigned valueOffsets[];

    unsigned getCount() const;
    ScriptObjectType getType(int index) const;
    ScriptObjectType getType(const char* name) const;
    const char* getName(int index) const;
    const char* getString(int index) const;
    const char* getString(const char* name) const;
    std::int32_t getInt32(int index) const;
    std::int32_t getInt32(const char* name) const;
    double getDouble(int index) const;
    double getDouble(const char* name) const;
    bool getBoolean(int index) const;
    bool getBoolean(const char* name) const;
    const ScriptObjectPtr getObject(int index) const;
    const ScriptObjectPtr getObject(const char* name) const;
    const ScriptArrayPtr getArray(int index) const;
    const ScriptArrayPtr getArray(const char* name) const;
    
private:
    static unsigned CalculateSize(const ScriptObjectSource& source);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptObject&);
    
    static void ScriptObjectDeleter(ScriptObject* ptr);
    
    friend class ScriptObjectFactory;
} __attribute__ ((aligned (2)));

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_H */

