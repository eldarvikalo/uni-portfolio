#include <iostream>

#define N 4

int maze[N][N];

void labirint_cin() {  // Ovo je iskljucivo za pohranu podataka iz .txt fajla
  int x, y;
  std::cin >> x >> y;

  int unos;
  int j = 0;
  for (auto i = 0; i <= x; ++i) {
    while (std::cin >> unos) {
      maze[i][j] = unos;
      ++j;
    }
  }
}

int rezultat[N][N];  // Krajnje rjesenje spremljeno u ovoj matrici
void ispis_lab() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) std::cout << rezultat[i][j] << " ";
    std::cout << std::endl;
  }
}

bool validno(
    int x,
    int y) {  // provjeravamo je li pozicija unutar labirinta i je li jednaka 1
  if (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1) return true;
  return false;
}

bool rjesenje_lab(int x, int y) {
  if (x == N - 1 && y == N - 1) {
    rezultat[x][y] = 1;
    return true;
  }

  if (validno(x, y) == true) {  // ako su x i y validni
    rezultat[x][y] = 1;         // setujemo tu poziciju na 1
    if (rjesenje_lab(x + 1, y) ==
        true)  // sada trazimo daljnju pozciju, ali po x osi
      return true;
    if (rjesenje_lab(x, y + 1) ==
        true)  // ako je x dosao do kraja, onda idemo po y osi
      return true;
    rezultat[x][y] =
        0;  // ako nije proslo ni po x ni po y osi, na kraju smo i setujemo na 0
    return false;
  }
  return false;
}

bool putDoCilja() {
  if (rjesenje_lab(0, 0) == false) {
    std::cout << "Nema puta";
    return false;
  }
  ispis_lab();
  return true;
}

int main() {
  labirint_cin();
  putDoCilja();
  return 0;
}
