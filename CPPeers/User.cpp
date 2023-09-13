/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <string>
#include <stdexcept>
#include <cctype>
#include "User.h"

using std::string;
using std::vector;

User::User(string userName) : userName(userName), userPosts() {
  if (userName.size() == 0) {
    throw std::invalid_argument("Invalid Argument");
  }
  for(long unsigned int i = 0; i < userName.size(); i++) {
    if(!islower(userName.at(i))) {
      throw std::invalid_argument("Invalid Argument");
    }
  }
}

string User::getUserName() {
  return userName;
}

vector<Post*>& User::getUserPosts() {
  return userPosts;
}

void User::addUserPost(Post* post) {
  if(post != nullptr) {
    userPosts.push_back(post);
  }
  else {
    throw std::invalid_argument("Invalid Argument");
  }
}
