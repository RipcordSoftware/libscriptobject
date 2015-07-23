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

#include "../libscriptobject.h"
#include "../script_object_vector_source.h"
#include "../script_array_vector_source.h"

class SimpleArrayTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(SimpleArrayTests, test0) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({});
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(0, array->getCount());
}

TEST_F(SimpleArrayTests, test1) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
}

TEST_F(SimpleArrayTests, test2) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue("ipsum")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("ipsum", array->getString(1));
}

TEST_F(SimpleArrayTests, test3) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, array->getType(1));
    ASSERT_FLOAT_EQ(3.14159, array->getDouble(1));
}

TEST_F(SimpleArrayTests, test4) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(false),
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(true)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(0));
    ASSERT_FALSE(array->getBoolean(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("world", array->getString(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(2));
    ASSERT_TRUE(array->getBoolean(2));
}

TEST_F(SimpleArrayTests, test5) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(false),
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(true),
        rs::scriptobject::utils::VectorValue(42)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(0));
    ASSERT_FALSE(array->getBoolean(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("world", array->getString(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(2));
    ASSERT_TRUE(array->getBoolean(2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, array->getType(3));
    ASSERT_EQ(42, array->getInt32(3));
}

TEST_F(SimpleArrayTests, test6) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(false),        
        rs::scriptobject::utils::VectorValue(true),
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(42),
        rs::scriptobject::utils::VectorValue(),
        rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::Undefined)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(0));
    ASSERT_FALSE(array->getBoolean(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, array->getType(1));
    ASSERT_TRUE(array->getBoolean(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(2));
    ASSERT_STREQ("world", array->getString(2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, array->getType(3));
    ASSERT_EQ(42, array->getInt32(3));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, array->getType(4));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Undefined, array->getType(5));
}

TEST_F(SimpleArrayTests, test7) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(false),
        rs::scriptobject::utils::VectorValue(true),
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(42)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_THROW({
        array->getBoolean(10);
    }, rs::scriptobject::UnknownScriptArrayIndexException);    
    
    ASSERT_THROW({
        array->getString(200);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
    
    ASSERT_THROW({
        array->getInt32(5000);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
    
    ASSERT_THROW({
        array->getDouble(-99);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
    
    ASSERT_THROW({
        array->getObject(-199);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
    
    ASSERT_THROW({
        array->getArray(111);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
    
    ASSERT_THROW({
        array->getType(345);
    }, rs::scriptobject::UnknownScriptArrayIndexException);
}

TEST_F(SimpleArrayTests, test8) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(false),        
        rs::scriptobject::utils::VectorValue(true),
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(42)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_THROW({
        array->getDouble(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getString(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getInt32(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getArray(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getObject(0);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        array->getDouble(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getInt32(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getString(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getArray(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getObject(1);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        array->getDouble(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getInt32(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getBoolean(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getArray(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getObject(2);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        array->getDouble(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getString(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getBoolean(3);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        array->getArray(3);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        array->getObject(3);
    }, rs::scriptobject::TypeCastException);
}

TEST_F(SimpleArrayTests, test9) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(),
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, array->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("world", array->getString(1));
}

TEST_F(SimpleArrayTests, test10) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::MAX),
        rs::scriptobject::utils::VectorValue("world")
    });
    
    ASSERT_THROW({
        rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    }, rs::scriptobject::UnknownSourceFieldTypeException);
}

TEST_F(SimpleArrayTests, test11) {
    rs::scriptobject::utils::ArrayVector vect;
    rs::scriptobject::ScriptObjectType types[] = { rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectType::Double, rs::scriptobject::ScriptObjectType::Int32 };
    
    for (int i = 0; i < 1024; ++i) {
        auto type = types[i % (sizeof(types) / sizeof(types[0]))];
        switch (type) {
            case rs::scriptobject::ScriptObjectType::String:
                vect.push_back(std::to_string(i).c_str());
                break;
            case rs::scriptobject::ScriptObjectType::Double:
                vect.push_back(((double)i)/1000);
                break;
            case rs::scriptobject::ScriptObjectType::Int32:
                vect.push_back(i);
                break;
        }                
    }
    
    rs::scriptobject::utils::ScriptArrayVectorSource source(vect);        
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(source);
    
    ASSERT_EQ(vect.size(), array->getCount());
    
    for (int i = 0; i < vect.size(); ++i) {
        ASSERT_EQ(vect[i].getType(), array->getType(i));
        
        switch (vect[i].getType()) {
            case rs::scriptobject::ScriptObjectType::String:
                ASSERT_STREQ(vect[i].getString(), array->getString(i));
                break;
            case rs::scriptobject::ScriptObjectType::Double:                
                ASSERT_FLOAT_EQ(vect[i].getDouble(), array->getDouble(i));
                break;
            case rs::scriptobject::ScriptObjectType::Int32:                
                ASSERT_EQ(vect[i].getInt32(), array->getInt32(i));
                break;
        }
    }    
}

TEST_F(SimpleArrayTests, test12) {
    rs::scriptobject::utils::ScriptArrayVectorSource childDefn({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray = rs::scriptobject::ScriptArrayFactory::CreateArray(childDefn);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue(childArray)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(1, array->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, array->getType(0));
    
    auto child = array->getArray(0);
    ASSERT_TRUE(!!child);

    ASSERT_EQ(1, child->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, child->getType(0));
    ASSERT_STREQ("world", child->getString(0));
}

TEST_F(SimpleArrayTests, test13) {
    rs::scriptobject::utils::ScriptArrayVectorSource childDefn({
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    auto childArray = rs::scriptobject::ScriptArrayFactory::CreateArray(childDefn);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        childArray
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(1, array->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, array->getType(0));
    ASSERT_TRUE(!!array->getArray(0));
}

TEST_F(SimpleArrayTests, test14) {
    rs::scriptobject::utils::ScriptObjectVectorSource childDefn({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(childDefn);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        childObject
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(1, array->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, array->getType(0));
    ASSERT_TRUE(!!array->getObject(0));
}

TEST_F(SimpleArrayTests, test15) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue(42),
        rs::scriptobject::utils::VectorValue(true),
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleArrayTests, test16) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue("hello")
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test17) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(42)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(43)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test18) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(true)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(false)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test19) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(99.0f)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test20) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue()
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::Undefined)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test21) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    rs::scriptobject::ScriptObjectHash digest1;
    array->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2 = { 0x7D, 0x79, 0x30, 0x37, 0xA0, 0x76, 0x01, 0x86, 0x57, 0x4B, 0x02, 0x82, 0xF2, 0xF4, 0x35, 0xE7 };
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleArrayTests, test22) {
    rs::scriptobject::utils::ScriptArrayVectorSource defn({
        rs::scriptobject::utils::VectorValue("world"),
        rs::scriptobject::utils::VectorValue("ipsum")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    rs::scriptobject::ScriptObjectHash digest1;
    array->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2 = { 0x38, 0xF4, 0xD8, 0x6A, 0x43, 0xCE, 0xD2, 0x5A, 0xEB, 0x1C, 0xA9, 0x9C, 0xF4, 0x8A, 0xF3, 0x44 };
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleArrayTests, test23) {
    rs::scriptobject::utils::ScriptObjectVectorSource child({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(child);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(childObject)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(childObject)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleArrayTests, test24) {
    rs::scriptobject::utils::ScriptObjectVectorSource child1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
    });
    
    auto childObject1 = rs::scriptobject::ScriptObjectFactory::CreateObject(child1);
    
    rs::scriptobject::utils::ScriptObjectVectorSource child2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum!!"))
    });
    
    auto childObject2 = rs::scriptobject::ScriptObjectFactory::CreateObject(child2);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(childObject1)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(childObject2)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleArrayTests, test25) {
    rs::scriptobject::utils::ScriptArrayVectorSource child({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray = rs::scriptobject::ScriptArrayFactory::CreateArray(child);
        
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(childArray)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(childArray)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleArrayTests, test26) {
    rs::scriptobject::utils::ScriptArrayVectorSource child1({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray1 = rs::scriptobject::ScriptArrayFactory::CreateArray(child1);
    
    rs::scriptobject::utils::ScriptArrayVectorSource child2({
        rs::scriptobject::utils::VectorValue("world!!!")
    });
    
    auto childArray2 = rs::scriptobject::ScriptArrayFactory::CreateArray(child2);
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn1({
        rs::scriptobject::utils::VectorValue(childArray1)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource defn2({
        rs::scriptobject::utils::VectorValue(childArray2)
    });
    
    auto array1 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn1);    
    rs::scriptobject::ScriptObjectHash digest1;
    array1->CalculateHash(digest1);
    
    auto array2 = rs::scriptobject::ScriptArrayFactory::CreateArray(defn2);
    rs::scriptobject::ScriptObjectHash digest2;
    array2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}