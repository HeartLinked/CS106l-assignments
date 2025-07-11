#include "user.h"

/**
 * Creates a new User with the given name and no friends.
 */
User::User(const std::string& name)
  : _name(name)
  , _friends(nullptr)
  , _size(0)
  , _capacity(0)
{
}

/**
 * Adds a friend to this User's list of friends.
 * @param name The name of the friend to add.
 */
void
User::add_friend(const std::string& name)
{
  if (_size == _capacity) {
    _capacity = 2 * _capacity + 1;
    std::string* newFriends = new std::string[_capacity];
    for (size_t i = 0; i < _size; ++i) {
      newFriends[i] = _friends[i];
    }
    delete[] _friends;
    _friends = newFriends;
  }

  _friends[_size++] = name;
}

/**
 * Returns the name of this User.
 */
std::string
User::get_name() const
{
  return _name;
}

/**
 * Returns the number of friends this User has.
 */
size_t
User::size() const
{
  return _size;
}

/**
 * Sets the friend at the given index to the given name.
 * @param index The index of the friend to set.
 * @param name The name to set the friend to.
 */
void User::set_friend(size_t index, const std::string& name)
{
  _friends[index] = name;
}

/** 
 * STUDENT TODO:
 * The definitions for your custom operators and special member functions will go here!
 */

User::~User() {
  delete[] _friends;
}

User::User(const User& user) {
  _name = user._name;
  _size = user._size;
  _capacity = user._capacity;
  if(user._friends == nullptr) {
    _friends = nullptr;
  } else {
    _friends = new std::string[_capacity];
    for(int i = 0; i < _size; i++) {
      _friends[i] = user._friends[i];
    }
  }
}

/**
 * 拷贝赋值运算符 (Copy Assignment Operator)
 * 作用：用 source 对象的值，覆盖一个已存在的 this 对象。
 */
User& User::operator = (const User& user) {
  if(this == &user) return *this;
  delete[] this -> _friends;

  _size = user._size;
  _capacity = user._capacity;
  _name = user._name;

  if(user._friends == nullptr) {
    _friends = nullptr;
  } else {
    _friends = new std::string[_capacity];
    for(int i = 0; i < _size; i++) {
      _friends[i] = user._friends[i];
    }
  }
  return *this;
}

std::ostream& operator << (std::ostream& os, const User& user) {
  os << "User(name=" << user.get_name() << ", friends=[";
  for(int i = 0; i < user._size; i++) {
    os << user._friends[i];
    if(i < user._size - 1) os << ", ";
  }
  os << "])";
  return os;
}

User& User::operator += (User& user) {
  if(this == &user) return *this;
  add_friend(user.get_name());
  user.add_friend(this -> get_name());
  return *this;
}

bool User::operator < (const User& user) const {
  return this->_name < user.get_name();
}
