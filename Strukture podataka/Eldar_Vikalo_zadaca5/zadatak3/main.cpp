#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class Predmet {
  public:
  std::string naziv;
};

class Ispit {
  public:
  Predmet predmet;
  std::string datumIspita;
};

struct Student {
  size_t indeksStudenta;
  std::string ime;
  std::string prezime;
  short sumaOcjena{0};
  std::vector<Ispit> polozeni;

  double prosjecnaOcjena() { return sumaOcjena / polozeni.size(); }
};

short Meni() {
  short option;

  do {
    std::cout << std::endl;
    std::cout << "1. Dodaj novog studenta" << std::endl;
    std::cout << "2. Dodaj novi ispit" << std::endl;
    std::cout << "3. Dodaj novi predmet" << std::endl;
    std::cout << "4. Dodaj novi rezultat zeljenog ispita" << std::endl;
    std::cout << "5. Ispisi sve ispite na zeljeni datum" << std::endl;
    std::cout << "6. Ispisi sve studente koji su polozili odredjeni ispit"
              << std::endl;
    std::cout << "7. Hronoloski ispisi sve ispite koje je polozio student i "
                 "ispisi njegovu prosjecnu ocjenu"
              << std::endl;
    std::cin >> option;
  } while (option < 1 || option > 7);
  return option;
}

int main() {
  Student s;
  Ispit is;
  Predmet p;

  short ocjena;
  std::unordered_map<int, Student> mapaStudenata;
  std::unordered_map<std::string, std::vector<Ispit>> mapaIspita;
  std::unordered_map<std::string,
                     std::unordered_map<std::string, std::vector<Student>>>
      mapa;  // ugnijezdena mapa
  std::vector<Predmet> predmeti;
  while (true) {
    short option = Meni();
    switch (option) {
      case 1:
        std::cout << "Broj indeksa studenta ";
        std::cin >> s.indeksStudenta;
        std::cout << "Ime studenta ";
        std::cin >> s.ime;
        std::cout << "Prezime studenta ";
        std::cin >> s.prezime;
        mapaStudenata[s.indeksStudenta] = s;
        break;
      case 2:
        std::cout << "Naziv ispita ";
        std::cin >> p.naziv;
        std::cout << "Datum ispita u formatu XX.XX.XXXX. ";
        std::cin >> is.datumIspita;
        is.predmet = p;
        for (auto &e : mapaIspita) {
          for (auto i = 0; i < e.second.size(); i++) {
            if (e.second.at(i).predmet.naziv == p.naziv) {
              if (e.first == is.datumIspita) {
                std::cout
                    << "Ne moze vise ispita iz jednog predmeta na isti datum"
                    << std::endl;
                break;
              }
            }
          }
        }

        mapaIspita[is.datumIspita].push_back(is);
        break;
      case 3:
        std::cout << "Naziv predmeta ";
        std::cin >> p.naziv;
        for (auto i = 0; i < predmeti.size(); i++) {
          if (predmeti.at(i).naziv == p.naziv) {
            std::cout << "Vec postoji taj predmet u sistemu" << std::endl;
            break;
          }
        }
        predmeti.push_back(p);
        break;
      case 4:
        std::cout << "Broj indeksa studenta ";
        std::cin >> s.indeksStudenta;
        for (auto &e : mapaStudenata) {
          if (e.second.indeksStudenta != s.indeksStudenta) {
            std::cout << "Nemamo studenta sa tim indeksom u sistemu"
                      << std::endl;
            break;
          }
        }
        std::cout << "Ocjena studenta ";
        std::cin >> ocjena;
        if (ocjena < 6) {
          std::cout << "Nije prolazna ocjena" << std::endl;
          break;
        }
        std::cout << "Datum ispita u formatu XX.XX.XXXX. ";
        std::cin >> is.datumIspita;
        std::cout << "Naziv predmeta ";
        std::cin >> p.naziv;
        is.predmet = p;
        mapaStudenata[s.indeksStudenta].polozeni.push_back(is);
        mapaStudenata[s.indeksStudenta].sumaOcjena += ocjena;
        mapa[is.datumIspita][p.naziv].push_back(
            mapaStudenata[s.indeksStudenta]);
        break;
      case 5:
        std::cout << "Datum ispita u formatu XX.XX.XXXX. ";
        std::cin >> is.datumIspita;
        for (auto &e : mapaIspita) {
          for (auto i = 0; i < e.second.size(); i++) {
            if (e.second.at(i).datumIspita != is.datumIspita) {
              std::cout << "Nema ispita na taj datum" << std::endl;
              break;
            }
          }
        }
        for (const Ispit &ispit : mapaIspita[is.datumIspita]) {
          std::cout << ispit.predmet.naziv << std::endl;
        }
        break;
      case 6:
        std::cout << "Datum ispita u formatu XX.XX.XXXX. ";
        std::cin >> is.datumIspita;
        std::cout << "Naziv predmeta ";
        std::cin >> p.naziv;

        for (const Student &student : mapa[is.datumIspita][p.naziv]) {
          std::cout << "Ime i prezime studenta: " << student.ime << " "
                    << student.prezime << std::endl;
        }
        break;
      case 7:
        std::cout << "Broj indeksa studenta ";
        std::cin >> s.indeksStudenta;
        for (const Ispit &ispit : mapaStudenata[s.indeksStudenta].polozeni) {
          std::cout << "Naziv predmeta: " << ispit.predmet.naziv << std::endl;
        }

        std::vector<Ispit> vektorIspita =
            mapaStudenata[s.indeksStudenta].polozeni;
        auto hronoloski = [](const Ispit &is1, const Ispit &is2) {
          int dan1 = std::stoi(is1.predmet.naziv.substr(0, 2));
          int mjesec1 = std::stoi(is1.predmet.naziv.substr(3, 2));
          int godina1 = std::stoi(is1.predmet.naziv.substr(5, 4));

          int dan2 = std::stoi(is2.predmet.naziv.substr(0, 2));
          int mjesec2 = std::stoi(is2.predmet.naziv.substr(3, 2));
          int godina2 = std::stoi(is2.predmet.naziv.substr(5, 4));
          if (godina1 == godina2) {
            if (mjesec1 == mjesec2) {
              return dan1 < dan2;
            } else {
              return mjesec1 < mjesec2;
            }
          } else {
            return godina1 < godina2;
          }
        };
        std::sort(vektorIspita.begin(), vektorIspita.end(), hronoloski);
        for (const Ispit &ispit : vektorIspita) {
          std::cout << ispit.predmet.naziv << std::endl;
        }

        std::cout << mapaStudenata[s.indeksStudenta].prosjecnaOcjena()
                  << std::endl;
        break;
    }
  }
}
