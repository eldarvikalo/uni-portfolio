#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>


template <typename T>
class MojVector
{
public:
  MojVector() : capacity_(0), size_(0), arr_(nullptr){};
  MojVector(const std::initializer_list<T> &l) : capacity_(l.size()), size_(l.size()), arr_(new T[capacity_])
  {
    int i = 0;
    for (const T& element : l)
    {
      arr_[i] = element;
      i++;
    }
    
  };
  MojVector(const MojVector &obj2) : capacity_(obj2.capacity_), size_(obj2.size_), arr_(new T[capacity_])
  {
    for (int i = 0; i < size_; ++i)
    {
      arr_[i] = obj2.arr_[i];
    }
  }
  MojVector &operator=(const MojVector &obj2)
  {
    //if(this == &obj2) return *this;

    delete[] arr_;
    capacity_ = obj2.capacity_;
    size_ = obj2.size_;
    arr_ = new T[capacity_];

    for (int i = 0; i < size_; ++i)
    {
      arr_[i] = obj2.arr_[i];
    }
    return *this;
  }
  MojVector(MojVector &&obj2) : capacity_(obj2.capacity_), size_(obj2.size_), arr_(obj2.arr_)
  {
    obj2.capacity_ = 0;
    obj2.size_ = 0;
    obj2.arr_ = nullptr;
  }
  MojVector &operator=(MojVector &&obj2)
  {
    //if(this == &obj2) return *this;
    delete[] arr_;
    capacity_ = obj2.capacity_;
    size_ = obj2.size_;
    arr_ = obj2.arr_;

    obj2.capacity_ = 0;
    obj2.size_ = 0;
    obj2.arr_ = nullptr;

    return *this;
  }

  ~MojVector()
  {
    delete[] arr_;
  }


  MojVector &push_back(T element)
  {
    if (capacity_ == size_)
    {
      T *novi_arr = new T[capacity_ + 1000];

      for (int i = 0; i < size_; ++i)
      {
        novi_arr[i] = arr_[i];
      }

      novi_arr[size_] = element;

      delete[] arr_;

      arr_ = novi_arr;

      capacity_ += 1000;
      size_++;
    }
    else
    {
      arr_[size_] = element;
      size_++;
    }

    return *this;
  }


  T &at(size_t position) const
  {
    if (size_ == 0 || position >= size_ || position < 0)
    {
      throw std::out_of_range("Ne ovoj poziciji nema elementa");
    }
    else
    {
      return arr_[position];
    }
  }
  T &operator[](size_t position) const
  {
      return arr_[position];
  }
  void clear()
  {
    size_ = 0;
    capacity_ = 0;
    delete[] arr_;
    arr_ = nullptr;
  }

  size_t size() const
  {
    return size_;
  }
  bool empty() const
  {
    return size_ == 0;
  }
  const T &back() const
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Vektor je prazan");
    }
    return arr_[size_ - 1];
  }

  const T &front() const
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Vektor je prazan");
    }
    return arr_[0];
  }
  T &back()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Vektor je prazan");
    }
    return arr_[size_ - 1];
  };

  T &front()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Vektor je prazan");
    }
    return arr_[0];
  };

  void resize(size_t novi_capacity)
  {
    //if(capacity_ == novi_capacity) throw std::out_of_range("Vektor je vec na tom kapacitetu");
    if (novi_capacity >= size_)
    {
      T *novi_arr = new T[novi_capacity];

      for (int i = 0; i < size_; i++)
      {
        novi_arr[i] = arr_[i];
      }

      for (int i = size_; i < novi_capacity; i++)
      {
        novi_arr[i] = 0;
      }

      delete[] arr_;

      arr_ = novi_arr;

      capacity_ = novi_capacity;
      size_ = novi_capacity;
    }
    else
    {
      throw std::invalid_argument("Novi kapacitet mora biti veci od velicine");
    }
  }

  MojVector &pop_back()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Vektor je prazan");
    }
    else
    {
      size_--;
    }

    return *this;
  }
  size_t capacity() const
  {
    return capacity_;
  }
  bool operator==(const MojVector &obj2) const
  {
    if (size_ == obj2.size_)
    {
      for (int i = 0; i < size_; i++)
      {
        if (arr_[i] != obj2.arr_[i])
        {
          return false;
        }
      }
      return true;
    }
    else
    {
      return false;
    }
  }

  bool operator!=(const MojVector &obj2) const
  {
    return !operator==(obj2);
  }

  class Iterator;
  Iterator begin() const
  {
    return Iterator(arr_);
  }
  Iterator end() const
  {
    return Iterator(arr_ + size_);
  }
  Iterator find(const T &element) const
  {
    for (int i = 0; i < size_; i++)
    {
      if (arr_[i] == element)
      {
        return Iterator(arr_ + i);
      }
    }

    return end();
  }



  MojVector &insert(Iterator pos, T element)
  {
    T *novi_arr = new T[capacity_ + 1];

    Iterator it = begin();

    int i = 0;

    while (it != pos)
    {
      novi_arr[i++] = *it++;
    }

    novi_arr[i++] = element;

    while (pos != end())
    {
      novi_arr[i++] = *pos++;
    }

    delete[] arr_;
    arr_ = novi_arr;
    capacity_++;
    size_++;

    return *this;
  }



  Iterator erase(Iterator pos)
  {
    T *novi_arr = new T[capacity_ - 1];

    Iterator it = begin();

    int i = 0;

    while (it != pos)
    {
      novi_arr[i++] = *it++;
    }

    it = pos;
    it++;

    while (it != end())
    {
      novi_arr[i++] = *it++;
    }

    delete[] arr_;
    arr_ = novi_arr;
    capacity_--;
    size_--;

    return pos;
  }

  Iterator erase(Iterator beginIt, Iterator endIt)
  {
    T *novi_arr = new T[capacity_ - (endIt - beginIt)];

    Iterator it = begin();

    int i = 0;
    while (it != beginIt)
    {
      novi_arr[i++] = *it++;
    }

    it = endIt;
    while (it != end())
    {
      novi_arr[i++] = *it++;
    }

    delete[] arr_;
    arr_ = novi_arr;
    capacity_ -= endIt - beginIt;
    size_ -= endIt - beginIt;
    return beginIt;
  }

private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};



template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVector<T> &vec)
{
  for (const T &element : vec)
  {
    out << element << " ";
  }

  return out;
}

template <typename T>
class MojVector<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
public:
  Iterator(T *ptr) : ptr_(ptr) {}
  T &operator*() const
  {
    return *ptr_;
  }
  T *operator->() const
  {
    return ptr_;
  }

  Iterator &operator++()
  {
    ++ptr_;
    return *this;
  }

  Iterator operator++(int)
  {
    T *temp = ptr_;
    ++ptr_;
    return Iterator(temp);
  }

  Iterator &operator--()
  {
    --ptr_;
    return *this;
  }

  Iterator operator--(int)
  {
    T *temp = ptr_;
    --ptr_;
    return Iterator(temp);
  }

  Iterator operator+(size_t index)
  {
    return Iterator(ptr_ + index);
  }

  Iterator operator-(size_t index)
  {
    return Iterator(ptr_ - index);
  }

  size_t operator-(Iterator other)
  {
    return ptr_ - other.ptr_;
  }

  bool operator==(const Iterator &it) const
  {
    return ptr_ == it.ptr_;
  }
  bool operator!=(const Iterator &it) const
  {
    return ptr_ != it.ptr_;
  }
  bool operator<(const Iterator &it) const
  {
    return ptr_ < it.ptr_;
  }

  ~Iterator() = default;

private:
  T *ptr_;
};
