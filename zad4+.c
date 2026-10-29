#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struktura za polinom
typedef struct Polinom
{
    int koef;
    int eks;
    struct Polinom *next;
} Polinom;

// dodavanje i sortiranje polinoma po unosu
Polinom *dodPolinom(Polinom *head, int koef, int eks)
{
    //nema broj sa koef 0
    if (koef == 0)
        return head;

    Polinom *temp = head;
    Polinom *prev = NULL;

    //sortiranje po eks
    while (temp != NULL && temp->eks > eks)
    {
        prev = temp;
        temp = temp->next;
    }
    //isti eks zbrajamo koef
    if (temp != NULL && temp->eks == eks)
    {
        temp->koef += koef;
        if (temp->koef == 0)
        {
            if (prev == NULL)
                head = temp->next;
            else
                prev->next = temp->next;
            free(temp);
        }
        return head;
    }

    //dodavanje novog clana
    Polinom *nova = (Polinom *)malloc(sizeof(Polinom));
    if (nova == NULL)
    {
        printf("Greska: Alokacija memorije nije uspjela.\n");
        return head;
    }
    nova->koef = koef;
    nova->eks = eks;

    nova->next = temp;
    if (prev == NULL)
        head = nova;
    else
        prev->next = nova;
    return head;
}

// ispisuje polinom
int ispPolinom(Polinom *head)
{
    if (head == NULL)
    {
        printf("Polinom je prazan.\n");
        return -1;
    }

    Polinom *temp = head;
    while (temp != NULL)
    {
        printf("%dx^%d ", temp->koef, temp->eks);
        temp = temp->next;
        if (temp != NULL)
        {
            printf("+ ");
        }
    }
    printf("\n");
    return 0;
}

// oslobađa memoriju zauzetu za polinom
Polinom *freeDaPolimons(Polinom *head)
{
    Polinom *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    return NULL;
}

/*
Polinom *zbroji(Polinom *a, Polinom *b)
{
    Polinom *rezultat = NULL;
    for (; a != NULL; a = a->next)
    {
        rezultat = dodPolinom(rezultat, a->koef, a->eks);
    }
    for (; b != NULL; b = b->next)
    {
        rezultat = dodPolinom(rezultat, b->koef, b->eks);
    }

    return rezultat;
}
*/

//zbrajanje se automatski radi kod provjere unosa pa je ovo dosta
Polinom *zbrojAcc(Polinom *acc, Polinom *b){
    for (; b != NULL; b = b->next)
    acc = dodPolinom(acc, b->koef, b->eks);
    return acc;
}

Polinom *pomnozi(Polinom *a, Polinom *b)
{
    Polinom *rezultat = NULL;
    for (; a != NULL; a = a->next)
    {
        for (Polinom *tempB = b; tempB != NULL; tempB = tempB->next)
        {
            rezultat = dodPolinom(rezultat, a->koef * tempB->koef, a->eks + tempB->eks);
        }
    }
    return rezultat;
}

// cita jedan redak kao polinom iz datoteke
int loadRed(FILE *file, Polinom **out)
{
    char redak[1024];
    int parova=0;
    *out=NULL;

    if (fgets(redak, sizeof redak, file) == NULL)
        return -1;

    char *p = redak;
    int koef, eks, procitano;
    while (sscanf(p, "%d %d%n", &koef, &eks, &procitano) == 2)
    {
        *out = dodPolinom(*out, koef, eks);
        p += procitano;
        parova++;
    }
    return parova;
}

// ucitava iz datoteke
int loadDoc(const char *filename, Polinom **zbroj, Polinom **umnozak)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }

    Polinom *temp;
    int br=0;
    int parovi;

    *zbroj=NULL;
    *umnozak=NULL;

    while ((parovi=loadRed(file,&temp))!=-1)
    {
        if (parovi==0)
        {
            continue;
        }
        br++;
        printf("P%d= ",br);ispPolinom(temp);
        *zbroj=zbrojAcc(*zbroj,temp);
        
        if (br==1)
        {
            *umnozak=zbrojAcc(NULL,temp); //dodaje se prvi kao osnovna vrijednost
        }
        else
        {
            Polinom *temp1=pomnozi(*umnozak, temp);
            freeDaPolimons(*umnozak);
            *umnozak=temp1;
        }
        temp = freeDaPolimons(temp);
    }
    


    fclose(file);
    return br;
}

int main()
{
    Polinom *zb=NULL, *umn=NULL;

    int br=loadDoc("polinom.txt", &zb, &umn);
    if (br < 0)
    {
        return 1;
    }
    if (br == 0)
    {
        printf("Dokument nema nijedan polinom");
        return 0;
    }



    printf("\nZbroj svih polinoma = ");
    ispPolinom(zb);
    printf("Umnozak svih polinoma = ");
    ispPolinom(umn);

    freeDaPolimons(zb);
    freeDaPolimons(umn);
    return 0;
}