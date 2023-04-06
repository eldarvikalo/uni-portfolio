#include "heap.hpp"
#include <iostream>
#include <stdexcept>

int main(void)
{


  int size, value;
  std::cout << "Unesite broj clanova heapa" << std::endl;
  std::cin >> size;

  Heap<int> heap(size);
  for (size_t i = 0; i < size; i++) {
    std::cout << "Element: " << ' ';
    std::cin >> value;
    heap.insert(value);
  }
  
  // try{ 
  std::cout << "------------Ispis--------------" << std::endl;
  heap.ispis();
  std::cout << "Maksimalna vrijednost je "<< heap.getMax() << std::endl;
  std::cout << "Najmanji je "<< heap.getMin() << std::endl;
  std::cout << "------------Ispis--------------" << std::endl;
  heap.removeMax();
  std::cout << "Ispis nakon remove max" << std::endl;
  heap.ispis();
  std::cout << "Min vrjednost je " << heap.getMin() << std::endl;
  std::cout << "-------------------------------" << std::endl;
  std::cout << "Ispis nakon remove min" << std::endl;
  heap.removeMin();
  // std::cout << "Nakon remove min: " << heap.removeMin()<< std::endl;
  std::cout << "------------Ispis--------------" << std::endl;
  heap.ispis();
  std::cout << "-------------------------------" << std::endl;
  std::cout << "Najmanji je "<< heap.getMin() << std::endl;
  std::cout << "------------Ispis--------------" << std::endl;
  heap.ispis();
  
  std::cout << "Kopirani heap: " << std::endl;
  Heap<int> heapc{heap};
  heapc.ispis();

  Heap<int> heap1{3};  
  std::cout << "Default constructor" << std::endl;
  heap1.ispis();
  heap1 = heapc;
  std::cout << "Operator= " << std::endl;
  heap1.ispis();
  // }catch(std::out_of_range){
  // // std::cout << "Exception: " << std::endl; 
  // }


  
  
  return 0;
}
