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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H

#include <vector>
#include <string>

#include "script_object_definition.h"

namespace rs {
namespace scriptobject {
namespace test {

typedef std::vector<std::pair<std::string, rs::scriptobject::ScriptObjectType>> VectorDefn;

class VectorKeysDefn : public rs::scriptobject::ScriptObjectDefinition {
public:
    VectorKeysDefn(const VectorDefn& keys) : keys_(keys) {}
    
    virtual unsigned count() const override { return keys_.size(); }
    virtual const char* name(int index) const override { return keys_[index].first.c_str(); }
    virtual unsigned length(int index) const override { return keys_[index].first.length(); }
    virtual rs::scriptobject::ScriptObjectType type(int index) const override { return keys_[index].second; }
        
private:
    VectorDefn keys_;
};
    
}}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_OBJECT_VECTOR_DEFINITION_H */

