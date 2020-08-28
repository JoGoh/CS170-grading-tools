#include <fstream>
#include <iostream>
#include "list.h"

#include <cstdio>
#include <fstream>
#include <ctime>

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

void mainFunc(char **argv)
{
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
  
}

void createTmpFile()
{
  std::ofstream file;
  file.open ("tmpLarge.txt");
  
  file << "Process failed to complete within time limit";
}

void deleteTmpFile()
{
  remove("tmpLarge.txt");
}

void createTimeFile(double value)
{
  std::ofstream file;
  file.open ("timing.txt");
  
  file << "Process completed in " << value << " ms!";
}

int main(int argc, char **argv) {
  if(argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file name>\n";
    return 1;
  }
  
  createTmpFile();
  
  std::clock_t    start;
  start = std::clock();
  mainFunc(argv);
  
  auto ms = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000.0);
  //std::cout << "Time: " <<  << " ms" << std::endl;
  
  deleteTmpFile();
  
  createTimeFile(ms);
  
  return 0;
}
