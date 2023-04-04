#pragma once

#include <iostream>
#include <iterator>

template <typename K, typename V>
struct Node {
  public:
  K key;
  V val;
  Node *next;

  Node(K k, V v) : key{k}, val{v}, next{nullptr} {}
};

template <typename K, typename V>
struct Element {
  public:
  int count;
  Node<K, V> *head;
  Node<K, V> *tail;
  Element *next;

  Element() : count{0}, next{nullptr} { head = tail = nullptr; }
};

template <typename K, typename V>
class Iterator
    : public std::iterator<std::bidirectional_iterator_tag, std::pair<K, V>> {
  Node<K, V> *itr;
  Element<K, V> *el;

  public:
  Iterator(Node<K, V> *i, Element<K, V> *e) : itr{i}, el{e} {}
  Iterator() : itr(nullptr), el(nullptr) {}

  void swap(Iterator &other) {
    std::swap(itr, other.itr);
    std::swap(el, other.el);
  }

  Iterator &operator++() {
    if (itr->next == nullptr) {
      while (el->next != nullptr) {
        el = el->next;
        if (el->head != nullptr) {
          itr = el->head;
          break;
        } else
          itr = nullptr;
      }
    } else
      itr = itr->next;

    return *this;
  }

  Iterator operator++(int) {
    Iterator tmp(*this);
    if (itr->next == nullptr) {
      while (el->next != nullptr) {
        el = el->next;
        if (el->head != nullptr) {
          itr = el->head;
          break;
        } else
          itr = nullptr;
      }
    } else
      itr = itr->next;

    return tmp;
  }

  template <typename key, typename value>
  bool operator==(const Iterator<key, value> &ikv) const {
    return itr == ikv.itr && el == ikv.el;
  }

  template <typename key, typename value>
  bool operator!=(const Iterator<key, value> &ikv) const {
    return itr != ikv.itr || el != ikv.el;
  }

  std::pair<K, V> &operator*() const {
    return std::pair<K, V>(itr->key, itr->val);
  }

  std::pair<K, V> *operator->() const {
    auto ret = std::pair<K, V>(itr->key, itr->val);
    return &ret;
  }
};

template <typename K, typename V>
class UnorderedMap {
  private:
  Element<K, V> *arr[10];
  size_t hash(const K &key) {
    size_t x = std::hash<K>()(key);
    return x % size;
  }
  int size;

  public:
  typedef Iterator<K, V> myIt;
  typedef Iterator<const K, const V> cMyIt;

  UnorderedMap() : size{10} {
    arr[0] = new Element<K, V>();
    for (int i = 1; i < 10; ++i) {
      arr[i] = new Element<K, V>();
      arr[i - 1]->next = arr[i];
    }
  }

  myIt begin() {
    if (size == 0) {
      myIt it(nullptr, nullptr);
      return it;
    } else {
      Element<K, V> *temp = arr[0];
      while (temp->head != nullptr) temp = temp->next;

      myIt it(temp->head, temp);
      return it;
    }
  }

  myIt end() {
    myIt it(nullptr, nullptr);
    return it;
  }

  std::pair<myIt, bool> emplace(const K &k, const V &val) {
    std::pair<K, V> p;
    p.first = k;
    p.second = val;
    int index = hash(p.first);
    if (arr[index]->head == nullptr) {
      arr[index]->head = new Node<K, V>(p.first, p.second);
      arr[index]->tail = arr[index]->head;
      ++(arr[index]->count);
    } else {
      Node<K, V> *temp = new Node<K, V>(p.first, p.second);
      arr[index]->tail->next = temp;
      arr[index]->tail = temp;
      ++(arr[index]->count);
    }

    ++size;
    myIt it(arr[index]->tail, arr[index]);
    return std::pair<myIt, bool>(it, true);
  }

  myIt find(K k) {
    int index = hash(k);
    Node<K, V> *temp = arr[index]->head;
    while (temp != nullptr) {
      if (temp->key == k) {
        myIt it(temp, arr[index]);
        return it;
      } else
        temp = temp->next;
    }

    return end();
  }

  bool erase(K k) {
    int index = hash(k);
    Node<K, V> *temp = arr[index]->head;
    Node<K, V> *t2 = temp;
    while (temp != nullptr) {
      if (temp->key == k) {
        if (arr[index]->count == 1) {
          delete temp;
          arr[index]->head = arr[index]->tail = nullptr;
        } else if (arr[index]->head == temp) {
          arr[index]->head = arr[index]->head->next;
          delete temp;
        } else if (arr[index]->tail == temp) {
          delete temp;
          t2->next = nullptr;
          arr[index]->tail = t2;
        } else {
          t2->next = temp->next;
          delete temp;
        }
        --(arr[index]->count);
        --size;
        return true;
      } else {
        t2 = temp;
        temp = temp->next;
      }
    }

    return false;
  }

  V &operator[](K k) {
    int index = hash(k);
    Node<K, V> *temp = arr[index]->head;
    while (temp != nullptr) {
      if (temp->key == k)
        return temp->val;
      else
        temp = temp->next;
    }
  }
};
