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
void helper(string word, string floatingWord, const set<std::string>& dict, std::set<string>& output , size_t next);

// Definition of primary wordle function
std::set<std::string> wordle(
  const std::string& in,
  const std::string& floating,
  const std::set<std::string>& dict)
{
  // We need to return a set of strings that contain all the words
  // in the dictionary that satisfies the fixed and floating requirements
  set<string> output;
  
  // this is the index we will go through
  size_t next = 0;

  // Now let's construct and call a helper recrusive function that 
  // will use the floating and fixed hints to create words that check out
  helper(in, floating, dict, output, next);

  // And finally we can return the outputs from the helper function
  return output;

}

// Define any helper functions here
void helper(string word, string floatingWord, const set<std::string>& dict, std::set<string>& output, size_t next)
{

  if (word.size() == next) {
    if ((dict.find(word) != dict.end()) && (floatingWord.empty()))  {
      output.insert(word);
    }
    return;
  }

  if (word[next] != '-') {
    helper(word, floatingWord, dict, output, next + 1);
  }
  else  {
    for (char start = 'a'; start <= 'z'; start++) {
      string word2 = word;
      word2[next] = start;

      string floatingWord2 = floatingWord;
      size_t letter = floatingWord.find(start);

      if (letter != string::npos) {
        floatingWord2.erase(letter, 1);
      }

      helper(word2, floatingWord2, dict, output, next + 1);
    }
  }

}
