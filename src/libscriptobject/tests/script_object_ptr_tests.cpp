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
#include <algorithm>

#include "../script_item_ptr.h"

class SomeTestType final : public rs::scriptobject::ScriptItemPtrCountedBase<SomeTestType> {
public:
    SomeTestType(long& destroyed) : destroyed_(destroyed) {}
    ~SomeTestType() { ++destroyed_; }
    
    int TheAnswer() { return 42; }
    
    long& destroyed_;
};

class SomeCountedTestType final : public rs::scriptobject::ScriptItemPtrBase<SomeCountedTestType> {
public:
    SomeCountedTestType(long& destroyed) : destroyed_(destroyed) {}
    ~SomeCountedTestType() { ++destroyed_; }
    
    int TheAnswer() { return 42; }
    
    long& destroyed_;
    
private:
    friend rs::scriptobject::ScriptItemPtrBase<SomeCountedTestType>;
    
    rs::scriptobject::ScriptItemPtrBase<SomeCountedTestType>::atomic_count_type refCount_{0};
};

class SortableTestType final : public rs::scriptobject::ScriptItemPtrCountedBase<SortableTestType> {
public:
    SortableTestType(int value) : value_(value) {}
    SortableTestType(const SortableTestType& other) = default;
    SortableTestType(SortableTestType&&) = default;
    ~SortableTestType() { ++destroyed_; }
    
    int value_;
    static int destroyed_;
};

int SortableTestType::destroyed_ = 0;

using SortableTestTypePtr = rs::scriptobject::ScriptItemPtr<SortableTestType>;

class ScriptObjectPtrTests : public ::testing::Test {
protected:
    virtual void SetUp() {
        SortableTestTypePtr::element_type::destroyed_ = 0;
    }
    
    virtual void TearDown() {
        
    }            
};

TEST_F(ScriptObjectPtrTests, test0) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = new SomeTestType{destroyed};
        delete ptr;
    }
    
    ASSERT_EQ(1, destroyed);
}

#if 0
// * this test is legacy: the constructor was changed to private so this will fail to compile
TEST_F(ScriptObjectPtrTests, test1) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = rs::scriptobject::ScriptItemPtr<SomeTestType>{new SomeTestType{destroyed}};
    }
    
    ASSERT_EQ(1, destroyed);
}
#endif

TEST_F(ScriptObjectPtrTests, test2) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = rs::scriptobject::make_script_item_ptr<SomeTestType>(destroyed);
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test3) {
    long destroyed = 0;
    
    auto ptr1 = rs::scriptobject::make_script_item_ptr<SomeTestType>(destroyed);
    decltype(ptr1) ptr2 = ptr1;
    ASSERT_EQ(2, ptr2.count());
    ptr2.reset();
    ASSERT_EQ(0, ptr2.count());
    ASSERT_EQ(1, ptr1.count());
    ptr1.reset();
    ASSERT_EQ(0, ptr2.count());
    ASSERT_EQ(0, ptr1.count());
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test4) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_script_item_ptr<SomeTestType>(destroyed);
        auto ptr2 = rs::scriptobject::ScriptItemPtr<SomeTestType>{};

        ASSERT_EQ(1, ptr1.count());
        ptr2 = ptr1;
        ASSERT_EQ(2, ptr1.count());
        ASSERT_EQ(2, ptr2.count());    
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test5) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = rs::scriptobject::make_script_item_ptr<SomeTestType>(destroyed);
        ASSERT_EQ(42, ptr->TheAnswer());
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test6) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::ScriptItemPtr<SomeTestType>{};
        decltype(ptr1) ptr2{ptr1};

        ASSERT_EQ(0, ptr1.count());
        ASSERT_EQ(0, ptr2.count());
        
        auto ptr3 = rs::scriptobject::make_script_item_ptr<SomeTestType>(destroyed);
        ASSERT_EQ(0, ptr1.count());
        ASSERT_EQ(0, ptr2.count());
        ASSERT_EQ(1, ptr3.count());
        
        ptr1 = ptr3;
        ASSERT_EQ(2, ptr1.count());
        ASSERT_EQ(0, ptr2.count());
        ASSERT_EQ(2, ptr3.count());
        
        ptr2 = ptr1;
        ASSERT_EQ(3, ptr1.count());
        ASSERT_EQ(3, ptr2.count());
        ASSERT_EQ(3, ptr3.count());
    }
}

TEST_F(ScriptObjectPtrTests, test7) {
    const int count = 1024;
    
    if (true) {
        std::vector<SortableTestTypePtr> data;
        data.reserve(count);

        for (int i = 0; i < data.capacity(); ++i) {
            data.emplace_back(rs::scriptobject::make_script_item_ptr<SortableTestTypePtr::element_type>(i));
        }

        for (int i = 0; i < data.size(); ++i) {
            ASSERT_EQ(i, data[i]->value_);
            ASSERT_EQ(1, data[i].count());
        }

        std::random_shuffle(data.begin(), data.end());

        for (int i = 0; i < data.size(); ++i) {
            ASSERT_EQ(1, data[i].count());
        }

        std::sort(data.begin(), data.end(), [](const SortableTestTypePtr& l, const SortableTestTypePtr& r) { return l->value_ < r->value_; });

        for (int i = 0; i < data.size(); ++i) {
            ASSERT_EQ(i, data[i]->value_);
            ASSERT_EQ(1, data[i].count());
        }

        ASSERT_EQ(0, SortableTestTypePtr::element_type::destroyed_);
    }
    
    ASSERT_EQ(count, SortableTestTypePtr::element_type::destroyed_);
}

