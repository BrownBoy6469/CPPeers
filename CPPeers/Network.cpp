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
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "Network.h"

using std::string;
using std::vector;

Network::Network() {
  // empty containers of vectors already created
  // no implementation is needed here
}

void Network::loadFromFile(string fileName) {
  std::ifstream file(fileName);
  string type = "";
  string userName = "";
  string postIdTxt = "";
  string postText = "";
  if(file.is_open()) {
    while(file >> type) {
      if(file.eof()) {
        //std::cout << "eof" << std::endl;
        return;
      }
      if(type == "User") {
        //std::cout << "User detected" << std::endl;
        file >> userName;
        if(file.bad() or file.fail()) {
          throw std::runtime_error("Runtime Error1");
        }
        for(long unsigned int i = 0; i < userName.size(); i++) {
          if(!islower(userName.at(i))) {
            throw std::runtime_error("Runtime Error2");
          }
        }

        try {
          addUser(userName);
        }
        catch (std::invalid_argument& e) {
          throw std::runtime_error("Runtime Error10");
        }
      }
      else if(type == "Post") {
        //std::cout << "Post detected" << std::endl;
        file >> postIdTxt;
        if(file.bad() or file.fail()) {
          throw std::runtime_error("Runtime Error3");
        }
        if(!isdigit(postIdTxt.at(0))) {
          throw std::runtime_error("Runtime Error4");
        }
        /*for(long unsigned int j = 0; i < postId.size(); i++) {
          if(!isdigit(postIdTxt.at(i))) {
            throw std::runtime_error("Invalid Argument");
          }
        }*/

        file >> userName;
        if(file.bad() or file.fail()) {
          throw std::runtime_error("Runtime Error5");
        }
        for(long unsigned int j = 0; j < userName.size(); j++) {
          if(!islower(userName.at(j))) {
            throw std::runtime_error("Runtime_Error6");
          }
        }

        std::getline(file, postText);
        if(file.bad() or file.fail()) {
          throw std::runtime_error("Runtime Error7");
        }
        if(postText == "\0") {
          throw std::runtime_error("Runtime Error8");
        }

        unsigned int postId = static_cast<unsigned int>(std::stoul(postIdTxt));
        postText.erase(postText.begin());
        try {
          addPost(postId, userName, postText);
        }
        catch (std::invalid_argument& e) {
          throw std::runtime_error("Runtime Error11");
        } 
      }

      else {
        std::cout << "Unknown" << std::endl;
        throw std::runtime_error("Runtime Error9");
      }
    }
  }
  else {
    throw std::invalid_argument("Invalid Argument");
  }
}

void Network::addUser(string userName) {
  for(long unsigned int i = 0; i < userName.size(); i++) {
    if(isupper(userName.at(i))) {
      int c = userName.at(i);
      userName.at(i) = tolower(c);
    }
  }

  for(int j = 0; j < users.size(); j++) {
    if((*users.at(j)).getUserName() == userName) {
      throw std::invalid_argument("Invalid Argument");
    }
  }

  User* newUser = new User(userName);
  users.push_back(newUser);
  std::cout << "Added User " << userName << std::endl;
}

void Network::addPost(unsigned int postId, string userName, string postText) {
  bool isName = false;
  int index = 0;
  for(int j = 0; j < users.size(); j++) {
    if((*users.at(j)).getUserName() == userName) {
      index = j;
      isName = true;
    }
  }
  if(!isName) {
    throw std::invalid_argument("Invalid Argument");
  }

  for(int i = 0; i < posts.size(); i++) {
    if((*posts.at(i)).getPostId() == postId) {
      throw std::invalid_argument("Invalid Argument");
    }
  }

  Post* newPost = new Post(postId, userName, postText);
  posts.push_back(newPost);
  (*users.at(index)).addUserPost(newPost);

  vector<string> allTags{(*newPost).findTags()};
  /*for(int a = 0; a < allTags.size(); a++) {
    std::cout << allTags.at(a) << std::endl;
  }*/

  for(int k = 0; k < allTags.size(); k++) {
    for(int l = 0; l < tags.size(); l++) {
      if((*tags.at(l)).getTagName() == allTags.at(k)) {
        (*tags.at(l)).addTagPost(newPost);
        //std::cout << (*tags.at(l)).getTagPosts().size() << std::endl;
        break;
      }
    }
    try {
      Tag* newTag = new Tag(allTags.at(k));
      tags.push_back(newTag);
      (*tags.at(tags.size() - 1)).addTagPost(newPost);
    }
    catch (std::invalid_argument& e) {}
  }

  std::cout << "Added Post " << postId << " by " << userName << std::endl;
}

vector<Post*> Network::getPostsByUser(string userName) {
  bool isName = false;
  int index = 0;

  for(int i = 0; i < users.size(); i++) {
    if((*users.at(i)).getUserName() == userName) {
      index = i;
      isName = true;
    }
  }
  if(!isName) {
    throw std::invalid_argument("Invalid Argument");
  }

  return (*users.at(index)).getUserPosts();
}

vector<Post*> Network::getPostsWithTag(string tagName) {
  bool isTag = false;
  int index = 0;
  int size = 0;

  for(int i = 0; i < tags.size(); i++) {
    //std:: cout << (*tags.at(i)).getTagPosts().size() << std::endl;
    //std:: cout << (*tags.at(i)).getTagName() << std::endl;
    if((*tags.at(i)).getTagName() == tagName) {
      if((*tags.at(i)).getTagPosts().size() > size) {
        size = (*tags.at(i)).getTagPosts().size();
        index = i;
      }      
      isTag = true;
    }
  }
  if(!isTag) {
    throw std::invalid_argument("Invalid Argument");
  }

  //std::cout << (*tags.at(index)).getTagPosts().size() << std::endl;
  return (*tags.at(index)).getTagPosts();
}

vector<string> Network::getMostPopularHashtag() {
  vector<string> mostPop;
  int size = 0;
  size = (*tags.at(0)).getTagPosts().size();
  mostPop.push_back((*tags.at(0)).getTagName());
  //std:: cout << (*tags.at(0)).getTagName() << " " << (*tags.at(0)).getTagPosts().size() << std::endl;

  for(int i = 1; i < tags.size(); i++) {
    //std:: cout << (*tags.at(i)).getTagName() << " " << (*tags.at(i)).getTagPosts().size() << std::endl;
    if((*tags.at(i)).getTagPosts().size() > size) {
      mostPop.pop_back();
      mostPop.push_back((*tags.at(i)).getTagName());
      size = (*tags.at(i)).getTagPosts().size();
    }
  }

  for(int j = 1; j < tags.size(); j++) {
    if((*tags.at(j)).getTagPosts().size() == size) {
      if((*tags.at(j)).getTagName() != mostPop.at(0)) {
        mostPop.push_back((*tags.at(j)).getTagName());
      }
    }
  }

  return mostPop;
}

/**
  * Destructor
  * Do not change; already implemented.
  */
Network::~Network() {
  for (unsigned int i = 0; i < users.size(); ++i) {
    delete users.at(i);
  }
  for (unsigned int i = 0; i < tags.size(); ++i) {
    delete tags.at(i);
  }
  for (unsigned int i = 0; i < posts.size(); ++i) {
    delete posts.at(i);
  }
}
