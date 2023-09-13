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
#include "Tag.h"

using std::string;
using std::vector;

Tag::Tag(string tagName) : tagName(tagName), tagPosts() {

  if(tagName.size() < 2) {
    throw std::invalid_argument("Invalid Argument");
  }

  if(tagName.at(0) != '#') {
    throw std::invalid_argument("Invalid Argument");
  }

  for(long unsigned int i = 1; i < tagName.size() - 1; i++) {
    if(!islower(tagName.at(i))) {
      throw std::invalid_argument("Invalid Argument");
    }
  }

  if(islower(tagName.at(tagName.size() - 1)) == false 
  and tagName.at(tagName.size() - 1) != '!'
  and tagName.at(tagName.size() - 1) != ',' 
  and tagName.at(tagName.size() - 1) != '.' 
  and tagName.at(tagName.size() - 1) != '?') 
  {
    throw std::invalid_argument("Invalid Argument");
  }
}

string Tag::getTagName() {
  return tagName;
}

vector<Post*>& Tag::getTagPosts() {
  return tagPosts;
}

void Tag::addTagPost(Post* post) {
  if(post != nullptr) {
    tagPosts.push_back(post);
  }
  else {
    throw std::invalid_argument("Invalid Argument");
  }
}
