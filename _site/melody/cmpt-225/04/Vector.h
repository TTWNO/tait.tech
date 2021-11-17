// transcriber's note: include is added from slide because otherwise it will not compile
#include <utility>
#include <stdexcept>

template <typename Object>
class Vector
{
  public:
    explicit Vector(int initSize=0)
      : theSize{initSize}, theCapacity{initSize + SPARE_CAPACITY}
      {objects = new Object[theCapacity];}

    Vector(const Vector& rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{nullptr}
    {
      objects = new Object[theCapacity];
      for(int k=0;k<theSize;++k){
        objects[k] = rhs.objects[k];
      }
    }

    Vector& operator=(const Vector& rhs)
    {
      Vector copy = rhs;
      std::swap(*this,copy);
      return *this;
    }

    ~Vector()
      {delete[] objects;}

    Vector(Vector&& rhs)
      : theSize{rhs.theSize}, theCapacity{rhs.theCapacity}, objects{rhs.objects}
    {
      rhs.objects=nullptr;
      rhs.theSize=0;
      rhs.theCapacity=0;
    }
  
    Vector& operator=(Vector&& rhs)
    {
      std::swap(theSize,rhs.theSize);
      std::swap(theCapacity,rhs.theCapacity);
      std::swap(objects,rhs.objects);
      return *this;
    }

    //stacky stuff
    void push_back(Object x)
    {
      if(theSize==theCapacity)
        reserve(2*theCapacity+1);
      objects[theSize++]=std::move(x);
    }

    void pop_back()
    {
      if(empty())
        // transcriber's note: the original line here was the following, however, it was changed to compile
        // throw UnderflowException();
        throw std::underflow_error::underflow_error;
      --theSize;
    }
    
    const Object& back() const
    {
      if(empty())
        // See note on line 58
        throw std::underflow_error::underflow_error;
      return objects[theSize-1];
    }

    // transcriber's note: these three functions added to make compilation work
    const int size() const
    {
      return theSize;
    }
    Object& operator[](int index)
    {
      return objects[index];
    }
    const Object& operator[](int index) const
    {
      return objects[index];
    }
    bool empty() const {return size() == 0;}
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
  

    typedef Object* iterator;
    typedef const Object* const_iterator;
    
    iterator begin()
      {return &objects[0];}
    const_iterator begin() const
      {return &objects[0];}
    iterator end()
      {return &objects[size()];}
    const_iterator end() const
      {return &objects[size()];}

    static const int SPARE_CAPACITY=2;

  private:
    int theSize;
    int theCapacity;
    Object* objects;
};
