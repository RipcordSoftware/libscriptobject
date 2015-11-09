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

#ifndef SCRIPT_ITEM_PTR_H
#define SCRIPT_ITEM_PTR_H

#include <atomic>
#include <memory>
#include <new>

namespace rs {
namespace scriptobject {

template <typename T, typename AllocT = unsigned char>
class ScriptItemPtrBase {
public:
    using count_type = long;
    using atomic_count_type = std::atomic<count_type>;
    using allocated_type = AllocT;
    
    ScriptItemPtrBase() {}
    ScriptItemPtrBase(ScriptItemPtrBase&&) {}
    
    inline static void AddRef(T* ptr) noexcept {
        if (ptr) ++ptr->refCount_;
    }
    
    inline static void Release(T* ptr) noexcept {
        if (ptr) {
            auto count = --ptr->refCount_;
            if (count == 0) {
                ptr->~T();
                auto rawPtr = reinterpret_cast<AllocT*>(ptr);
                delete[] rawPtr;
            }
        }
    }
    
    inline count_type Count(T* ptr) const noexcept {
        return ptr != nullptr ? ptr->refCount_.load() : 0;
    }
};

template <typename T, typename AllocT = unsigned char>
class ScriptItemPtrCountedBase : public ScriptItemPtrBase<T, AllocT> {
    
private:
    friend class ScriptItemPtrBase<T, AllocT>;    
    
    typename ScriptItemPtrBase<T, AllocT>::atomic_count_type refCount_{0};
};
    
template <typename T>
class ScriptItemPtr final {
public:
    using element_type = T;
        
    ScriptItemPtr() : ScriptItemPtr(nullptr) {}
    ScriptItemPtr(const ScriptItemPtr<T>& other) : ptr_(other.ptr_) { if (ptr_) ptr_->AddRef(ptr_); }
    
    ScriptItemPtr(ScriptItemPtr<T>&& rhs) {
        ptr_ = rhs.ptr_;
        rhs.ptr_ = nullptr;
    }
    
    inline ~ScriptItemPtr() { if (ptr_) ptr_->Release(ptr_); }   
    
    inline T* get() const noexcept { return ptr_; }
    inline typename T::allocated_type* getRawPtr() const noexcept { return reinterpret_cast<typename T::allocated_type*>(ptr_); }
    inline void reset() noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = nullptr; }
    inline typename ScriptItemPtrBase<T>::count_type count() const noexcept { return ptr_ ? ptr_->Count(ptr_) : 0; }
    
    inline void operator=(ScriptItemPtr<T>&& rhs) noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = rhs.ptr_; rhs.ptr_ = nullptr; }
    inline void operator=(const ScriptItemPtr<T>& rhs) noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = rhs.ptr_; if (ptr_) ptr_->AddRef(ptr_); }
    
    inline T& operator*() const { if (!ptr_) throw std::bad_cast{}; return *ptr_; }
    inline T* operator->() const noexcept { return ptr_; }
    inline bool operator!() const noexcept { return ptr_ == nullptr; }
    
private:
    template <typename TT, typename... Args>
    friend ScriptItemPtr<TT> make_script_item_ptr(Args&&... args);
    
    template <typename TT, typename... Args>
    friend ScriptItemPtr<TT> make_sized_script_item_ptr(size_t, Args&&... args);
    
    ScriptItemPtr(T* ptr) : ptr_(ptr) { if (ptr_) ptr_->AddRef(ptr_); }
    
    T* ptr_;
};

template <typename T, typename... Args>
ScriptItemPtr<T> make_script_item_ptr(Args&&... args) {
    auto size = sizeof(T) / sizeof(typename T::allocated_type);
    size += (sizeof(T) % sizeof(typename T::allocated_type) > 0) ? 1 : 0;
    
    auto ptr = new typename T::allocated_type[size];
    
#ifdef DEBUG_SCRIPT_OBJECT
    // in debug mode fill the memory with ? chars
    if (sizeof(typename T::allocated_type) == 1) {
        std::fill_n(ptr, size, '?');
    }
#endif
    
    return ScriptItemPtr<T>{new (ptr) T(std::forward<Args>(args)...)};
}

template <typename T, typename... Args>
ScriptItemPtr<T> make_sized_script_item_ptr(size_t size, Args&&... args) {
    auto minSize = sizeof(T) / sizeof(typename T::allocated_type);
    minSize += (sizeof(T) % sizeof(typename T::allocated_type) > 0) ? 1 : 0;    
    if (size < minSize) {
        throw std::bad_array_new_length{};
    }   
    
    auto ptr = new typename T::allocated_type[size];
    
#ifdef DEBUG_SCRIPT_OBJECT
    // in debug mode fill the memory with ? chars
    if (sizeof(typename T::allocated_type) == 1) {
        std::fill_n(ptr, size, '?');
    }
#endif
    
    return ScriptItemPtr<T>{new (ptr) T(std::forward<Args>(args)...)};
}

}}

#endif	/* SCRIPT_ITEM_PTR_H */
