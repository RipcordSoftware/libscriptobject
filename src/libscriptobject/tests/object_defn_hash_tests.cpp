#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <algorithm>

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

class ObjectDefnHashTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(ObjectDefnHashTests, test1) {
    ObjectKeysDefn defn({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    unsigned char hash[16];
    std::fill_n(hash, sizeof(hash), 0);
    
    defn.CalculateHash(hash);
    
    unsigned total = 0;
    for (int i = 0; i < sizeof(hash); ++i) {
        total += hash[i];
    }
    
    ASSERT_NE(0, total);
}

TEST_F(ObjectDefnHashTests, test2) {
    ObjectKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn1.CalculateHash(hash2);
    
    for (int i = 0; i < sizeof(hash1); ++i) {
        ASSERT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(ObjectDefnHashTests, test3) {
    ObjectKeysDefn defn1({{ "hello1", rs::scriptobject::ScriptObjectType::String }});
    ObjectKeysDefn defn2({{ "hello2", rs::scriptobject::ScriptObjectType::String }});
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
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
    ObjectKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    ObjectKeysDefn defn2({{ "hello", rs::scriptobject::ScriptObjectType::Double }});
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
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
    ObjectKeysDefn defn1({{ "hello", rs::scriptobject::ScriptObjectType::String }, { "pi", rs::scriptobject::ScriptObjectType::Double }});
    ObjectKeysDefn defn2({{ "hello", rs::scriptobject::ScriptObjectType::String }});
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
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
    ObjectKeysDefn defn({
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
    
    unsigned char hash[16];
    std::fill_n(hash, sizeof(hash), 0);
    
    defn.CalculateHash(hash);
    
    unsigned total = 0;
    for (int i = 0; i < sizeof(hash); ++i) {
        total += hash[i];
    }
    
    ASSERT_NE(0, total);
}

TEST_F(ObjectDefnHashTests, test7) {
    ObjectKeysDefn defn1({
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
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
    std::fill_n(hash2, sizeof(hash2), 0);        
    
    defn1.CalculateHash(hash2);
    
    for (int i = 0; i < sizeof(hash1); ++i) {
        ASSERT_EQ(hash1[i], hash2[i]);
    }
}

TEST_F(ObjectDefnHashTests, test8) {
    ObjectKeysDefn defn1({
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
    
    ObjectKeysDefn defn2({
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
    
    unsigned char hash1[16];
    std::fill_n(hash1, sizeof(hash1), 0);
    
    defn1.CalculateHash(hash1);
    
    unsigned char hash2[16];
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