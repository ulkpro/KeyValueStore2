#include <iostream>
#include <vector>
#include <string>
#include "KeyValueStore.h"

void printUsage() {
    std::cout << "Usage:\n";
    std::cout << "  KeyValueStore2 --set <key> <value>      # Insert a key-value pair\n";
    std::cout << "  KeyValueStore2 --get <key>             # Retrieve a value by key\n";
    std::cout << "  KeyValueStore2 --remove <key>          # Delete a key\n";
    std::cout << "  KeyValueStore2 --display               # Show all key-value pairs\n";
    std::cout << "  KeyValueStore2 --help                  # Show usage information\n";
}

int main(int argc, char* argv[]) {
    KeyValueStore kvs(5); 

    if (argc < 2) {
        printUsage();
        return 1;
    }

    std::string command = argv[1];

    if (command == "--set") {
        if (argc != 4) {
            std::cerr << "Error: --set requires both a key and a value.\n";
            printUsage();
            return 1;
        }
        std::string key = argv[2];
        std::string value = argv[3];
        kvs.set(key, value);
        std::cout << "Inserted: [" << key << "] -> [" << value << "]\n";
    }

    else if (command == "--get") {
        if (argc != 3) {
            std::cerr << "Error: --get requires a key.\n";
            printUsage();
            return 1;
        }
        std::string key = argv[2];
        auto result = kvs.get(key);
        if (result) {
            std::cout << "Value: " << *result << "\n";
        }
        else {
            std::cout << "Key not found.\n";
        }
    }

    else if (command == "--remove") {
        if (argc != 3) {
            std::cerr << "Error: --remove requires a key.\n";
            printUsage();
            return 1;
        }
        std::string key = argv[2];
        if (kvs.remove(key)) {
            std::cout << "Key removed: " << key << "\n";
        }
        else {
            std::cout << "Key not found.\n";
        }
    }

    else if (command == "--display") {
        kvs.displayAll();
    }

    else if (command == "--help") {
        printUsage();
    }

    else {
        std::cerr << "Error: Unknown command '" << command << "'.\n";
        printUsage();
        return 1;
    }

    return 0;
}
