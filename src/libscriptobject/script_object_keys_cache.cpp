#include "script_object_keys_cache.h"

#include <functional>
#include <memory>

std::unordered_set<rs::scriptobject::ScriptObjectKeysPtr, rs::scriptobject::ScriptObjectKeysCache::KeyHash, rs::scriptobject::ScriptObjectKeysCache::KeyEqual> rs::scriptobject::ScriptObjectKeysCache::cache_[rs::scriptobject::ScriptObjectKeysCache::NUM_CACHES];
std::recursive_mutex rs::scriptobject::ScriptObjectKeysCache::cacheLock_[rs::scriptobject::ScriptObjectKeysCache::NUM_CACHES];

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysCache::AddObjectKeys(const ScriptObjectKeysPtr& keys) {
    auto index = getCacheIndex(keys);
    
    std::unique_lock<std::recursive_mutex> lk(cacheLock_[index]);
    auto newKeys = GetObjectKeys(keys);
    if (!newKeys) {
        cache_[index].insert(keys);
        newKeys = keys;
    }
    
    return newKeys;
}

rs::scriptobject::ScriptObjectKeysPtr rs::scriptobject::ScriptObjectKeysCache::GetObjectKeys(const ScriptObjectKeysPtr& keys) {       
    auto index = getCacheIndex(keys);
    
    std::unique_lock<std::recursive_mutex> lk(cacheLock_[index]);
    auto iter = cache_[index].find(keys);
    if (iter != cache_[index].end()) {
        return *iter;
    } else {
        return nullptr;
    }    
}

std::size_t rs::scriptobject::ScriptObjectKeysCache::getCount() {
    std::size_t count = 0;
    
    for (int i = 0; i < NUM_CACHES; i++) {
        std::unique_lock<std::recursive_mutex> lk(cacheLock_[i]);
        count += cache_[i].size();
    }
    
    return count;
}

void rs::scriptobject::ScriptObjectKeysCache::Flush() {
    for (int i = 0; i < NUM_CACHES; i++) {
        std::unique_lock<std::recursive_mutex> lk(cacheLock_[i]);
        cache_[i].clear();
    }
}

unsigned rs::scriptobject::ScriptObjectKeysCache::getCacheIndex(const ScriptObjectKeysPtr& keys) {
    auto temp = reinterpret_cast<unsigned*>(keys->hash);
    return *temp % NUM_CACHES;
}