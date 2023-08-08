#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Pont
{
    int x, y;
} Pont;

double tavolsag(Pont p1, Pont p2)
{
    /* pitagorasz */
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
}

bool kb_egyenlo(double a, double b, double eps)
{
    return fabs(a - b) < eps;
}

/* SDL-es inicializálás InfoC-ről */
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

int main(int argc, char *argv[])
{
    /* SDL-es inicializálás meghívása szintén az InfoC-ről */
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("K\u00fapszeletek", 640, 480, &window, &renderer);

    const double eps = 2e0;

    /* 1. feladat: kör */
    Pont p1 = { 320, 240 };
    double d1 = 200;

    /* 2. feladat: ellipszis */
    Pont p2 = { 240, 200 };
    Pont p3 = { 400, 280 };
    double d2 = 250;

    /* 3. feladat: hiperbola */
    Pont p4 = { 240, 240 };
    Pont p5 = { 400, 240 };
    double d3 = 100;

    /* 4. feladat: parabola */
    Pont p6 = { 320, 240 };
    int ex1 = 400;

    for (int y = 0; y < 480; y++)
    {
        for (int x = 0; x < 640; x++)
        {
            Pont p = { x, y };

            /* 1. feladat (piros) */
            if (kb_egyenlo(tavolsag(p, p1), d1, eps))
                pixelRGBA(renderer, x, y, 255, 0, 0, 255);

            /* 2. feladat (zöld) */
            if (kb_egyenlo(tavolsag(p, p2) + tavolsag(p, p3), d2, eps))
                pixelRGBA(renderer, x, y, 0, 255, 0, 255);

            /* 3. feladat (kék) */
            if (kb_egyenlo(fabs(tavolsag(p, p4) - tavolsag(p, p5)), d3, eps))
                pixelRGBA(renderer, x, y, 0, 0, 255, 255);

            /* 4. feladat (fehér) */
            if (kb_egyenlo(tavolsag(p, p6), fabs(x - ex1), eps))
                pixelRGBA(renderer, x, y, 255, 255, 255, 255);
        }
    }

    stringRGBA(renderer, 400, 30, "Kor", 255, 0, 0, 255);
    stringRGBA(renderer, 320, 120, "Ellipszis", 0, 255, 0, 255);
    stringRGBA(renderer, 170, 10, "Hiperbola", 0, 0, 255, 255);
    stringRGBA(renderer, 10, 50, "Parabola", 255, 255, 255, 255);

    /* SDL-es eventloop InfoC-ről */
    SDL_RenderPresent(renderer);

    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT)
        ;

    SDL_Quit();

    return 0;
}
