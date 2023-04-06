#include <iostream>

unsigned long kusur_kombinacije(int a[], int n) {
  int pom[n + 1];
  int i = 0;

  while (i < n + 1) {
    pom[i] = 0;
    ++i;
  }
  // postavljene vrijednosti na 0 jer je lokalna varijabla, u slucaju
  // da nisu vrijednosti 0, rezultat bude skroz drugacji

  pom[0] = 1;

  int size = sizeof(&a) / sizeof(a[0]);  // broj apoena
  for (int i = 0; i < size + 1; ++i) {
    for (int j = 0; j < n + 1; ++j) {
      if (a[i] <= j) {
        pom[j] += pom[(j - a[i])];
      }
    }
  }
  return pom[n];
}

int main() {
  int n;
  std::cin >> n;
  int a[3];

  int i = 0;
  while (std::cin >> a[i]) ++i;
  std::cin.clear();
  // int size = sizeof(a)/sizeof(a[0]);

  // std::cout << "n " << n<< std::endl;
  // for(auto e : a)
  //   std::cout <<e<<' ';
  // std::cout << std::endl;

  std::cout << kusur_kombinacije(a, n) << std::endl;

  return 0;
}
