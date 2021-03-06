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
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(0), object->getSize());
}

TEST_F(SimpleObjectTests, test1) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->getKeys()->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - 6);
}

TEST_F(SimpleObjectTests, test2) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->getKeys()->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("lorem"));
    ASSERT_STREQ("ipsum", object->getString(1));
    ASSERT_STREQ("ipsum", object->getString("lorem"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(2), object->getSize() - 6 - 6);
}

TEST_F(SimpleObjectTests, test3) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectKey key;
    ASSERT_TRUE(object->getKeys()->getKey("hello", key));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello"));
    ASSERT_STREQ("world", object->getString(0));
    ASSERT_STREQ("world", object->getString("hello"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, object->getType(1));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, object->getType("pi"));
    ASSERT_FLOAT_EQ(3.14159, object->getDouble(1));
    ASSERT_FLOAT_EQ(3.14159, object->getDouble("pi"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(2), object->getSize() - 6 - sizeof(double));
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
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(3), object->getSize() - 6);
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
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(4), object->getSize() - 6 - sizeof(std::int32_t));
}

TEST_F(SimpleObjectTests, test6) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),        
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("divByZero", rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::Undefined))
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
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType(4));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType("nil"));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Undefined, object->getType(5));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Undefined, object->getType("divByZero"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(6), object->getSize() - 6 - sizeof(std::int32_t));
}

TEST_F(SimpleObjectTests, test6b) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType("not_the_answer"));
    ASSERT_EQ(-42, object->getInt32(0));
    ASSERT_EQ(-42, object->getInt32("not_the_answer"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - sizeof(std::int32_t));
}

TEST_F(SimpleObjectTests, test6c) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::UInt32, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::UInt32, object->getType("the_answer"));
    ASSERT_EQ(42, object->getUInt32(0));
    ASSERT_EQ(42, object->getUInt32("the_answer"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - sizeof(std::uint32_t));
}

TEST_F(SimpleObjectTests, test6d) {
    auto value = std::numeric_limits<std::int64_t>::min();
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("min_int64", rs::scriptobject::utils::VectorValue(value)),
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int64, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int64, object->getType("min_int64"));
    ASSERT_EQ(value, object->getInt64(0));
    ASSERT_EQ(value, object->getInt64("min_int64"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - sizeof(std::int64_t));
}


TEST_F(SimpleObjectTests, test6e) {
    auto value = std::numeric_limits<std::int64_t>::max();
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("max_int64", rs::scriptobject::utils::VectorValue(value)),
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int64, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int64, object->getType("max_int64"));
    ASSERT_EQ(value, object->getInt64(0));
    ASSERT_EQ(value, object->getInt64("max_int64"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - sizeof(std::int64_t));
}

