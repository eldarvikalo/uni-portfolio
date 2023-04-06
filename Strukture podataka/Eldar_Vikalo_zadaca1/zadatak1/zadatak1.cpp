#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>


class Radnik
{
private:
    std::string firstName_;
    std::string lastName_;
    int age_;
    int internship_;
    int salary_;
    std::string telephoneNumber_;

  public:

    std::string GetFirstName() const
    {
      return firstName_;
    }

    std::string GetLastName() const
    {
      return lastName_;
    }

    int GetAge() const
    {
      return age_;
    }

    int GetInternship() const
    {
      return internship_;
    }

    int GetSalary() const
    {
      return salary_;
    }

    std::string GetTelephoneNumber() const
    {
      return telephoneNumber_;
    }

    void SetFirstName(std::string firstName)
    {
      firstName_ = firstName;
    }

    void SetLastName(std::string lastName)
    {
      lastName_ = lastName;
    }

    void SetAge(int age)
    {
      age_ = age;
    }

    void SetInternship(int internship)
    {
      internship_ = internship;
    }

    void SetSalary(int salary)
    {
       salary_ = salary;
    }

    void SetTelephoneNumber(std::string telephoneNumber)
    {
      telephoneNumber_ = telephoneNumber;
    }

};

void UpisiRadnike(std::ifstream& input, std::vector<Radnik>& vec)
{ 
  std::string firstname, lastname, age, internship, salary, telephonenumber;
  Radnik radnik;

  while(input)
  {
        std::getline(input, firstname, ',');
        radnik.SetFirstName(firstname);
        std::getline(input, lastname, ',');
        radnik.SetLastName(lastname);
        std::getline(input , age, ',');
        radnik.SetAge(std::stoi(age));
        std::getline(input,internship, ',');
        radnik.SetInternship(std::stoi(internship));
        std::getline(input, salary, ',');
        radnik.SetSalary(std::stoi(salary));
        std::getline(input, telephonenumber);
        radnik.SetTelephoneNumber(telephonenumber);

        vec.push_back(radnik);

  }

}

void IspisRadnika(const std::vector<Radnik>& vec)
{
  for(Radnik radnik : vec)
  {
    std::cout << radnik.GetFirstName() << ' ' << radnik.GetLastName() << ' ' << radnik.GetAge() << ' ' << radnik.GetInternship() << ' ' << radnik.GetSalary() << ' ' << radnik.GetTelephoneNumber() << std::endl;
  }
}



void Retirement(std::vector<Radnik>& radnici)
{
  auto iter = std::remove_if(radnici.begin(), radnici.end() , [](Radnik radnik){
      return radnik.GetAge() > 55;
      });

  radnici.erase(iter, radnici.end());
}

  int temporarySalary;
  int increasedSalary;

  void Salary_10_percent(std::vector<Radnik>& radnici)
{
  std::sort(radnici.begin() , radnici.end(), [](Radnik a, Radnik b)
      {
      return a.GetAge() < b.GetAge();
      });

  for(int i = 0; i< 15; i++)
  {
    temporarySalary = radnici.at(i).GetSalary();
    increasedSalary = temporarySalary + temporarySalary*0.1;
    radnici.at(i).SetSalary(increasedSalary);
  }
}

void Salary_20_percent(std::vector<Radnik>& radnici)
{
  for(Radnik& r : radnici)
  {
    if(r.GetInternship() > 15)
    {
      temporarySalary = r.GetSalary();
      increasedSalary = temporarySalary + temporarySalary*0.2;
      r.SetSalary(increasedSalary);
    }
  }
}


int main(void)
{

  std::vector<Radnik> radnici;

  std::ifstream input;

  input.open("acme.txt"); 

  UpisiRadnike(input, radnici);

  input.close();

  input.open("globex.txt");

  UpisiRadnike(input, radnici);

  input.close();

  Retirement(radnici); //Penzionisanje radnika 

  Salary_10_percent(radnici); //Plata za mlade

  Salary_20_percent(radnici); //Plata za iskusnije radnike

  std::sort(radnici.begin(), radnici.end(), [](const Radnik& r1, const Radnik& r2){
  if(r1.GetFirstName() == r2.GetFirstName())
  return r1.GetLastName() < r2.GetLastName();
  else
  return r1.GetFirstName() < r2.GetFirstName();
      });

  std::ofstream output;
  output.open("corp.txt");
  
  for( const Radnik& r : radnici)
  {
    output << r.GetFirstName() << ' ' << r.GetLastName() << '-' <<r.GetAge() << '('<<r.GetInternship()<< ')' << '-' << r.GetSalary() << " : "<<r.GetTelephoneNumber() <<std::endl; 
  }

  output.close();

return 0;
}
