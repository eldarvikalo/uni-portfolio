#include <iostream>
#define N 9

int sudoku[N][N];

void sudoku_cin() {  // unos rezultata iz .txt fajla u globalnu matricu sudoku
  int unos;
  int j = 0;
  for (auto i = 0u; i <= N; ++i) {
    while (std::cin >> unos) {
      sudoku[i][j] = unos;
      ++j;
    }
  }
}

void ispis() {  // ispis sudoku tabele
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cout << sudoku[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool tabela3x3(int i, int j, int k, int sudoku[N][N]) {
  // Provjeravamo postoji li vrijednost k u tabeli 3x3
  int red = i - (i % 3);
  int kol = j - (j % 3);
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (sudoku[x + red][y + kol] == k) {
        return false;  // k postoji u 3x3 tabeli i vracamo false
      }
    }
  }
  return true;  // vracamo true ako k tu ne postoji
}

bool validno(int sudoku[N][N], int i, int j, int k) {
  // Provjeravamo redove i kolone, da li je tu vrijednst k
  for (int x = 0; x < N; x++) {
    // Red
    if (sudoku[i][x] == k) {  // ako pronadjemo vracamo false
      return false;
    }
    // Kolona
    if (sudoku[x][j] == k) {  // ako pronadjemo vracamo false
      return false;
    }
  }

  return tabela3x3(i, j, k, sudoku);
}
bool rjesenje(int sudoku[N][N]) {
  int i = 0, j = 0;
  bool pronaslo = false;
  // preko ugnijezdene petlje trazimo prazno mjesto na sudoku tabli
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      if (sudoku[i][j] ==
          0) {  // ako postoji prazno mjesto, pronaslo je  = true
        pronaslo = true;
        break;
      }
    }
    if (pronaslo) break;  // pronasli smo prazno mjesto, te sa true izlazimo
  }

  // Ako nemamo vise praznih mjesta, vracamo true. Dosli smo do kraja
  if (i == N && j == N) {
    return true;
  }

  for (int k = 1; k <= N; k++) {
    // ukoliko je validno, tu postavljamo vriednost k
    if (validno(sudoku, i, j, k)) {
      sudoku[i][j] =
          k;  // ako funckija validno vrati true, to znaci da nismo nasli
              // vrijednost k na tom mjestu i tek onda se postavljamo u tabelu
      if (rjesenje(sudoku) == true)
        return true;  // rekurzivno trazimo mjesta i setujemo
                      // vrijednosti k
      sudoku[i][j] = 0;
    }
  }
  return false;
}

int main() {
  sudoku_cin();
  rjesenje(sudoku);
  ispis();

  return 0;
}
