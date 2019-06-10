#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <deque>

using namespace std;


struct studentas
{
    string vardas;
    string pavarde;
    int egz;
    double galutinis;
    double nd_vidurkis;

} ;

void skaiciavimai(studentas& stud);
studentas generate_data(int i);
int tikrinimas(studentas stud);
void out(studentas stud, ofstream& file);



int main ()

{

    deque<studentas> stud;
    int i = 0;
    int kiekis = 10000;
    ifstream data;
    data.open("visi.txt");
    string line;
    for(int i = 0; i < kiekis; i++)

    {

        studentas naujas;
        data >> line;
        naujas.vardas = line;
        data >> line;
        naujas.pavarde = line;
        data >> line;
        naujas.nd_vidurkis = stod(line);
        data >> line;
        naujas.egz = stoi(line);
        stud.push_back(naujas);

    }


    auto start = chrono::steady_clock::now();
    ofstream failas_t;
    ofstream failas_n;
    failas_t.open("teigiami.txt");
    failas_n.open("neigiami.txt");

    failas_n << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (vid.)" << endl;
    failas_n << "-----------------------------------------------------------------------" << endl;
    failas_t << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (vid.)" << endl;
    failas_t << "-----------------------------------------------------------------------" << endl;
    for (deque<studentas>::iterator it = stud.begin(); it != stud.end(); it++)

    {

        skaiciavimai(*it);
        int ar = tikrinimas(*it);
        if(ar > 0)
       {
            out(*it,failas_t);
        }
        else
        {
            out(*it,failas_n);
        }
        i++;
    }
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout  << "Uztruko: " << chrono::duration <double, milli> (diff).count() << " milli s" << endl;
    failas_n.close();
    failas_t.close();
    return 0;

}

studentas get_data(int i, ifstream data)

{

    studentas stud;
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
    return stud;

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
