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