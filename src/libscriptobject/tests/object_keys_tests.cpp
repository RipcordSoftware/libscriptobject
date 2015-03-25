#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "../libscriptobject.h"
#include "../script_object_vector_definition.h"

class ObjectKeysTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(ObjectKeysTests, test1) {
    rs::scriptobject::test::VectorKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(0));
    ASSERT_STREQ("hello", keys->getKeyName(0));        
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(1));
    ASSERT_STREQ(nullptr, keys->getKeyName(1));
}

TEST_F(ObjectKeysTests, test1b) {
    rs::scriptobject::test::VectorKeysDefn defn{{}};
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(0, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(0));
    ASSERT_STREQ(nullptr, keys->getKeyName(0));            
}

TEST_F(ObjectKeysTests, test2) {    
    rs::scriptobject::test::VectorKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }, { "world", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(2, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(0));
    ASSERT_STREQ("hello", keys->getKeyName(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(1));
    ASSERT_STREQ("world", keys->getKeyName(1));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(2));
    ASSERT_STREQ(nullptr, keys->getKeyName(2));
}

TEST_F(ObjectKeysTests, test3) {    
    rs::scriptobject::test::VectorKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(0));
    ASSERT_STREQ("hello", keys->getKeyName(0));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(1));
    ASSERT_STREQ("world", keys->getKeyName(1));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, keys->getKeyType(2));
    ASSERT_STREQ("pi", keys->getKeyName(2));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, keys->getKeyType(3));
    ASSERT_STREQ("child", keys->getKeyName(3));
}

TEST_F(ObjectKeysTests, test4) {    
    rs::scriptobject::test::VectorKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(0));
    ASSERT_STREQ("hello", keys->getKeyName(0));
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(keys->getKey("hello", key));
    ASSERT_EQ(0, key.index);
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
}

TEST_F(ObjectKeysTests, test4b) {
    rs::scriptobject::test::VectorKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(0));
    ASSERT_STREQ("hello", keys->getKeyName(0));
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_FALSE(keys->getKey("hellox", key));
}

TEST_F(ObjectKeysTests, test5) {
    rs::scriptobject::test::VectorKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String },
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, keys->getKeyType(~0));
    ASSERT_STREQ("child", keys->getKeyName(~0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(~1));
    ASSERT_STREQ("hello", keys->getKeyName(~1));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, keys->getKeyType(~2));
    ASSERT_STREQ("pi", keys->getKeyName(~2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, keys->getKeyType(~3));
    ASSERT_STREQ("world", keys->getKeyName(~3));
}

TEST_F(ObjectKeysTests, test5b) {
    rs::scriptobject::test::VectorKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String },
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(~10));
    ASSERT_STREQ(nullptr, keys->getKeyName(~10));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(~100));
    ASSERT_STREQ(nullptr, keys->getKeyName(~100));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(~200));
    ASSERT_STREQ(nullptr, keys->getKeyName(~2000));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, keys->getKeyType(~300));
    ASSERT_STREQ(nullptr, keys->getKeyName(~3000));
}

TEST_F(ObjectKeysTests, test6) {
    rs::scriptobject::test::VectorKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_FALSE(keys->getKey("helloa", key));
    ASSERT_FALSE(keys->getKey("hellox", key));
    ASSERT_FALSE(keys->getKey("worlda", key));
    ASSERT_FALSE(keys->getKey("worldx", key));
    ASSERT_FALSE(keys->getKey("pia", key));
    ASSERT_FALSE(keys->getKey("pix", key));
    ASSERT_FALSE(keys->getKey("childa", key));
    ASSERT_FALSE(keys->getKey("childx", key));
}

TEST_F(ObjectKeysTests, test7) {
    rs::scriptobject::test::VectorKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(keys->getKey("hello", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
    ASSERT_TRUE(keys->getKey("world", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
    ASSERT_TRUE(keys->getKey("pi", key));    
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key.type);
    ASSERT_TRUE(keys->getKey("child", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Object, key.type);
}