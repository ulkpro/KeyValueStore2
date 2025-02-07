#include "Cache.h"

LRUCache::LRUCache(size_t capacity) : capacity(capacity) {}

std::optional<std::string> LRUCache::get(const std::string& key) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    auto it = cacheMap.find(key);
    if (it == cacheMap.end()) {
        return std::nullopt;
    }

    
    cacheList.splice(cacheList.begin(), cacheList, it->second);
    return it->second->second;
}


void LRUCache::put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(cacheMutex);

    auto it = cacheMap.find(key);
    if (it != cacheMap.end()) {
        
        cacheList.splice(cacheList.begin(), cacheList, it->second);
        it->second->second = value;
        return;
    }

    
    if (cacheList.size() >= capacity) {
        auto last = cacheList.back().first;
        cacheList.pop_back();
        cacheMap.erase(last);
    }

    
    cacheList.emplace_front(key, value);
    cacheMap[key] = cacheList.begin();
}


void LRUCache::displayCache() const {
    std::lock_guard<std::mutex> lock(cacheMutex);
    std::cout << "Cache Contents:\n";
    for (const auto& pair : cacheList) {
        std::cout << "[" << pair.first << "] -> [" << pair.second << "]\n";
    }
}
