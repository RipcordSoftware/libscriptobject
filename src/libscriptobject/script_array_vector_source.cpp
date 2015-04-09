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

#include "script_array_vector_source.h"

#include <cstring>

rs::scriptobject::test::ScriptArrayVectorSource::ScriptArrayVectorSource(const ArrayVector& array) : array_(array) {    
}

unsigned rs::scriptobject::test::ScriptArrayVectorSource::count() const {
    return array_.size();
}

rs::scriptobject::ScriptObjectType rs::scriptobject::test::ScriptArrayVectorSource::type(int index) const {
    return array_[index].getType();
}

bool rs::scriptobject::test::ScriptArrayVectorSource::getBoolean(int index) const {
    return array_[index].getBoolean();
}

std::int32_t rs::scriptobject::test::ScriptArrayVectorSource::getInt32(int index) const {
    return array_[index].getInt32();
}

double rs::scriptobject::test::ScriptArrayVectorSource::getDouble(int index) const {
    return array_[index].getDouble();
}

const char* rs::scriptobject::test::ScriptArrayVectorSource::getString(int index) const {
    return array_[index].getString();
}

int rs::scriptobject::test::ScriptArrayVectorSource::getStringLength(int index) const {
    return ::strlen(getString(index));
}

const rs::scriptobject::ScriptObjectPtr rs::scriptobject::test::ScriptArrayVectorSource::getObject(int index) const {
    return array_[index].getObject();
}

const rs::scriptobject::ScriptArrayPtr rs::scriptobject::test::ScriptArrayVectorSource::getArray(int index) const {
    return array_[index].getArray();
}