#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <string.h>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void menu() {

    cout << "1. Sisse logimine" << endl;
    cout << "2. Loo konto" << endl;
    cout << "3. exit" << endl;

}

void kasutaja_menu(double raha, string arveldus, string nimi) {

    cout << "-----------------------------------------------------" << endl;
    cout << " " << nimi << " | " << arveldus << " | " << raha << " Eurot  " << endl;
    cout << "-----------------------------------------------------" << endl;

    cout << "1. Saada raha" << endl;
    cout << "2. Vaata logi" << endl;
    cout << "3. Sisesta raha" << endl;
    cout << "4. vaheta konto settinguid" << endl;
    cout << "5. Logi välja" << endl;

}

void seadme_menu() {

    //cout << "1. Muuda kasutaja nime" << endl;
    cout << "1. Muuda kasutaja parooli" << endl;
    //cout << "3. Kustuta kasutaja" << endl;
    cout << "2. Tagasi" << endl;

}

void kirjuta(string kasutaja_tunnus, vector<string> kasutaja, double raha) {   
    
    ofstream fail;  
    fail.open("kasutaja_info\\" + kasutaja_tunnus + ".txt", ios::trunc);
    fail << kasutaja[0] << ";" << kasutaja[1] << ";" << kasutaja[2] << ";" << kasutaja[3] << ";" << raha << endl;
    fail.close();

}

void logi_saadi(string saaja_kasutaja, string saat_kasutaja, double raha) {

    time_t now = time(0);
    char *date = ctime(& now);

    ofstream SeeLogi;

    SeeLogi.open("logi\\" + saaja_kasutaja + ".log", ios::app);

    SeeLogi << saat_kasutaja << " saatis teile " << raha << " Eurot" << " | kell: " << date << endl;

    SeeLogi.close();

}

void logi_saatsid(string saaja_kasutaja, string saat_kasutaja, double raha) {

    time_t now = time(0);
    char *date = ctime(& now);

    ofstream SeeLogi;

    SeeLogi.open("logi\\" + saat_kasutaja + ".log", ios::app);

    SeeLogi << "Saatsite " << raha << " Eurot kasutajale " << saaja_kasutaja << " | kell: " << date << endl;

    SeeLogi.close();

}

void logi_rahalisamine(string see_kasutaja, double raha) {

    time_t now = time(0);
    char *date = ctime(& now);

    ofstream SeeLogi;

    SeeLogi.open("logi\\" + see_kasutaja + ".log", ios::app);

    SeeLogi << "Te sisestasitte " << raha << " Eurot" << " | kell: " << date << endl;

    SeeLogi.close();

}

vector<string> info_saamine(fs::path path) {

    string anme;
    vector<string> kasutaja;

    ifstream andmed(path);

    while (getline(andmed, anme, ';')) {

        kasutaja.push_back(anme);

    }

    return kasutaja;
}

void vaata_logi(string path) {

    ifstream logi(path);
    string rida;

    if(! logi.is_open()) {

        cout << "Ei saanud logi faili avada." << endl;

    }
    else {

        while (getline(logi, rida)) {

            cout << rida << endl;

        }
    }
    
}

void raha_saatmine() {
    
    string nimi, arveldus, kasutaja_tunnus, rida, temp_rida;
    double summa = 0;
    
    vector<string> kasutaja = {"lahe mees", "meelah", "kaks", "EE185470931905460488", "300"};
    vector<string> temp_kasutaja, paths;

    kasutaja = info_saamine("kasutaja_info/" + kasutaja[1] + ".txt");
    double minu_raha = stoi(kasutaja[4]);
    
    // viskab minema \n
    cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n'); 

    cout << "Sisesta saaja nimi: ";
    getline(cin, nimi);

    cout << "\nSisesta saaja arveldusarve: ";
    cin >> arveldus;

    cout << "\nSisesta summa: ";
    cin >> summa;

    while (summa < 1) {

        cout << "\nSumma on väiksem kui 1 euro" << endl;
        cout << "Sisesta summa: ";
        cin >> summa;

        while (summa > minu_raha) {

            cout << "\nSumma on suurem kui teil raha on" << endl;
            cout << "Sisesta summa: ";
            cin >> summa;

        }
        
    }

    string path = "kasutaja_info/";
    for (const auto & entry : fs::directory_iterator(path)) {

        cout << entry.path() << endl;
        //paus.push_back(entry.path());
    

        ifstream seeFail(entry.path());
        while (getline(seeFail, rida, ';')) {

            if (rida.find(arveldus) != string::npos) {

                cout << "Leitud" << endl;

                temp_kasutaja = info_saamine(entry.path());

                double raha = stoi(temp_kasutaja[4]);
                minu_raha -= summa;
                raha += summa;

                kirjuta(kasutaja[1], kasutaja, minu_raha);
                logi_saatsid(temp_kasutaja[0], kasutaja[0], summa);

                kirjuta(temp_kasutaja[1], temp_kasutaja, raha);
                logi_saadi(temp_kasutaja[0], kasutaja[0], summa);

                cout << summa << " Eurot on saadetud kasutajale " << temp_kasutaja[0] << endl;

                temp_kasutaja.clear();

                break;

            }
            else {

                cout << "Ei leitud" << endl;
            }
        }
    }

}



