/****************************************************************************
  FileName     [ array.h ]
  PackageName  [ util ]
  Synopsis     [ Define dynamic array package ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present LaDs(III), GIEE, NTU, Taiwan ]
****************************************************************************/

#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <algorithm>

using namespace std;

// NO need to implement class ArrayNode
//
template <class T>
class Array
{
public:
   // TODO: decide the initial value for _isSorted
   Array() : _data(0), _size(0), _capacity(0) {}
   ~Array() { delete []_data; }

   // DO NOT add any more data member or function for class iterator
   class iterator
   {
      friend class Array;

   public:
      iterator(T* n= 0): _node(n) {}
      iterator(const iterator& i): _node(i._node) {}
      ~iterator() {} // Should NOT delete _node

      // TODO: implement these overloaded operators
      const T& operator * () const { return (*this); }
      T& operator * () { return (*_node); }
      iterator& operator ++ () { ++_node; return (*this); }
      iterator operator ++ (int) { iterator temp = *this; ++(*this); return temp; }
      iterator& operator -- () { --_node; return (*this); }
      iterator operator -- (int) { iterator temp = *this; --(*this); return temp; } 

      iterator operator + (int i) const { iterator temp; temp._node=this->_node+i; return temp; }
      iterator& operator += (int i) { _node=_node+i; return (*this); }

      iterator& operator = (const iterator& i) { _node=i._node; return (*this); }

      bool operator != (const iterator& i) const { return _node!=i._node; }
      bool operator == (const iterator& i) const { return _node==i._node; }

   private:
      T*    _node;
   };

   // TODO: implement these functions
   iterator begin() const { if(_capacity==0) return 0; else return iterator(_data); }
   iterator end() const { if(_capacity==0) return 0; else return iterator(_data+_size); }
   bool empty() const { return _size==0; }
   size_t size() const { return _size; }

   T& operator [] (size_t i) { return _data[i]; }
   const T& operator [] (size_t i) const { return _data[i]; }

   void push_back(const T& x) {
       if(_size==_capacity){
           if(_capacity==0) _capacity=1;
           else _capacity*=2;
           T* newdata = new T[_capacity];
           for(size_t i=0;i<_size;i++){
               newdata[i]=_data[i];
           }
           if(_data!=NULL) delete []_data;
           _data=newdata;
       }
       _data[_size++] = x;
   }
   void pop_front() {
       if (empty()) return;
       if(_size>=2) {
            _data[0]=_data[_size-1];
            --_size;
       }   
       else _size=0;
   }
   void pop_back() { 
        if(!empty()) --_size;
   }

   bool erase(iterator pos) {
       if(empty()) return false;
       (*pos)=_data[_size-1];
       --_size;
       return true;
   }
   bool erase(const T& x) {
       if(find(x)==end()) return false;
       else {
           erase(find(x));
           return true;
       }
   }

   iterator find(const T& x) {
       for(size_t i=0;i<_size;i++){
           if(_data[i]==x) return iterator(_data+i);
       }
       return end();
   }

   void clear() { _size=0; }

   // [Optional TODO] Feel free to change, but DO NOT change ::sort()
   void sort() const { if (!empty()) ::sort(_data, _data+_size); _isSorted=true;}

   // Nice to have, but not required in this homework...
   // void reserve(size_t n) { ... }
   // void resize(size_t n) { ... }

private:
   // [NOTE] DO NOT ADD or REMOVE any data member
   T*            _data;
   size_t        _size;       // number of valid elements
   size_t        _capacity;   // max number of elements
   mutable bool  _isSorted;   // (optionally) to indicate the array is sorted

   // [OPTIONAL TODO] Helper functions; called by public member functions
};

#endif // ARRAY_H
