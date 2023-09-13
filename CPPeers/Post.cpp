/*
 *
 * This code is copyrighted (c) 2021 by
 * Texas A&M Computer Science
 *
 *	There will be RIGOROUS cheat checking on your exams!!
 *	DON'T POST ANYWHERE!! such as CHEGG, public Github, etc
 *  You will be legally responsible.
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cctype>
#include "Post.h"

using std::string;
using std::vector;

Post::Post(unsigned int postId, string userName, string postText)
  : postId(postId), userName(userName), postText(postText) {
  if (postId == 0 || userName == "" || postText == "") {
    throw std::invalid_argument("post constructor: invalid parameter values");
  }
}

unsigned int Post::getPostId() {
  return postId;
}

string Post::getPostUser() {
  return userName;
}

string Post::getPostText() {
  return postText;
}

vector<string> Post::findTags() {
  vector<string> allTags;
  std::stringstream stream;
  stream << postText;
  string word;

  while (stream >> word) {
    if(word.at(0) == '#') {
      if(word.at(word.size() - 1) == '!' or word.at(word.size() - 1) == ','
      or word.at(word.size() - 1) == '.' or word.at(word.size() - 1) == '?')
      {
        word.pop_back();
      }

      for(long unsigned int i = 0; i < word.size(); i++) {
        if(isupper(word.at(i))) {
          int c = word.at(i);
          word.at(i) = tolower(c);
        }
      }

      allTags.push_back(word);
    }
  }

  return allTags;
}