TEST_F(SimpleObjectTests, test6f) {
    auto value = std::numeric_limits<std::uint64_t>::max();
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("max_uint64", rs::scriptobject::utils::VectorValue(value)),
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::UInt64, object->getType(0));
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::UInt64, object->getType("max_uint64"));
    ASSERT_EQ(value, object->getUInt64(0));
    ASSERT_EQ(value, object->getUInt64("max_uint64"));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), object->getSize() - sizeof(std::uint64_t));
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
    
    ASSERT_EQ(nullptr, object->getString("pqr", false));
    
    ASSERT_THROW({
        object->getInt32("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getUInt32("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getInt64("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);    
    
    ASSERT_THROW({
        object->getUInt64("xyz");
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
        object->getUInt32(5050);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getInt64(5500);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
    
    ASSERT_THROW({
        object->getUInt64(5005);
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
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42))
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
        object->getUInt32("wet");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt64("wet");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getUInt64("wet");
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
        object->getUInt32("hello");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt64("hello");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getUInt64("hello");
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
        object->getInt32("the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt64("the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getUInt64("the_answer");
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
        object->getDouble("not_the_answer");
    }, rs::scriptobject::TypeCastException);    

    ASSERT_THROW({
        object->getUInt32("not_the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt64("not_the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getUInt64("not_the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getString("not_the_answer");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean("not_the_answer");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject("not_the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getArray("not_the_answer");
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
        object->getUInt32("sunny");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt64("sunny");
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getUInt64("sunny");
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
        object->getUInt32(0);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getInt64(0);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getUInt64(0);
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
        object->getUInt32(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt64(1);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getUInt64(1);
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
        object->getUInt32(2);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt64(2);
    }, rs::scriptobject::TypeCastException);        
    
    ASSERT_THROW({
        object->getUInt64(2);
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
        object->getInt32(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt64(3);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getUInt64(3);
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
    
    ASSERT_THROW({
        object->getDouble(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getUInt32(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getInt64(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getUInt64(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getString(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getBoolean(4);
    }, rs::scriptobject::TypeCastException);            
    
    ASSERT_THROW({
        object->getArray(4);
    }, rs::scriptobject::TypeCastException);    
    
    ASSERT_THROW({
        object->getObject(4);
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
    rs::scriptobject::ScriptObjectType types[] = { 
        rs::scriptobject::ScriptObjectType::String, rs::scriptobject::ScriptObjectType::Double, 
        rs::scriptobject::ScriptObjectType::Int32, rs::scriptobject::ScriptObjectType::UInt32,
        rs::scriptobject::ScriptObjectType::Int64, rs::scriptobject::ScriptObjectType::UInt64,
        rs::scriptobject::ScriptObjectType::Boolean, rs::scriptobject::ScriptObjectType::Null
    };
    
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
            case rs::scriptobject::ScriptObjectType::UInt32:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue((std::uint32_t)i)));
                break;                
            case rs::scriptobject::ScriptObjectType::Int64:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue((std::int64_t)std::numeric_limits<std::int32_t>::max() + i)));
                break;                                
            case rs::scriptobject::ScriptObjectType::UInt64:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue((std::uint64_t)std::numeric_limits<std::uint32_t>::max() + i)));
                break;                                
            case rs::scriptobject::ScriptObjectType::Boolean:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue(i % 2 == 0)));
                break;                                
            case rs::scriptobject::ScriptObjectType::Null:
                vect.push_back(std::make_pair(std::to_string(i), rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::Null)));
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
            case rs::scriptobject::ScriptObjectType::UInt32:           
                ASSERT_EQ(std::get<1>(vect[i]).getUInt32(), object->getUInt32(i));
                break;                
            case rs::scriptobject::ScriptObjectType::Int64:           
                ASSERT_EQ(std::get<1>(vect[i]).getInt64(), object->getInt64(i));
                break;                
            case rs::scriptobject::ScriptObjectType::UInt64:           
                ASSERT_EQ(std::get<1>(vect[i]).getUInt64(), object->getUInt64(i));
                break;                
            case rs::scriptobject::ScriptObjectType::Boolean:           
                ASSERT_EQ(std::get<1>(vect[i]).getBoolean(), object->getBoolean(i));
                break;
            case rs::scriptobject::ScriptObjectType::Null:           
                ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType(i));
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
                ASSERT_EQ(std::get<1>(vect[i]).getInt32(), object->getInt32(name));
                break;
            case rs::scriptobject::ScriptObjectType::UInt32:
                ASSERT_EQ(std::get<1>(vect[i]).getUInt32(), object->getUInt32(name));
                break;
            case rs::scriptobject::ScriptObjectType::Int64:
                ASSERT_EQ(std::get<1>(vect[i]).getInt64(), object->getInt64(name));
                break;
            case rs::scriptobject::ScriptObjectType::UInt64:
                ASSERT_EQ(std::get<1>(vect[i]).getUInt64(), object->getUInt64(name));
                break;
            case rs::scriptobject::ScriptObjectType::Boolean:
                ASSERT_EQ(std::get<1>(vect[i]).getBoolean(), object->getBoolean(name));
                break;
            case rs::scriptobject::ScriptObjectType::Null:
                ASSERT_EQ(rs::scriptobject::ScriptObjectType::Null, object->getType(name));
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
    
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1), 
        object->getSize(false) - sizeof(rs::scriptobject::ScriptObjectPtr));
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1) * 2, 
        object->getSize(true) - 6 - sizeof(rs::scriptobject::ScriptObjectPtr));
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
    
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(1) + rs::scriptobject::ScriptArray::CalculateSizeOverhead(1), 
            object->getSize(true) - sizeof(rs::scriptobject::ScriptArrayPtr) - sizeof(double));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(2), 
            targetObject->getSize(true) - 6 - sizeof(double));
}

TEST_F(SimpleObjectTests, test17) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("min_i64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::min()))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("max_i64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::max())),
        std::make_pair("max_ui64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::max()))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2);
    
    ASSERT_EQ(10, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::UInt32, key6.type);
    
    rs::scriptobject::ScriptObjectKey key7;
    ASSERT_TRUE(targetObject->getKeys()->getKey("not_the_answer", key7));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key7.type);
    
    rs::scriptobject::ScriptObjectKey key8;
    ASSERT_TRUE(targetObject->getKeys()->getKey("min_i64", key8));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int64, key8.type);
    
    rs::scriptobject::ScriptObjectKey key9;
    ASSERT_TRUE(targetObject->getKeys()->getKey("max_i64", key9));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int64, key9.type);
    
    rs::scriptobject::ScriptObjectKey key10;
    ASSERT_TRUE(targetObject->getKeys()->getKey("max_ui64", key10));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::UInt64, key10.type);
        
    ASSERT_EQ(rs::scriptobject::ScriptObject::CalculateSizeOverhead(10), 
            targetObject->getSize(true) - 6 - 6 - sizeof(double) - 
            sizeof(std::uint32_t) - sizeof(std::int32_t) -
            sizeof(std::int64_t) - sizeof(std::int64_t) -
            sizeof(std::uint64_t));
}

