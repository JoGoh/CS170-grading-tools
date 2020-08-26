/*****************************************************************************/
/*!
\file   cs170_vector.h
\author Josiah Goh
\par    email: goh.j\@digipen.edu
\par    DigiPen login: goh.j
\par    Course: CS170
\par    Lab 07
\date   02/03/2019
\brief  
This file contains the implementation of a vector class template and the
following specialized template functions and functions for Lab #07.
    Functions include:
    
vector      // default constructor
vector      // constructor
vector      // copy constructor
operator=   // copy assignment
~vector     // default destructor
size        //gettor for vsize
capacity    //gettor for vcap
push_front
push_back
pop_back
insert
remove
empty
operator[]  //overloaded 
clear     
grow      //self defined fn for capacity
Print      // general template
Print      // specialized template for float
Print      // specialized template for unsigned char
Print      // specialized template for double
Print      // specialized template for strings   
    Specific portions that gave you the most trouble: NONE
    
*/
/*****************************************************************************/

#include <iomanip>      // std::cout.width, std::cout.precision
#include <iostream>     // std::cout
namespace cs170
{
    
/*****************************************************************************/
/*!
   \class vector
  
   \brief
        templeted vector class.
*/
/*****************************************************************************/
    template <typename T>
    class vector
    {
        /* The number of elements in the array. */
        size_t vsize;
        // use unsigned because if below 0 its largest possible number,
        //easier for out of bounds check
  
        /* The allocated size of the array also known as the capacity. */
        size_t vcap;// used unsigned to compare with vsize
      
        /* The dynamically allocated array. */
        T * varray;
        
        public:
        
/*****************************************************************************/
/*!
    \brief
        Default constructor, allocates the memory and 
        initialize the data members.
*/
/*****************************************************************************/
        vector(): vsize(0), vcap(0), varray(nullptr){}//default cter
        
/*****************************************************************************/
/*!
    \brief
        Copy constructor, constructs an object by copying a value from another
    object.

    \param rhs
        The value to be copied over.
*/
/*****************************************************************************/      
        vector(const vector<T>& rhs)
        : vsize(rhs.vsize), vcap(rhs.vcap), varray(new T [vcap])//cpy cter
        {
            for(size_t i = 0; i<vsize; i++)//assigning array values
            {
                varray[i]=rhs.varray[i];
            }
        }
        
/*****************************************************************************/
/*!
    \brief
        Assignment operator overloaded.

    \param rhs
        The right operand to be copied.
    
    \return the copy of the parameter passed in.
*/
/*****************************************************************************/    
        vector& operator= (const vector<T>& rhs)
        {
            if( this==&rhs)//if same elements
                return *this;
                
            vsize=rhs.vsize;
            vcap=rhs.vcap;
            
            T* newarray=new T[vcap];// allocate noew memry space
            
            for(size_t i =0; i<vsize; i++)//copy values over
            {
                newarray[i]=rhs.varray[i];
            }
            
            delete[] varray;//del old array
        
            varray= newarray;//shift the ptr to new   
            return *this;
        }

/*****************************************************************************/
/*!
    \brief
        Default Destructor, deallocates any memory allocated by the constructor.
*/
/*****************************************************************************/        
        ~vector()//dtor
        {   
            delete[] varray;
            varray = nullptr;
        }

/*****************************************************************************/
/*!
    \brief
        gettor for vsize.
    
    \return vsize
*/
/*****************************************************************************/
        size_t size()const
        {
            return vsize;
        }
    
/*****************************************************************************/
/*!
    \brief
        gettor for vcap.
    
    \return vcap
*/
/*****************************************************************************/
        size_t capacity() const
        {
            return vcap;
        }
        
/*****************************************************************************/
/*!
    \brief
        Overload operator[] to return the element of the array.

    \param pos
        The position of the element in the array.
    
    \return reference to the element.
*/
/*****************************************************************************/   
        T& operator[] (const size_t& pos)
        {   
            if(pos>=vsize)//if out of bounds
                std::abort();
            
            return varray[pos];                 
        }
        
