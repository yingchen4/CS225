#include "List.h"
#include <iostream>
#include <string>
#include "List.h"

int main() {
  List<int> list;
  list.insertBack(5);
  list.insertBack(2);
  list.insertBack(2);
  list.insertBack(6);
  list.insertBack(0);
  list.insertBack(10);
  list.insertBack(1);
  list.print(std::cout);
  std::cout << std::endl;

  list.sort();
  std::cout << "sorted" << std::endl;
  list.print(std::cout);
  std::cout << std::endl;
}