TEST_F(SimpleObjectTests, test18) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });    
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object1);
    
    ASSERT_EQ(object1.get(), targetObject.get());   
}

TEST_F(SimpleObjectTests, test19) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(0.0f)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(0)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(0)),
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum")),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("nil", rs::scriptobject::utils::VectorValue()),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2);
    
    ASSERT_EQ(7, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::UInt32, key6.type);
    ASSERT_EQ(42u, targetObject->getUInt32(key6.index));
    
    rs::scriptobject::ScriptObjectKey key7;
    ASSERT_TRUE(targetObject->getKeys()->getKey("not_the_answer", key7));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key7.type);
    ASSERT_EQ(-42, targetObject->getInt32(key7.index));
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
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2);
    
    ASSERT_EQ(7, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::UInt32, key6.type);
    ASSERT_EQ(42u, targetObject->getUInt32(key6.index));
    
    rs::scriptobject::ScriptObjectKey key7;
    ASSERT_TRUE(targetObject->getKeys()->getKey("not_the_answer", key7));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key7.type);
    ASSERT_EQ(-42, targetObject->getInt32(key7.index));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2);
    
    ASSERT_EQ(4, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("child", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Object, key3.type);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("array", key4));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(1, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(2, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(3, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(0, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(1, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_EQ(4, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_EQ(5, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
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
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(7, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::UInt32, key6.type);
    ASSERT_EQ(5, key6.index);
    
    rs::scriptobject::ScriptObjectKey key7;
    ASSERT_TRUE(targetObject->getKeys()->getKey("not_the_answer", key7));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Int32, key7.type);
    ASSERT_EQ(6, key7.index);
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Front);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
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
    
    auto targetObject = rs::scriptobject::ScriptObject::Merge(object1, object2, rs::scriptobject::ScriptObject::MergeStrategy::Back);
    
    ASSERT_EQ(6, targetObject->getCount());
    
    rs::scriptobject::ScriptObjectKey key1;
    ASSERT_TRUE(targetObject->getKeys()->getKey("hello", key1));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key1.type);
    ASSERT_STREQ("world", targetObject->getString(key1.index));
    ASSERT_EQ(0, key1.index);
    
    rs::scriptobject::ScriptObjectKey key2;
    ASSERT_TRUE(targetObject->getKeys()->getKey("pi", key2));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Double, key2.type);
    ASSERT_FLOAT_EQ(3.14159f, targetObject->getDouble(key2.index));
    ASSERT_EQ(3, key2.index);
    
    rs::scriptobject::ScriptObjectKey key3;
    ASSERT_TRUE(targetObject->getKeys()->getKey("nil", key3));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Null, key3.type);
    ASSERT_EQ(4, key3.index);
    
    rs::scriptobject::ScriptObjectKey key4;
    ASSERT_TRUE(targetObject->getKeys()->getKey("lorem", key4));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::String, key4.type);
    ASSERT_STREQ("ipsum", targetObject->getString(key4.index));
    ASSERT_EQ(1, key4.index);
    
    rs::scriptobject::ScriptObjectKey key5;
    ASSERT_TRUE(targetObject->getKeys()->getKey("wet", key5));
    ASSERT_EQ((unsigned)rs::scriptobject::ScriptObjectType::Boolean, key5.type);
    ASSERT_FALSE(targetObject->getBoolean(key5.index));
    ASSERT_EQ(2, key5.index);
    
    rs::scriptobject::ScriptObjectKey key6;
    ASSERT_TRUE(targetObject->getKeys()->getKey("the_answer", key6));
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
    
    ASSERT_EQ(3, object->getStringLength(0));
    ASSERT_EQ(5, object->getStringLength(1));
    ASSERT_EQ(11, object->getStringLength(2));
}

