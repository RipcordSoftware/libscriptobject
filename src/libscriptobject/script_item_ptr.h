/**
 * @file
 * Declares ScriptItemPtr and associated types
 * 
 * @internal
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

#ifndef RS_LIBSCRIPTOBJECT_SCRIPT_ITEM_PTR_H
#define RS_LIBSCRIPTOBJECT_SCRIPT_ITEM_PTR_H

#include <atomic>
#include <memory>
#include <new>
#include <algorithm>

namespace rs {
namespace scriptobject {

/**
 * A derivable template type containing methods to operate on reference counted types
 */
template <typename T, typename AllocT = unsigned char>
class ScriptItemPtrBase {
public:
    using count_type = long;
    using atomic_count_type = std::atomic<count_type>;
    using allocated_type = AllocT;
    
    /**
     * Increments the reference counter by one
     * @param ptr A pointer to the reference counted instance
     */
    inline static void AddRef(T* ptr) noexcept {
        if (ptr) ptr->refCount_.fetch_add(1, std::memory_order::memory_order_relaxed);
    }
    
    /**
     * Decrements the reference counter by one. 
     * Deallocates the object if the counter hits zero.
     * @param ptr A pointer to the reference counted instance
     */
    inline static void Release(T* ptr) noexcept {
        if (ptr) {
            auto count = ptr->refCount_.fetch_add(-1, std::memory_order::memory_order_relaxed);
            if (count == 1) {
                ptr->~T();
                auto rawPtr = reinterpret_cast<AllocT*>(ptr);
                delete[] rawPtr;
            }
        }
    }
    
    /**
     * Gets the number of references to the counted instance
     * @param ptr A pointer to the reference counted instance
     * @return The number of references counted on the instance
     */
    inline count_type Count(T* ptr) const noexcept {
        return ptr ? ptr->refCount_.load(std::memory_order::memory_order_relaxed) : 0;
    }
};

/**
 * A derivable template type containing a thread-safe reference counter
 * @see ScriptItemPtrBase
 * @see ScriptItemPtr
 */
template <typename T, typename AllocT = unsigned char>
class ScriptItemPtrCountedBase : public ScriptItemPtrBase<T, AllocT> {
    
private:
    friend class ScriptItemPtrBase<T, AllocT>;    
    
    typename ScriptItemPtrBase<T, AllocT>::atomic_count_type refCount_{0};
};
    
/**
 * A (partially) thread-safe reference counted pointer template type
 * @remarks
 * The reference counted instance is guaranteed to be thread safe however referencing pointer
 * instances are not safe. For example a ScriptItemPtr instance *x* cannot be shared between threads
 * if any of the state change methods are used (reset, swap, etc) since the pointer to the counted
 * instance is not itself thread-safe. Two threads can however share ScriptItemPtr instances *x* and *y*
 * which point to the same counted instance if they are 'owned' by different threads.
 * @see ScriptItemPtrBase
 * @see ScriptItemPtrCountedBase
 */
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
    
    /**
     * Gets a pointer to the counted instance
     * @return A pointer to the counted instance
     */
    inline T* get() const noexcept { return ptr_; }
    
    /**
     * Gets a pointer to the contained type instance
     * @return A pointer to the contained instance
     */
    inline typename T::allocated_type* getRawPtr() const noexcept { return reinterpret_cast<typename T::allocated_type*>(ptr_); }
    
    /**
     * Resets (releases) the reference count this instance holds on the counted instance
     */
    inline void reset() noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = nullptr; }
    
    /**
     * Gets the number of references to the counted instance
     * @return The number of active references
     */
    inline typename ScriptItemPtrBase<T>::count_type count() const noexcept { return ptr_ ? ptr_->Count(ptr_) : 0; }
    
    /**
     * Moves the rhs instance to the lhs instance release any lhs count currently held
     * @param rhs The instance to assign to the current instance
     */
    inline void operator=(ScriptItemPtr<T>&& rhs) noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = rhs.ptr_; rhs.ptr_ = nullptr; }
    
    /**
     * Assigns the counted reference to another instance releasing the reference to the previously held instance
     * @param rhs The instance to assign to the current instance
     */
    inline void operator=(const ScriptItemPtr<T>& rhs) noexcept { if (ptr_) ptr_->Release(ptr_); ptr_ = rhs.ptr_; if (ptr_) ptr_->AddRef(ptr_); }
    
    /**
     * Returns a reference to the counted instance
     */
    inline T& operator*() const { if (!ptr_) throw std::bad_cast{}; return *ptr_; }
    
    /**
     * Returns a pointer to the counted instance on which members can be referenced easily
     */
    inline T* operator->() const noexcept { return ptr_; }
    
    /**
     * Tests for pointer validity
     * @return True if the pointer is valid, false otherwise
     */
    inline bool operator!() const noexcept { return ptr_ == nullptr; }
    
    /**
     * Swaps two counted pointers
     * @param rhs
     */
    inline void swap(ScriptItemPtr<T>& rhs) noexcept {
        T* temp = ptr_;
        ptr_ = rhs.ptr_;
        rhs.ptr_ = temp;
    }
    
private:
    template <typename TT, typename... Args>
    friend ScriptItemPtr<TT> make_script_item_ptr(Args&&... args);
    
    template <typename TT, typename... Args>
    friend ScriptItemPtr<TT> make_sized_script_item_ptr(size_t, Args&&... args);
    
    ScriptItemPtr(T* ptr) : ptr_(ptr) { if (ptr_) ptr_->AddRef(ptr_); }
    
    T* ptr_;
};

/**
 * Creates a ScriptItemPtr<T> much like std::make_shared would
 * @param args The arguments to be forwarded to the constructor of T
 * @return A counted pointer
 */
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

/**
 * Creates a ScriptItemPtr<T> much like std::make_shared would, however in this
 * case we give the allocator a fixed size buffer for the new object
 * @param size The size of the buffer to allocate for the new counted T
 * @param args The arguments to be forwarded to the constructor of T
 * @return A counted pointer
 */
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

/**
 * An std::swap compatible swap function for ScriptItemPtr<T>
 * @param lhs The lhs pointer to swap
 * @param rhs The rhs pointer to swap
 */
template <typename T>
inline void swap(ScriptItemPtr<T>& lhs, ScriptItemPtr<T>& rhs) noexcept {
    lhs.swap(rhs);
}

}}

#endif	/* RS_LIBSCRIPTOBJECT_SCRIPT_ITEM_PTR_H */
