#ifndef CACHE_H
#define CACHE_H

#include <unordered_map>
#include <list>
#include <mutex>
#include <optional>
#include <iostream>

class LRUCache {
public:
    LRUCache(size_t capacity);

    std::optional<std::string> get(const std::string& key);
    void put(const std::string& key, const std::string& value);
    void displayCache() const;

private:
    size_t capacity;
    std::list<std::pair<std::string, std::string>> cacheList;
    std::unordered_map<std::string, std::list<std::pair<std::string, std::string>>::iterator> cacheMap;
    mutable std::mutex cacheMutex; 
};

#endif