TEST_F(ScriptObjectPtrTests, test8) {
    const int count = 1024;
    
    if (true) {
        std::vector<SortableTestTypePtr> data;
        data.reserve(count);
        
        for (int i = 0; i < data.capacity(); ++i) {
            data.emplace_back(rs::scriptobject::make_script_item_ptr<SortableTestTypePtr::element_type>(i));
        }

        if (true) {
            std::vector<SortableTestTypePtr> copy{data.cbegin(), data.cend()};
        }

        ASSERT_EQ(0, SortableTestTypePtr::element_type::destroyed_);
    }
    
    ASSERT_EQ(count, SortableTestTypePtr::element_type::destroyed_);
}

TEST_F(ScriptObjectPtrTests, test9) {
    const int count = 1024;
    
    std::vector<SortableTestTypePtr> data;
    data.reserve(count);

    for (int i = 0; i < data.capacity(); ++i) {
        data.emplace_back(rs::scriptobject::make_script_item_ptr<SortableTestTypePtr::element_type>(i));
    }   

    for (int i = 0; i < data.size(); ++i) {
        data[i].reset();        
        ASSERT_EQ(i + 1, SortableTestTypePtr::element_type::destroyed_);
    }
    
    ASSERT_EQ(count, SortableTestTypePtr::element_type::destroyed_);
}

TEST_F(ScriptObjectPtrTests, test10) {
    const int count = 1024;
    
    std::vector<SortableTestTypePtr> data;
    data.reserve(count);

    for (int i = 0; i < data.capacity(); ++i) {
        data.emplace_back(rs::scriptobject::make_script_item_ptr<SortableTestTypePtr::element_type>(i));
    }
    
    std::vector<SortableTestTypePtr> copy{data.cbegin(), data.cend()};

    for (int i = 0; i < data.size(); ++i) {
        data[i].reset();
        ASSERT_EQ(i, SortableTestTypePtr::element_type::destroyed_);        
        copy[i].reset();
        ASSERT_EQ(i + 1, SortableTestTypePtr::element_type::destroyed_);        
    }
    
    ASSERT_EQ(count, SortableTestTypePtr::element_type::destroyed_);
}

TEST_F(ScriptObjectPtrTests, test11) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType), destroyed);
    }
    
    if (true) {
        auto ptr = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType) + 1, destroyed);
    }
    
    EXPECT_THROW({
        auto ptr = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType) - 1, destroyed);
    }, std::length_error);
    
    ASSERT_EQ(2, destroyed);
}

TEST_F(ScriptObjectPtrTests, test12) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType), destroyed);
        decltype(ptr1) ptr2{std::move(ptr1)};
        
        ASSERT_FALSE(!!ptr1);
        ASSERT_TRUE(!!ptr2);
        ASSERT_EQ(nullptr, ptr1.get());
        ASSERT_EQ(0, ptr1.count());
        ASSERT_NE(nullptr, ptr2.get());
        ASSERT_EQ(1, ptr2.count());
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test13) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType), destroyed);
        decltype(ptr1) ptr2{};
        
        ASSERT_EQ(nullptr, ptr2.get());
        ASSERT_EQ(0, ptr2.count());
        
        ptr2 = std::move(ptr1);
        
        ASSERT_FALSE(!!ptr1);
        ASSERT_TRUE(!!ptr2);
        ASSERT_EQ(nullptr, ptr1.get());
        ASSERT_EQ(0, ptr1.count());
        ASSERT_NE(nullptr, ptr2.get());
        ASSERT_EQ(1, ptr2.count());
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test14) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_sized_script_item_ptr<SomeTestType>(sizeof(SomeTestType), destroyed);
        ptr1.reset();
        
        EXPECT_THROW({
            (*ptr1).TheAnswer();
        }, std::bad_cast);
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test15) {
    long destroyed = 0;
    
    if (true) {
        auto ptr = rs::scriptobject::make_script_item_ptr<SomeCountedTestType>(destroyed);
    }
    
    ASSERT_EQ(1, destroyed);
}

TEST_F(ScriptObjectPtrTests, test16) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_script_item_ptr<SomeCountedTestType>(destroyed);
        auto ptr2 = rs::scriptobject::make_script_item_ptr<SomeCountedTestType>(destroyed);
    }
    
    ASSERT_EQ(2, destroyed);
}

TEST_F(ScriptObjectPtrTests, test17) {
    long destroyed = 0;
    
    if (true) {
        auto ptr1 = rs::scriptobject::make_script_item_ptr<SomeCountedTestType>(destroyed);
        auto ptr2 = rs::scriptobject::make_script_item_ptr<SomeCountedTestType>(destroyed);
        
        swap(ptr1, ptr2);
    }
    
    ASSERT_EQ(2, destroyed);
}