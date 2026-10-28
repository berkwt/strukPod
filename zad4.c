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

// cita jedan redak kao polinom iz datoteke
Polinom *loadRed(FILE *file)
{
    Polinom *head = NULL;
    char redak[1024];

    if (fgets(redak, sizeof redak, file) == NULL)
        return NULL;

    char *p = redak;
    int koef, eks, procitano;
    while (sscanf(p, "%d %d%n", &koef, &eks, &procitano) == 2)
    {
        head = dodPolinom(head, koef, eks);
        p += procitano;
    }
    return head;
}

// ucitava iz datoteke
int loadDoc(const char *filename, Polinom **p1, Polinom **p2)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }

    *p1 = loadRed(file);
    *p2 = loadRed(file);

    fclose(file);
    return 0;
}

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

int main()
{
    Polinom *p1 = NULL, *p2 = NULL;

    if (loadDoc("polinom.txt", &p1, &p2) != 0)
    {
        return 1;
    }

    printf("P1 = ");
    ispPolinom(p1);
    printf("P2 = ");
    ispPolinom(p2);

    Polinom *zbroj = zbroji(p1, p2);
    Polinom *umnozak = pomnozi(p1, p2);

    printf("P1 + P2 = ");
    ispPolinom(zbroj);
    printf("P1 * P2 = ");
    ispPolinom(umnozak);

    freeDaPolimons(p1);
    freeDaPolimons(p2);
    freeDaPolimons(zbroj);
    freeDaPolimons(umnozak);

    return 0;
}