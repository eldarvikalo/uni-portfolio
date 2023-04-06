#include <iostream>

void heapify(int arr[], int n, int i) {
  // i je korijen stable, n je size od niza
  int parent = i;
  int lc = 2 * i + 1;
  int rc = 2 * i + 2;

  // Uslov da je lijevo dijete vece od roditelja
  if (lc < n && arr[lc] > arr[parent]) parent = lc;
  // Uslov da je desno dijete vece od roditelja
  if (rc < n && arr[rc] > arr[parent]) parent = rc;
  // Ako parent nije korijen
  if (parent != i) {
    std::swap(arr[i], arr[parent]);

    // rekurzijom radimo na podstablu
    heapify(arr, n, parent);
  }
}

void heapSort(int arr[], int n) {
  // mijenajamo indekse u nizu
  for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
    // Trenutni korijen saljemo na kraj niza
    std::swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

void ispis(int arr[], int n) {
  for (int i = 0; i < n; ++i) std::cout << arr[i] << " ";
  std::cout << std::endl;
}

int main() {
  int arr[20];
  int i = 0;
  while (std::cin >> arr[i]) ++i;

  int n = sizeof(arr) / sizeof(arr[0]);

  std::cout << "Nesortirani niz: ";
  ispis(arr, n);
  heapSort(arr, n);

  std::cout << "Sortirani niz: ";
  ispis(arr, n);
}
