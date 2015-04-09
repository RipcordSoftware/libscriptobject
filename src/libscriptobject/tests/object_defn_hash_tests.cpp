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

#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <algorithm>

#include "../libscriptobject.h"
#include "../script_object_vector_definition.h"
#include "script_object_vector_definition.h"

class ObjectDefnHashTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(ObjectDefnHashTests, test1) {
    rs::scriptobject::test::VectorKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    rs::scriptobject::ScriptObjectHash hash;
    std::fill_n(hash, sizeof(hash), 0);
    
    defn.CalculateHash(hash);
    
    unsigned total = 0;
    for (int i = 0; i < sizeof(hash); ++i) {
        total += hash[i];
    }
    
    ASSERT_NE(0, total);
}

TEST_F(ObjectDefnHashTests, test2) {
    rs::scriptobject::test::VectorKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn1.CalculateHash(hash2);
    
    for (int i = 0; i < sizeof(hash1); ++i) {
        ASSERT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(ObjectDefnHashTests, test3) {
    rs::scriptobject::test::VectorKeysDefn defn1({{ "hello1", rs::scriptobject::ScriptObjectType::String }});
    rs::scriptobject::test::VectorKeysDefn defn2({{ "hello2", rs::scriptobject::ScriptObjectType::String }});
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn2.CalculateHash(hash2);
    
    unsigned total1 = 0, total2 = 0;
    for (int i = 0; i < sizeof(hash1); ++i) {
        total1 += hash1[i];
        total2 += hash2[i];
    }
    
    ASSERT_NE(0, total1);
    ASSERT_NE(0, total2);
    ASSERT_NE(total1, total2);
}

TEST_F(ObjectDefnHashTests, test4) {
    rs::scriptobject::test::VectorKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    rs::scriptobject::test::VectorKeysDefn defn2({{ "hello", rs::scriptobject::ScriptObjectType::Double }});
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn2.CalculateHash(hash2);
    
    unsigned total1 = 0, total2 = 0;
    for (int i = 0; i < sizeof(hash1); ++i) {
        total1 += hash1[i];
        total2 += hash2[i];
    }
    
    ASSERT_NE(0, total1);
    ASSERT_NE(0, total2);
    ASSERT_NE(total1, total2);
}

TEST_F(ObjectDefnHashTests, test5) {
    rs::scriptobject::test::VectorKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }, { "pi", rs::scriptobject::ScriptObjectType::Double }});
    rs::scriptobject::test::VectorKeysDefn defn2({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn2.CalculateHash(hash2);
    
    unsigned total1 = 0, total2 = 0;
    for (int i = 0; i < sizeof(hash1); ++i) {
        total1 += hash1[i];
        total2 += hash2[i];
    }
    
    ASSERT_NE(0, total1);
    ASSERT_NE(0, total2);
    ASSERT_NE(total1, total2);
}

TEST_F(ObjectDefnHashTests, test6) {
    rs::scriptobject::test::VectorKeysDefn defn({
        { "0", rs::scriptobject::ScriptObjectType::String },
        { "1", rs::scriptobject::ScriptObjectType::String },
        { "2", rs::scriptobject::ScriptObjectType::String },
        { "3", rs::scriptobject::ScriptObjectType::String },
        { "4", rs::scriptobject::ScriptObjectType::Object },
        { "5", rs::scriptobject::ScriptObjectType::String },
        { "6", rs::scriptobject::ScriptObjectType::Double },
        { "7", rs::scriptobject::ScriptObjectType::String },
        { "8", rs::scriptobject::ScriptObjectType::String },
        { "9", rs::scriptobject::ScriptObjectType::Int32 },
        { "10", rs::scriptobject::ScriptObjectType::String },
        { "11", rs::scriptobject::ScriptObjectType::String },
        { "12", rs::scriptobject::ScriptObjectType::Null },
        { "13", rs::scriptobject::ScriptObjectType::String },
        { "14", rs::scriptobject::ScriptObjectType::String },
        { "15", rs::scriptobject::ScriptObjectType::Array },
        { "16", rs::scriptobject::ScriptObjectType::String },
        { "17", rs::scriptobject::ScriptObjectType::Object },
        { "18", rs::scriptobject::ScriptObjectType::String },
        { "19", rs::scriptobject::ScriptObjectType::String },
    });
    
    rs::scriptobject::ScriptObjectHash hash;
    std::fill_n(hash, sizeof(hash), 0);
    
    defn.CalculateHash(hash);
    
    unsigned total = 0;
    for (int i = 0; i < sizeof(hash); ++i) {
        total += hash[i];
    }
    
    ASSERT_NE(0, total);
}

TEST_F(ObjectDefnHashTests, test7) {
    rs::scriptobject::test::VectorKeysDefn defn1({
        { "0", rs::scriptobject::ScriptObjectType::String },
        { "1", rs::scriptobject::ScriptObjectType::String },
        { "2", rs::scriptobject::ScriptObjectType::String },
        { "3", rs::scriptobject::ScriptObjectType::String },
        { "4", rs::scriptobject::ScriptObjectType::Object },
        { "5", rs::scriptobject::ScriptObjectType::String },
        { "6", rs::scriptobject::ScriptObjectType::Double },
        { "7", rs::scriptobject::ScriptObjectType::String },
        { "8", rs::scriptobject::ScriptObjectType::String },
        { "9", rs::scriptobject::ScriptObjectType::Int32 },
        { "10", rs::scriptobject::ScriptObjectType::String },
        { "11", rs::scriptobject::ScriptObjectType::String },
        { "12", rs::scriptobject::ScriptObjectType::Null },
        { "13", rs::scriptobject::ScriptObjectType::String },
        { "14", rs::scriptobject::ScriptObjectType::String },
        { "15", rs::scriptobject::ScriptObjectType::Array },
        { "16", rs::scriptobject::ScriptObjectType::String },
        { "17", rs::scriptobject::ScriptObjectType::Object },
        { "18", rs::scriptobject::ScriptObjectType::String },
        { "19", rs::scriptobject::ScriptObjectType::String }
    });
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn1.CalculateHash(hash2);
    
    for (int i = 0; i < sizeof(hash1); ++i) {
        ASSERT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(ObjectDefnHashTests, test8) {
    rs::scriptobject::test::VectorKeysDefn defn1({
        { "0", rs::scriptobject::ScriptObjectType::String },
        { "1", rs::scriptobject::ScriptObjectType::String },
        { "2", rs::scriptobject::ScriptObjectType::String },
        { "3", rs::scriptobject::ScriptObjectType::String },
        { "4", rs::scriptobject::ScriptObjectType::Object },
        { "5", rs::scriptobject::ScriptObjectType::String },
        { "6", rs::scriptobject::ScriptObjectType::Double },
        { "7", rs::scriptobject::ScriptObjectType::String },
        { "8", rs::scriptobject::ScriptObjectType::String },
        { "9", rs::scriptobject::ScriptObjectType::Int32 },
        { "10", rs::scriptobject::ScriptObjectType::String },
        { "11", rs::scriptobject::ScriptObjectType::String },
        { "12", rs::scriptobject::ScriptObjectType::Null },
        { "13", rs::scriptobject::ScriptObjectType::String },
        { "14", rs::scriptobject::ScriptObjectType::String },
        { "15", rs::scriptobject::ScriptObjectType::Array },
        { "16", rs::scriptobject::ScriptObjectType::String },
        { "17", rs::scriptobject::ScriptObjectType::Object },
        { "18", rs::scriptobject::ScriptObjectType::String },
        { "19", rs::scriptobject::ScriptObjectType::String }
    });
    
    rs::scriptobject::test::VectorKeysDefn defn2({
        { "0", rs::scriptobject::ScriptObjectType::String },
        { "1", rs::scriptobject::ScriptObjectType::String },
        { "2", rs::scriptobject::ScriptObjectType::String },
        { "3", rs::scriptobject::ScriptObjectType::String },
        { "4", rs::scriptobject::ScriptObjectType::Object },
        { "5", rs::scriptobject::ScriptObjectType::String },
        { "6", rs::scriptobject::ScriptObjectType::Double },
        { "7", rs::scriptobject::ScriptObjectType::String },
        { "8", rs::scriptobject::ScriptObjectType::String },
        { "9", rs::scriptobject::ScriptObjectType::Int32 },
        { "10", rs::scriptobject::ScriptObjectType::String },
        { "11", rs::scriptobject::ScriptObjectType::String },
        { "12", rs::scriptobject::ScriptObjectType::Null },
        { "13", rs::scriptobject::ScriptObjectType::String },
        { "14", rs::scriptobject::ScriptObjectType::String },
        { "15", rs::scriptobject::ScriptObjectType::Array },
        { "16", rs::scriptobject::ScriptObjectType::String },
        { "17", rs::scriptobject::ScriptObjectType::Object },
        { "18", rs::scriptobject::ScriptObjectType::String },
        { "_19", rs::scriptobject::ScriptObjectType::Null }
    });
    
    rs::scriptobject::ScriptObjectHash hash1;
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    rs::scriptobject::ScriptObjectHash hash2;
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn2.CalculateHash(hash2);
    
    unsigned total1 = 0, total2 = 0;
    for (int i = 0; i < sizeof(hash1); ++i) {
        total1 += hash1[i];
        total2 += hash2[i];
    }
    
    ASSERT_NE(0, total2);
    ASSERT_NE(0, total2);
    ASSERT_NE(total1, total2);
}

TEST_F(ObjectDefnHashTests, test9) {
    rs::scriptobject::test::VectorDefn vect;
    for (int i = 0; i < 1024; ++i) {        
        vect.push_back({ std::to_string(i), rs::scriptobject::ScriptObjectType::String });
    }
    
    rs::scriptobject::test::VectorKeysDefn defn(vect);
    
    rs::scriptobject::ScriptObjectHash hash;
    std::fill_n(hash, sizeof(hash), 0);
    
    defn.CalculateHash(hash);
    
    unsigned total = 0;
    for (int i = 0; i < sizeof(hash); ++i) {
        total += hash[i];
    }
    
    ASSERT_NE(0, total);
}