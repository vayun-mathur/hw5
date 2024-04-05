#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// check if word is valid
bool isValid(string word, const string& in, const string& floating);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> result;
    for (const string& word : dict) {
        bool valid = true;
        for(char c : word) {
            if(!(c >= 'a' && c <= 'z')) {
                valid = false;
                break;
            }
        }
        if (valid && isValid(word, in, floating)) {
            result.insert(word);
        }
    }
    return result;
}

// Define any helper functions here
// in is the characters that must be in the word, where '-' is an unknown character
// floating is the characters that must be somewhere in the word
bool isValid(string word, const string& in, const string& floating) {
    if(word.length() != in.length()) {
        return false;
    }
    map<char, int> wordMap;
    int len = word.length();

    for(int i = 0; i < len; i++) {
        if(in[i] == '-') {
            wordMap[word[i]]++;
            continue;
        }
        if(in[i] != word[i]) {
            return false;
        }
    }
    map<char, int> floatingMap;
    for(char c : floating) {
        floatingMap[c]++;
    }
    for(auto& p : floatingMap) {
        if(wordMap[p.first] < p.second) {
            return false;
        }
    }
    return true;
}