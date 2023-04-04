#pragma once

#include <iostream>
#include <stack>
#include <queue>


namespace Types{

template<typename T>
class BST{
  private:

  struct Node{
    Node* left{nullptr};
    Node* right{nullptr};
    T data_;
    Node(T& element) : data_{element} {}
    Node(T&& element) : data_{element} {}
  };

  Node* root_ = nullptr;

  static void print_subtree(Node* root){
    if(root == nullptr) return;
    std::cout<<root->data_ <<' ';
    print_subtree(root->left);
    print_subtree(root->right);
  }

  static int depth(Node* current){
    if(current == nullptr) return 0;
    int dubina_lijevo = depth(current->left);
    int dubina_desno = depth(current->right);
    return 1 + std::max(dubina_lijevo, dubina_desno);
  }

  static void clear_subtree(Node*& root)
  {
    if(root == nullptr) return;
    clear_subtree(root->left);
    clear_subtree(root->right);
    delete root;
    root = nullptr;
  }

  static void preorder(Node* current)
  {
    if(current == nullptr) return;
    std::cout<< current->data_ << ' ';
    preorder(current->left);
    preorder(current->right);
    std::stack<Node*> s;
    s.push(current);
    while(!s.empty()){
      auto node = s.top();
      s.pop();
      std::cout<<current->data_<<' ';
      if(node->right) s.push(node->right);
      if(node->left) s.push(node->left);
    }
  }

    static void inorder(Node* current){
      if(current == nullptr)  return;
      inorder(current->left);
      std::cout << current->data_ <<' ';
      inorder(current->right);
    }

    static void postorder(Node* current)
    {
      if(current == nullptr)  return;
      postorder(current->left);
      postorder(current->right);
      std::cout << current->data_ <<' ';
    }

    void insert_subtree(Node* root)
    {
      if(root == nullptr) return;
      insert(root->data_);
      insert_subtree(root->right);
      insert_subtree(root->left);
    }

  public:
    BST() = default;

    BST(const BST& other){
      insert_subtree(other.root_);
    }

    BST(BST&& other)  : root_{other.root_}{
      other.root_ = nullptr;
    }

    BST& operator=(const BST& other){
      clear();
      insert_subtree(other.root_);
      return *this;
    }

    BST& operator=(BST&& other)
    {
      clear();
      root_ = other.root_;
      other.root_ = nullptr;
      return *this;
    }

    ~BST() {clear();}

    void clear(){
      clear_subtree(root_);
    }

    void print() const {
      print_subtree(root_);
      std::cout << std::endl;
    }

    bool empty() const {return root_ == nullptr;}
    int depth() const {return depth(root_);}

    void insert(T element)
    {
      if(empty()) root_ = new Node(element);
      else {
        Node* previous;
        Node* current = root_;

        while(current != nullptr)
        {
          if(element < current->data_){
            previous = current;
            current = current->left;
          } else if (element > current->data_){
            previous = current;
            current = current->right;
          } 
        }
      }
    }

    void preorder(){return preorder(root_);}

    void inorder(){return inorder(root_);}

    void postorder(){return postorder(root_);}
    
    void erase(const T& other){

      Node* previous = nullptr;
      auto temp = root_;

      while(temp!=nullptr)
      {
        if(temp->data_ == other)
        {
          if(previous == nullptr) eraseNode(root_);
          else if(previous->right == temp)  eraseNode(previous->right);
          else if(previous->left == temp) eraseNode(previous->left);
        }
        else if(other < temp->data_)
        {
          previous = temp;
          temp = temp->left;
        }else
          temp = temp->right;
      }

    }

  void eraseNode(Node*& node){
    if(node->left == nullptr && node->right == nullptr){
      delete node;
      node = nullptr;
    } else if(node ->left == nullptr){
      auto temp = node;
      node = node->right;
      delete temp;
    } else if(node->right == nullptr){
      auto temp = node;
      node = node->left;
      delete temp;
    } else{
      Node* previous = nullptr;
      auto temp = node->left;
      while(temp -> right){
        previous = temp;
        temp = temp->right;
      }
      node ->data_ = std::move(temp->data_);

      if(previous == nullptr)
        node->left = temp->left;
      else
        previous->right = temp->left;
      delete temp;
      
    }
  }




  };





}
