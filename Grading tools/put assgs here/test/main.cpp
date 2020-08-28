#include <fstream>
#include <iostream>
#include "list.h"

Node *read_list_push_front(const char *filename, Node *&list)
{
  std::ifstream fin(filename);
  if (!fin.is_open())
    std::cout << filename << " is not found!" << std::endl;
  else {
    int value;
    while (fin >> value) { push_front(list, value); }
  }

  return list;
}

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file name>\n";
    return 1;
  }
  
  Node *list = nullptr;

  list = read_list_push_front(argv[1], list);
  print_list(list);
  
  std::cout << std::endl << "Reversing: " << std::endl;
  
  reverse(list);
  print_list(list);
  
  
  std::cout << std::endl << "Sorting: " << std::endl;

  sort(list);
  print_list(list);
  
  std::cout << std::endl << "Uniquing: " << std::endl;

  unique(list);
  print_list(list);
  
  std::cout << std::endl << "Clearing: " << std::endl;
  
  clear(list);
  print_list(list);

  return 0;
}