void renamethis(vector<string> kasutaja, fs::path vana_path) {
	
    auto uus = kasutaja[1];
    fs::path uus_path = "kasutaja_info/" + uus + ".txt";

    vana_path.replace_filename(uus_path);

} 

void nime_muutus(vector<string> kasutaja, double raha) {

    string uus_enimi, uus_pnimi, esi_kolm, pere_kolm, vana_tunnus, tais_nimi;

    cout << "Sisesta uus eesnimi: ";
    cin >> uus_enimi;

    cout << "\nSisesta uus perekonnanimi: ";
    cin >> uus_pnimi;

    for (int i = 0; i < 3; i++) {

        esi_kolm += uus_enimi[i];

    }
    for (int i = 0; i < 3; i++) {

        pere_kolm +=  uus_pnimi[i];

    }

    vana_tunnus = kasutaja[1];
    tais_nimi = uus_enimi + " " + uus_pnimi;
    kasutaja[1] = pere_kolm + esi_kolm;
    kasutaja[0] = tais_nimi;
    auto vana_path = "kasutaja_info/" + vana_tunnus + ".txt";

    kirjuta(vana_tunnus, kasutaja, raha);
    renamethis(kasutaja, vana_path);


}

void parooli_muutus(vector<string> kasutaja, double raha) {

    string vana_parool, uus_parool, uus_parool_k;

    cout << "Sisesta vana parool: ";
    cin >> vana_parool;

    cout << "\nSisesta uus parool: ";
    cin >> uus_parool;

    cout << "\nKinnita parool: ";
    cin >> uus_parool_k;

    if (vana_parool == kasutaja[2] && uus_parool == uus_parool_k) {

        kasutaja[2] = uus_parool;

        kirjuta(kasutaja[1], kasutaja, raha);

    }
    else {

        cout << "\nMidagi oli valesti" << endl;

    }
    

}

bool kustuta_kasutaja(vector<string> kasutaja) {

    char kindel;
    bool kustutatud = true;

    cout << "Kas oled kindel y/n: ";
    cin >> kindel;
    fs::path pool = "kasutaja_info/" + kasutaja[1] + ".txt";

    if (kindel == 'y') {

        remove(pool);

        kustutatud = true;

        return kustutatud;

    }
    else {

        kustutatud = false;

        return kustutatud;

    }
}

bool seadmed(vector<string> kasutaja, double raha) {

    int menu_valik;
    bool tagasi = false, login = false, kustutatud = false;

    while (tagasi == false) {

        kasutaja = info_saamine("kasutaja_info/" + kasutaja[1] + ".txt");
        seadme_menu();
        cin >> menu_valik;

        while (menu_valik > 2) {

            cout << "Valisitte liiga suure numbri\n(Valige 1-2)" << endl;
            seadme_menu();
            cin >> menu_valik;

        }

        switch (menu_valik) {

            case 3:
                
                cout << "\nValik 1" << endl;
                nime_muutus(kasutaja, raha);
                break;
                
            case 1:
                
                cout << "\nValik 1" << endl;
                parooli_muutus(kasutaja, raha);
                break;

            case 4:
                
                cout << "\nValik 3" << endl;
                kustutatud = kustuta_kasutaja(kasutaja);

                if (kustutatud == true) {

                    tagasi = true;
                    login = false;
                    return login;

                }
                else {

                    login = true;
                    return login;

                }
                
                break;

            case 2:
                cout << "\nValik 2" << endl;
                tagasi = true;
                break;

            default:
                cout << "Midagi Läks valesti" << endl;
                while (menu_valik > 3) {

                    cout << "Valisitte liiga suure numbri\n(Valige 1-2)" << endl;
                    seadme_menu();
                    cin >> menu_valik;

                }
                break;
        
        }
    }

    return login = true;
    
}

