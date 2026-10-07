#include <iostream>
#include <stdio.h>

// Definiranje strukture za studenta
typedef struct
{
    char ime[50];
    char prezime[50];
    int bodovi;
} Stud;

//Brojanje redaka/studenata u datoteci
int brojanjeStudenata(FILE *fp)
{
    int br = 0;
    
    char crta[256];

    while (fgets(crta, sizeof(crta), fp) != NULL)
    {
        br++;
    }
    //Alternativa za brojanje redaka/studenata
    /*
    char znak;
    while ((znak = fgetc(fp)) != EOF)
    {
        if (znak == '\n')
        {
            br++;
        }
    }
    */
    if (br == 0)
    {
        printf("Datoteka je prazna ili neispravno formatirana.\n");
        fclose(fp);
        return 0;
    }

    rewind(fp);
    return br;
}


int main()
{
    FILE *fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        std::cout << "Greska: Nije moguce otvoriti datoteku\n";
        return 1;
    }

    int brojStud = brojanjeStudenata(fp);
    char tempIme[50], tempPrezime[50];
    int tempBodovi;

    // Dinamička alokacija prostora za niz struktura studenata
    Stud *studenti = (Stud *)malloc(brojStud * sizeof(Stud));
    if (studenti == NULL)
    {
        printf("Greska pri alokaciji memorije!\n");
        fclose(fp);
        return 2;
    }

    double maxBodovi = 0.0;

    // Učitavanje podataka i traženje maxBodova
    for (int i = 0; i < brojStud; i++)
    {
        fscanf(fp, "%49s %49s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);

        if (studenti[i].bodovi > maxBodovi)
        {
            maxBodovi = studenti[i].bodovi;
        }
    }
    // Alternativna verzija "Učitavanje podataka i traženje maxBodova"
    /*
    for (int i = 0; i < brojStud; i++)
    {
        Stud *s = &studenti[i]; 
        
        if (fscanf(fp, "%49s %49s %d", s->ime, s->prezime, &s->bodovi) != 3)
        {
            std::cout << "Greska pri ucitavanju studenta na indeksu " << i << "\n";
            break;
        }

        if (s->bodovi > maxBodovi)
        {
            maxBodovi = s->bodovi;
        }
    }
    */

    // Ispis podataka o studentima, apsolutnih i relativnih bodova
    for (int i = 0; i < brojStud; i++)
    {
        double relativniBodovi = 0.0;

        if (maxBodovi > 0)
        {
            relativniBodovi = (double(studenti[i].bodovi) / maxBodovi) * 100.0;
        }

        //-15 za poravnanje
        printf("%-15s %-15s %-15d %-15.2f%%\n",
               studenti[i].ime,
               studenti[i].prezime,
               studenti[i].bodovi,
               relativniBodovi);
    }
    // Alternativna verzija "Ispis podataka o studentima, apsolutnih i relativnih bodova"
    /*
    for (int i = 0; i < brojStud; i++)
    {
        Stud *s = &studenti[i];

        double relativniBodovi = 0.0;

        if (maxBodovi > 0)
        {
            relativniBodovi = (double(s->bodovi) / maxBodovi) * 100.0;
        }

        printf("%-15s %-15s %-15d %-15.2f%%\n",
               s->ime,
               s->prezime,
               s->bodovi,
               relativniBodovi);
    }
    */
    fclose(fp);
    return 0;   
}