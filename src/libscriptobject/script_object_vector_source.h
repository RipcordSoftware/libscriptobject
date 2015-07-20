/*
 *  This file is part of libscriptobject.
 *
 *  libscriptobject is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libscriptobject is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libscriptobject.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H

#include <vector>
#include <string>

#include "script_object_source.h"

namespace rs {
namespace scriptobject {
namespace utils {

class VectorValue final {
public: 
    VectorValue();
    VectorValue(const VectorValue& other);    
    VectorValue(VectorValue&& other);        
    VectorValue(rs::scriptobject::ScriptObjectType type);    
    VectorValue(double value);
    VectorValue(std::int32_t value);    
    VectorValue(bool value);    
    VectorValue(const char* value);    
    VectorValue(const ScriptObjectPtr value);
    VectorValue(const ScriptArrayPtr value);
    ~VectorValue();
    
    rs::scriptobject::ScriptObjectType getType() const;
    double getDouble() const;    
    std::int32_t getInt32() const;    
    bool getBoolean() const;    
    const char* getString() const;
    const ScriptObjectPtr getObject() const;
    const ScriptArrayPtr getArray() const;
    
private:
    static char* CopyString(const char* source);
    
    rs::scriptobject::ScriptObjectType type_;
    union Value {
        double d_;
        std::int32_t i_;
        bool b_;
        char* s_;
        ScriptObjectPtr* obj_;
        ScriptArrayPtr* arr_;
    } value_;
};
    
typedef std::vector<std::pair<std::string, VectorValue>> ObjectVector;

class ScriptObjectVectorSource final : public rs::scriptobject::ScriptObjectSource {
public:
    ScriptObjectVectorSource(const ObjectVector& source);
    
    virtual unsigned count() const override;
    virtual const char* name(int index) const override;
    virtual unsigned length(int index) const override;
    virtual rs::scriptobject::ScriptObjectType type(int index) const override;
    
    virtual bool getBoolean(int index) const override;
    virtual int32_t getInt32(int index) const override;
    virtual double getDouble(int index) const override;
    virtual const char* getString(int index) const override;
    virtual int getStringLength(int index) const override;
    
    virtual const ScriptObjectPtr getObject(int index) const override;
    virtual const ScriptArrayPtr getArray(int index) const override;
        
private:
    ObjectVector source_;
};

}}}
    
#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_SOURCE_H */

