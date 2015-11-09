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

#include "script_array_factory.h"

#include <algorithm>

std::atomic<unsigned> rs::scriptobject::ScriptArrayFactory::count_;
std::atomic<unsigned long> rs::scriptobject::ScriptArrayFactory::totalBytes_;

rs::scriptobject::ScriptArrayPtr rs::scriptobject::ScriptArrayFactory::CreateArray(const rs::scriptobject::ScriptArraySource& source) {
    auto size = ScriptArray::CalculateSize(source);
    
    auto sourceCount = source.count();
    auto array = make_sized_script_item_ptr<ScriptArrayPtr::element_type>(size, size, sourceCount);
    
    auto valueStart = ScriptArray::getValueStart(*array);
    auto types = ScriptArray::getTypeStart(*array);
    unsigned offset = 0, stringOffset = size - (valueStart - array.getRawPtr()) - ScriptArray::CalculateTypesSize(source.count());
    for (int i = 0; i < array->count_; ++i) {
        const auto type = source.type(i);
        switch (type) {
            case ScriptObjectType::Int32:
                *reinterpret_cast<std::int32_t*>(valueStart + offset) = source.getInt32(i);
                array->offsets_[i] = offset;
                offset += sizeof(std::int32_t);                
                break;
            case ScriptObjectType::Double:
                *reinterpret_cast<double*>(valueStart + offset) = source.getDouble(i);
                array->offsets_[i] = offset;
                offset += sizeof(double);
                break;
            case ScriptObjectType::Boolean:
                array->offsets_[i] = source.getBoolean(i);
                offset += 0;
                break;
            case ScriptObjectType::Object: {
                auto child = source.getObject(i);
                new (static_cast<void*>(valueStart + offset)) ScriptObjectPtr(child);
                array->offsets_[i] = offset;
                offset += sizeof(ScriptObjectPtr);
                break;
            }
            case ScriptObjectType::Array: {
                auto child = source.getArray(i);
                new (static_cast<void*>(valueStart + offset)) ScriptArrayPtr(child);
                array->offsets_[i] = offset;
                offset += sizeof(ScriptArrayPtr);
                break;
            }
            case ScriptObjectType::String: {
                auto stringLength = source.getStringLength(i);
                stringOffset -= stringLength + 1;
                std::copy_n(source.getString(i), stringLength, valueStart + stringOffset);
                *(valueStart + stringOffset + stringLength) = '\0';
                array->offsets_[i] = stringOffset;
                break;
            }
            case ScriptObjectType::Null:
                array->offsets_[i] = 0;
                break;
            case ScriptObjectType::Undefined:
                array->offsets_[i] = 0;
                break;
        }
        
        types[i] = type;
    }
    
    ++ScriptArrayFactory::count_;
    ScriptArrayFactory::totalBytes_ += size;
    
    return array;
}

unsigned rs::scriptobject::ScriptArrayFactory::getCount() {
    return count_;
}

unsigned long rs::scriptobject::ScriptArrayFactory::getTotalBytesAllocated() {
    return totalBytes_;
}