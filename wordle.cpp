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
void allCombos(std::string in, std::string floating, size_t index, std::set<std::string>& results, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    std::string curr = in;
    allCombos(curr, floating, 0, results, dict);
    return results;
}

// Define any helper functions here
void allCombos(std::string in, std::string floating, size_t index, std::set<std::string>& results, const set<string>& dict){
  //base case
  if (index == in.size()){ // max characters
    if (floating.empty() && dict.find(in) != dict.end()){ // used all required letters
      results.insert(in);
    }
    return;
  }

  //not editing the fixed character i.e. -i--
  if (in[index] != '-'){
    allCombos(in, floating, index + 1, results, dict);
    return;
  }


  for (size_t i = 0; i < floating.size(); ++i){
    std::string newFloating = floating;
    newFloating.erase(i, 1);

    in [index] = floating[i];
    allCombos(in, newFloating, index + 1, results, dict);
  }

  if (floating.size() < (in.size() - index)){
    for (char x = 'a'; x <= 'z'; ++x){
      if (floating.find(x) != string::npos){
        continue;
      }
      in[index] = x;
      allCombos(in, floating, index + 1, results, dict);
    }
  }
  in [index] = '-';
}