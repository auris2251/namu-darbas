#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;
const int max_stud_kiekis = 10000;
struct studentas
{
    string vardas;
    string pavarde;
    int egz;
    double galutinis;
    double nd_vidurkis;
} ;
void skaiciavimai(studentas& stud);
void generate_data(studentas& stud, int i);
int tikrinimas(studentas stud);
void out(studentas stud, ofstream& file);


int main ()

{
    vector<studentas> stud;
    int i = 0;
    int kiekis = 0;
    cout << "Kiek norite generuoti duomenu? (max 10000)" << endl;
    try
    {
        while(true)
        {
            cin >> kiekis;
            if(kiekis > 10000)
            {
                cout << "Per didelis pasinroktas duomenu kiekis! Iveskite is naujo" << endl;
            }
            else if (kiekis < 0)
            {
                cout << "Per mazas pasirinktas duomenu kiekis! Iveskite is naujo" << endl;
            }
            else
            {
                break;
            }
        }
    }
    catch(int e)
    {
        cout << "Klaidos nr " << e << endl;
    }
    ofstream failas_t;
    ofstream failas_n;
    failas_t.open("teigiami.txt");
    failas_n.open("neigiami.txt");
    failas_n << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (vid.)" << endl;
    failas_n << "-----------------------------------------------------------------------" << endl;
    failas_t << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (vid.)" << endl;
    failas_t << "-----------------------------------------------------------------------" << endl;
    for(int j = 0; j < kiekis; j++)

    {

        generate_data(stud[j], j);
        skaiciavimai(stud[j]);
        int ar = tikrinimas(stud[j]);
        if(ar > 0)
        {
            failas(stud[j],failas_t);
        }
        else
        {
            failas(stud[j],failas_n);
        }
        i++;

    }

    failas_n.close();
    failas_t.close();
    return 0;

}
void generate_data(studentas& stud, int i)
{

    stud.nd_vidurkis = 0;
    stud.vardas = "vardas" + to_string(i);
    stud.pavarde = "pavarde" + to_string(i);
    for(int i = 0; i < 5; i++)
    {
        int ran = rand() % 10 + 1;
        stud.nd_vidurkis += ran;
    }
    int random = rand() % 10 + 1;
    stud.egz = random;
    stud.nd_vidurkis = stud.nd_vidurkis / 5;
}

void skaiciavimai(studentas& stud)
{
    stud.galutinis = stud.nd_vidurkis * 0.4 + stud.egz * 0.6;
}
int tikrinimas(studentas stud)
{
    if(stud.galutinis < 5)
    {
       return -1;
    }
    else
    {
        return 1;
    }

}
void out(studentas stud, ofstream& file)
{
    file << left << setw(15) << stud.vardas << setw(15) << stud.pavarde << right << setw(5) << stud.galutinis << endl;
}
