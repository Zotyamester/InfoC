#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/* VÁSZON */

#define CANVAS_SIZE 1024
#define PADDING 16
#define RADIUS ((CANVAS_SIZE - 2 * PADDING) / 2)
#define ORIGO_X CANVAS_SIZE / 2
#define ORIGO_Y CANVAS_SIZE / 2

/* KERET */

#define FACE_WIDTH 8
#define BACKFACE_COLOR "#f1faee"
#define FRONTFACE_COLOR "#e63946"

/* OSZTÁSOK */

#define HOUR_TICK_WIDTH 6
#define MINUTE_TICK_WIDTH 2

#define HOUR_TICK_COLOR "#219ebc"
#define MINUTE_TICK_COLOR "#8ecae6"

#define HOUR_TICK_RATIO 0.08
#define MINUTE_TICK_RATIO 0.05

/* MUTATÓK */

#define HOUR_HAND_WIDTH 6
#define MINUTE_HAND_WIDTH 4
#define SECOND_HAND_WIDTH 2

#define HOUR_HAND_COLOR "#1d3557"
#define MINUTE_HAND_COLOR "#457b9d"
#define SECOND_HAND_COLOR "#a8dadc"

#define HOUR_HAND_RATIO 0.5
#define MINUTE_HAND_RATIO 0.85
#define SECOND_HAND_RATIO 0.9

/* MATEMATIKAI ÉS FIZIKAI MENNYISÉGEK, VÁLTÓSZÁMOK */

#define PI 3.14159265358979323846

#define SECONDS_IN_MINUTE 60
#define MINUTES_IN_HOUR 60
#define SECONDS_IN_HOUR (MINUTES_IN_HOUR * SECONDS_IN_MINUTE)

/* SZÖGSEBESSÉGEK A MUTATÓKHOZ */

#define ANGULAR_VELOCITY_H (1.0 / 43200.0 * 2.0 * PI)
#define ANGULAR_VELOCITY_M (1.0 / 3600.0 * 2.0 * PI)
#define ANGULAR_VELOCITY_S (1.0 / 60.0 * 2.0 * PI)

/** \brief Kiírja a megadott fájlba az óra hátterét adó SVG-alakzatot.
 *
 * \param fp A kimeneti fájl.
 *
 */

void print_clock_backface(FILE *fp)
{
    fprintf(fp, "\t<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"none\" fill=\"%s\" />\n",
            ORIGO_X, ORIGO_Y, RADIUS, BACKFACE_COLOR);
}

/** \brief Kiírja a megadott fájlba az óra keretét adó SVG-alakzatot.
 *
 * \param fp A kimeneti fájl.
 *
 */

void print_clock_frontface(FILE *fp)
{
    fprintf(fp, "\t<circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke-width=\"%d\" stroke=\"%s\" fill=\"none\" />\n",
            ORIGO_X, ORIGO_Y, RADIUS, FACE_WIDTH, FRONTFACE_COLOR);
}


/** \brief Kiírja a megadott fájlba az osztásokat leíró SVG-alakzatokat.
 *
 * \param fp A kimeneti fájl.
 *
 */

void print_clock_ticks(FILE *fp)
{
    /* itt nem kell babrálni a szöggel,
       mert tök mindegy, honnan megyek */
    for (int minute = 0; minute < 60; minute++)
    {
        /* azért a percekbõl számoljuk,
           és nem közvetlen a szöget léptetjük,
           mert az IEE754 nem elég pontos */
        double angle = ANGULAR_VELOCITY_S * minute;

        bool is_hour = minute % 5 == 0;

        int x2 = ORIGO_X + cos(angle) * RADIUS;
        int y2 = ORIGO_Y - sin(angle) * RADIUS;

        double tick_ratio = is_hour ? HOUR_TICK_RATIO : MINUTE_TICK_RATIO;

        int x1 = ORIGO_X + cos(angle) * RADIUS * (1 - tick_ratio);
        int y1 = ORIGO_Y - sin(angle) * RADIUS *  (1 - tick_ratio);

        int tick_width;
        const char *tick_color;

        if (is_hour)
        {
            tick_width = HOUR_TICK_WIDTH;
            tick_color = HOUR_TICK_COLOR;
        }
        else
        {
            tick_width = MINUTE_TICK_WIDTH;
            tick_color = MINUTE_TICK_COLOR;
        }

        fprintf(fp, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"%d\" stroke=\"%s\" stroke-linecap=\"round\" />\n",
                x1, y1, x2, y2, tick_width, tick_color);
    }
}

