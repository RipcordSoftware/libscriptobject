/**
 * @file 
 * Declares VectorValue and ScriptObjectVectorSource, utility classes which make it easy to create objects from std::vector
 * 
 * @internal
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
#include <cstdint>
#include <type_traits>
#include <limits>

#include "script_object_source.h"

namespace rs {
namespace scriptobject {
/// Utility (helper) types reside in this namespace
namespace utils {

/**
 * A simple sciptable value type capable of containing any ScriptObjectType typed field
 */
class VectorValue final {
public: 
    VectorValue();
    VectorValue(const VectorValue& other);    
    VectorValue(VectorValue&& other);        
    VectorValue(rs::scriptobject::ScriptObjectType type);
    
    template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
    VectorValue(T value) {
        type_ = rs::scriptobject::ScriptObjectType::Double;
        value_.d_ = value;
    }
    
    template <typename T, typename std::enable_if<std::is_signed<T>::value && !std::is_floating_point<T>::value>::type* = nullptr>
    VectorValue(T value) {
        if (value >= std::numeric_limits<std::int32_t>::min() &&
            value <= std::numeric_limits<std::int32_t>::max()) {
            type_ = rs::scriptobject::ScriptObjectType::Int32;
            value_.i32_ = value;
        } else {
            type_ = rs::scriptobject::ScriptObjectType::Int64;
            value_.i64_ = value;
        }
    }
    
    template <typename T, typename std::enable_if<std::is_unsigned<T>::value && !std::is_same<T, bool>::value>::type* = nullptr>
    VectorValue(T value) {
        if (value <= std::numeric_limits<std::uint32_t>::max()) {
            type_ = rs::scriptobject::ScriptObjectType::UInt32;
            value_.ui32_ = value;
        } else {
            type_ = rs::scriptobject::ScriptObjectType::UInt64;
            value_.ui64_ = value;
        }
    }
    
    template <typename T, typename std::enable_if<std::is_same<T, bool>::value>::type* = nullptr>
    VectorValue(T value) {
        type_ = rs::scriptobject::ScriptObjectType::Boolean;
        value_.b_ = value;
    }
    
    template <typename T, typename std::enable_if<std::is_same<T, char>::value>::type* = nullptr>
    VectorValue(const T* value) {
        type_ = rs::scriptobject::ScriptObjectType::String;
        value_.s_ = CopyString(value);
    }
    
    VectorValue(const ScriptObjectPtr value);
    VectorValue(const ScriptArrayPtr value);
    ~VectorValue();
    
    rs::scriptobject::ScriptObjectType getType() const;
    double getDouble() const;    
    std::int32_t getInt32() const;
    std::uint32_t getUInt32() const;
    std::int64_t getInt64() const;
    std::uint64_t getUInt64() const;
    bool getBoolean() const;    
    const char* getString() const;
    const ScriptObjectPtr getObject() const;
    const ScriptArrayPtr getArray() const;
    
private:
    static char* CopyString(const char* source);
    
    rs::scriptobject::ScriptObjectType type_;
    union Value {
        double d_;
        std::int32_t i32_;
        std::uint32_t ui32_;
        std::int64_t i64_;
        std::uint64_t ui64_;
        bool b_;
        char* s_;
        ScriptObjectPtr* obj_;
        ScriptArrayPtr* arr_;
    } value_;
};

/**
 * A std::vector containing key value pairs of field name and values
 * @see VectorValue
 */
using ObjectVector = std::vector<std::pair<std::string, VectorValue>>;

/**
 * A type representing an object source stored in a vector
 * @see ScriptObjectSource
 */
class ScriptObjectVectorSource final : public rs::scriptobject::ScriptObjectSource {
public:
    ScriptObjectVectorSource(const ObjectVector& source);
    
    virtual unsigned count() const override;
    virtual const char* name(int index) const override;
    virtual unsigned length(int index) const override;
    virtual rs::scriptobject::ScriptObjectType type(int index) const override;
    
    virtual bool getBoolean(int index) const override;
    virtual std::int32_t getInt32(int index) const override;
    virtual std::uint32_t getUInt32(int index) const override;
    virtual std::int64_t getInt64(int index) const override;
    virtual std::uint64_t getUInt64(int index) const override;
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
