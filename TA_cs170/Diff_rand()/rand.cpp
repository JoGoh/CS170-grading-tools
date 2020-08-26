#include <iostream>
#include <cstdlib> 
// generate random numbers between low and high 
int RandomInt(int low, int high)
{
  int number = std::rand() % (high - low + 1) + low;
  return number;
}

int main ()
{
	int size = 10;
	
	int *array = new int[size]; //dynamic
	
	for (int i = 0; i < size; i++)
    array[i] = RandomInt(1, 9);
		
	for (int i{}; i<size; i++)
		std::cout<<array[i]<<std::endl;	
		
	delete[] array;
	
	return 0; 
}