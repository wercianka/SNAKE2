#include "classes.h"
#include <ctime>

Apple::Apple()
{
    if (!textureApple.loadFromFile("snake/apple4.png"))
    {
        // Handle loading error
    }
    generate();
    spriteApple.setTexture(textureApple, false);
    spriteApple.setPosition((float)appleX, (float)appleY);
}

void Apple::generate()
{
    srand((int)time(0));

    appleX = ((rand() % 34) * 16) + 48;
    appleY = ((rand() % 21) * 16) + 96;
    spriteApple.setPosition((float)appleX, (float)appleY);
}

void Apple::drawApple(sf::RenderWindow &mWindow)
{
    mWindow.draw(spriteApple);
}