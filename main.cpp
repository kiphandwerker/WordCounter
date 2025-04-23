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

std::string CleanWord(const std::string &word) {
    std::string cleaned;
    for (char ch : word) {
        if (std::isalpha(ch)) {
            cleaned += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
    }
    return cleaned;
}

std::vector<std::pair<std::string, int>> SortWordCounts(const std::unordered_map<std::string, int>& wordCounts) {
    std::vector<std::pair<std::string, int>> sortedWords(wordCounts.begin(), wordCounts.end());

    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const auto& a, const auto& b) {
            if (a.second == b.second)
                return a.first < b.first; 
            return a.second > b.second;
        });

    return sortedWords;
}

void PrintResults(const std::vector<std::pair<std::string, int>>& words) {
    for (const auto& pair : words) {
        std::cout << std::setw(15) << std::left << pair.first << " : " << pair.second << '\n';
    }
}
void WordandFreq(
    const std::string& filename,
    const std::unordered_set<std::string>& ExcludeWords,
    const std::unordered_set<std::string>& IncludeTerms,
    bool ShowFull = true,
    bool ShowInclusion = true) {

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return;
    }

    std::unordered_map<std::string, int> wordCounts;
    std::unordered_map<std::string, int> includeCounts;
    std::vector<std::string> allWords;
    std::string word;

    while (file >> word) {
        std::string cleaned = CleanWord(word);
        if (!cleaned.empty()) {
            allWords.push_back(cleaned);
            if (ExcludeWords.find(cleaned) == ExcludeWords.end()) {
                ++wordCounts[cleaned];
            }
        }
    }
    file.close();

    // Check for included terms (words or phrases)
    for (size_t i = 0; i < allWords.size(); ++i) {
        for (const auto& term : IncludeTerms) {
            std::istringstream iss(term);
            std::vector<std::string> termWords;
            std::string w;
            while (iss >> w) termWords.push_back(w);

            bool match = true;
            for (size_t j = 0; j < termWords.size(); ++j) {
                if (i + j >= allWords.size() || allWords[i + j] != termWords[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                ++includeCounts[term];
            }
        }
    }

    if (ShowFull) {
        std::cout << "Word Frequencies (excluding stop words):\n";
        PrintResults(SortWordCounts(wordCounts));
    }

    if (ShowInclusion) {
        std::cout << "\nIncluded Term Counts:\n";
        PrintResults(SortWordCounts(includeCounts));
    }
}

int main() {
    std::string filename = "example.txt";

    std::unordered_set<std::string> ExcludeWords = {
        "the", "and", "is", "in", "on", "at", "a", "an", "of", "to", "with", "for"
    };

    std::unordered_set<std::string> IncludeTerms = {
        "thought", "shall", "they", "take ye", "shall"
    };

    WordandFreq(filename, ExcludeWords, IncludeTerms, false, true);

    return 0;
}
