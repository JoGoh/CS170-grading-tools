#include <iostream>             // cout, endl
#include <iomanip>              // setw
#include <string>
#include "list.h"

int main() {
  std::string funcName[6] = {"AddToFront ",
                             "AddToEnd   ",
                             "Find       ",
                             "Delete     ",
                             "Insert     ",
                             "Concatenate"};

  Node *list1 = 0, *list2 = 0;
  int choice, listID, value, position;
  Node **pChosenList, *foundNode = 0;

  do {
    std::cin >> choice >> listID >> value >> position;

    if (choice != 0) {
      std::cout << funcName[choice-1] << ": ";

      if (listID == 1)
        pChosenList = &list1;
      else
        pChosenList = &list2;

      switch (choice) {
        case 1:
          AddToFront(pChosenList, value);
          break;

        case 2:
          AddToEnd(pChosenList, value);
          break;

        case 3:
          foundNode = Find(*pChosenList, value);
          break;

        case 4:
          Delete(pChosenList, value);
          break;

        case 5:
          Insert(pChosenList, value, position);
          break;

        case 6:
          Concat(&list1, &list2);
          break;
      }

      switch (choice) {
        case 1:
        case 2:
        case 4:
        case 5:
          std::cout << "List" << listID << " (" << std::setw(2) << 
              Count(*pChosenList) << " nodes): ";
              PrintList(*pChosenList);
          break;

        case 3:
          if (foundNode)
              std::cout << "Value " << value << 
              " was found in List" << listID << ".\n";
          else
              std::cout << "Value " << value << 
              " was not found in List" << listID << ".\n";
          break;

        case 6:
          std::cout << "\n";
          std::cout << "List1" <<
              " (" << std::setw(2) << Count(list1) << " nodes): ";
          PrintList(list1);

          std::cout << "List2" <<
              " (" << std::setw(2) << Count(list2) << " nodes): ";
          PrintList(list2);
          break;
      }
    }
  } while (choice != 0);

  FreeList(list1);
  FreeList(list2);
}
