#include "classes.h"

GameFont::GameFont()
{
    if (!slkscrb.loadFromFile("snake/slkscrb.ttf"))
    {
        // error...
    }
}