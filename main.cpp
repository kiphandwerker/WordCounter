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

void PrintResults(auto &words){
    for (const auto& pair : words) {
        std::cout << std::setw(15) << std::left << pair.first << " : " << pair.second << '\n';
    }
}
void WordandFreq(
    const std::string& filename, 
    const std::unordered_set<std::string>& ExcludeWords,
    const std::unordered_set<std::string>& IncludeWords,
    bool ShowFull = {true},
    bool ShowInclusion = {true}) {
    
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::unordered_map<std::string, int> wordCounts;
    std::unordered_map<std::string, int> specificWordCounts;
    std::string word;

    while (file >> word) {
        std::string cleaned = CleanWord(word);
        if (cleaned.empty()) continue;

        if (ExcludeWords.find(cleaned) == ExcludeWords.end()) {
            ++wordCounts[cleaned];
        }

        if (IncludeWords.find(cleaned) != IncludeWords.end()) {
            ++specificWordCounts[cleaned];
        }
    }

    file.close();

    auto sortedWords = SortWordCounts(wordCounts);

    if(ShowFull == true){
        std::cout << "Word Frequencies (excluding specified words):\n";
        PrintResults(sortedWords);
    }

    auto sortedSpecificWords = SortWordCounts(specificWordCounts);

    if(ShowInclusion == true){
        std::cout << "\nSpecific Word Counts (sorted):\n";
        PrintResults(sortedSpecificWords);
    }

}

int main() {
    std::string filename = "example.txt";
    bool ShowFull = {false};

    std::unordered_set<std::string> ExcludeWords = {
        "the", "and", "is", "in", "on", "at", "a", "an", "of", "to", "with", "for"
    };

    std::unordered_set<std::string> IncludeWords = {
        "thought", "shall", "they", "take"
    };

    WordandFreq(filename, ExcludeWords, IncludeWords, ShowFull = false);

    return 0;
}
