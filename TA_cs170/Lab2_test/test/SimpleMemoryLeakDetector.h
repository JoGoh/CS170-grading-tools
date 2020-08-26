/******************************************************************************/
/*!
\file   SimpleMemoryLeakDetector.h
\author Tan Yu Jie
\par    email: yujie.tan\@digipen.edu
\par    DigiPen login: yujie.tan
\par    Course: CS170
\par    Lab #13
\date   12/4/2017
\brief  
    This file contains the declaration of the following functions for the 
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
    
  Hours spent on this assignment: 3 hours

  Specific portions that gave you the most trouble:
  None
    
  
*/
/******************************************************************************/
#ifndef SIMPLE_MEMORY_LEAK_DETECTOR_H
#define SIMPLE_MEMORY_LEAK_DETECTOR_H
#include <exception>
#ifdef _WIN32
#pragma warning( disable : 4290 )
#define _GLIBCXX_THROW throw
#else
#endif

namespace CS170L {
  struct Deallocate_Exception:public std::exception {
    virtual const char *what() const throw();
  };

  class Detector {
  public:
    static Detector & get_detector();
    static void print_stats();
    void *allocate(size_t sz) throw(std::bad_alloc);
    void deallocate(void *addr) throw(Deallocate_Exception);
  private:
    ~Detector();
    void grow();
     Detector();
     Detector(const Detector &);
     Detector & operator =(const Detector &);
    static Detector *detector;
    void **array;
    size_t size;
    size_t capacity;
    size_t num_allocs;
    size_t num_deallocs;
  };
}
#endif