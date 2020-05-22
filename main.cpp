#include <iostream>
#include <string>
#include <fstream>
#include <limits>

class Ksiazki {
    private:
        long kol_numer;
        std::string sygnatura;
        std::string imie_autora;
        std::string nazwisko_autora;
        std::string tytul;
        std::string ISBN;
        std::string wydawnictwo;
        short rok_wydania;
    public:
        void setParam(long kol_numer, std::string syg, std::string im_au, std::string naz_au, std::string tyt, std::string ISBN, std::string wyd, short rok);
        void dodajKsiazke();
        void listuj();
        void wyszukajKsiazke();
        void usunKsiazke();
        void wyswietlKsiazke();
        void pobierzDane();
        Ksiazki();

};

//Nadanie domyslnych wartosci ksiazce po utworzeniu obiektu
Ksiazki::Ksiazki(){
    this->kol_numer = 0;
    this->sygnatura = "";
    this->imie_autora = "";
    this->nazwisko_autora = "";
    this->tytul = "";
    this->ISBN = "";
    this->wydawnictwo = "";
    this->rok_wydania = 2000;
}

//Nadanie ksiazce parametrow czyli wpisanych przez uzytkownika tytulu,numeru itd.
void Ksiazki::setParam(long ko_numer, std::string syg, std::string im_au, std::string naz_au, std::string tyt, std::string ISBN, std::string wyd, short rok){
    this->kol_numer = ko_numer;
    this->sygnatura = syg;
    this->imie_autora = im_au;
    this->nazwisko_autora = naz_au;
    this->tytul = tyt;
    this->ISBN = ISBN;
    this->wydawnictwo = wyd;
    this->rok_wydania = rok;
}

//Funkcja wyswietlajaca parametry ksiazki, uzywana byla w celach testowych
void Ksiazki::wyswietlKsiazke(){
    std::cout<< this->kol_numer << " " << this->sygnatura << " " << this->imie_autora << " " << this->nazwisko_autora
    << " " << this->tytul << " " << this->ISBN << " "
    << this->wydawnictwo << " " << this->rok_wydania << std::endl;
}

//Funckja, ktora odczytuje z pliku i wyswietla wszystkie ksiazki w nim zawarte
void Ksiazki::listuj(){
    std::string nazwa = "ksiazki.txt";
    std::fstream plik;
    std::string zdanie = "";
    plik.open(nazwa, std::ios::in);
    std::cout << "Zawartosc pliku: " << std::endl;
    do {
        getline(plik,zdanie);
        std::cout << zdanie << std::endl;
    } while(!plik.eof()); //Petla sie wykonuje, az do konca pliku
    plik.close();
}

void enter(){
    std::cout << "Nacisnij Enter, aby kontynuowac" << std::endl;
    getchar();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //Ignorujemy wpisane przez uzytkownika wartosci jesli jakies wpisal w celu zniwelowania bledow
}

//Funkcja weryfikujaca czy podany ciag jest liczba (int)
int pobierzLiczbe(std::string pole) {
    int d;
    std::string z;
    bool isError;
    do {
        isError=false;
        std::cout << "Podaj " << pole << ": " << std::endl;
        try{
            std::getline(std::cin,z);
            d=std::stoi(z.c_str());
        } catch (std::invalid_argument const &e){
            std::cerr << "Nieprawidlowa wartosc! \n";
            isError=true;
        } catch (std::out_of_range const &e) {
            std::cerr << "Przekroczenie dopuszczalnej wartosci! \n";
            isError=true;
        }
    } while (isError);

    return d;
}

std::string pobierzStringa(std::string pole) {
    std::cout << "Podaj " << pole << ": " << std::endl;
    std::string s;
    std::cin >> s;
    return s;
}

void Ksiazki::pobierzDane(){
    this->kol_numer = pobierzLiczbe("kolejny numer");
    this->sygnatura = pobierzStringa("sygnature");
    this->imie_autora = pobierzStringa("imie");
    this->nazwisko_autora = pobierzStringa("nazwisko");
    this->tytul = pobierzStringa("tytul");
    this->ISBN = pobierzStringa("ISBN");
    this->wydawnictwo = pobierzStringa("nazwe wydawnictwa");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n'); //Ignorujemy wpisane przez uzytkownika poprzednie wartosci w celu unikniecia bledow
    this->rok_wydania = pobierzLiczbe("rok wydania");
}

//Dodajemy nowa ksiazke do naszego pliku ksiazki.txt, wczesniej pobralismy od uzytkownika parametry
void Ksiazki::dodajKsiazke(){
    std::string nazwa = "ksiazki.txt";
    std::fstream plik;
    plik.open(nazwa, std::ios::app);
    plik << this->kol_numer << " " << this->sygnatura << " " << this->imie_autora <<
    " " << this->nazwisko_autora << " " << this->tytul << " " << this->ISBN << " " <<
    this->wydawnictwo << " " << this->rok_wydania << std::endl;
    plik.close();
}

