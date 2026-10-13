#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

// Def. strukture osoba
struct Osoba
{
    string ime;
    string prezime;
    int godRod;
    Osoba *next;
};

// Dinamicko dodavanje na pocetak liste (A)
void dodP(Osoba *&head, string ime, string prezime, int godRod)
{
    Osoba *novaOsoba = new Osoba();
    novaOsoba->ime = ime;
    novaOsoba->prezime = prezime;
    novaOsoba->godRod = godRod;
    novaOsoba->next = head;
    head = novaOsoba;
}

// Ispis liste (B)
void outL(Osoba *head)
{
    Osoba *temp = head;
    while (temp != NULL)
    {
        cout << "Ime: " << temp->ime << ", Prezime: " << temp->prezime << ", Godina rođenja: " << temp->godRod << endl;
        temp = temp->next;
    }
}

// Dinamicko dodavanje na kraj liste (C)
void dodK(Osoba *&head, string ime, string prezime, int godRod)
{
    Osoba *novaOsoba = new Osoba();
    novaOsoba->ime = ime;
    novaOsoba->prezime = prezime;
    novaOsoba->godRod = godRod;
    novaOsoba->next = NULL;

    if (head == NULL)
    {
        head = novaOsoba;
    }
    else
    {
        Osoba *temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = novaOsoba;
    }
}

// Pronalazenje po prezimenu (D)
Osoba *findP(Osoba *head, string prezime)
{
    Osoba *temp = head;
    while (temp != NULL)
    {
        if (temp->prezime == prezime)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Brisanje po prezimenu (E)
void delP(Osoba *&head, string prezime)
{

    Osoba *temp = head;
    Osoba *prev = NULL;

    if (temp != NULL && temp->prezime == prezime)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << "Osoba sa prezimenom " << prezime << " nije pronađena." << endl;
        return;
    }

    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    delete temp;
}

// Popravljenje pronalazenja i brisanja po prezimenu (D i E)
int findALLP(Osoba *head, string prezime)
{
    int n = 0;
    Osoba *temp = head;

    while (temp != NULL)
    {
        if (temp->prezime == prezime)
        {
            cout << temp->ime << " " << temp->prezime << " " << temp->godRod << endl;
            n++;
        }
        temp = temp->next;
    }

    return n;
}
int delALLP(Osoba *&head, string prezime)
{
    int n = 0;

    // brisanje sa pocetka
    while (head != NULL && head->prezime == prezime)
    {
        Osoba *temp = head;
        head = head->next;
        delete temp;
        n++;
    }

    // brisanje ostalih
    Osoba *temp = head;
    while (temp != NULL && temp->next != NULL)
    {
        if (temp->next->prezime == prezime)
        {
            Osoba *temp2 = temp->next;
            temp->next = temp2->next;
            delete temp2;
            n++;
        }
        else
        {
            temp = temp->next;
        }
    }

    return n;
}

// Za ucitavanje iz datoteke
int loadFromFile(Osoba *&head, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Greska: Nije moguce otvoriti datoteku " << filename << endl;
        return -1;
    }

    string ime, prezime;
    int godRod;
    while (file >> ime >> prezime >> godRod)
    {
        dodK(head, ime, prezime, godRod);
    }

    file.close();
    return 0;
}

int main()
{
    Osoba *head = NULL;

    int load = loadFromFile(head, "listOsobe.txt");
    if (load == -1)
    {
        cout << "Greska prilikom ucitavanja podataka." << endl;
    }

    int i = 1;
    while (i != 0)
    {
        cout << "Izaberite opciju:" << endl;
        cout << "1. Dodaj osobu na pocetak liste" << endl;
        cout << "2. Dodaj osobu na kraj liste" << endl;
        cout << "3. Ispisi listu" << endl;
        cout << "4. Pronadji prvu osobu po prezimenu" << endl;
        cout << "5. Obrisi prvu osobu po prezimenu" << endl;
        cout << "6. Pronadji sve osobe po prezimenu" << endl;
        cout << "7. Obrisi sve osobe po prezimenu" << endl;
        cout << "0. Izlaz" << endl;
        cin >> i;

        switch (i)
        {
        case 1:
        {
            string ime, prezime;
            int godRod;
            cout << "Unesite ime, prezime i godinu rodjenja: ";
            cin >> ime >> prezime >> godRod;
            dodP(head, ime, prezime, godRod);
            break;
        }
        case 2:
        {
            string ime, prezime;
            int godRod;
            cout << "Unesite ime, prezime i godinu rodjenja: ";
            cin >> ime >> prezime >> godRod;
            dodK(head, ime, prezime, godRod);
            break;
        }
        case 3:
            outL(head);
            break;
        case 4:
        {
            string prezime;
            cout << "Unesite prezime za pretragu: ";
            cin >> prezime;
            findP(head, prezime);
            break;
        }
        case 5:
        {
            string prezime;
            cout << "Unesite prezime za brisanje: ";
            cin >> prezime;
            delP(head, prezime);
            break;
        }
        case 6:
        {
            string prezime;
            cout << "Unesite prezime za pretragu: ";
            cin >> prezime;
            int broj = findALLP(head, prezime);
            cout << "Pronadeno osoba: " << broj << endl;
            break;
        }
        case 7:
        {
            string prezime;
            cout << "Unesite prezime za brisanje: ";
            cin >> prezime;
            int obrisano = delALLP(head, prezime);
            cout << "Obrisano osoba: " << obrisano << endl;
            break;
        }
        case 0:
            cout << "Izlaz..." << endl;
            break;
        default:
            cout << "Nepoznata opcija." << endl;
        }
    }

    // oslobadanje memorije
    while (head != NULL)
    {
        Osoba *temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}

// Kod nije optimiziran za osobe sa dualnim imenima i/ili prezimenima, blizi se ponoc idem lec.