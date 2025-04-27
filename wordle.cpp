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
std::set<std::string> allCombos(std::string in, std::string floating, size_t index);
std::set<std::string> validWords(const std::set<std::string>& combos, const std::set<std::string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> combos = allCombos(in, floating, 0);
    return validWords(combos, dict);
}

// Define any helper functions here
std::set<std::string> allCombos(std::string in, std::string floating, size_t index){
  std::set<std::string> results;

  //base case
  if (index == in.size()){ // max characters
    if (floating.empty()){ // used all required letters
      results.insert(in);
    }
    return results;
  }

  //not editing the fixed character i.e. -i--
  if (in[index] != '-'){
    return allCombos(in, floating, index + 1);
  }

// character generation for ---
  std::set<std::string> temp;

  // use floating first
  if (in[index] == '-'){
    for (unsigned int i = 0; i < floating.size(); ++i){
      std::string newIn;
      newIn = in;
      newIn[index] = floating[i];

      std::string newFloating;
      newFloating = floating;
      newFloating.erase(i, 1); //remove used letter

      std::set<std::string> newResults = allCombos(newIn, newFloating, index + 1);
      temp.insert(newResults.begin(), newResults.end());
    }
  }

  // fill in the rest
  if (floating.size() < (in.size() - index)){
    for (char c = 'a' ; c <= 'z'; ++c){
      if (floating.find(c) >= floating.size()){ //
        std::string newIn = in;
        newIn[index] = c;

        std::set<std::string> newResults = allCombos(newIn, floating, index + 1); // no edits to floating
        temp.insert(newResults.begin(), newResults.end());
      }
    }
  }
  return temp;
}

std::set<std::string> validWords(const std::set<std::string> & combos, const std::set<std::string> & dict){
  std::set<std::string> validOutput;

  for (const std::string& word : combos){
    if (dict.find(word) != dict.end()){ // look through valid words dictionary
      validOutput.insert(word);
    }
  }
  return validOutput;
}