TEST_F(SimpleObjectTests, test29) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(11, object->getStringLength(0));
    ASSERT_EQ(5, object->getStringLength(1));
    ASSERT_EQ(3, object->getStringLength(2));
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
    
    ASSERT_EQ(11, object->getStringLength(1));
    ASSERT_EQ(5, object->getStringLength(3));
    ASSERT_EQ(3, object->getStringLength(5));
}

TEST_F(SimpleObjectTests, test31) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(3, object->getStringLength(0));
    
    ASSERT_THROW({
        object->getStringLength(1);
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getStringLength(10);
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}

TEST_F(SimpleObjectTests, test32) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum"))        
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(3, object->getStringLength("abc"));
    ASSERT_EQ(5, object->getStringLength("hello"));
    ASSERT_EQ(11, object->getStringLength("text"));
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
    
    ASSERT_EQ(3, object->getStringLength("abc"));
    ASSERT_EQ(5, object->getStringLength("hello"));
    ASSERT_EQ(11, object->getStringLength("text"));
}

TEST_F(SimpleObjectTests, test34) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(3, object->getStringLength(0));
    
    ASSERT_THROW({
        object->getStringLength("the_answer");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->getStringLength("xyz");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}

TEST_F(SimpleObjectTests, test35) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_TRUE(object->setString(1, "hello world"));
    ASSERT_STREQ("hello world", object->getString(1));
    
    ASSERT_FALSE(object->setString(1, "hello world from mars"));
    ASSERT_STREQ("hello world", object->getString(1));
    
    ASSERT_TRUE(object->setString(1, "hello"));
    ASSERT_STREQ("hello", object->getString(1));
    ASSERT_EQ(5, object->getStringLength(1));
    
    ASSERT_TRUE(object->setString("text", "welcome"));
    ASSERT_STREQ("welcome", object->getString("text"));
    ASSERT_EQ(7, object->getStringLength("text"));
    
    ASSERT_FALSE(object->setString("text", "hello world from mars"));
    ASSERT_STREQ("welcome", object->getString("text"));
    
    ASSERT_THROW({
        object->setString("the_answer", "once more into the ....");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->setString("not_the_answer", "once more into the ....");
    }, rs::scriptobject::TypeCastException);
    
    ASSERT_THROW({
        object->setString("xyz", "the bomb");
    }, rs::scriptobject::UnknownScriptObjectFieldException);
}

