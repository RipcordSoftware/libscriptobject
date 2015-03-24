#include "script_object_definition.h"

#include "md5.h"

void rs::scriptobject::ScriptObjectDefinition::CalculateHash(unsigned char digest[16]) {
    MD5 md5;
    const int fieldCount = count();
        
    for (int i = 0; i < fieldCount; ++i) {
        md5.update(name(i), length(i));
    }
    
    unsigned char typeBuffer[16];
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