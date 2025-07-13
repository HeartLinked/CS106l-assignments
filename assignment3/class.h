#pragma once

#include <map>
#include <string>

class Book {
private:
  std::string title;
  std::string author;
  int totalPages;
  int currentPage;
  bool isValidPage(int Page);

public:
  Book();
  Book(std::string title, std::string author, int totalPages);

  std::string getTitle() const;
  void goToPage(int page);
  void settotalPages(int page);
};
