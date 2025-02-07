#ifndef KEYVALUESTORE_H
#define KEYVALUESTORE_H

#include <unordered_map>
#include <string>
#include <optional>
#include <iostream>
#include <fstream>
#include <shared_mutex>
#include <nlohmann/json.hpp>
#include "Cache.h" 

class KeyValueStore {
public:
    KeyValueStore(size_t cacheSize = 5); 
    ~KeyValueStore();

    void set(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key);
    bool remove(const std::string& key);
    void displayAll() const;

    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

private:
    std::unordered_map<std::string, std::string> store;
    std::string dataFile = "data/data.json";
    mutable std::shared_mutex storeMutex;

    LRUCache cache; 
};

#endif