TEST_F(SimpleObjectTests, test36) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("items", rs::scriptobject::utils::VectorValue()),
        std::make_pair("divByZero", rs::scriptobject::utils::VectorValue(rs::scriptobject::ScriptObjectType::Undefined)),
        std::make_pair("min_i64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::min())),
        std::make_pair("max_ui64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::max()))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(11, object1->getCount());
    ASSERT_EQ(11, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test37) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyzxyz"))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(6, object1->getCount());
    ASSERT_EQ(6, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test38) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159))        
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(6, object1->getCount());
    ASSERT_EQ(6, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test39) {
    rs::scriptobject::utils::ScriptObjectVectorSource child({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto childObject = rs::scriptobject::ScriptObjectFactory::CreateObject(child);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childObject))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    ASSERT_EQ(6, object1->getCount());
    ASSERT_EQ(6, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test40) {
    rs::scriptobject::utils::ScriptObjectVectorSource child1({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto childObject1 = rs::scriptobject::ScriptObjectFactory::CreateObject(child1);
    
    rs::scriptobject::utils::ScriptObjectVectorSource child2({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world!!!"))
    });
    
    auto childObject2 = rs::scriptobject::ScriptObjectFactory::CreateObject(child2);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childObject1))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childObject2))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(7, object1->getCount());
    ASSERT_EQ(7, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test41) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectHash digest1;
    object->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2 = { 0xFC, 0x5E, 0x03, 0x8D, 0x38, 0xA5, 0x70, 0x32, 0x08, 0x54, 0x41, 0xE7, 0xFE, 0x70, 0x10, 0xB0 };
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test42) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("lorem", rs::scriptobject::utils::VectorValue("ipsum"))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    rs::scriptobject::ScriptObjectHash digest1;
    object->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2 = { 0x86, 0x33, 0x29, 0x4C, 0x72, 0xBD, 0x07, 0x80, 0x83, 0xA3, 0x36, 0xBC, 0x9E, 0x6E, 0xFA, 0x5E };
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test43) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({
        std::make_pair("_id", rs::scriptobject::utils::VectorValue("6CA0F225-47A1-4DF4-9F2E-70D72276E2BC")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("_deleted", rs::scriptobject::utils::VectorValue(true))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("_id", rs::scriptobject::utils::VectorValue("DF02BC9B-5D80-4D3E-935C-5E66BE3806B2")),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("_deleted", rs::scriptobject::utils::VectorValue(false))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(3, object1->getCount());
    ASSERT_EQ(3, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1, [](const char* name) { return name[0] != '_'; });
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2, [](const char* name) { return name[0] != '_'; });
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test44) {
    rs::scriptobject::utils::ScriptArrayVectorSource child1({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray1 = rs::scriptobject::ScriptArrayFactory::CreateArray(child1);
    
    rs::scriptobject::utils::ScriptArrayVectorSource child2({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray2 = rs::scriptobject::ScriptArrayFactory::CreateArray(child2);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childArray1)),
        std::make_pair("min_i64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::min())),
        std::make_pair("max_ui64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::max()))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childArray2)),
        std::make_pair("min_i64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::min())),
        std::make_pair("max_ui64", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::max()))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(10, object1->getCount());
    ASSERT_EQ(10, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) == 0);
}

TEST_F(SimpleObjectTests, test45) {
    rs::scriptobject::utils::ScriptArrayVectorSource child1({
        rs::scriptobject::utils::VectorValue("world")
    });
    
    auto childArray1 = rs::scriptobject::ScriptArrayFactory::CreateArray(child1);
    
    rs::scriptobject::utils::ScriptArrayVectorSource child2({
        rs::scriptobject::utils::VectorValue("world!!!")
    });
    
    auto childArray2 = rs::scriptobject::ScriptArrayFactory::CreateArray(child2);
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childArray1))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("child", rs::scriptobject::utils::VectorValue(childArray2))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(7, object1->getCount());
    ASSERT_EQ(7, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test45b) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(-42)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz"))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(6, object1->getCount());
    ASSERT_EQ(6, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test45c) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("big_number", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::min()))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("big_number", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::int64_t>::max()))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(7, object1->getCount());
    ASSERT_EQ(7, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test45d) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn1({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("big_number", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::min()))
    });
    
    rs::scriptobject::utils::ScriptObjectVectorSource defn2({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("big_number", rs::scriptobject::utils::VectorValue(std::numeric_limits<std::uint64_t>::max()))
    });
    
    auto object1 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn1);
    auto object2 = rs::scriptobject::ScriptObjectFactory::CreateObject(defn2);
    
    ASSERT_EQ(7, object1->getCount());
    ASSERT_EQ(7, object2->getCount());
    
    rs::scriptobject::ScriptObjectHash digest1;
    object1->CalculateHash(digest1);
    
    rs::scriptobject::ScriptObjectHash digest2;
    object2->CalculateHash(digest2);
    
    ASSERT_TRUE(rs::scriptobject::CompareScriptObjectHash(digest1, digest2) != 0);
}

