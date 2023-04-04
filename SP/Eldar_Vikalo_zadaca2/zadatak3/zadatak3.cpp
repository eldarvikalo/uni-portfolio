#include <iostream>
#include "MojVektor.hpp"
#include <string>
#include <algorithm>

class Osoba{
  protected:
    std::string ime_;
    std::string prezime_;
    short godineStartosti_;
};

class Automobil{
  private:

  std::string model_;
  std::string boja_;
  int godinaProizvodnje_;

  public:

  std::string GetModel() const
  {
    return model_;
  }

  std::string GetBoja() const
  {
    return boja_;
  }

  int GetGodinaProizvodnje() const
  {
    return godinaProizvodnje_;
  }

  void SetModel(std::string model)
  {
    model_ = model;
  }

  void SetBoja(std::string boja)
  {
    boja_ = boja;
  }

  void SetGodinaProizvodnje(int godinaProizvodnje)
  {
    godinaProizvodnje_ = godinaProizvodnje;
  }

};

class Vozac : Osoba {
  private:

  short godineStaza_;
  Automobil automobil_;
  unsigned int vrijemeVoznje_;

  public:

  std::string GetIme() const
  {
    return ime_;
  }

  std::string GetPrezime() const
  {
    return prezime_;
  }

  short GetGodineStarosti() const
  {
    return godineStartosti_;
  }

  short GetGodineStaza() const
  {
    return godineStaza_;
  }

  unsigned int GetVrijemeVoznje() const
  {
    return vrijemeVoznje_;
  }

  Automobil GetAutomobil() const
  {
    return automobil_;
  }

  void SetIme(std::string ime)
  {
    ime_ = ime;
  }

  void SetPrezime(std::string prezime)
  {
    prezime_ = prezime;
  }

  void SetGodineStarosti(short godineStarosti)
  {
    godineStartosti_= godineStarosti;
  }

  void SetGodineStaza(short godineStaza)
  {
    godineStaza_ = godineStaza;
  }

  void SetVrijemeVoznje(unsigned int vrijemeVoznje)
  {
    vrijemeVoznje_ = vrijemeVoznje;
  }

  void SetAutomobil(Automobil automobil)
  {
    automobil_ = automobil;
  }



};

void UnosPodatakaVozaca(MojVektor<Vozac>& vozaci)
{
  Vozac vozac;
  Automobil automobil;
  std::string ime, prezime, model, boja;
  short godineStarosti, godineStaza;
  int godinaProizvodnje;
  unsigned int vrijemeVoznje;


  short n;
  std::cout<<"Unesite zeljeni broj vozaca ";
  std::cin>>n;

  for(int i =0; i<n; i++)
  {
    std::cout << i+1 <<". vozac: " << std::endl;
    std::cout << "Unesite ime: "  << std::endl;
    std::cin >> ime;
    vozac.SetIme(ime);

    std::cout << "Unesite prezime: " << std::endl;
    std::cin >> prezime;
    vozac.SetPrezime(prezime);

    std::cout << "Unesite godine starosti: " << std::endl;
    std::cin >> godineStarosti;
    vozac.SetGodineStarosti(godineStarosti);

    std::cout << "Unesite godine staza: " << std::endl;
    std::cin >> godineStaza;
    vozac.SetGodineStaza(godineStaza);

    std::cout << "Unesite model automobila vozaca: " << std::endl;
    std::cin >> model;
    automobil.SetModel(model);

    std::cout << "Unesite boju automobila"  << std::endl;
    std::cin >> boja;
    automobil.SetBoja(boja);

    std::cout << "Unesite godinu proizvodnje automobila" << std::endl;
    std::cin >> godinaProizvodnje;
    automobil.SetGodinaProizvodnje(godinaProizvodnje);

    vozac.SetAutomobil(automobil);

    std::cout << "Unesite vrijeme za koje vozac odveze trku" << std::endl;
    std::cin >> vrijemeVoznje;
    vozac.SetVrijemeVoznje(vrijemeVoznje);

    vozaci.push_back(vozac);
  }
}

void IspisVozaca(const MojVektor<Vozac>& v)
{

  for(const Vozac& vo : v)
  {
    std::cout << vo.GetIme() << ' ' << vo.GetPrezime() << " ima "<< vo.GetGodineStarosti() <<  " godina i "<< vo.GetGodineStaza() << " godina staza, a vozi "<< vo.GetAutomobil().GetModel() << ' ' << vo.GetAutomobil().GetBoja() << " boje, koji je proizveden "<< vo.GetAutomobil().GetGodinaProizvodnje() << " godine. Vozac je sa tim automobilom odvozio trku za vrijeme: " <<vo.GetVrijemeVoznje() << " minuta. "<< std::endl;
  }
}



void RekordStaze(MojVektor<Vozac>& vektor)
{
  int rekordStaze = 201;
  for( Vozac& v : vektor)
  {
  if(v.GetVrijemeVoznje() < rekordStaze)
    std::cout << "Vozac " << v.GetIme() << ' '<< v.GetPrezime() << " je oborio rekord ove staze!!! " << std::endl;
  else
    break;
  }
}

int main(void)
{



  MojVektor<Vozac> vozaci;

  UnosPodatakaVozaca(vozaci);

  std::sort(vozaci.begin(), vozaci.end(), [](Vozac v1, Vozac v2){
      return v1.GetVrijemeVoznje() < v2.GetVrijemeVoznje();
      });

  IspisVozaca(vozaci);
  RekordStaze(vozaci);

  return 0;
}
