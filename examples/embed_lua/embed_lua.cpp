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

#include <iostream>

#include "sol.hpp"

#include "libscriptobject.h"
#include "script_object_vector_source.h"

using namespace std;
using namespace rs::scriptobject;

// declare a C++ class we can expose to Lua
struct DynamicObject {
    // a getter method for the objects fields
    // maps the libscriptobject field value to Lua by name
    sol::object get_property_lua(const char* name, sol::this_state s) {
        switch (obj_->getType(name)) {
            case ScriptObjectType::String: return sol::make_object(s, obj_->getString(name));
            case ScriptObjectType::Int32: return sol::make_object(s, obj_->getInt32(name));
            case ScriptObjectType::Int64: return sol::make_object(s, obj_->getInt64(name));
            case ScriptObjectType::Double: return sol::make_object(s, obj_->getDouble(name));
            case ScriptObjectType::Boolean: return sol::make_object(s, obj_->getBoolean(name));
            default: return sol::make_object(s, "undefined");
        }
    }
    
    // A static object instance which we can expose to Lua
    static ScriptObjectPtr obj_;
};

ScriptObjectPtr DynamicObject::obj_;

int main() {
    // init the Lua library
    sol::state lua;
    lua.open_libraries(sol::lib::base);

    // expose the dynamic class to Lua
    lua.new_usertype<DynamicObject>("DynamicObject",
        sol::meta_function::index, &DynamicObject::get_property_lua);
    
    // create an object source
    utils::ScriptObjectVectorSource source({
        make_pair("hello", utils::VectorValue("world")),
        make_pair("lorem", utils::VectorValue("ipsum")),
        make_pair("pi", utils::VectorValue(3.14159)),
        make_pair("moreTaxes", utils::VectorValue(false)),
    });

    // use the object factory to create the new object based on our source
    auto object = ScriptObjectFactory::CreateObject(source);

    // attach the object to the dynamic class
    DynamicObject::obj_ = object;

    // ask Lua to output some field values
    lua.script(R"(
        obj = DynamicObject:new()
        print('hello = ' .. obj.hello)
        print('lorem = ' .. obj.lorem)
        print('pi = ' .. obj.pi)
        print('moreTaxes = ' .. tostring(obj.moreTaxes))
    )");
}
