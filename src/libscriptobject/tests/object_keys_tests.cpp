#include <gtest/gtest.h>

#include <thread>
#include <vector>
#include <string>

#include "../script_object_keys.h"

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
}

TEST_F(ObjectKeysTests, test2) {    
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }, { "world", rs::scriptobject::ScriptObjectType::String }});
    auto keys = rs::scriptobject::ScriptObjectKeysFactory::CreateKeys(defn);
    
    ASSERT_EQ(2, keys->count);
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 0));
    ASSERT_STRCASEEQ("hello", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 0));        
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectKeys::getKeyType(*keys, 1));
    ASSERT_STRCASEEQ("world", rs::scriptobject::ScriptObjectKeys::getKeyName(*keys, 1));        
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