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

#include "libscriptobject.h"
#include "script_object_vector_source.h"

int main() {
    // create an object source
    rs::scriptobject::utils::ScriptObjectVectorSource source({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("moreTaxes", rs::scriptobject::utils::VectorValue(false)),
    });

    // use the object factory to create the new object based on our source
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(source);

    // get the object keys
    auto keys = object->getKeys();

    // output the object key names and values to stdout
    std::cout << keys->getKeyName(0) << ": " << object->getString(0) << std::endl;
    std::cout << keys->getKeyName(1) << ": " << object->getString(1) << std::endl;
    std::cout << keys->getKeyName(2) << ": " << object->getDouble(2) << std::endl;
    std::cout << keys->getKeyName(3) << ": " << (object->getBoolean(3) ? "true" : "false") << std::endl;
}
