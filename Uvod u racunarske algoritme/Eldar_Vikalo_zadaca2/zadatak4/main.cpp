#include <iostream>

int maksimalnaSuma(int arr[], int size) {
  int ukupno = arr[0];    // ova varijabla nam predstavlja sve sto je sabrano do sad
  int trenutni = arr[0]; // trenutni je najveci broj do sad sabran, koji se poredi sa ukupno,
                        // gdje se pohrani prava najveca suma

  for (int i = 1; i < size; i++) {
    trenutni = std::max(arr[i], trenutni + arr[i]);
    ukupno = std::max(ukupno, trenutni);
  }
  return ukupno;
}

int main(void) {
  int arr[8];
  int i = 0;
  while (std::cin >> arr[i]) ++i;

  int size = sizeof(arr) / sizeof(arr[0]);
  int maximum = maksimalnaSuma(arr, size);
  std::cout << "Maksimalna suma unutar niza je " << maximum << std::endl;

  return 0;
}