//Funkcja umozliwiajaca wyszukanie ksiazki poprzez wpisanie frazy
void Ksiazki::wyszukajKsiazke(){
    bool isFraza = false;
    std::string fraza = "";
    std::cout << "Prosze wpisac poszukiwana fraze:";
    std::getline(std::cin,fraza);
    std::fstream plik;
    std::string zdanie;
    plik.open("ksiazki.txt");
    size_t pos;
    while(plik.good()){
        getline(plik,zdanie);
        pos=zdanie.find(fraza); //Sprawdzamy czy w danym wierszu znajduje sie podana fraza
        if(pos!=std::string::npos) { //Jesli tak to przypisujemy dany wiersz do frazy i konczymy szukanie
            fraza = zdanie;
            isFraza = true;
            break;
        }
    }
    if(isFraza) {
        std::cout << "Znaleziono ksiazke z wyszukana fraza!" << std::endl;
        std::cout << fraza << std::endl; //Wyswietlamy nasz znaleziony wiersz
    } else {
        std::cout << "Nieznaleziono szukanej frazy!" << std::endl; //Wyswietlamy komunikat jesli nie znajdziemy wiersza z dana fraza
    }

    plik.close();
}
/* Funkcja usuwajaca ksiazke po znalezieniu wiersza z dana fraza
Dziala w takie sposob, ze wszystkie wiersze niezawierajace danej frazy kopiuje do pliku tmp.txt
A na stepnie usuwa plik ksiazki.txt i zamienia nazwe temp.txt na ksiazki.txt
Dzieki temu powstaje nam nowy plik z ksiazkami bez ksiazek z podana wczesniej fraza */
void Ksiazki::usunKsiazke(){
    bool isFraza = false;
    std::string fraza = "";
    std::cout << "Prosze wpisac poszukiwana fraze:";
    std::getline(std::cin,fraza);
    std::fstream plik;
    std::ofstream temp;
    std::string zdanie;
    plik.open("ksiazki.txt");
    temp.open("temp.txt");
    size_t pos;
    while(getline(plik,zdanie)){
        pos=zdanie.find(fraza);
        if(pos==std::string::npos) {
            temp << zdanie << std::endl;
        }
    }
    std::cout << "Usunieto rekord/y z podana fraza (jesli nie znaleziono frazy to rekordy pozostaly bez zmian)" << std::endl;
    plik.close();
    temp.close();
    remove("ksiazki.txt");
    rename("temp.txt","ksiazki.txt");
}

int main(){
    Ksiazki ksiazka;
    while(true){
        int numer = 0;
        std::string opcja;
        bool inBlad;
        std::cout << "Wybierz opcje(1,2,3,4,5):" << std::endl;
        std::cout << "1.Dodaj ksiazke" << std::endl;
        std::cout << "2.Listuj ksiazki" << std::endl;
        std::cout << "3.Wyszukaj ksiazke" << std::endl;
        std::cout << "4.Usun ksiazke" << std::endl;
        std::cout << "5.Zakoncz" << std::endl;

        //Sprawdzamy czy podany ciag jest liczba
        do {
            inBlad = false;
            std::cout << "Podaj numer opcji: ";
            getline(std::cin,opcja);
            for(char c: opcja){
                if(c >= '0' && c <= '9') numer = numer * 10 + (c - '0');
                else {
                    inBlad = true;
                    std::cerr << "Nieprawidlowa wartosc! Podaj wartosc z zakresu 1-5.\n";
                    numer = 0;
                    break;
                }
            }
        } while(inBlad || opcja=="");
        //Po pobraniu od uzytkownika opcji sprawdzamy czy istnieje i jesli tak to wykonujemy funkcje w niej zawarte
        switch(numer){
            case 1:
                std::cout << "Wybrales opcje 1\n";
                ksiazka.pobierzDane();
                ksiazka.dodajKsiazke();
                enter();
                break;
            case 2:
                std::cout << "Wybrales opcje 2\n";
                ksiazka.listuj();
                enter();
                break;
            case 3:
                std::cout << "Wybrales opcje 3\n";
                ksiazka.wyszukajKsiazke();
                enter();
                break;
            case 4:
                std::cout << "Wybrales opcje 4\n";
                ksiazka.usunKsiazke();
                enter();
                break;
            case 5:
                std::cout << "Zakonczono dzialanie programu!";
                return 0;
            default:
                std::cout << "Nieprawidlowa wartosc! Podaj wartosc z zakresu 1-5.\n";
                enter();
                break;
        }

    }

    getchar();
    EXIT_SUCCESS;
}