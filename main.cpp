#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

// Helper function to clean a word (remove punctuation and convert to lowercase)
std::string cleanWord(const std::string& word) {
    std::string cleaned;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return cleaned;
}

// Example usage
int main() {
    
    std::cout << "Hello world" << std::endl;
    return 0;
}
