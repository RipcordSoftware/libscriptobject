#include <gtest/gtest.h>

#include <vector>
#include <string>

#include "../libscriptobject.h"

typedef std::vector<std::pair<std::string, rs::scriptobject::ScriptObjectType>> KeysDefn;

class ObjectKeysDefn : public rs::scriptobject::ScriptObjectDefinition {
public:
    ObjectKeysDefn(const KeysDefn& keys) : keys_(keys) {
        
    }
    
    virtual unsigned count() const override { return keys_.size(); }
    virtual const char* name(int index) const override { return keys_[index].first.c_str(); }
    virtual unsigned length(int index) const override { return keys_[index].first.length(); }
    virtual rs::scriptobject::ScriptObjectType type(int index) const override { return keys_[index].second; }
        
private:
    KeysDefn keys_;
};

class ObjectKeysTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(ObjectKeysTests, test1) {
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));        
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 1));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 1));
}

TEST_F(ObjectKeysTests, test1b) {
    ObjectKeysDefn defn{{}};
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(0, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));            
}

TEST_F(ObjectKeysTests, test2) {    
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }, { "world", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(2, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 1));
    ASSERT_STRCASEEQ("world", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 1));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 2));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 2));
}

TEST_F(ObjectKeysTests, test3) {    
    ObjectKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 1));
    ASSERT_STRCASEEQ("world", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 1));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 2));
    ASSERT_STRCASEEQ("pi", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 2));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 3));
    ASSERT_STRCASEEQ("child", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 3));
}

TEST_F(ObjectKeysTests, test4) {    
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "hello", key));
    ASSERT_EQ(0, key.index);
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
}

TEST_F(ObjectKeysTests, test4b) {
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(1, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "hellox", key));
}

TEST_F(ObjectKeysTests, test5) {
    ObjectKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String },
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Object, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~0));
    ASSERT_STRCASEEQ("child", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~1));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~1));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~2));
    ASSERT_STRCASEEQ("pi", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~2));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~3));
    ASSERT_STRCASEEQ("world", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~3));
}

TEST_F(ObjectKeysTests, test5b) {
    ObjectKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String },
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~10));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~10));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~100));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~100));    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~200));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~2000));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Unknown, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, ~300));
    ASSERT_STRCASEEQ(nullptr, rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, ~3000));
}

TEST_F(ObjectKeysTests, test6) {
    ObjectKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "helloa", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "hellox", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "worlda", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "worldx", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "pia", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "pix", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "childa", key));
    ASSERT_FALSE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "childx", key));
}

TEST_F(ObjectKeysTests, test7) {
    ObjectKeysDefn defn({
        { "hello", rs::scriptobject::ScriptObjectType::String }, 
        { "world", rs::scriptobject::ScriptObjectType::String },
        { "pi", rs::scriptobject::ScriptObjectType::Double },
        { "child", rs::scriptobject::ScriptObjectType::Object }
    });
    
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(4, keys->count);
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "hello", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
    ASSERT_TRUE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "world", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key.type);
    ASSERT_TRUE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "pi", key));    
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key.type);
    ASSERT_TRUE(rs::scriptobject::ScriptObjectKeys::getKey(*keys, "child", key));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Object, key.type);
}