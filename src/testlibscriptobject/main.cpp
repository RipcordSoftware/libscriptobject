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
#include <fstream>
#include <sstream>
#include <iomanip>
#include <array>

#include <unistd.h>

#include "script_object_json_source.h"
#include "script_array_json_source.h"
#include "script_object_factory.h"
#include "script_array_factory.h"
#include "script_object_keys_cache.h"

void ShowObject(const rs::scriptobject::ScriptObjectPtr object, int depth);
void ShowArray(const rs::scriptobject::ScriptArrayPtr array, int depth);

std::string EscapeString(const char* source) {
    std::string escaped = source;
    
    int pos = 0;
    while ((pos = escaped.find('\r')) != std::string::npos) {
        escaped[pos] = '\\';
        escaped.insert(pos + 1, 1, 'r');
    }
    
    while ((pos = escaped.find('\n')) != std::string::npos) {
        escaped[pos] = '\\';
        escaped.insert(pos + 1, 1, 'n');
    }
    
    return escaped;    
}

void ShowArray(const rs::scriptobject::ScriptArrayPtr array, int depth = 0) {
    auto padding = std::string(depth * 2, ' ');
    
    std::cout << '[' << std::endl;
    
    auto fieldCount = array->getCount();
    for (int i = 0; i < fieldCount; i++) {
        if (i > 0) {
            std::cout << ',' << std::endl;
        }
        
        std::cout << padding;
        
        switch (array->getType(i)) {
            case rs::scriptobject::ScriptObjectType::Boolean:
                std::cout << (array->getBoolean(i) ? "true" : "false");
                break;
            case rs::scriptobject::ScriptObjectType::Int32:
                std::cout << array->getInt32(i);
                break;
            case rs::scriptobject::ScriptObjectType::Double:
                std::cout << std::setprecision(12) << array->getDouble(i);
                break;
            case rs::scriptobject::ScriptObjectType::String:
                std::cout << '"' << EscapeString(array->getString(i)) << '"';
                break;
            case rs::scriptobject::ScriptObjectType::Object:
                ShowObject(array->getObject(i), depth + 1);
                break;
            case rs::scriptobject::ScriptObjectType::Array:
                ShowArray(array->getArray(i), depth + 1);
                break;
            case rs::scriptobject::ScriptObjectType::Null:
                std::cout << "null";
                break;
        }
    }
    
    std::cout << std::endl << padding << ']';
}

void ShowObject(const rs::scriptobject::ScriptObjectPtr object, int depth = 0) {
    auto padding = std::string(depth * 2, ' ');
    
    std::cout << '{' << std::endl;
    
    auto fieldCount = object->getCount();
    for (int i = 0; i < fieldCount; i++) {
        if (i > 0) {
            std::cout << ',' << std::endl;
        }
        
        std::cout << padding << '"' << object->getName(i) << "\": ";
        
        switch (object->getType(i)) {
            case rs::scriptobject::ScriptObjectType::Boolean:
                std::cout << (object->getBoolean(i) ? "true" : "false");
                break;
            case rs::scriptobject::ScriptObjectType::Int32:
                std::cout << object->getInt32(i);
                break;
            case rs::scriptobject::ScriptObjectType::Double:
                std::cout << std::setprecision(12) << object->getDouble(i);
                break;
            case rs::scriptobject::ScriptObjectType::String:
                std::cout << '"' << EscapeString(object->getString(i)) << '"';
                break;
            case rs::scriptobject::ScriptObjectType::Object:
                ShowObject(object->getObject(i), depth + 1);
                break;
            case rs::scriptobject::ScriptObjectType::Array:
                ShowArray(object->getArray(i), depth + 1);
                break;
            case rs::scriptobject::ScriptObjectType::Null:
                std::cout << "null";
                break;
        }        
    }    
    
    std::cout << std::endl << padding << '}';
}

void ShowMemoryState() {
    auto pid = ::getpid();
        
    std::stringstream filename;
    filename << "/proc/" << pid << "/status";

    std::ifstream statstream;
    statstream.open(filename.str(), std::ios::in);
    
    if (statstream) {
        std::cerr << std::endl;

        std::string line;
        while (getline(statstream, line)) {
            if (line.length() > 2 && line[0] == 'V' && line[1] == 'm') {
                std::cerr << line << std::endl;
            }
        }
    }
}

bool IsObject(const char* json, int length) {
    int front = 0;
    while (front < (length - 1) && (json[front] == ' ' || json[front] == '\t' || json[front] == '\n')) {
        front++;
    }
    
    int back =  length - 1;
    while (back > 0 && json[back] == ' ' || json[back] == '\t' || json[back] == '\n') {
        back--;
    }
    
    return json[front] == '{' && json[back] == '}';
}

bool IsArray(const char* json, int length) {
    int front = 0;
    while (front < (length - 1) && (json[front] == ' ' || json[front] == '\t' || json[front] == '\n')) {
        front++;
    }
    
    int back = length - 1;
    while (back > 0 && json[back] == ' ' || json[back] == '\t' || json[back] == '\n') {
        back--;
    }
    
    return json[front] == '[' && json[back] == ']';
}


int main(int argc, char** argv) {
    
    if (argc != 2) {
        std::cout << "command line: [json file]" << std::endl;
        return 1;
    } else {
        try {
            std::ifstream istream;
            istream.open(argv[1], std::ios::in | std::ios::binary);
            if (!istream) {
                throw "Unable to open input file";
            }
            
            std::cerr << "Reading... ";
            istream.seekg(0, std::ios::end);
            auto fileLength = istream.tellg();
            istream.seekg(0, std::ios::beg);

            char* json = new char[fileLength];
            istream.read(json, fileLength);        
            std::cerr << "done" << std::endl;

            ShowMemoryState();
        
            std::cerr << "Parsing... ";
            
            if (IsObject(json, fileLength)) {
                rs::scriptobject::ScriptObjectJsonSource source(&json[0]);
                auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(source);
                ShowObject(object);
            } else if (IsArray(json, fileLength)) {
                rs::scriptobject::ScriptArrayJsonSource source(&json[0]);
                auto object = rs::scriptobject::ScriptArrayFactory::CreateArray(source);
                ShowArray(object);
            } else {
                throw "Error: the input file was not recognised as JSON";
            }
            
            std::cerr << "done, found: " << std::endl << 
                rs::scriptobject::ScriptObjectKeysCache::getCount() << " keys" << std::endl <<
                rs::scriptobject::ScriptObjectFactory::getCount() << " objects" << std::endl <<
                (rs::scriptobject::ScriptObjectFactory::getTotalBytesAllocated() / 1024) << " total objects KB" << std::endl <<
                rs::scriptobject::ScriptArrayFactory::getCount() << " arrays" << std::endl <<
                (rs::scriptobject::ScriptArrayFactory::getTotalBytesAllocated() / 1024) << " total array KB" << std::endl;
            
            delete[] json;
            
            ShowMemoryState();

            return 0;
        } catch (const char* msg) {
            std::cerr << "Error: " << msg << std::endl;
            return 2;
        }
    }
}