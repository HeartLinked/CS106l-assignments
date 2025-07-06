/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>

std::string kYourName = "Feiyang Li"; // Don't forget to change this!
std::string get_initials(const std::string s);

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
    std::ifstream ifs(filename);
    if(!ifs.is_open()) return {};
    std::string name;
    std::set<std::string> s;
    while(std::getline(ifs, name)) {
      s.insert(name);
    }
    ifs.close();
    return s;
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> q;
  // for(auto it = students.begin(); it != students.end(); it++) {
  //   if((*it).at(0) == name.at(0)) q.push(&(*it));
  // }

  for(auto &s: students) {
    if (!s.empty() && !name.empty() && get_initials(name) == get_initials(s)) q.push(&s);
  }
  return q;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
    if(matches.empty()) return "NO MATCHES FOUND.";
    
    // For this example, we will just return the first match.
    // You can implement your own logic here to determine the best match.
    std::string match = *matches.front();
    matches.pop();
    
    // You can add more complex logic here to choose a different match.
    return match;

}

std::string get_initials(const std::string s) {
  if(s.empty()) return {};
  std::string ans = "";
  ans += s[0];
  for(int i = 0; i < s.size(); i++) {
    if(s[i] == ' ' && i + 1 < s.size()) return ans + s[i + 1];
  }
  return {};
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"
