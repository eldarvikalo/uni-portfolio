#include <iostream>
#include <initializer_list>
#include "MojVektor.hpp"
#include <math.h>

class Polinom
{
public:
  Polinom(const std::initializer_list<int> &lista)
      : stepen_polinoma_(lista.size() - 1), koeficijenti_polinoma_(lista)
  {
  }

  Polinom(unsigned int broj_koeficijenata)
      : stepen_polinoma_(broj_koeficijenata - 1)
  {
    koeficijenti_polinoma_.resize(broj_koeficijenata);
  }

  Polinom(const Polinom &p)
      : stepen_polinoma_(p.stepen_polinoma_), koeficijenti_polinoma_(p.koeficijenti_polinoma_)
  {
  }

  void setStepenPolinoma(int stepen)
  {
    stepen_polinoma_ = stepen;
  }

  int getStepenPolinoma() const
  {
    return stepen_polinoma_;
  }

  void setKoeficijentiPolinoma(const MojVektor<int> &koeficijenti)
  {
    koeficijenti_polinoma_ = koeficijenti;
  }

  MojVektor<int> getKoeficijentiPolinoma() const
  {
    return koeficijenti_polinoma_;
  }

  Polinom operator+(const Polinom &p)
  {
    int i = 0;
    if (stepen_polinoma_ >= p.stepen_polinoma_)
    {
      Polinom novi = *this;
      for (int koeficijent : p.koeficijenti_polinoma_)
      {
        novi.koeficijenti_polinoma_.at(i++) += koeficijent;
      }

      return novi;
    }
    else
    {
      Polinom novi(p.stepen_polinoma_ + 1);
      MojVektor<int> novi_koeficijenti = p.koeficijenti_polinoma_;

      for (int koeficijent : koeficijenti_polinoma_)
      {
        novi_koeficijenti.at(i++) += koeficijent;
      }

      novi.koeficijenti_polinoma_ = novi_koeficijenti;

      return novi;
    }
  }

  Polinom operator-(const Polinom &p)
  {
    int i = 0;
    if (stepen_polinoma_ >= p.stepen_polinoma_)
    {
      Polinom novi = *this;
      for (int koeficijent : p.koeficijenti_polinoma_)
      {
        novi.koeficijenti_polinoma_.at(i++) -= koeficijent;
      }

      return novi;
    }
    else
    {
      Polinom novi(p.stepen_polinoma_ + 1); // ovdje sam dodo +1???
      MojVektor<int> novi_koeficijenti;

      while (i < stepen_polinoma_ + 1)
      {
        novi_koeficijenti.push_back(koeficijenti_polinoma_.at(i) - p.koeficijenti_polinoma_.at(i));
        i++;
      }

      while (i < p.getStepenPolinoma() + 1)
      {
        novi_koeficijenti.push_back(p.koeficijenti_polinoma_.at(i) * -1);
      }

      novi.koeficijenti_polinoma_ = novi_koeficijenti;

      return novi;
    }
  }

  Polinom operator*(const Polinom &p)
  {
    int broj_koeficijenata = stepen_polinoma_ + p.stepen_polinoma_ + 2;
    Polinom novi(broj_koeficijenata);

    MojVektor<int> novi_koeficijenti;

    novi_koeficijenti.resize(broj_koeficijenata);

    for (int i = 0; i < stepen_polinoma_ + 1; i++)
    {
      for (int j = 0; j < p.stepen_polinoma_ + 1; j++)
      {
        novi_koeficijenti.at(i + j) += koeficijenti_polinoma_.at(i) * p.koeficijenti_polinoma_.at(j);
      }
    }

    novi.koeficijenti_polinoma_ = novi_koeficijenti;

    return novi;
  }

  double operator()(double x)
  {
    double rezultat = 0;

    for (int i = 0; i < stepen_polinoma_ + 1; i++)
    {
      rezultat += koeficijenti_polinoma_.at(i) * std::pow(x, i);
    }

    return rezultat;
  }

  Polinom izvod()
  {
    Polinom novi = *this;

    novi.koeficijenti_polinoma_.erase(novi.koeficijenti_polinoma_.begin());

    novi.stepen_polinoma_--;

    for (int i = 0; i < novi.stepen_polinoma_ + 1; i++)
    {
      novi.koeficijenti_polinoma_.at(i) *= i + 1;
    }

    return novi;
  }

  Polinom &operator+=(const Polinom &p)
  {
    return *this = operator+(p);
  }

private:
  int stepen_polinoma_;
  MojVektor<int> koeficijenti_polinoma_;
};

std::istream &operator>>(std::istream &in, Polinom &p)
{
  int koeficijent;
  MojVektor<int> koeficijenti;

  for (int i = 0; i < p.getStepenPolinoma() + 1; i++)
  {
    std::cout << "Unesite " << i << ". koeficijent: ";
    in >> koeficijent;
    koeficijenti.push_back(koeficijent);
  }

  p.setKoeficijentiPolinoma(koeficijenti);

  return in;
}

std::ostream &operator<<(std::ostream &out, const Polinom &p)
{
  MojVektor<int> koeficijenti = p.getKoeficijentiPolinoma();

  out << koeficijenti.at(0);

  for (int i = 1; i < p.getStepenPolinoma() + 1; i++)
  {
    if (koeficijenti.at(i) < 0)
    {
      out << " - " << koeficijenti.at(i) * -1 << "*x^"<< i;
    }
    else if (koeficijenti.at(i) > 0)
    {
      out << " + " << koeficijenti.at(i) << "*x^" << i;
    }
  }

  out << std::endl;

  return out;
}

int main()
{
  Polinom p1({-1, 2}); // P(x): -1 + 2*x
  Polinom p2(3);       // polinom drugog stepena (a + b*x + c*x^2)
  std::cin >> p2;      // učitati sa tastature polinom drugog stepena

  std::cout << "P1(x): " << p1 << std::endl;
  std::cout << "P2(x): " << p2 << std::endl;

  auto p3 = p1 + p2;
  auto p4 = p2 - p1;
  auto p5 = p1 * p2;

  std::cout << "P3(x): " << p3 << std::endl;
  std::cout << "P4(x): " << p4 << std::endl;
  std::cout << "P5(x): " << p5 << std::endl;

  double rezultat = p3(5);
  std::cout << "P3(5): " << rezultat << std::endl;

  p3 = p2.izvod();
  std::cout << "P2'(x): " << p3 << std::endl;

  std::cout << "P2'(5): " << p3(5) << std::endl;

  p2 += p1;

  std::cout << "P2(x): " << p2 << std::endl;
}
