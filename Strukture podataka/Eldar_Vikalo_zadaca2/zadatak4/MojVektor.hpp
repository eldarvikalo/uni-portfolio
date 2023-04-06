#pragma once

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class MojVektor
{
public:
  MojVektor() : capacity_(0), size_(0), arr_(nullptr){};
  MojVektor(const std::initializer_list<T> &lista) : capacity_(lista.size()), size_(lista.size()), arr_(new T[capacity_])
  {
    int i = 0;
    for (const T &element : lista)
    {
      arr_[i] = element;
      ++i;
    }
    // for (int i = 0; i < lista.size(); i++)
    // {
    //   arr_[i] = lista[i];
    // }
  };
  MojVektor(const MojVektor &drugi) : capacity_(drugi.capacity_), size_(drugi.size_), arr_(new T[capacity_])
  {
    for (int i = 0; i < size_; ++i)
    {
      arr_[i] = drugi.arr_[i];
    }
  }
  MojVektor &operator=(const MojVektor &drugi)
  {
    delete[] arr_;
    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    arr_ = new T[capacity_];

    for (int i = 0; i < size_; ++i)
    {
      arr_[i] = drugi.arr_[i];
    }

    return *this;
  }
  MojVektor(MojVektor &&drugi) : capacity_(drugi.capacity_), size_(drugi.size_), arr_(drugi.arr_)
  {
    drugi.capacity_ = 0;
    drugi.size_ = 0;
    drugi.arr_ = nullptr;
  }
  MojVektor &operator=(MojVektor &&drugi)
  {
    delete[] arr_;
    capacity_ = drugi.capacity_;
    size_ = drugi.size_;
    arr_ = drugi.arr_;

    drugi.capacity_ = 0;
    drugi.size_ = 0;
    drugi.arr_ = nullptr;

    return *this;
  }

  ~MojVektor()
  {
    delete[] arr_;
  }

  MojVektor &push_back(T element)
  {
    if (capacity_ == size_)
    {
      T *novi_arr = new T[capacity_ + 1];

      for (int i = 0; i < size_; ++i)
      {
        novi_arr[i] = arr_[i];
      }

      novi_arr[size_] = element;

      delete[] arr_;

      arr_ = novi_arr;

      capacity_++;
      size_++;
    }
    else
    {
      arr_[size_] = element;
      size_++;
    }

    return *this;
  }
  T &at(size_t pozicija) const
  {
    if (size_ == 0 || pozicija >= size_ || pozicija < 0)
    {
      throw std::out_of_range("Nepostojeca pozicija");
    }
    else
    {
      return arr_[pozicija];
    }
  }
  T &operator[](size_t pozicija) const
  {
    return arr_[pozicija];
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
      throw std::out_of_range("Prazan vektor.");
    }
    return arr_[size_ - 1];
  }

  const T &front() const
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Prazan vektor.");
    }
    return arr_[0];
  }
  T &back()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Prazan vektor.");
    }
    return arr_[size_ - 1];
  };
  T &front()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Prazan vektor.");
    }
    return arr_[0];
  };

  void resize(size_t novi_capacity)
  {
    // Potencijalno implementirat da se ne resize-a ako je iste velicine
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
      throw std::invalid_argument("Novi kapacitet mora biti veci ili jednak od trenutnog size-a");
    }
  }

  MojVektor &pop_back()
  {
    if (size_ == 0)
    {
      throw std::out_of_range("Prazan vektor.");
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
  bool operator==(const MojVektor &drugi) const
  {
    if (size_ == drugi.size_)
    {
      for (int i = 0; i < size_; i++)
      {
        if (arr_[i] != drugi.arr_[i])
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

  bool operator!=(const MojVektor &drugi) const
  {
    return !operator==(drugi);
  };

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

  // if(v.find(5) == v.end()) std::cout << "Taj broj se ne nalazi u vektoru"
  // v.insert(v.begin()+5,62).insert();

  MojVektor &insert(Iterator pos, T element)
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

  // for(int x : v){
  //   v.push_back(x);
  // }

  Iterator erase(Iterator pos)
  {
    T *novi_arr = new T[capacity_ - 1];

    Iterator it = begin();

    int i = 0;

    while (it != pos)
    {
      novi_arr[i++] = *it++;
    }

    pos++;

    while (pos != end())
    {
      novi_arr[i++] = *pos++;
    }

    delete[] arr_;
    arr_ = novi_arr;
    capacity_--;
    size_--;

    return begin();
  }

  Iterator erase(Iterator beginIt, Iterator endIt)
  {
    // std::cout << "Novi kapacitet: " << capacity_ - (endIt - beginIt) << std::endl;
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
    return begin();
  }

private:
  size_t capacity_;
  size_t size_;
  T *arr_;
};

// MojVektor<int> v;
// fileStream << v;

template <typename T>
std::ostream &operator<<(std::ostream &out, const MojVektor<T> &vektor)
{
  for (const T &element : vektor)
  {
    out << element << " ";
  }

  return out;
}

template <typename T>
class MojVektor<T>::Iterator
    : public std::iterator<std::random_access_iterator_tag, T>
{
public:
  Iterator(T *ptr) : ptr_(ptr) {}
  T &operator*() const
  {
    return *ptr_;
  }
  T &operator->() const
  {
    return *ptr_;
  }

  Iterator &operator++()
  {
    ++ptr_;
    return *this;
  }

  Iterator operator++(int)
  {
    T *kopija = ptr_;
    ++ptr_;
    return Iterator(kopija);
  }

  Iterator &operator--()
  {
    --ptr_;
    return *this;
  }

  Iterator operator--(int)
  {
    T *kopija = ptr_;
    --ptr_;
    return Iterator(kopija);
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
