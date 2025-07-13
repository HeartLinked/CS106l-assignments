#include "class_simple.h"

Book::Book() {}

Book::Book(std::string title, std::string author, int totalPages): title(title), author(author), totalPages(totalPages) {}

bool Book::isValidPage(int Page) {
    return !(Page > totalPages);
}

std::string Book::getTitle() const {
    return title;
}

void Book::goToPage(int Page) {
    currentPage = Page;
}

void Book::settotalPages(int Page) {
    totalPages = Page;
}