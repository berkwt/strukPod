//STOG - struktura varijable i pokazivaca na vrh
//first in first out
//push - dodaje element na vrh stoga
//pop - uklanja element sa vrha stoga
//push kod varijabli, pop kod akcija
//rezultate akcija push
//zadnje dvi varijable se vataju na pop

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//stvaranje stoga
typedef struct stog
{
    int br;
    struct stog *top;
} stog;

//ubacivanje
stog *push(stog *top, int br)
{
    stog *novi = (stog *)malloc(sizeof(stog));
    if (novi == NULL)
    {
        printf("Greska: Alokacija memorije nije uspjela.\n");
        return top;
    }
    novi->br = br;
    novi->top = top;
    return novi;
}

//izbacivanje
stog *pop(stog *top)
{
    if (top == NULL)
    {
        printf("Greska: Stog je prazan.\n");
        return NULL;
    }
    stog *temp = top;
    top = top->top;
    free(temp);
    return top;
}

//citanje sa .txt
int loadFromFile(stog **top, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }
    int n, brZ=0, br=0;
    //citanje znakova u .txt
    while ((n=fgetc(file))!=EOF)
    {
        if (isdigit(n))
        {
            br=br*10+(n-'0');
            brZ=1;
            //*top=push(*top,br);
            continue;
        }
        if(brZ){
            *top=push(*top,br);
            br=0;
            brZ=0;
        }
        else
        {
            int brNew, br1, br2;
            switch (n)
            {
            case '+':
                br1 = (*top)->br;
                *top = pop(*top);
                br2 = (*top)->br;
                *top = pop(*top);
                brNew = br2 + br1;
                *top = push(*top, brNew);
                break;
            case '-':
                br1 = (*top)->br;
                *top = pop(*top);
                br2 = (*top)->br;
                *top = pop(*top);
                brNew = br2 - br1;
                *top = push(*top, brNew);
                break;
            case '*':
                br1 = (*top)->br;
                *top = pop(*top);
                br2 = (*top)->br;
                *top = pop(*top);
                brNew = br2 * br1;
                *top = push(*top, brNew);
                break;
            case '/':
                br1 = (*top)->br;
                *top = pop(*top);
                br2 = (*top)->br;
                *top = pop(*top);
                brNew = br2 / br1;
                *top = push(*top, brNew);
                break;
            
            default:
                break; //za sve osin trazenog skip
            }
        }
        
    }
    //if (brZ)*top = push(*top, br); nepotrebno jer nebi postfix zavrsavati sa brojem
    fclose(file);
    return 0;
}

int main()
{
    stog *top = NULL;
    if(loadFromFile(&top, "postfix.txt")!=0)
    {
        return 1;
    }

    if (top != NULL)
        printf("Rezultat: %d\n", top->br);
    else
        printf("Stog je prazan.\n");

    while (top != NULL)
    {
        top = pop(top);
    }

    return 0;
}