#include "HelloWorld.h"
#include <iostream>
using std::cout;
using std::endl;

extern "C" {

HelloWorld *allocator() {

  cout << "HelloWorld allocator" << endl;
  return new HelloWorld();
}

void deallocator(HelloWorld *ptr) {

  cout << "HelloWorld deallocator" << endl;
  delete ptr;
}

void helloprint(HelloWorld *ptr) { cout << "evildojo" << endl; }
void helloprint2(HelloWorld *ptr) { ptr->hello(); }
}

void HelloWorld::hello() { cout << "HelloWorld new" << endl; }
//  void HelloWorld::hello() { cout << "Hello, World!" << endl; }

// HelloWorld::HelloWorld() {}

// void HelloWorld::hello() { cout << "Hello, World!" << endl; }
