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

    std::unordered_map<std::string, int> wordCounts;
    std::string word;

    while (file >> word) {
        std::string cleaned = CleanWord(word);
        if (!cleaned.empty()) {
            ++wordCounts[cleaned];
        }
    }

    file.close();

    std::cout << "Word Frequencies:\n";
    for (const auto& pair : wordCounts) {
        std::cout << std::setw(15) << std::left << pair.first << " : " << pair.second << '\n';
    }
}
// Example usage
int main() {
    std::string filename = "example.txt"; // Replace with your actual filename
    WordandFreq(filename);
    return 0;
}
