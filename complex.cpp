#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <iomanip> 


std::vector<std::string> tokenize(const std::string& code) {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : code) {
        if (std::isalnum(c) || c == '_') {
            token += c;
        } else if (!token.empty()) {
            tokens.push_back(token);
            token.clear();
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// Function to compute Jaccard similarity between two sets
double jaccardSimilarity(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2) {
    std::unordered_set<std::string> intersection;
    std::unordered_set<std::string> unionSet;

    for (const std::string& token : set1) {
        if (set2.find(token) != set2.end()) {
            intersection.insert(token);
        }
        unionSet.insert(token);
    }

    for (const std::string& token : set2) {
        unionSet.insert(token);
    }

    if (unionSet.empty()) {
        return 0.0;
    }

    return static_cast<double>(intersection.size()) / unionSet.size();
}

int main() {
    std::string file1Name, file2Name;

    std::cout << "Enter the first file name: ";
    std::cin >> file1Name;

    std::cout << "Enter the second file name: ";
    std::cin >> file2Name;

    std::ifstream file1(file1Name);
    std::ifstream file2(file2Name);

    if (!file1 || !file2) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    std::string code1((std::istreambuf_iterator<char>(file1)), std::istreambuf_iterator<char>());
    std::string code2((std::istreambuf_iterator<char>(file2)), std::istreambuf_iterator<char>());

    std::vector<std::string> tokens1 = tokenize(code1);
    std::vector<std::string> tokens2 = tokenize(code2);

    std::unordered_set<std::string> set1(tokens1.begin(), tokens1.end());
    std::unordered_set<std::string> set2(tokens2.begin(), tokens2.end());

    double similarity = jaccardSimilarity(set1, set2);

    std::cout << "Plagiarism Similarity: " << std::fixed << std::setprecision(2) << similarity * 100.0 << "%" << std::endl;

    return 0;
}
