#include <iostream>
// #include <algorithm>

int podSekv(int arr[], int n) {
  int temp[n];

  for (auto i = 0; i < n; i++)  // sve u temp nizu setujemo na 0
    temp[i] = 0;

  temp[0] = 1;

  for (int i = 1; i < n; i++) {
    // temp[i] = 1;
    for (int j = 0; j < i; j++) {
      if (arr[j] < arr[i] && temp[j] > temp[i]) temp[i] = temp[j];
    }
    temp[i]++;
  }

  int sekvenca = 0;
  for (int i = 0; i < n; ++i) sekvenca = std::max(sekvenca, temp[i]);
  return sekvenca;

  // auto sekvenca = std::max_element(temp, temp+n); // moze i ovako umjesto
  // petlje return *sekvenca;
}

int main() {
  int arr[9];
  int i = 0;
  while (std::cin >> arr[i]) ++i;

  int n = sizeof(arr) / sizeof(arr[0]);

  std::cout << "Duzina najduze rastuce podsekvence je: " << podSekv(arr, n)
            << std::endl;

  return 0;
}
