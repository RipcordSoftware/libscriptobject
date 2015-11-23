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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H

#include <memory>

#include "script_object_type.h"
#include "script_object_hash.h"
#include "script_item_ptr.h"

namespace rs {
namespace scriptobject {

class ScriptArraySource;

class ScriptArray;
using ScriptArrayPtr = ScriptItemPtr<ScriptArray>;

class ScriptObject;
using ScriptObjectPtr = ScriptItemPtr<ScriptObject>;

class ScriptArray final : public ScriptItemPtrBase<ScriptArray> {
private:
    const unsigned size_;
    ScriptItemPtrBase<ScriptArray>::atomic_count_type refCount_{0};
    struct {
        unsigned singleTypeFlag_ : 1;
        unsigned spareFlag1_ : 1;
        unsigned spareFlag2_ : 1;
        unsigned spareFlag3_ : 1;
        unsigned count_ : 28;
    };
    unsigned offsets_[/*count*/];
    //unsigned char values[];
    //ScriptObjectType types[count];

public:
    std::uint64_t getSize(bool includeChildren = false) const;
    unsigned getCount() const;
    ScriptObjectType getType(int index) const;
    const char* getString(int index) const;
    std::int32_t getInt32(int index) const;
    std::uint32_t getUInt32(int index) const;
    std::int64_t getInt64(int index) const;
    std::uint64_t getUInt64(int index) const;
    double getDouble(int index) const;
    bool getBoolean(int index) const;
    const ScriptObjectPtr getObject(int index) const;
    const ScriptArrayPtr getArray(int index) const;
    
    void CalculateHash(ScriptObjectHash&, bool (*)(const char*) = nullptr);
    
    static unsigned CalculateSizeOverhead(unsigned fieldCount);
    
private:
    friend class ScriptItemPtrBase<ScriptArray>;
    friend ScriptArrayPtr make_sized_script_item_ptr<ScriptArrayPtr::element_type>(size_t, unsigned&, unsigned&);
    friend class ScriptArrayFactory;
    
    ScriptArray(unsigned size, unsigned count);
    ~ScriptArray();
    
    static unsigned CalculateSize(const ScriptArraySource& source);
    static unsigned CalculateTypesSize(unsigned fieldCount);
    const unsigned char* getValueStart() const;
    static unsigned char* getValueStart(ScriptArray& array);
    const ScriptObjectType* getTypeStart() const;
    static ScriptObjectType* getTypeStart(ScriptArray& array);    

} __attribute__ ((aligned (4)));;

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ARRAY_H */

