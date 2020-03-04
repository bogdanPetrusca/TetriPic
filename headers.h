#ifndef headers
#define headers
#pragma pack(1)

struct rgb
{
 unsigned char blue;
 unsigned char green;
 unsigned char red;
};

struct rotatie
{
    int a;
    int b;
    int c;
    int d;
};

struct coordonate
{
    int x;
    int y;
};

struct piesa
{
    char type;
    int rotation;
    int place;
};

struct bonus
{
    struct rgb *pixel_color;
    struct piesa *type_piesa;
    struct rgb *(**piesa_construire);
    int height;
    int width;

};
#pragma pack()
#endif