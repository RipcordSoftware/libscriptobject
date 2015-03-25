#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "../libscriptobject.h"
#include "../script_object_vector_source.h"

class SimpleObjectTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(SimpleObjectTests, test0) {
    rs::scriptobject::test::VectorObjectSource defn({});
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(0, object->getCount());
}

TEST_F(SimpleObjectTests, test1) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->keys->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
}

TEST_F(SimpleObjectTests, test2) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("lorem", rs::scriptobject::ScriptObjectType::String, "ipsum")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->keys->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("lorem"));
    ASSERT_STREQ("ipsum", object->getString(1));
    ASSERT_STREQ("ipsum", object->getString("lorem"));
}

TEST_F(SimpleObjectTests, test3) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("pi", rs::scriptobject::ScriptObjectType::Double, "3.14159")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->keys->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, object->getType("pi"));
    ASSERT_FLOAT_EQ(3.14159, object->getDouble(1));
    ASSERT_FLOAT_EQ(3.14159, object->getDouble("pi"));
}

TEST_F(SimpleObjectTests, test4) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("wet", rs::scriptobject::ScriptObjectType::Boolean, "false"),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("sunny", rs::scriptobject::ScriptObjectType::Boolean, "true")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("wet"));
    ASSERT_FALSE(object->getBoolean(0));
    ASSERT_FALSE(object->getBoolean("wet"));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(1));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("sunny"));
    ASSERT_TRUE(object->getBoolean(2));
    ASSERT_TRUE(object->getBoolean("sunny"));    
}

TEST_F(SimpleObjectTests, test5) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("wet", rs::scriptobject::ScriptObjectType::Boolean, "false"),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("sunny", rs::scriptobject::ScriptObjectType::Boolean, "true"),
        std::make_tuple("the_answer", rs::scriptobject::ScriptObjectType::Int32, "42")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("wet"));
    ASSERT_FALSE(object->getBoolean(0));
    ASSERT_FALSE(object->getBoolean("wet"));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(1));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("sunny"));
    ASSERT_TRUE(object->getBoolean(2));
    ASSERT_TRUE(object->getBoolean("sunny"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType(3));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType("the_answer"));
    ASSERT_EQ(42, object->getInt32(3));
    ASSERT_EQ(42, object->getInt32("the_answer"));
}

TEST_F(SimpleObjectTests, test6) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("wet", rs::scriptobject::ScriptObjectType::Boolean, "false"),        
        std::make_tuple("sunny", rs::scriptobject::ScriptObjectType::Boolean, "true"),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("the_answer", rs::scriptobject::ScriptObjectType::Int32, "42")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("wet"));
    ASSERT_FALSE(object->getBoolean(0));
    ASSERT_FALSE(object->getBoolean("wet"));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("sunny"));
    ASSERT_TRUE(object->getBoolean(1));
    ASSERT_TRUE(object->getBoolean("sunny"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(2));
    ASSERT_STREQ("world", object->getString("hello"));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType(3));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType("the_answer"));
    ASSERT_EQ(42, object->getInt32(3));
    ASSERT_EQ(42, object->getInt32("the_answer"));
}

TEST_F(SimpleObjectTests, test7) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("wet", rs::scriptobject::ScriptObjectType::Boolean, "false"),        
        std::make_tuple("sunny", rs::scriptobject::ScriptObjectType::Boolean, "true"),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("the_answer", rs::scriptobject::ScriptObjectType::Int32, "42")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_THROW({
        object->getBoolean("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getString("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getInt32("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getDouble("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);

    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, object->getType("xyz"));
        
    ASSERT_THROW({
        object->getBoolean(10);
    }, rs::scriptobject::UnknownScriptObjectFieldException);    
    
    ASSERT_THROW({
        object->getString(200);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getInt32(5000);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getDouble(-99);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    //ASSERT_THROW({
    //    object->getObject(-199);
    //}, rs::scriptobject::UnknownScriptObjectFieldException);
    
    //ASSERT_THROW({
    //    object->getArray(111);
    //}, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, object->getType(345));
}

TEST_F(SimpleObjectTests, test8) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("wet", rs::scriptobject::ScriptObjectType::Boolean, "false"),        
        std::make_tuple("sunny", rs::scriptobject::ScriptObjectType::Boolean, "true"),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world"),
        std::make_tuple("the_answer", rs::scriptobject::ScriptObjectType::Int32, "42")
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_THROW({
        object->getDouble("wet");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getString("wet");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt32("wet");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getDouble("hello");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean("hello");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt32("hello");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getDouble("the_answer");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString("the_answer");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean("the_answer");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getDouble("sunny");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString("sunny");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt32("sunny");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getDouble(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt32(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getDouble(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt32(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getDouble(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt32(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getDouble(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean(3);
    }, rs::scriptobject::TypeCastException);            
    
}

TEST_F(SimpleObjectTests, test9) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("nil", rs::scriptobject::ScriptObjectType::Null, ""),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world")        
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType("nil"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(1));
    ASSERT_STREQ("world", object->getString("hello"));
}

TEST_F(SimpleObjectTests, test10) {
    rs::scriptobject::test::VectorObjectSource defn({
        std::make_tuple("bad", rs::scriptobject::ScriptObjectType::MAX, ""),
        std::make_tuple("hello", rs::scriptobject::ScriptObjectType::String, "world")        
    });
    
    ASSERT_THROW({
        rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    }, rs::scriptobject::UnknownSourceFieldTypeException);
}