#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>
#include <vector>
#include <algorithm>

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

    // Transfer map to vector for sorting
    std::vector<std::pair<std::string, int>> sortedWords(wordCounts.begin(), wordCounts.end());

    // Sort by frequency (descending). If same frequency, sort alphabetically.
    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const auto& a, const auto& b) {
            if (a.second == b.second)
                return a.first < b.first; // alphabetical order
            return a.second > b.second;   // descending frequency
        });

    std::cout << "Word Frequencies (sorted):\n";
    for (const auto& pair : sortedWords) {
        std::cout << std::setw(15) << std::left << pair.first << " : " << pair.second << '\n';
    }
}

int main() {
    std::string filename = "example.txt"; // Replace with your actual filename
    WordandFreq(filename);
    return 0;
}
