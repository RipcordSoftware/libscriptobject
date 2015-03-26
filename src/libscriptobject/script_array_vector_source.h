#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_VECTOR_SOURCE_H
#define	RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_VECTOR_SOURCE_H

#include <vector>

#include "script_array_source.h"
#include "script_object_vector_source.h"

namespace rs {
namespace scriptobject {
namespace test {
    
typedef std::vector<VectorValue> ArrayVector;

class ScriptArrayVectorSource : public ScriptArraySource {
public:
    ScriptArrayVectorSource(const ArrayVector&);
    
    virtual unsigned count() const override;
    virtual ScriptObjectType type(int index) const override;
    virtual bool getBoolean(int index) const override;
    virtual std::int32_t getInt32(int index) const override;
    virtual double getDouble(int index) const override;
    virtual const char* getString(int index) const override;
    virtual int getStringLength(int index) const override;
    virtual const ScriptObjectPtr getObject(int index) const override;
    virtual const ScriptArrayPtr getArray(int index) const override;

private:
    const ArrayVector array_;
};

}}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_VECTOR_SOURCE_H */

