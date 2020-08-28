#include <fstream>
#include <iostream>
#include <forward_list>

void print_list(std::forward_list<int> list) {
  for (auto value : list)
    std::cout << value << " ";
  std::cout << std::endl;
}

std::forward_list<int> read_list_push_front(const char *filename, std::forward_list<int> &list) {
  std::ifstream fin(filename);
  if (!fin.is_open())
    std::cout <<filename<<" is not found!" << std::endl;
  else {
    int value;
    while (fin >> value) { list.push_front(value); }
  }
  return list;
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file name>\n";
    return 1;
  }
  std::forward_list<int> list;

  list = read_list_push_front(argv[1],list);
  print_list(list);
  
  std::cout << std::endl << "Reversing: " << std::endl;
  list.reverse();
  print_list(list);

  
  std::cout << std::endl << "Sorting: " << std::endl;
  list.sort();
  print_list(list);

  std::cout << std::endl << "Uniquing: " << std::endl;
  list.unique();
  print_list(list);
  
  
  std::cout << std::endl << "Clearing: " << std::endl;
  list.clear();
  print_list(list);
}
