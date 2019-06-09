#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>

#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

struct studentai
{
    string vardas;
    string pavarde;
    int egz;
    double galutinis;
    double nd_vidurkis;
};

studentai gauti_studenta(int i);
void skaiciuoti_galutini(studentai& stud);
bool ar_teigiama_grupe(studentai stud);
void uzpildyti_eilute(studentai stud, ofstream& file);
void skaityti_is_failo(string eilute, studentai& stud);
std::vector<std::string> split(std::string strToSplit, char delimeter);




int main ()
{
    vector<studentai> stud;

    ofstream failas_t;
    ofstream failas_n;
    failas_t.open("teigiami.txt");
    failas_n.open("neigiami.txt");

    failas_n << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis vid." << endl;
    failas_n << "-----------------------------------------------------------------" << endl;
    failas_t << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis vid." << endl;
    failas_t << "-----------------------------------------------------------------" << endl;


    ifstream prad_failas;
    prad_failas.open ("studentai.txt");
    int n = 0;
    string eilute;
    prad_failas >> eilute;
    while (prad_failas >> eilute)
    {
        skaityti_is_failo(eilute, stud[n]);
        if(ar_teigiama_grupe(stud[n]))
        {
            uzpildyti_eilute(stud[n], failas_t);
        }
        else
        {
            uzpildyti_eilute(stud[n], failas_n);
        }
        n++;
    }
    prad_failas.close();

    int kiekis = 0;
    cout << "Kiek duomenu generuoti ";
    try {
        cin >> kiekis;
    } catch(int e) {
        cout << "Klaida " << e << endl;
    }

    auto pradzios_laikas = chrono::steady_clock::now();


    for(int i = 0; i < kiekis; i++)
    {

        stud.push_back(gauti_studenta(i));
        skaiciuoti_galutini(stud[i]);
        if(ar_teigiama_grupe(stud[i]))
        {
            uzpildyti_eilute(stud[i], failas_t);
        }
        else
        {
            uzpildyti_eilute(stud[i], failas_n);
        }
    }
    failas_n.close();
    failas_t.close();

    auto pabaigos_laikas = chrono::steady_clock::now();
    auto laiko_skirtumas = pabaigos_laikas - pradzios_laikas;
    cout  << "Uztruko " << chrono::duration <double, milli> (laiko_skirtumas).count() << " milisekundziu" << endl;
    return 0;
}

void uzpildyti_eilute(studentai stud, ofstream& file)
{
    file << left << setw(15) << stud.vardas << setw(15) << stud.pavarde << right << setw(5) << stud.galutinis << endl;
}

studentai gauti_studenta(int i)
{
    studentai stud;
    stud.nd_vidurkis = 0;
    stud.vardas = "Vardas-" + to_string(i);
    stud.pavarde = "Pavarde-" + to_string(i);
    for(int i = 0; i < 5; i++)
    {
        int ran = rand() % 10 + 1;
        stud.nd_vidurkis += ran;
    }
    stud.egz = rand() % 10 + 1;
    stud.nd_vidurkis = stud.nd_vidurkis / 5;
    return stud;
}

bool ar_gera_grupe(studentai stud)
{
    return stud.galutinis >= 5;
}

void skaiciuoti_galutini(studentai& stud)
{
    stud.galutinis = stud.nd_vidurkis * 0.4 + stud.egz * 0.6;
}

void skaityti_is_failo(string eilute, studentai& stud)
{
    std::vector<std::string> data;

    data = split(eilute, ';');

    stud.vardas = data[0];
    stud.pavarde = data[1];
    stud.nd_vidurkis = stoi(data[2]);
    stud.egz = stoi(data[3]);
}

std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
        splittedStrings.push_back(item);
    }
    return splittedStrings;
}
