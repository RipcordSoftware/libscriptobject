#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "../libscriptobject.h"
#include "../script_object_vector_source.h"
#include "../script_array_vector_source.h"

class SimpleObjectTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(SimpleObjectTests, test0) {
    rs::scriptobject::test::ScriptObjectVectorSource defn({});
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(0, object->getCount());
}

TEST_F(SimpleObjectTests, test1) {
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world"))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("lorem", rs::scriptobject::test::VectorValue("ipsum"))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("pi", rs::scriptobject::test::VectorValue(3.14159))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("wet", rs::scriptobject::test::VectorValue(false)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("sunny", rs::scriptobject::test::VectorValue(true))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("wet", rs::scriptobject::test::VectorValue(false)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("sunny", rs::scriptobject::test::VectorValue(true)),
        std::make_tuple("the_answer", rs::scriptobject::test::VectorValue(42))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("wet", rs::scriptobject::test::VectorValue(false)),        
        std::make_tuple("sunny", rs::scriptobject::test::VectorValue(true)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("the_answer", rs::scriptobject::test::VectorValue(42))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("wet", rs::scriptobject::test::VectorValue(false)),        
        std::make_tuple("sunny", rs::scriptobject::test::VectorValue(true)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("the_answer", rs::scriptobject::test::VectorValue(42))
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
    
    ASSERT_THROW({
        object->getObject(-199);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getArray(111);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, object->getType(345));
}

TEST_F(SimpleObjectTests, test8) {
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("wet", rs::scriptobject::test::VectorValue(false)),        
        std::make_tuple("sunny", rs::scriptobject::test::VectorValue(true)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world")),
        std::make_tuple("the_answer", rs::scriptobject::test::VectorValue(42))
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("nil", rs::scriptobject::test::VectorValue()),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world"))        
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
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("bad", rs::scriptobject::test::VectorValue(rs::scriptobject::ScriptObjectType::MAX)),
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world"))        
    });
    
    ASSERT_THROW({
        rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    }, rs::scriptobject::UnknownSourceFieldTypeException);
}

TEST_F(SimpleObjectTests, test11) {
    rs::scriptobject::test::ObjectVector vect;
    rs::scriptobject::ScriptObjectType types[] = { rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectType::Double, rs::scriptobject::ScriptObjectType::Int32 };
    
    for (int i = 0; i < 1024; ++i) {
        auto type = types[i % (sizeof(types) / sizeof(types[0]))];
        vect.push_back(std::make_tuple(std::to_string(i), rs::scriptobject::test::VectorValue(std::to_string(i).c_str())));
    }
    
    rs::scriptobject::test::ScriptObjectVectorSource source(vect);        
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(source);
    
    ASSERT_EQ(vect.size(), object->getCount());
    
    for (int i = 0; i < vect.size(); ++i) {
        ASSERT_EQ(std::get<1>(vect[i]).getType(), object->getType(i));
        ASSERT_STREQ(std::get<0>(vect[i]).c_str(), object->getName(i));
        
        switch (std::get<1>(vect[i]).getType()) {
            case rs::scriptobject::ScriptObjectType::String:
                ASSERT_STREQ(std::get<1>(vect[i]).getString(), object->getString(i));
                break;
            case rs::scriptobject::ScriptObjectType::Double:                
                ASSERT_FLOAT_EQ(std::get<1>(vect[i]).getDouble(), object->getDouble(i));
                break;
            case rs::scriptobject::ScriptObjectType::Int32:                
                ASSERT_FLOAT_EQ(std::get<1>(vect[i]).getInt32(), object->getInt32(i));
                break;
        }
    }
    
    for (int i = 0; i < vect.size(); ++i) {
        auto name = std::get<0>(vect[i]).c_str();
        auto type = std::get<1>(vect[i]).getType();
        
        ASSERT_EQ(type, object->getType(name));
        
        switch (type) {
            case rs::scriptobject::ScriptObjectType::String:
                ASSERT_STREQ(std::get<1>(vect[i]).getString(), object->getString(name));
                break;
            case rs::scriptobject::ScriptObjectType::Double:                
                ASSERT_FLOAT_EQ(std::get<1>(vect[i]).getDouble(), object->getDouble(name));
                break;
            case rs::scriptobject::ScriptObjectType::Int32:                
                ASSERT_FLOAT_EQ(std::get<1>(vect[i]).getInt32(), object->getInt32(name));
                break;
        }
    }
}

TEST_F(SimpleObjectTests, test12) {
    rs::scriptobject::test::ScriptObjectVectorSource child({
        std::make_tuple("hello", rs::scriptobject::test::VectorValue("world"))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(child);
    
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("child", childObject)
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(1, object->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, object->getType("child"));
    
    {
        auto childObj = object->getObject(0);
        ASSERT_TRUE(!!childObj);

        ASSERT_EQ(1, childObj->getCount());
        ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, childObj->getType(0));
        ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, childObj->getType("hello"));
        ASSERT_STREQ("world", childObj->getString("hello"));
    }
    
    {
        auto childObj = object->getObject("child");
        ASSERT_TRUE(!!childObj);
        
        ASSERT_EQ(1, childObj->getCount());
        ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, childObj->getType(0));
        ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, childObj->getType("hello"));
        ASSERT_STREQ("world", childObj->getString("hello"));        
    }
}

TEST_F(SimpleObjectTests, test13) {
    rs::scriptobject::test::ScriptArrayVectorSource arrayDefn({
        rs::scriptobject::test::VectorValue(3.14159)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(arrayDefn);
    
    rs::scriptobject::test::ScriptObjectVectorSource defn({
        std::make_tuple("array", array)
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(1, object->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, object->getType("array"));    
    ASSERT_TRUE(!!object->getArray(0));
    ASSERT_TRUE(!!object->getArray("array"));
}