#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Osoba
{
    char ime[50];
    char prezime[50];
    int godRod;
    struct Osoba *next;
} Osoba;

void dodP(Osoba **head, char *ime, char *prezime, int godRod)
{
    Osoba *novaOsoba = (Osoba *)malloc(sizeof(Osoba));
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godRod = godRod;
    novaOsoba->next = *head;
    *head = novaOsoba;
}

void outL(Osoba *head)
{
    Osoba *temp = head;
    while (temp != NULL)
    {
        printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n", temp->ime, temp->prezime, temp->godRod);
        temp = temp->next;
    }
}

void dodK(Osoba **head, char *ime, char *prezime, int godRod)
{
    Osoba *novaOsoba = (Osoba *)malloc(sizeof(Osoba));
    strcpy(novaOsoba->ime, ime);
    strcpy(novaOsoba->prezime, prezime);
    novaOsoba->godRod = godRod;
    novaOsoba->next = NULL;

    if (*head == NULL)
    {
        *head = novaOsoba;
    }
    else
    {
        Osoba *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = novaOsoba;
    }
}

void findP(Osoba *head, char *prezime)
{
    Osoba *temp = head;
    while (temp != NULL)
    {
        if (strcmp(temp->prezime, prezime) == 0)
        {
            printf("Ime: %s, Prezime: %s, Godina rođenja: %d\n", temp->ime, temp->prezime, temp->godRod);
            return;
        }
        temp = temp->next;
    }
    printf("Osoba sa prezimenom %s nije pronađena.\n", prezime);
}

void delP(Osoba **head, char *prezime)
{
    Osoba *temp = *head;
    Osoba *prev = NULL;

    while (temp != NULL && strcmp(temp->prezime, prezime) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Osoba sa prezimenom %s nije pronađena.\n", prezime);
        return;
    }

    if (prev == NULL)
    {
        *head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    free(temp);
}

int findALLP(Osoba *head, char *prezime)
{
    int n = 0;
    Osoba *temp = head;

    while (temp != NULL)
    {
        if (strcmp(temp->prezime, prezime) == 0)
        {
            printf("%s %s %d\n", temp->ime, temp->prezime, temp->godRod);
            n++;
        }
        temp = temp->next;
    }

    return n;
}

int delALLP(Osoba **head, char *prezime)
{
    int n = 0;

    // brisanje sa pocetka
    while (*head != NULL && strcmp((*head)->prezime, prezime) == 0)
    {
        Osoba *temp = *head;
        *head = (*head)->next;
        free(temp);
        n++;
    }

    // brisanje ostalih
    Osoba *temp = *head;
    while (temp != NULL && temp->next != NULL)
    {
        if (strcmp(temp->next->prezime, prezime) == 0)
        {
            Osoba *temp2 = temp->next;
            temp->next = temp2->next;
            free(temp2);
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
int loadFromFile(Osoba **head, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }

    char ime[50], prezime[50];
    int godRod;
    while (fscanf(file, "%49s %49s %d", ime, prezime, &godRod) == 3)
    {
        dodK(head, ime, prezime, godRod);
    }

    fclose(file);
    return 0;
}

int main()
{
    Osoba *head = NULL;

    int load = loadFromFile(&head, "listOsobe.txt");
    if (load == -1)
    {
        printf("Greska prilikom ucitavanja podataka.\n");
    }

    int i = 1;
    while (i != 0)
    {
        printf("Izaberite opciju:\n");
        printf("1. Dodaj osobu na pocetak liste\n");
        printf("2. Dodaj osobu na kraj liste\n");
        printf("3. Ispisi listu\n");
        printf("4. Pronadji prvu osobu po prezimenu\n");
        printf("5. Obrisi prvu osobu po prezimenu\n");
        printf("6. Pronadji sve osobe po prezimenu\n");
        printf("7. Obrisi sve osobe po prezimenu\n");
        printf("0. Izlaz\n");
        scanf("%d", &i);

        switch (i)
        {
        case 1:
        {
            char ime[50], prezime[50];
            int godRod;
            printf("Unesite ime, prezime i godinu rodjenja: ");
            scanf("%49s %49s %d", ime, prezime, &godRod);
            dodP(&head, ime, prezime, godRod);
            break;
        }
        case 2:
        {
            char ime[50], prezime[50];
            int godRod;
            printf("Unesite ime, prezime i godinu rodjenja: ");
            scanf("%49s %49s %d", ime, prezime, &godRod);
            dodK(&head, ime, prezime, godRod);
            break;
        }
        case 3:
            outL(head);
            break;
        case 4:
        {
            char prezime[50];
            printf("Unesite prezime za pretragu: ");
            scanf("%49s", prezime);
            findP(head, prezime);
            break;
        }
        case 5:
        {
            char prezime[50];
            printf("Unesite prezime za brisanje: ");
            scanf("%49s", prezime);
            delP(&head, prezime);
            break;
        }
        case 6:
        {
            char prezime[50];
            printf("Unesite prezime za pretragu: ");
            scanf("%49s", prezime);
            int broj = findALLP(head, prezime);
            printf("Pronadeno osoba: %d\n", broj);
            break;
        }
        case 7:
        {
            char prezime[50];
            printf("Unesite prezime za brisanje: ");
            scanf("%49s", prezime);
            int obrisano = delALLP(&head, prezime);
            printf("Obrisano osoba: %d\n", obrisano);
            break;
        }
        case 0:
            printf("Izlaz...\n");
            break;
        default:
            printf("Nepoznata opcija.\n");
        }
    }

    // oslobadanje memorije
    Osoba *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}