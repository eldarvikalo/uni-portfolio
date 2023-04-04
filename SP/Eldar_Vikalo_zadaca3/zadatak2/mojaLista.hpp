#pragma once
#include <initializer_list>
#include <iostream>
template <typename T>
struct Node
{
    Node *prev_;
    Node *next_;
    T value_;
};

template <typename T>
class mojaLista
{
private:
    Node<T> *head_;
    size_t size_;

public:
    mojaLista() : head_(nullptr), size_(0) {}
    mojaLista(const std::initializer_list<T> &initLista) : head_(nullptr), size_(0)
    {
        for (const T &element : initLista)
        {
            push_back(element);
        }
    }
    mojaLista(const mojaLista &novi) : head_(nullptr), size_(0)
    {
        Node<T> *novi_head_ = novi.head_;

        while (novi_head_ != nullptr)
        {
            push_back(novi_head_->value_);
            novi_head_ = novi_head_->next_;
        }
    }
    mojaLista(mojaLista &&novi) : head_(novi.head_), size_(novi.size_)
    {
        novi.head_ = nullptr;
        novi.size_ = 0;
    }
    mojaLista &operator=(const mojaLista &novi)
    {
        clear();

        Node<T> *novi_head_ = novi.head_;

        while (novi_head_ != nullptr)
        {
            push_back(novi_head_->value_);
            novi_head_ = novi_head_->next_;
        }

        return *this;
    }
    mojaLista &operator=(mojaLista &&novi)
    {
        clear();

        head_ = novi.head_;
        size_ = novi.size_;
        novi.head_ = nullptr;
        novi.size_ = 0;

        return *this;
    }
    void clear()
    {
        size_t old_size = size_;
        for (size_t i = 0; i < old_size; i++)
        {
            pop_front();
        }

        head_ = nullptr;
        size_ = 0;
    }
    void pop_back()
    {
        if (size_ == 0)
        {
            // bacit neki exception
        }
        else if (size_ == 1)
        {
            delete head_;
            head_ = nullptr;
            size_ = 0;
        }
        else
        {
            Node<T> *tmp = head_;
            while (tmp->next_ != nullptr)
            {
                tmp = tmp->next_;
            }
            tmp->prev_->next_ = nullptr;
            delete tmp;
            size_--;
        }
    }
    T front() { return head_->value_; };
    T back()
    {
        Node<T> *tmp = head_;

        while (tmp->next_ != nullptr)
        {
            tmp = tmp->next_;
        }

        return tmp->value_;
    }
    bool operator==(const mojaLista &novi) const
    {
        if (size_ == novi.size_)
        {
            Node<T> *head_1 = head_;
            Node<T> *head_2 = novi.head_;
            while (head_1 != nullptr)
            {
                if (head_1->value_ != head_2->value_)
                {
                    return false;
                }
                head_1 = head_1->next_;
                head_2 = head_2->next_;
            }
            return true;
        }
        return false;
    }
    bool operator!=(const mojaLista &novi) const
    {
        return !operator==(novi);
    }
    class Iterator;
    Iterator begin() { return Iterator(head_); }
    Iterator end() { return Iterator(nullptr); }
    void insert(Iterator position, T value)
    {
        if (position == begin())
        {
            push_front(value);
            return;
        }

        if (position == end())
        {
            push_back(value);
            return;
        }

        Node<T> *tmp = head_;

        while (Iterator(tmp->next_) != position)
        {
            tmp = tmp->next_;
        }

        tmp->next_ = new Node<T>{tmp, tmp->next_, value};

        tmp->next_->next_->prev_ = tmp->next_;
        size_++;
    }
    void erase(Iterator position)
    {
        if (position == begin())
        {
            pop_front();
            return;
        }

        Node<T> *tmp = head_;
        Node<T> *tmp2;

        while (Iterator(tmp->next_) != position)
        {
            tmp = tmp->next_;
        }

        if (++Iterator(tmp->next_) == end())
        {
            pop_back();
            return;
        }

        tmp2 = tmp->next_;
        tmp->next_ = tmp2->next_;
        tmp->next_->prev_ = tmp;

        delete tmp2;
        size_--;
    }
    void push_front(T element)
    {
        head_ = new Node<T>{nullptr, head_, element};
        head_->next_->prev_ = head_;
        size_++;
    }
    void push_back(T element)
    {
        if (size_ == 0)
        {
            head_ = new Node<T>{nullptr, nullptr, element};
        }
        else
        {
            Node<T> *tmp = head_;

            while (tmp->next_ != nullptr)
            {
                tmp = tmp->next_;
            }

            tmp->next_ = new Node<T>{tmp, nullptr, element};
        }
        size_++;
    }
    void pop_front()
    {
        if (size_ == 0)
        {
            // bacit neki exception
        }
        else if (size_ == 1)
        {
            delete head_;
            head_ = nullptr;
            size_ = 0;
        }
        else
        {
            head_ = head_->next_;
            delete head_->prev_;
            head_->prev_ = nullptr;
        }
        size_--;
    }
    size_t size() { return size_; }
    ~mojaLista()
    {
        clear();
    }
};

template <typename T>
class mojaLista<T>::Iterator : public std::iterator<std::bidirectional_iterator_tag, T>
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

    Iterator &operator--()
    {
        if (p_ == nullptr)
            return *this;

        p_ = p_->prev_;
        return *this;
    }

    Iterator operator--(int)
    {
        if (p_ == nullptr)
            return *this;
        Iterator temp = *this;
        p_ = p_->prev_;
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
