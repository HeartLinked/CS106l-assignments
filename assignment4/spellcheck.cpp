#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include <string>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  std::vector<std::string::iterator> vec = find_all(source.begin(), source.end(), [](char c){
    return c == ' ' || c == '\t' || c == '\n';
  });
  Corpus tokens;

  std::transform(vec.begin(), vec.end() - 1, vec.begin() + 1, std::inserter(tokens, tokens.end()), [&source](auto it_begin, auto it_end){
    return Token(source, it_begin, it_end);
  });

  std::erase_if(tokens, [](const Token& token){
    return token.content.empty();
  });


  return tokens;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  auto source_filtered = source 
  | std::ranges::views::filter([&dictionary](const Token& token) {
    return !dictionary.contains(token.content);
  })
  | std::ranges::views::transform([&dictionary](const Token& token) {
    auto suggestions_view = dictionary | std::ranges::views::filter([&token](const std::string s){
      return levenshtein(token.content, s) == 1;
    });
    std::set<std::string> suggestions(suggestions_view.begin(), suggestions_view.end());
    return Misspelling{token, suggestions};
  }) 
  | std::ranges::views::filter([](const Misspelling& misspelling){
    return !misspelling.suggestions.empty();
  });


  return std::set<Misspelling>(source_filtered.begin(), source_filtered.end());
};

/* Helper methods */

#include "utils.cpp"