TEST_F(SimpleObjectTests, test46) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({        
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(true)),
        std::make_pair("text", rs::scriptobject::utils::VectorValue("lorem ipsum")),
        std::make_pair("the_answer", rs::scriptobject::utils::VectorValue(42u)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),        
        std::make_pair("pi", rs::scriptobject::utils::VectorValue(3.14159)),
        std::make_pair("abc", rs::scriptobject::utils::VectorValue("xyz")),
        std::make_pair("not_the_answer", rs::scriptobject::utils::VectorValue(-42))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    int index = -1;
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, object->getType("wet", index));
    ASSERT_EQ(0, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("text", index));
    ASSERT_EQ(1, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::UInt32, object->getType("the_answer", index));
    ASSERT_EQ(2, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("hello", index));
    ASSERT_EQ(3, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Double, object->getType("pi", index));
    ASSERT_EQ(4, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, object->getType("abc", index));
    ASSERT_EQ(5, index);
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Int32, object->getType("not_the_answer", index));
    ASSERT_EQ(6, index);
}

TEST_F(SimpleObjectTests, test47) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    auto newObject = rs::scriptobject::ScriptObject::DeleteField(object, "hello");
    ASSERT_EQ(2, newObject->getCount());
    
    int index = -1;
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, newObject->getType("wet", index));
    ASSERT_EQ(0, index);
    ASSERT_FALSE(newObject->getBoolean(index));
    ASSERT_FALSE(newObject->getBoolean("wet"));
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, newObject->getType("sunny", index));
    ASSERT_EQ(1, index);
    ASSERT_TRUE(newObject->getBoolean(index));
    ASSERT_TRUE(newObject->getBoolean("sunny"));
    
    newObject = rs::scriptobject::ScriptObject::DeleteField(object, "sunny");
    ASSERT_EQ(2, newObject->getCount());
    
    index = -1;
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, newObject->getType("wet", index));
    ASSERT_EQ(0, index);
    ASSERT_FALSE(newObject->getBoolean(index));
    ASSERT_FALSE(newObject->getBoolean("wet"));
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, newObject->getType("hello", index));
    ASSERT_EQ(1, index);
    ASSERT_STREQ("world", newObject->getString(index));
    ASSERT_STREQ("world", newObject->getString("hello"));
    
    newObject = rs::scriptobject::ScriptObject::DeleteField(object, "wet");
    ASSERT_EQ(2, newObject->getCount());
    
    index = -1;
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, newObject->getType("hello", index));
    ASSERT_EQ(0, index);
    ASSERT_STREQ("world", newObject->getString(index));
    ASSERT_STREQ("world", newObject->getString("hello"));
    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::Boolean, newObject->getType("sunny", index));
    ASSERT_EQ(1, index);
    ASSERT_TRUE(newObject->getBoolean(index));
    ASSERT_TRUE(newObject->getBoolean("sunny"));
}

TEST_F(SimpleObjectTests, test48) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    auto newObject = rs::scriptobject::ScriptObject::DeleteField(object, "sunny");
    newObject = rs::scriptobject::ScriptObject::DeleteField(newObject, "wet");
    ASSERT_EQ(1, newObject->getCount());
    
    int index = -1;    
    ASSERT_EQ(rs::scriptobject::ScriptObjectType::String, newObject->getType("hello", index));
    ASSERT_EQ(0, index);
    ASSERT_STREQ("world", newObject->getString(index));
    ASSERT_STREQ("world", newObject->getString("hello"));
    
    newObject = rs::scriptobject::ScriptObject::DeleteField(newObject, "hello");
    ASSERT_EQ(0, newObject->getCount());
}

TEST_F(SimpleObjectTests, test49) {
    rs::scriptobject::utils::ScriptObjectVectorSource defn({
        std::make_pair("wet", rs::scriptobject::utils::VectorValue(false)),
        std::make_pair("hello", rs::scriptobject::utils::VectorValue("world")),
        std::make_pair("sunny", rs::scriptobject::utils::VectorValue(true))
    });
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    
    auto newObject = rs::scriptobject::ScriptObject::DeleteField(object, "xyz");
    ASSERT_EQ(3, newObject->getCount());
    ASSERT_EQ(object.get(), newObject.get());
}

TEST_F(SimpleObjectTests, test50) {
    rs::scriptobject::utils::ObjectVector source;
    rs::scriptobject::utils::ScriptObjectVectorSource defn{source};
    
    auto object = rs::scriptobject::ScriptObjectFactory::CreateObject(defn);
    ASSERT_EQ(0, object->getCount());    
    
    auto newObject = rs::scriptobject::ScriptObject::DeleteField(object, "xyz");
    ASSERT_EQ(0, newObject->getCount());    
}