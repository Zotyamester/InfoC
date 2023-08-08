#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SZALAGMERET 32768

int main()
{
    char programkod[] = "+[->,+]<[.<]"; /* bemenet kiírása visszafelé */
    int ip = 0; /* programszámláló (PC) <=> utasításszámláló (IP) */

    char szalag[SZALAGMERET] = { 0 };
    int fej = 0; /* szalagot vezérlő egysége feje */

    bool hiba = false;

    while (!hiba && programkod[ip] != '\0')
    {
        switch (programkod[ip++])
        {
        case '>': /* jobbra léptetés */
            fej += 1;
            if (fej == SZALAGMERET)
                hiba = true;
            break;
        case '<': /* balra léptetés */
            fej -= 1;
            if (fej < 0)
                hiba = true;
            break;
        case '+': /* növelés */
            szalag[fej] += 1;
            break;
        case '-': /* csökkentés */
            szalag[fej] -= 1;
            break;
        case '.': /* karakter kiírása */
            printf("%c", szalag[fej]); /* ha nincs ..., putchar se legyen */
            break;
        case ',': /* karakter beolvassa */
        {
            char c;
            if (scanf("%c", &c) == EOF) /* ez is gyorsabb lenne a ...-ral */
                c = -1;
            szalag[fej] = c;
        }
        break;
        case '[': /* elöltesztelő ciklus kezdete */
            if (szalag[fej] == 0) /* kiugrunk a ciklus utánra */
            {
                int melyseg = 1;
                while (melyseg > 0 && programkod[ip] != '\0')
                {
                    if (programkod[ip] == '[')
                        melyseg += 1;
                    else if (programkod[ip] == ']')
                        melyseg -= 1;
                    ip += 1;
                }
                if (melyseg > 0)
                    hiba = true;
            }
            break;
        case ']': /* ciklus vége */
            /* xxx]xxx
                   ^-- ip
               a switch tetején megnöveltük az ip-t,
               úgyhogy most a ] után vagyunk eggyel */
            ip -= 1;
            int melyseg = 1;
            while (melyseg > 0 && ip > 0)
            {
                ip -= 1;
                if (programkod[ip] == '[')
                    melyseg -= 1;
                else if (programkod[ip] == ']')
                    melyseg += 1;
            }
            if (melyseg > 0)
                hiba = true;
            break;
        default: /* minden más karekter kommentnek minősül */
            break;
        }
    }

    if (hiba)
    {
        fprintf(stderr, "A megadott kod hibas volt.\n");
        return 1;
    }

    return 0;
}
