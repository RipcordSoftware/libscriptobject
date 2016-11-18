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
#include "libscriptobject_gason.h"

using namespace std;
using namespace rs::scriptobject;

int main() {
    // an object defined in the JSON format
    auto json = R"(
        { "hello": "world", "lorem": "ipsum", "pi": 3.14159, "moreTaxes": false }
    )";

    // create an object source
    ScriptObjectJsonSource source{json};

    // use the object factory to create the new object based on our source
    auto object = ScriptObjectFactory::CreateObject(source);

    // get the object keys
    auto keys = object->getKeys();

    // output the object key names and values to stdout
    cout << keys->getKeyName(0) << ": " << object->getString(0) << endl;
    cout << keys->getKeyName(1) << ": " << object->getString(1) << endl;
    cout << keys->getKeyName(2) << ": " << object->getDouble(2) << endl;
    cout << keys->getKeyName(3) << ": " << (object->getBoolean(3) ? "true" : "false") << endl;
}