				const T& operator[] (const size_t& pos) const
        {   
            if(pos>=vsize)//if out of bounds
                std::abort();
            
            return varray[pos];                 
        }
        
/*****************************************************************************/
/*!
    \brief
        self defined function to expand the capacity if required.
*/
/*****************************************************************************/
        void grow()// own function to expand capacity
        {
            if(vcap==0)
            {
                vcap++;     //increment only by one 
                varray= new T[vcap];        //allocate mem to it
            }
            
            else
            {
                vcap*=2;//double original vcap since have to be in pow of 2
                
                T* newarray=new T[vcap];// allocate noew memry space
                
                for(size_t i =0; i<vsize; i++)//copy values over
                {
                    newarray[i]=varray[i];
                }
                
                delete[] varray;//del old array
        
                varray= newarray;//shift the ptr to new     
            }       
        }
        
/*****************************************************************************/
/*!
    \brief
        Push element to back of vector.

    \param element
        The element to be put at the end of the vector.
*/
/*****************************************************************************/  
        void push_back (const T & element)
        {
            if(vsize==vcap)//when the size has reached capacity
                grow();
            
            varray[vsize++]=element;//both assgining and incremen at one line
        }
        
/*****************************************************************************/
/*!
    \brief
        Push element to front of vector.

    \param element
        The element to be put at the front of the vector.
*/
/*****************************************************************************/
        void push_front (const T & element)
        {
            if(vsize==vcap)//when the size has reached capacity
                grow();
            vsize++;
            for(size_t i=0; i<vsize; i++)//shift values backward
            {
                varray[i+1]=varray[i];      
            }
            
            varray[0]=element;//first element assigned
        }

/*****************************************************************************/
/*!
    \brief
        pops an element from the end of the vector.
*/
/*****************************************************************************/     
        void pop_back()
        {
            vsize--;//ignores last element
        }

/*****************************************************************************/
/*!
    \brief
        checks if vector is empty or not.
*/
/*****************************************************************************/   
        bool empty() const
        {
            if(vsize==0)
                return true;
            
            return false;
        }       
        
/*****************************************************************************/
/*!
    \brief
        clears the vector, setting size to 0 while leaving capacity alone.
*/
/*****************************************************************************/
        void clear()
        {
            vsize = 0;
        }
    
/*****************************************************************************/
/*!
    \brief
        erases an element from the specific point of the vector.

    \param pos
        The position to be erased.
*/
/*****************************************************************************/
        void erase(const int & pos)
        {
            // also guards if pos>vsize (out of bounds)
            for(size_t i=0, j=1; (j+pos)<vsize; i++, j++)
            {
                varray[i+pos]=varray[j+pos];
            }
            vsize--;
        }

/*****************************************************************************/
/*!
    \brief
        inserts an element at a specific position in vector.

    \param pos
        The position to be inserted.
    
    \param val
        the value to be inserted.   
*/
/*****************************************************************************/
        void insert(const size_t& pos, const T& val)
        {           
            if(vsize==vcap)
                grow();
							
						if(pos>=vcap)
                std::abort();
            
            vsize++;
            //shift values, do both decrement i and compare in the conditional
            for(size_t i=vsize; --i>pos;)
            {
                varray[i]=varray[i-1];
            }

            varray[pos]=val;            
        }               
        
    };//end of class

/*****************************************************************************/
/*!
    \brief
        A print function template that will print out a templated Vector.

    \param array
        The vector to be printed out
*/
/*****************************************************************************/
    template <typename T>
    void Print(const cs170::vector<T> & array)
    {
        for (size_t i = 0; i < array.size(); ++i)
        {
            std::cout << array[i] << "  ";
        }
        std::cout
        << "("
        << "size=" << array.size()
        << ", "
        << "capacity=" << array.capacity()
        << ")"
        << std::endl;
    }
        
/*****************************************************************************/
/*!
    \brief
        An explicit specialization print fn for float.

    \param array
        The vector to be printed out
*/
/*****************************************************************************/
    template<>
    void Print(const cs170::vector<float> &array)
    {
        for (size_t i = 0; i < array.size(); ++i)
        {
            std::cout.width(5);       //no. of spaces
            std::cout.precision(3);   //how many sig fig
            std::cout << array[i]<< "  ";//additional space after first element
        }
        std::cout
        << "("
        << "size=" << array.size()
        << ", "
        << "capacity=" << array.capacity()
        << ")"
        << std::endl;
    }
    
/*****************************************************************************/
/*!
    \brief
        A specialized print function template that will print unsigned char
        type Vector.

    \param array
        The vector to be printed out
*/
/*****************************************************************************/
    template<>
    void Print(const cs170::vector<unsigned char> &array)
    {
        for (size_t i = 0; i < array.size(); ++i)
        {
            std::cout << int(array[i]) << "  ";//forcefully make it int
        }
        std::cout
        << "("
        << "size=" << array.size()
        << ", "
        << "capacity=" << array.capacity()
        << ")"
        << std::endl;
    }

/*****************************************************************************/
/*!
    \brief
        A print function template that will print out a templated Vector.

    \param array
        The vector to be printed out
*/
/*****************************************************************************/
    template<>
    void Print(const cs170::vector<double> &array)
    {
        for (size_t i = 0; i < array.size(); ++i)
        {
            std::cout.width(7);
            std::cout.precision(5);
            std::cout << std::left << array[i] << "  ";
        }
        std::cout
        << "("
        << "size=" << array.size()
        << ", "
        << "capacity=" << array.capacity()
        << ")"
        << std::endl;
    }   
}   