/** \brief Kiírja a megadott fájlba a paraméterekkel megadott óramutatót leíró SVG-alakzatot.
 *
 * \param fp A kimeneti fájl.
 * \param angle A mutató forgásszöge vízszintessel bezárt elõjeles szögként megadva.
 * \param hand_width A mutató vastagsága.
 * \param hand_color A mutató színe.
 *
 */

void print_clock_hand(FILE *fp, double angle, double hand_ratio, int hand_width, const char *hand_color)
{
    angle = angle + PI / 2;

    int x2 = ORIGO_X - cos(angle) * RADIUS * hand_ratio;
    int y2 = ORIGO_Y - sin(angle) * RADIUS * hand_ratio;

    int x1 = ORIGO_X;
    int y1 = ORIGO_Y;

    fprintf(fp, "\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"%d\" stroke=\"%s\" stroke-linecap=\"round\" />\n",
            x1, y1, x2, y2, hand_width, hand_color);
}

/** \brief Kiírja a megadott fájlba az óramutatókat leíró SVG-alakzatokat
 *
 * \param fp A kimeneti fájl.
 * \param hours Az órák értéke 0 és 23 között.
 * \param minutes A percek értéke 0 és 59 között.
 * \param seconds A másodpercek értéke 0 és 59 között.
 *
 */

void print_clock_hands(FILE *fp, int hours, int minutes, int seconds)
{
    hours %= 12;

    int time_in_seconds = hours * SECONDS_IN_HOUR + minutes * SECONDS_IN_MINUTE + seconds;

    double ang_h = ANGULAR_VELOCITY_H * time_in_seconds;
    double ang_m = ANGULAR_VELOCITY_M * time_in_seconds;
    double ang_s = ANGULAR_VELOCITY_S * time_in_seconds;

    print_clock_hand(fp, ang_h, HOUR_HAND_RATIO, HOUR_HAND_WIDTH, HOUR_HAND_COLOR);
    print_clock_hand(fp, ang_m, MINUTE_HAND_RATIO, MINUTE_HAND_WIDTH, MINUTE_HAND_COLOR);
    print_clock_hand(fp, ang_s, SECOND_HAND_RATIO, SECOND_HAND_WIDTH, SECOND_HAND_COLOR);
}

/** \brief Kirajzol egy órát SVG formátumban a megadott fájlba.
 *
 * \param filename A kimeneti SVG-fájl neve.
 * \param hours Az órák értéke 0 és 23 között.
 * \param minutes A percek értéke 0 és 59 között.
 * \param seconds A másodpercek értéke 0 és 59 között.
 * \return A visszatérési érték 0, ha nem volt gond a fájlbeolvasással, -1, ha igen.
 *
 */

int print_clock(const char *filename, int hours, int minutes, int seconds)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        return -1;
    }

    fprintf(fp, "<svg width=\"%d\" height=\"%d\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n",
            CANVAS_SIZE, CANVAS_SIZE);

    print_clock_backface(fp);
    print_clock_ticks(fp);
    print_clock_hands(fp, hours, minutes, seconds);
    print_clock_frontface(fp);

    fprintf(fp, "</svg>\n");

    fclose(fp);

    return 0;
}

/** \brief A program belépési kódja. Bekérdez egy idõt három egész számként, majd kirajzol egy órát ilyen idõbeállítással.
 *
 * \param argc Parancssori argumentumok száma.
 * \param argv A parancssori argumentumok nincsenek használva a program által.
 * \return Sikeres esetén 0, egyébként -1.
 *
 */

int main(int argc, char *argv[])
{
    int hours, minutes, seconds;

    scanf("%d %d %d", &hours, &minutes, &seconds);

    if (print_clock("ora.svg", hours, minutes, seconds) != 0)
    {
        perror("Nem sikerult fajlba irni az orat: ");
        return -1;
    }

    return 0;
}
