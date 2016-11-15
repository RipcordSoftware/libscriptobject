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
#include "script_array_vector_source.h"

using namespace std;
using namespace rs::scriptobject;

int main() {
    // create an array source
    utils::ScriptArrayVectorSource source({
        utils::VectorValue("hello world"),
        utils::VectorValue("lorem ipsum"),
        utils::VectorValue(3.14159),
        utils::VectorValue(false),
    });

    // use the array factory to create the new array based on our source
    auto array = ScriptArrayFactory::CreateArray(source);

    // output the array values to stdout
    cout << array->getString(0) << endl;
    cout << array->getString(1) << endl;
    cout << array->getDouble(2) << endl;
    cout << (array->getBoolean(3) ? "true" : "false") << endl;
}
