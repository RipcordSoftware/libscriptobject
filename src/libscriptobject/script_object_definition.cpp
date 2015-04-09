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

#include "script_object_definition.h"

#include "md5.h"

void rs::scriptobject::ScriptObjectDefinition::CalculateHash(ScriptObjectHash digest) const {
    MD5 md5;
    const int fieldCount = count();
        
    for (int i = 0; i < fieldCount; ++i) {
        md5.update(name(i), length(i));
    }
    
    unsigned char typeBuffer[64];
    int typeBufferBlocks = fieldCount / sizeof(typeBuffer);
    int typeBufferOverflow = fieldCount % sizeof(typeBuffer);
    int typeIndex = 0;
    
    for (int i = 0; i < typeBufferBlocks; ++i) {
        for (int j = 0; j < sizeof(typeBuffer); ++j) {
            typeBuffer[j] = static_cast<unsigned char>(type(typeIndex++));
        }
        
        md5.update(typeBuffer, sizeof(typeBuffer));
    }
    
    if (typeBufferOverflow > 0) {
        for (int i = 0; i < typeBufferOverflow; ++i) {
            typeBuffer[i] = static_cast<unsigned char>(type(typeIndex++));
        }
        
        md5.update(typeBuffer, typeBufferOverflow);
    }
    
    md5.finalize();
    md5.bindigest(digest);
}