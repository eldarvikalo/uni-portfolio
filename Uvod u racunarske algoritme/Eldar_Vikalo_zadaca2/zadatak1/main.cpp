#include <iostream>

int minimum(int arr[], int beg, int end) {
  while (beg < end) {
    int mid = beg + (end - beg) / 2;  // pronadjemo middle
    if (arr[mid] == arr[end])  // poredimo, ako su jednaki, end smanjujemo
      end--;
    else if (arr[mid] >
             arr[end])  // ako je mid veci, beginu dodjelimo indeks od mid+1
      beg = mid + 1;
    else
      end = mid;  // ako ne udjemo ni u jedan uslov, sad je end jedank middle
  }
  return arr[end];
}

int main(void) {
  int i = 0;
  int a[6];
  while (std::cin >> a[i]) ++i;

  // int a[] = {32,32,432,45325,46,334,23};
  int n = sizeof(a) / sizeof(a[0]);

  auto x = minimum(a, 0, n - 1);

  std::cout << x << std::endl;
  return 0;
}

