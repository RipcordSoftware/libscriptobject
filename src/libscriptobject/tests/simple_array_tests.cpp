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
    rs::scriptobject::test::ScriptArrayVectorSource defn({});
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(0, array->getCount());
}

TEST_F(SimpleArrayTests, test1) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue("world")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
}

TEST_F(SimpleArrayTests, test2) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue("ipsum")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("ipsum", array->getString(1));
}

TEST_F(SimpleArrayTests, test3) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(3.14159)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(0));
    ASSERT_STREQ("world", array->getString(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, array->getType(1));
    ASSERT_FLOAT_EQ(3.14159, array->getDouble(1));
}

TEST_F(SimpleArrayTests, test4) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(false),
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(true)
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
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(false),
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(true),
        rs::scriptobject::test::VectorValue(42)
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
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(false),        
        rs::scriptobject::test::VectorValue(true),
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(42)
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
}

TEST_F(SimpleArrayTests, test7) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(false),
        rs::scriptobject::test::VectorValue(true),
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(42)
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
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(false),        
        rs::scriptobject::test::VectorValue(true),
        rs::scriptobject::test::VectorValue("world"),
        rs::scriptobject::test::VectorValue(42)
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
        array->getDouble(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getInt32(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getString(1);
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
        array->getDouble(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getString(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        array->getBoolean(3);
    }, rs::scriptobject::TypeCastException);                
}

TEST_F(SimpleArrayTests, test9) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(),
        rs::scriptobject::test::VectorValue("world")
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, array->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, array->getType(1));
    ASSERT_STREQ("world", array->getString(1));
}

TEST_F(SimpleArrayTests, test10) {
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        rs::scriptobject::test::VectorValue(rs::scriptobject::ScriptObjectType::MAX),
        rs::scriptobject::test::VectorValue("world")
    });
    
    ASSERT_THROW({
        rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    }, rs::scriptobject::UnknownSourceFieldTypeException);
}

TEST_F(SimpleArrayTests, test13) {
    rs::scriptobject::test::ScriptArrayVectorSource childDefn({
        rs::scriptobject::test::VectorValue(3.14159)
    });
    
    auto childArray = rs::scriptobject::ScriptArrayFactory::CreateArray(childDefn);
    
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        childArray
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(1, array->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, array->getType(0));
    ASSERT_TRUE(!!array->getArray(0));
}

TEST_F(SimpleArrayTests, test14) {
    rs::scriptobject::test::ScriptObjectVectorSource childDefn({
        std::make_tuple("pi", rs::scriptobject::test::VectorValue(3.14159))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(childDefn);
    
    rs::scriptobject::test::ScriptArrayVectorSource defn({
        childObject
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(defn);
    ASSERT_EQ(1, array->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, array->getType(0));
    ASSERT_TRUE(!!array->getObject(0));
}