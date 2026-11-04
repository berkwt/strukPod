#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// bolje rj zadatka 5

typedef struct stog
{
    int br;
    struct stog *top;
} stog;

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

int provBr(stog *top)
{
    if (top == NULL || (top)->top == NULL) {
        printf("Greska: Nedovoljno operanada na stogu za operaciju.\n");
        return -1;
    }
    return 0;
}

int loadFromFile(stog **top, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Greska: Nije moguce otvoriti datoteku %s\n", filename);
        return -1;
    }

    int n;
    int br = 0, check = 0;
    while ((n = fgetc(file)) != EOF)
    {
        if (isdigit(n))
        {
            br = br * 10 + (n - '0');
            check = 1;
            continue;
        }

        int brNew, br1, br2;
        switch (n)
        {
        case '+':
            if (provBr(*top) == -1) return -1;
            br1 = (*top)->br;
            *top = pop(*top);
            br2 = (*top)->br;
            *top = pop(*top);
            brNew = br2 + br1;
            *top = push(*top, brNew);
            check = 2;
            break;
        case '-':
            if (provBr(*top) == -1) return -1;
            br1 = (*top)->br;
            *top = pop(*top);
            br2 = (*top)->br;
            *top = pop(*top);
            brNew = br2 - br1;
            *top = push(*top, brNew);
            check = 2;
            break;
        case '*':
            if (provBr(*top) == -1) return -1;
            br1 = (*top)->br;
            *top = pop(*top);
            br2 = (*top)->br;
            *top = pop(*top);
            brNew = br2 * br1;
            *top = push(*top, brNew);
            check = 2;
            break;
        case '/':
            if (provBr(*top) == -1) return -1;
            br1 = (*top)->br;
            *top = pop(*top);
            br2 = (*top)->br;
            *top = pop(*top);
            if (br1 == 0)
            {
                printf("Greska: Dijeljenje s nulom.\n");
                return -1;
            }
            brNew = br2 / br1;
            *top = push(*top, brNew);
            check = 2;
            break;
        case ' ':
            if (check == 1)
            {
                *top = push(*top, br);
                br = 0;
                check = 0;
                break;
            }
            if (check == 2)
            {
                check = 0;
                break;
            }
            else
            {
                printf("ERROR '%c' nebi trebao biti tu\n", n);
                check = 0;
                break;
            }
        case '\n':
            if (*top != NULL)
                printf("Rezultat: %d\n", (*top)->br);
            else
                printf("Stog je prazan.\n");

            break;
        default:
            printf("ERROR NEPOZNAT ZNAK '%c'\n", n);
            break;
        }
    }
    if (*top != NULL)
        printf("Rezultat: %d\n", (*top)->br);
    else
        printf("Stog je prazan.\n");
    fclose(file);
    return 0;
}

int main()
{
    stog *top = NULL;
    if (loadFromFile(&top, "postfix.txt") != 0)
    {
        return 1;
    }

    while (top != NULL)
    {
        top = pop(top);
    }

    return 0;
}