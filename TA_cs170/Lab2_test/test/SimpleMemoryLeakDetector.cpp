/******************************************************************************/
/*!
\file   SimpleMemoryLeakDetector.cpp
\author Tan Yu Jie
\par    email: yujie.tan\@digipen.edu
\par    DigiPen login: yujie.tan
\par    Course: CS170
\par    Lab #13
\date   12/4/2017
\brief  
    This file contains the implementation of the following functions for the 
    lab assignment 13
      
    Class Functions include:
    get_detector
    print_stats
    allocate
    deallocate
    grow
    Detector()
    Detector(const Detector&)
    Detector copy assignment
    
    Non-class Functions:
    GetBooks
    Print
    
  Hours spent on this assignment: 3 hours

  Specific portions that gave you the most trouble:
  None
    
  
*/
/******************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <new>
#ifdef _WIN32
#pragma warning( disable : 4290 )
#define _GLIBCXX_THROW throw
#else
#endif
#include "SimpleMemoryLeakDetector.h"


namespace CS170L {
/******************************************************************************/
/*!
  \brief
    Prints Error message
   
*/
/******************************************************************************/
  const char *Deallocate_Exception::what() const throw()
  {
    return "Deallocation Error!\n";
  }
/******************************************************************************/
/*!
  \brief
    Print the number of times of memory allocated and memory deallocated
    
*/
/******************************************************************************/
  void Detector::print_stats()
  {
    if( Detector::get_detector().num_allocs !=  Detector::get_detector().num_deallocs)
    {
      
    std::fprintf(stderr, "Number of allocations : %zu\n",
                 Detector::get_detector().num_allocs);
    std::fprintf(stderr, "Number of deallocations : %zu\n",
                 Detector::get_detector().num_deallocs);
    }
  }
/******************************************************************************/
/*!
  \brief
    Makes a detector object
    
*/
/******************************************************************************/
  Detector & Detector::get_detector() {

    if (detector == 0) {
      detector =
          reinterpret_cast < Detector * >(std::malloc(sizeof(Detector)));

      if (detector == 0) {
        std::puts("Error in allocating pointer to Detector!\n");
        std::exit(10);
      }
      detector->size = 0;
      detector->capacity = 0;
      detector->array = 0;
      detector->num_allocs = 0;
      detector->num_deallocs = 0;
      /* atexit is a C call that ensures a particular function gets called
      before the program terminates */
      std::atexit(print_stats);

    }
    return *detector;
  }
/******************************************************************************/
/*!
  \brief
    Allocates memory 
    
  \param sz
    Allocates sz amount of memory
    
*/
/******************************************************************************/
  void *Detector::allocate(size_t sz) throw(std::bad_alloc) 
  {
    if(size==capacity)
      grow();
    //Allocating memory
    void* tmp = (void*)std::malloc(sz);
    //Adding to the list of memory allocated
    array[size]=tmp;
    ++num_allocs;
    ++size;
    return tmp;
  }
/******************************************************************************/
/*!
  \brief
    Deallocates memory 
    
  \param addr
    Deallocates memory in addr
    
*/
/******************************************************************************/
  void Detector::deallocate(void *addr) throw(Deallocate_Exception) 
  {
    size_t count=0;
    while(count<size)
    {//Found memory and freeing it
      if(addr==array[count])
      {
        std::free(addr);
        while(count<size)
        {
          array[count]=array[count+1];
          ++count;
        }
        --size;
        ++num_deallocs;
        return;
      }
      ++count;
    }
    throw (Deallocate_Exception{});
  }
/******************************************************************************/
/*!
  \brief
    Constructor for Detector
    
*/
/******************************************************************************/
Detector::Detector()
  :array{nullptr}, size{0}, capacity{0}, num_allocs{0}, num_deallocs{0} {}
/******************************************************************************/
/*!
  \brief
    Copy Constructor for Detector
*/
/******************************************************************************/
  Detector::Detector(const Detector &)
  {}
/******************************************************************************/
/*!
  \brief
    Copy assignment for Detector
    
  \return
    The assigned Detector
*/
/******************************************************************************/
  Detector& Detector::operator=(const Detector &)
  {
    return *this;
  }
/******************************************************************************/
/*!
  \brief
    Destructor for Detector
    
*/
/******************************************************************************/
Detector::~Detector()
{
  std::free(array);
  std::free(detector);
}
/******************************************************************************/
/*!
  \brief
    Allocates memory to maintain the list of memory that is allocated
    
*/
/******************************************************************************/
  void Detector::grow() 
  {
    if(capacity==0)
    {
      array=(void**)std::malloc(sizeof(void*));
      capacity=1;
      return;
    }
    else if(size+1 >= capacity)
    {
      capacity*=2;
      size_t count=0;
      void** newarray=nullptr;
      newarray=(void**)std::malloc(capacity*sizeof(void*));
      while(count<size)
      {
        newarray[count]=array[count];
        ++count;
      }
      std::free(array);
      array=newarray;
    }
  }
}

CS170L::Detector * CS170L::Detector::detector = NULL;
/******************************************************************************/
/*!
  \brief
    Overloaded operator new that is using the allocate function
    
  \param sz
    Allocates sz amount of memory
    
*/
/******************************************************************************/
void *operator new(size_t sz) _GLIBCXX_THROW(std::bad_alloc)
{
  void* tmp = CS170L::Detector::get_detector().allocate(sz);
  return tmp;
}
/******************************************************************************/
/*!
  \brief
    Overloaded operator new [] that is using the allocate function
    
  \param sz
    Allocates sz amount of memory
    
*/
/******************************************************************************/
void *operator new[] (size_t sz) _GLIBCXX_THROW(std::bad_alloc)
{
  void* tmp = CS170L::Detector::get_detector().allocate(sz);
  return tmp;
}
/******************************************************************************/
/*!
  \brief
    Overloaded operator delete that is using the deallocate function
    
  \param m
    deallocates memory in the address
    
*/
/******************************************************************************/
void operator delete(void *m) noexcept
{
  try
  {
    CS170L::Detector::get_detector().deallocate(m);
  }
  catch (CS170L::Deallocate_Exception e)
  {
    fprintf (stdout, e.what());
  }
}
/******************************************************************************/
/*!
  \brief
    Overloaded operator delete[] that is using the deallocate function
    
  \param m
    deallocates memory in the address
    
*/
/******************************************************************************/
void operator delete[] (void *m) noexcept
{
  try
  {
  CS170L::Detector::get_detector().deallocate(m);
  }
  catch (CS170L::Deallocate_Exception e)
  {
    fprintf (stdout, e.what());
  }
}