#pragma once
#include <iterator>

template <typename T>
struct Node
{
    Node *next_;
    T value_;
};

template <typename T>
class Lista
{


public:
    Lista() : head_(nullptr), size_(0) {}
    Lista(const Lista &novi) : head_(nullptr), size_(0)
    {
        Node<T> *tmp = novi.head_;
        for (size_t i = 0; i < novi.size_; i++)
        {
            add(tmp->value_);
            tmp = tmp->next_;
        }
    }
    Lista(Lista &&novi) : head_(novi.head_), size_(novi.size_)
    {
        novi.head_ = nullptr;
        novi.size_ = 0;
    }
    Lista &operator=(const Lista &novi)
    {
        Node<T> *tmp;

        while (head_ != nullptr)
        {
            tmp = head_->next_;
            delete head_;
            head_ = tmp;
        }

        head_ = nullptr;
        size_ = 0;

        tmp = novi.head_;
        for (size_t i = 0; i < novi.size_; i++)
        {
            add(tmp->value_);
            tmp = tmp->next_;
        }
        return *this;
    }
    Lista &operator=(Lista &&novi)
    {
        Node<T> *tmp;

        while (head_ != nullptr)
        {
            tmp = head_->next_;
            delete head_;
            head_ = tmp;
        }

        head_ = novi.head_;
        size_ = novi.size_;

        novi.head_ = nullptr;
        novi.size_ = 0;

        return *this;
    }

    void clear()
    {
        Node<T> *tmp;

        while (head_ != nullptr)
        {
            tmp = head_->next_;
            delete head_;
            head_ = tmp;
        }

        size_ = 0;
    }
    void add(T element)
    {
        if (size_ == 0)
        {
            head_ = new Node<T>{nullptr, element};
            size_++;
            return;
        }
        else
        {
            Node<T> *tmp = head_;

            if (head_->value_ > element)
            {
                head_ = new Node<T>{head_, element};
                size_++;
                return;
            }

            while (tmp->next_ != nullptr)
            {
                if (tmp->next_->value_ > element)
                {
                    Node<T> *novi_node = new Node<T>{tmp->next_, element};
                    tmp->next_ = novi_node;
                    size_++;
                    return;
                }
                tmp = tmp->next_;
            }

            tmp->next_ = new Node<T>{nullptr, element};
            size_++;
        }
    }

    class Iterator;
    Iterator begin()
    {
        return Iterator(head_);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    template <typename Predicate>
    Iterator find(Predicate p) // std::function<bool(T)>
    {
        Iterator it = begin();

        while (it != end())
        {
            if (p(*it))
                return it;
            it++;
        }

        return end();
    }

    void remove(Iterator pos)
    {
        if (pos == begin())
        {
            Node<T> *tmp = head_;
            head_ = head_->next_;
            delete tmp;
            size_--;
            return;
        }

        Node<T> *prev = head_;

        while (prev->next_ != nullptr)
        {
            if (Iterator(prev->next_) == pos)
            {
                Node<T> *tmp = prev->next_;
                prev->next_ = prev->next_->next_;
                delete tmp;
                size_--;
                return;
            }
            prev = prev->next_;
        }
    }
    size_t size() { return size_; };



    ~Lista() { clear(); }

  private:
    Node<T> *head_;
    size_t size_;
};


template <typename T>
class Lista<T>::Iterator : public std::iterator<std::forward_iterator_tag, T>
{
public:
    Iterator(Node<T> *p) : p_{p} {}

    Iterator &operator++()
    {
        if (p_ == nullptr)
            return *this;

        p_ = p_->next_;
        return *this;
    }

    Iterator operator++(int)
    {
        if (p_ == nullptr)
            return *this;
        Iterator temp = *this;
        p_ = p_->next_;
        return temp;
    }

    bool operator==(const Iterator &novi)
    {
        return p_ == novi.p_;
    }

    bool operator!=(const Iterator &novi)
    {
        return p_ != novi.p_;
    }

    T &operator*()
    {
        return p_->value_;
    }

    T *operator->()
    {
        return &p_->value_;
    }

private:
    Node<T> *p_;
};
