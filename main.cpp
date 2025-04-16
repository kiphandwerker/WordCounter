#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>

std::string CleanWord(const std::string& word) {
    std::string cleaned;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return cleaned;
}

void WordandFreq(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

}
// Example usage
int main() {

    std::cout << "Hello world" << std::endl;
    return 0;
}
