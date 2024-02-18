/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <iterator>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                                                         const string &word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    ifstream wordsFile(word_list_fname);
    std::string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) {
            if (word.size() == 5) {
                std::string self = word;
                std::string first = self.substr(1);
                std::string second = self.substr(0,1) + self.substr(2);
                if (d.homophones(self, first) && d.homophones(first, second)) {
                    std::tuple<std::string, std::string, std::string> tup(self, first, second);
                    ret.push_back(tup);
                }
            }
        }
    }


    
        
    
    /* Your code goes here! */
    return ret;
}
