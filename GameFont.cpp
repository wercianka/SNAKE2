#include "classes.h"

GameFont::GameFont()
{
    if (!slkscrb.loadFromFile("snake/slkscrb.ttf"))
    {
        // error...
    }
    if (!kongtext.loadFromFile("snake/kongtext.ttf"))
    {
        // error...
    }
    if (!chary.loadFromFile("snake/chary.ttf"))
    {
        // error...
    }
}