#include "KeyValueStore.h"
#include <filesystem>
#include <shared_mutex>

using json = nlohmann::json;
namespace fs = std::filesystem;

KeyValueStore::KeyValueStore(size_t cacheSize) : cache(cacheSize) {
    loadFromFile(dataFile);
}

KeyValueStore::~KeyValueStore() {
    saveToFile(dataFile);
}


void KeyValueStore::set(const std::string& key, const std::string& value) {
    std::unique_lock lock(storeMutex);
    store[key] = value;
    cache.put(key, value);
}


std::optional<std::string> KeyValueStore::get(const std::string& key) {
    {
        std::shared_lock lock(storeMutex);
        auto cachedValue = cache.get(key);
        if (cachedValue) return cachedValue; 
    }

    
    std::shared_lock lock(storeMutex);
    auto it = store.find(key);
    if (it != store.end()) {
        cache.put(key, it->second); 
        return it->second;
    }
    return std::nullopt;
}


bool KeyValueStore::remove(const std::string& key) {
    std::unique_lock lock(storeMutex);
    if (store.erase(key) > 0) {
        cache.put(key, "");  
        std::cout << "Removed key: [" << key << "]\n";
        return true;
    }
    return false;
}


void KeyValueStore::displayAll() const {
    std::shared_lock lock(storeMutex);
    if (store.empty()) {
        std::cout << "Store is empty.\n";
        return;
    }
    std::cout << "Current Key-Value Pairs:\n";
    for (const auto& pair : store) {
        std::cout << "[" << pair.first << "] -> [" << pair.second << "]\n";
    }
}


void KeyValueStore::saveToFile(const std::string& filename) {
    try {
        std::unique_lock lock(storeMutex);
        fs::create_directories("data");
        std::ofstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for writing: " << filename << "\n";
            return;
        }
        json j(store);
        file << j.dump(4);
        std::cout << "Data saved to " << filename << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving data: " << e.what() << "\n";
    }
}


void KeyValueStore::loadFromFile(const std::string& filename) {
    try {
        if (!fs::exists(filename)) {
            std::cout << "No existing data file found. Starting with an empty store.\n";
            return;
        }
        std::unique_lock lock(storeMutex);
        std::ifstream file(filename);
        if (!file) {
            std::cerr << "Error opening file for reading: " << filename << "\n";
            return;
        }
        json j;
        file >> j;
        store = j.get<std::unordered_map<std::string, std::string>>();
        std::cout << "Data loaded from " << filename << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading data: " << e.what() << "\n";
    }
}
