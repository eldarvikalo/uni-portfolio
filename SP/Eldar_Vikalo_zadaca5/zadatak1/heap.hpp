#pragma once
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class Heap {
  private:
  T* ptr;
  size_t capacity_;
  size_t size_;

  public:
  // Heap() :size_{0}, capacity_{100}, ptr{nullptr}{}
  Heap(size_t cap) : size_{0}, capacity_{cap}, ptr{new T[cap]} {}
  Heap(const Heap& obj2)
      : size_{obj2.size_}, capacity_{obj2.capacity_}, ptr{new T[size_]} {
    // for (int i = 0; i < size_; i++) {
    //   ptr[i] = obj2.ptr[i];
    // }
    std::copy(obj2.ptr, obj2.ptr + size_, ptr);
  }

  Heap(Heap&& obj2)
      : size_{obj2.size_}, capacity_{obj2.capacity_}, ptr{obj2.ptr} {
    obj2.size_ = 0;
    obj2.ptr = nullptr;
  }

  Heap& operator=(const Heap& obj2) {
    if (this == &obj2) return *this;
    delete[] ptr;
    capacity_ = obj2.capacity_;
    size_ = obj2.size_;
    ptr = new T[capacity_];
    for (int i = 0; i < size_; ++i) {
      ptr[i] = obj2.ptr[i];
    }

    return *this;
  }

  Heap& operator=(Heap&& obj2) {
    if (this == &obj2) return *this;
    delete[] ptr;
    capacity_ = obj2.capacity_;
    size_ = obj2.size_;
    ptr = obj2.ptr;

    obj2.capacity_ = 0;
    obj2.size_ = 0;
    obj2.ptr = nullptr;

    return *this;
  }

  ~Heap() { delete[] ptr; }

  void insert(const T& element) {
    if (size_ == capacity_)
      realoc();
    else {
      size_++;
      size_t i = size_ - 1;
      ptr[i] = element;

      while (i > 1 && ptr[i / 2] < ptr[i]) {
        std::swap(ptr[i], ptr[i / 2]);
        i /= 2;
      }
      for (int i = size_ / 2 - 1; i >= 0; i--) {
        heapify(size_, i);
      }
    }
  }

  void heapify(int size, int i) {
    int parent = i;
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    if (left < size && ptr[left] > ptr[parent]) parent = left;
    if (right < size && ptr[right] > ptr[parent]) parent = right;
    if (parent != i) {
      std::swap(ptr[i], ptr[parent]);
      heapify(size, parent);
    }
  }

  void realoc() {
    capacity_ *= 2;
    T* tmp = ptr;
    ptr = new T[capacity_];
    std::copy(tmp, tmp + size_, ptr);
    delete[] tmp;
  }

  void removeMax() {
    if (size_ == 0)
      throw std::out_of_range(
          "Ne moze izbrisati maksimalnu vrijednost, heap je prazan");
    if (size_ == 1) size_--;

    ptr[0] = ptr[size_ - 1];
    size_--;
    heapify(size_, 0);
  }

  T getMax() {
    if (size_ == 0)
      throw std::out_of_range(
          "Ne moze vratiti maksimalnu vrijednost, jer je heap prazan");
    if (size_ == 1)
      return ptr[0];
    else {
      for (int i = size_ / 2 - 1; i >= 0; i--) {
        sort(size_ - 1);
      }
      return ptr[0];
    }
  }

  void removeMin() {
    if (size_ == 0) {
      throw std::out_of_range(
          "Ne moze izbrisati minimalnu vrijednost, heap je prazan");
    } else if (size_ == 1) {
      size_--;
    } else {
      int temp = ptr[size_ / 2];
      int index = size_;
      for (int i = size_ / 2 + 1; i < size_; i++) {
        if (ptr[i] < temp) {
          temp = ptr[i];
          index = i;
        }
      }
      std::swap(ptr[size_ - 1], ptr[index]);
      --size_;
      sort(size_ - 1);
    }
  }

  T getMin() {
    if (size_ == 0) {
      throw std::out_of_range(
          "Ne moze vratiti minmalnu vrijednost, heap je prazan");
    }
    if (size_ == 1) return ptr[0];

    int temp = ptr[size_ / 2];
    for (int i = size_ / 2 + 1; i < size_; i++) {
      if (ptr[i] < temp) {
        temp = ptr[i];
      }
    }
    return temp;
  }

  void sort(size_t index) {
    while (index > 0 && ptr[(index - 1) / 2] < ptr[index]) {
      std::swap(ptr[(index - 1) / 2], ptr[index]);
      index = (index - 1) / 2;
    }
  }

  void ispis() {
    for (int i = 0; i < size_; i++) std::cout << ptr[i] << " ";
    std::cout << std::endl;
  }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const Heap<T>& heap) {
  out << "[";
  for (int i = 0; i < heap.size_; i++) {
    if (i < heap.size_ - 1)
      out << heap.ptr[i] << ",";
    else
      out << heap.ptr[i] << "]" << std::endl;
  }
  return out;
}