void lookasutaja() {

    time_t now = time(0);
    char *date = ctime(& now);

    srand(time(0));

    string enimi, pnimi, parool, parool2;
    string esi_kolm, pere_kolm, kasutaja_tunnus;
    string stemp, arveldus_arve, riik = "EE";
    int raha = 0;

    cout << "Sisesta enda eesnimi: ";
    cin >> enimi;
    
    cout << "\nSisesta enda perekonnanimi: ";
    cin >> pnimi;

    cout << "\nSisesta enda parool: ";
    cin >> parool;

    cout << "\nKinnita parool: ";
    cin >> parool2;


    while (parool2 != parool) {

        parool2.clear();
        parool.clear();

        cout << "\nSisesta enda parool: ";
        cin >> parool;

        cout << "\nKinnita parool: ";
        cin >> parool2;

    }

    string tais_nimi = enimi + " " + pnimi;

    // kasutaja tunnuse tegemine
    for (int i = 0; i < 3; i++) {

        esi_kolm += enimi[i];

    }
    for (int i = 0; i < 3; i++) {

        pere_kolm +=  pnimi[i];

    }

    kasutaja_tunnus = pere_kolm + esi_kolm;

    // arveldus arve genereerimine
    for (int j = 1; j <= 18; j++) {

        int irand = rand() % 10;

        string srand = to_string(irand);
        stemp += srand;

    }

    arveldus_arve = riik + stemp;

    ofstream SeeFail;

    SeeFail.open("kasutaja_info\\" + kasutaja_tunnus + ".txt", ios::app);

    SeeFail << tais_nimi << ";" << kasutaja_tunnus << ";" << parool << ";" << arveldus_arve << ";" << raha << endl;

    SeeFail.close();

    ofstream SeeLogi;

    SeeLogi.open("logi\\logi.log", ios::app);

    SeeLogi << "Loodi konto nimega: " << tais_nimi << " | kell: " << date << endl;

    SeeLogi.close();

    cout << "\n\nKasutaja tunnus: (" << kasutaja_tunnus << ")" << endl;
    cout << "(Jätta meelde)\n\n" << endl;

    // Prindib välja kasutaja info

}

void kasutaja_kasutamine() {

    string kasutaja_tunnus, parool, rida, anme;
    bool login = false;
    double raha_sisse;
    

    vector<string> temp, kasutaja;

    cout << "Sisesta kasutaja tunnus: ";
    cin >> kasutaja_tunnus;

    cout << "\nSisesta Parool: ";
    cin >> parool;

    // kasutaja leidmine ja kontroll
    ifstream andmed("kasutaja_info\\" + kasutaja_tunnus + ".txt");
    if(! andmed.is_open()) {

        cout << "\nKasutaja tunnus on vale" << endl;
    }
    else {

        while (getline(andmed, anme, ';')) {

            kasutaja.push_back(anme);

        }

        if (parool == kasutaja[2]) {

            login = true;

        }
        else {

            cout << "\nParool on vale" << endl;

        }

    }

    while (login == true) {

        int menu_valik;

        kasutaja = info_saamine("kasutaja_info/" + kasutaja[1] + ".txt");
        double raha = stoi(kasutaja[4]);
        kasutaja_menu(raha, kasutaja[3], kasutaja[0]);
        cin >> menu_valik;

        while (menu_valik > 5) {

            kasutaja_menu(raha, kasutaja[3], kasutaja[0]);
            cout << "Valisitte liiga suure numbri\n(Valige 1-5)" << endl;
            cin >> menu_valik;

        }
        switch (menu_valik) {
            case 1:
                cout << "\nValik 1" << endl;
                raha_saatmine();
                break;
                
            case 2:
                cout << "\nValik 2" << endl;
                vaata_logi("logi/" + kasutaja[0] + ".log");
                break;

            case 3:
                cout << "\nValik 3" << endl;
                cout << "Sisesta konto raha: ";
                cin >> raha_sisse;

                raha += raha_sisse;

                kirjuta(kasutaja_tunnus, kasutaja, raha);
                logi_rahalisamine(kasutaja[0], raha_sisse);
                break;

            case 4:
                cout << "\nValik 4" << endl;
                login = seadmed(kasutaja, raha);
                break;

            case 5:
                cout << "\nValik 5" << endl;
                login = false;
                break;

            default:
                cout << "Midagi Läks valesti" << endl;
                break;
        
        }
    }

}

int main() {

    int menu_valik;

    while (true) {

        menu();
        cin >> menu_valik;

        while (menu_valik > 3) {

            cout << "Valisitte liiga suure numbri\n(Valige 1-3)" << endl;
            menu();
            cin >> menu_valik;

        }

        switch (menu_valik) {

            case 1:
                cout << "\nValik 1" << endl;
                kasutaja_kasutamine();
                break;
                
            case 2:
                cout << "\nValik 2" << endl;
                lookasutaja();
                break;

            case 3:
                cout << "\nValik 3" << endl;
                return 0;
                break;

            default:

                cout << "Midagi Läks valesti" << endl;
                break;
        
        }
    }

}