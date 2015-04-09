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

#include "../libscriptobject.h"

class ExceptionTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        
    }
    
    virtual void TearDown() {
        
    }
    
    bool SanityCheckWhatMessage(const char* msg) {
        while (*msg != '\0') {
            if (*msg < 0x0d || *msg > 0x7e) {
                return false;
            }
            msg++;
        }
        return true;
    }
};

TEST_F(ExceptionTests, test0) {
    bool thrown = false;
    
    try {
        throw rs::scriptobject::ScriptObjectException();
    } catch (const rs::scriptobject::ScriptObjectException& e) {
        ASSERT_NE(nullptr, e.what());
        ASSERT_TRUE(SanityCheckWhatMessage(e.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ExceptionTests, test1) {
    bool thrown = false;
    
    try {
        throw rs::scriptobject::TypeCastException();
    } catch (const rs::scriptobject::TypeCastException& e) {
        ASSERT_NE(nullptr, e.what());
        ASSERT_TRUE(SanityCheckWhatMessage(e.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ExceptionTests, test2) {
    bool thrown = false;
    
    try {
        throw rs::scriptobject::UnknownSourceFieldTypeException();
    } catch (const rs::scriptobject::UnknownSourceFieldTypeException& e) {
        ASSERT_NE(nullptr, e.what());
        ASSERT_TRUE(SanityCheckWhatMessage(e.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ExceptionTests, test3) {
    bool thrown = false;
    
    try {
        throw rs::scriptobject::UnknownScriptObjectFieldException();
    } catch (const rs::scriptobject::UnknownScriptObjectFieldException& e) {
        ASSERT_NE(nullptr, e.what());
        ASSERT_TRUE(SanityCheckWhatMessage(e.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}

TEST_F(ExceptionTests, test4) {
    bool thrown = false;
    
    try {
        throw rs::scriptobject::UnknownScriptArrayIndexException();
    } catch (const rs::scriptobject::UnknownScriptArrayIndexException& e) {
        ASSERT_NE(nullptr, e.what());
        ASSERT_TRUE(SanityCheckWhatMessage(e.what()));
        thrown = true;
    }
    
    ASSERT_TRUE(thrown);
}