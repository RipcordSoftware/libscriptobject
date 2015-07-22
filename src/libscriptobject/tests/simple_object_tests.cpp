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
#include "../script_object_keys_cache.h"

class SimpleObjectTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        rs::scriptobject::ScriptObjectKeysCache::Flush();
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(SimpleObjectTests, test0) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({});
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(0, object->getCount());
}

TEST_F(SimpleObjectTests, test1) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),        
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),        
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
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
    
    ASSERT_THROW({
        object->getObject("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getArray("xyz");
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),        
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
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
        object->getObject("wet");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getArray("wet");
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
        object->getObject("hello");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getArray("hello");
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
        object->getObject("the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getArray("the_answer");
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
        object->getObject("sunny");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getArray("sunny");
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
        object->getArray(0);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject(0);
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
        object->getArray(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject(1);
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
        object->getArray(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject(2);
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
    
    ASSERT_THROW({
        object->getArray(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject(3);
    }, rs::scriptobject::TypeCastException);
}

TEST_F(SimpleObjectTests, test9) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))        
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
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("bad", rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::MAX)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))        
    });
    
    ASSERT_THROW({
        rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    }, rs::scriptobject::UnknownSourceFieldTypeException);
}

TEST_F(SimpleObjectTests, test11) {
    rs::scriptobject::utils::ObjectVector vect;
    rs::scriptobject::ScriptObjectType types[] = { rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectType::Double, rs::scriptobject::ScriptObjectType::Int32 };
    
    for (int i = 0; i < 1024; ++i) {
        auto type = types[i % (sizeof(types) / sizeof(types[0]))];
        
        switch (type) {
            case rs::scriptobject::ScriptObjectType::String:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue(std::to_string(i).c_str())));
                break;
            case rs::scriptobject::ScriptObjectType::Double:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue(((double)i) / 1000)));
                break;
            case rs::scriptobject::ScriptObjectType::Int32:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue(i)));
                break;
        }
    }
    
    rs::scriptobject::utils::ScriptObjectVectorSource source(vect);        
    
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
                ASSERT_EQ(std::get<1>(vect[i]).getInt32(), object->getInt32(i));
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
    rs::scriptobject::utils::ScriptObjectVectorSource child({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(child);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("child", childObject)
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
    rs::scriptobject::utils::ScriptArrayVectorSource arrayDefn({
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(arrayDefn);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("array", array)
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(1, object->getCount());
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Array, object->getType("array"));    
    ASSERT_TRUE(!!object->getArray(0));
    ASSERT_TRUE(!!object->getArray("array"));
}

TEST_F(SimpleObjectTests, test14) {
     rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });        
    
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn);    
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn);    
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn);    
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn);    
    
    ASSERT_EQ(1, rs::scriptobject::ScriptObjectKeysCache::getCount());
}

TEST_F(SimpleObjectTests, test15) {
     rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });        
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
    });
    
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(2, rs::scriptobject::ScriptObjectKeysCache::getCount());
}

TEST_F(SimpleObjectTests, test16) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
}

TEST_F(SimpleObjectTests, test17) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
}

TEST_F(SimpleObjectTests, test18) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });    
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object1);
    
    ASSERT_EQ(object1.get(), targetObject.get());   
}

TEST_F(SimpleObjectTests, test19) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(0.0f)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(0)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true))    
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(42, targetObject->getInt32(key6.index));
}

TEST_F(SimpleObjectTests, test20) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(42, targetObject->getInt32(key6.index));
}

TEST_F(SimpleObjectTests, test21) {
    rs::scriptobject::utils::ScriptObjectVectorSource child({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(child);        
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("child", childObject)
    });
    
    rs::scriptobject::utils::ScriptArrayVectorSource arrayDefn({
        rs::scriptobject::utils::VectorValue(3.14159)
    });
    
    auto array = rs::scriptobject::ScriptArrayFactory::CreateArray(arrayDefn);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("array", array)
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2);
    
    ASSERT_EQ(4, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("child", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Object, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("array", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Array, key4.type);
}

TEST_F(SimpleObjectTests, test22) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(1, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(0, key2.index);
}

TEST_F(SimpleObjectTests, test23) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(1, key2.index);
}

TEST_F(SimpleObjectTests, test24) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(3, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(0, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(1, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_EQ(4, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_EQ(5, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(2, key6.index);
}

TEST_F(SimpleObjectTests, test25) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(5, key6.index);
}

TEST_F(SimpleObjectTests, test26) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(0.0f)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(0)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true))    
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(42, targetObject->getInt32(key6.index));
    ASSERT_EQ(5, key6.index);
}

TEST_F(SimpleObjectTests, test27) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(0.0f)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(0)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true))    
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->keys->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->keys->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->keys->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->keys->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->keys->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->keys->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key6.type);
    ASSERT_EQ(42, targetObject->getInt32(key6.index));
    ASSERT_EQ(5, key6.index);
}

TEST_F(SimpleObjectTests, test28) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum"))        
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(4, object->getStringFieldLength(0));
    ASSERT_EQ(6, object->getStringFieldLength(1));
    ASSERT_EQ(12, object->getStringFieldLength(2));
}

TEST_F(SimpleObjectTests, test29) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(12, object->getStringFieldLength(0));
    ASSERT_EQ(6, object->getStringFieldLength(1));
    ASSERT_EQ(4, object->getStringFieldLength(2));
}

TEST_F(SimpleObjectTests, test30) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(12, object->getStringFieldLength(1));
    ASSERT_EQ(6, object->getStringFieldLength(3));
    ASSERT_EQ(4, object->getStringFieldLength(5));
}

TEST_F(SimpleObjectTests, test31) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(4, object->getStringFieldLength(0));
    
    ASSERT_THROW({
        object->getStringFieldLength(1);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getStringFieldLength(10);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}

TEST_F(SimpleObjectTests, test32) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum"))        
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(4, object->getStringFieldLength("abc"));
    ASSERT_EQ(6, object->getStringFieldLength("hello"));
    ASSERT_EQ(12, object->getStringFieldLength("text"));
}

TEST_F(SimpleObjectTests, test33) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(4, object->getStringFieldLength("abc"));
    ASSERT_EQ(6, object->getStringFieldLength("hello"));
    ASSERT_EQ(12, object->getStringFieldLength("text"));
}

TEST_F(SimpleObjectTests, test34) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(4, object->getStringFieldLength(0));
    
    ASSERT_THROW({
        object->getStringFieldLength("the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getStringFieldLength("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}

TEST_F(SimpleObjectTests, test35) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_TRUE(object->setString(1, "hello world"));
    ASSERT_STREQ("hello world", object->getString(1));
    
    ASSERT_FALSE(object->setString(1, "hello world from mars"));
    ASSERT_STREQ("hello world", object->getString(1));
    
    ASSERT_TRUE(object->setString("text", "welcome"));
    ASSERT_STREQ("welcome", object->getString("text"));
    
    ASSERT_FALSE(object->setString("text", "hello world from mars"));
    ASSERT_STREQ("welcome", object->getString("text"));
    
    ASSERT_THROW({
        object->setString("the_answer", "once more into the ....");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->setString("xyz", "the bomb");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}