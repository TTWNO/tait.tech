/*
Transcriber's note: these first two lines of ifndef and define are added to make compilation work.
Note 2: all changed lines are labled with "//CHANGE" (without the quotes)
*/
#ifndef _H_TVECTOR
#define _H_TVECTOR
#include <iostream>

template <typename Object>//CHANGE
class TVector
{
  public:
    // Constructor
    TVector(int initSize=0)
      : theSize{initSize}, theCapacity{initSize+10}
      {
        objects = new Object(theCapacity);//CHANGE: annotation: in IVector object(...) was int(...)
      }

    // Destructor
    ~TVector()
      {delete[] objects;}

    // Check for emptyness
    bool empty() const {return size() == 0;}

    // Return size of list
    int size() const {return theSize;}

    // Access the element at a given index
    // This is the non-const version, so you can change the element.
    Object& operator[](int index)//CHANGE
    {
      return objects[index];
    }

    // Access the element at a given index
    // This is the const version, for accessing the value only
    const Object& operator[](int index) const //CHANGE
    {
      return objects[index];
    }

    // Increase the capacity (i.e., array size)
    void reserve(int newCapacity)
    {
      if(newCapacity>theSize){
        Object *newArray = new int[newCapacity]; //CHANGE
        for (int k=0;k<theSize;++k){
          newArray[k] = std::move(objects[k]);
        }
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete [] newArray;
      }
    }
  
  // add a new element to end of the list
  void push_back(const Object& x)//CHANGE
  {
    if(theSize==theCapacity) reserve(2*theCapacity+1);
    objects[theSize++]=x;
  }

  // remove the last element from the list
  void pop_back()
  {
    --theSize;
  }

  // Print out the size and contents of the list
  void display() const
  {
    std::cout << "size=" << theSize << std::endl;

    for(int i=0;i<theSize;++i){
      std::cout<<"["<<i<<"]"<<"="<<objects[i]<<std::endl;
    }
  }
  
  private:
    int theSize;
    int theCapacity;
    Object* objects;//CHANGE
};

#endif
