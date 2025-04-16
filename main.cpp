#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
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

void WordandFreq(const std::string& filename, const std::unordered_set<std::string>& excludeWords) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::unordered_map<std::string, int> wordCounts;
    std::string word;

    while (file >> word) {
        std::string cleaned = CleanWord(word);
        if (!cleaned.empty() && excludeWords.find(cleaned) == excludeWords.end()) {
            ++wordCounts[cleaned];
        }
    }

    file.close();

    std::vector<std::pair<std::string, int>> sortedWords(wordCounts.begin(), wordCounts.end());

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const auto& a, const auto& b) {
            if (a.second == b.second)
                return a.first < b.first; 
            return a.second > b.second;
        });

    std::cout << "Word Frequencies (excluding specified words):\n";
    for (const auto& pair : sortedWords) {
        std::cout << std::setw(15) << std::left << pair.first << " : " << pair.second << '\n';
    }

    const int maxBars = 10;
    const int maxBarWidth = 20;

    std::cout << "\nASCII Histogram (top " << maxBars << "):\n\n";

    int count = 0;
    int maxFreq = sortedWords.empty() ? 0 : sortedWords[0].second;

    for (const auto& pair : sortedWords) {
        if (count++ >= maxBars) break;

        int barLength = static_cast<int>((static_cast<double>(pair.second) / maxFreq) * maxBarWidth);
        std::string bar(static_cast<std::size_t>(std::max(0, barLength)), '#');

        std::cout << std::setw(15) << std::left << pair.first
                  << " | " << std::setw(maxBarWidth) << std::left << bar
                  << " (" << pair.second << ")\n";
    }
}

int main() {
    std::string filename = "example.txt";

    // Words to exclude
    std::unordered_set<std::string> excludeWords = {
        "the", "and", "is", "in", "on", "at", "a", "an", "of", "to", "with"
    };

    WordandFreq(filename, excludeWords);
    return 0;
}
