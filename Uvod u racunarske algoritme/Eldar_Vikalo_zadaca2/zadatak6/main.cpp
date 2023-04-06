#include <iomanip>
#include <iostream>
#define N 8

int rezultat[N][N];

bool validno(
    int x, int y,
    int rezultat[N][N]) {  // provjera je li skok na neko mjesto validan
  return (x >= 0 && x < N && y >= 0 && y < N &&
          rezultat[x][y] == -1);  // ili je vec tu bio
}

void ispis() {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      std::cout << std::setw(3) << rezultat[i][j]
                << " ";  // ispis svih konjicevih skokova
    std::cout << std::endl;
  }
}

int konjicevSkok(int x, int y, int skok, int rezultat[N][N], int xSkok[N],
                 int ySkok[N]) {
  int x_dalje, y_dalje;
  if (skok == N * N)  // provjeravamo da li je cijela tabela popunjena
    return true;

  for (int i = 0; i < N; i++) {
    x_dalje = x + xSkok[i];
    y_dalje = y + ySkok[i];
    if (validno(
            x_dalje, y_dalje,
            rezultat)) {  // moramo provjeriti moze li skociti tamo, ako moze
      rezultat[x_dalje][y_dalje] = skok;  // skociti ce na to mjesto
      if (konjicevSkok(x_dalje, y_dalje, skok + 1, rezultat, xSkok, ySkok) ==
          true)
        return true;
      else
        rezultat[x_dalje][y_dalje] = -1;
    }
  }
  return false;  // vracamo false ako konjic ne moze da skoci na trazeno mjesto
}

bool tablaSkokova() {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) rezultat[i][j] = -1;
  int xSkok[N] = {2, 1, -1, -2, -2, -1, 1, 2};
  int ySkok[N] = {1, 2, 2, 1, -1, -2, -2, -1};
  rezultat[0][0] = 0;  // startamo od vrijednosti 0, pa za svaki skok +1

  if (konjicevSkok(0, 0, 1, rezultat, xSkok, ySkok) == false) {
    std::cout << "Nema gdje da skoci";
    return false;
  } else
    ispis();
  return true;
}

int main() { tablaSkokova(); }
