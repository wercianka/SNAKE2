#include "classes.h"

Snake::Snake()
{
    textureSnake.loadFromFile("snake/snake3.png");

    spriteSnake.setTexture(textureSnake, false);
    spriteSnake.setPosition(304.f, 240.f);
    total = 0;

    snakeX.push_back(304.f);
    snakeY.push_back(240.f);
    speed = 200;

    dirX = 0;
    dirY = 0;
    lives = 4;
    state = Normal;
}

void Snake::drawSnake(sf::RenderWindow &mWindow)
{
    for (int i = total; i >= 0; i--)
    {
        spriteSnake.setPosition((float)snakeX[i], (float)snakeY[i]);
        mWindow.draw(spriteSnake);
    }
}

void Snake::moveSnake()
{

    for (int i = total; i >= 0; i--)
    {
        if (i != 0)
        {
            snakeX[i] = snakeX[i - 1];
            snakeY[i] = snakeY[i - 1];
        }
        else
        {
            snakeX[0] = snakeX[0] + dirX * 16;
            snakeY[0] = snakeY[0] + dirY * 16;
        }
    }
}

bool Snake::checkBorder()
{

    if ((snakeX[0] <= 48) && (dirX == -1)) //lewo
    {
        return true;
    }
    if ((snakeX[0] >= (591 - 16)) && (dirX == 1)) //prawo
    {
        return true;
    }
    if ((snakeY[0] <= 96) && (dirY == -1)) //gora
    {
        return true;
    }
    if ((snakeY[0] >= (431 - 16)) && (dirY == 1)) //dol
    {
        return true;
    }

    return false;
}

bool Snake::checkCollision()
{
    for (int i = 4; i <= total; i++)
    {
        if ((snakeX[i] == snakeX[0]) && (snakeY[i] == snakeY[0]))
        {
            return true;
        }
    }
    return false;
}

void Snake::swapAtBorder()
{

    if (dirX == -1)
    {
        snakeX[0] = 576;
    }
    else if (dirX == 1)
    {
        snakeX[0] = 48;
    }
    else if (dirY == -1)
    {
        snakeY[0] = 416;
    }
    else
    {
        snakeY[0] = 96;
    }
}

bool Snake::checkReverse(int keyX, int keyY)
{
    if (((snakeX[0] + 16 * keyX) == (snakeX[1])) && ((snakeY[0] + 16 * keyY) == snakeY[1]))
    {
        return true;
    }

    return false;
}

void Snake::reset()
{
    snakeX.clear(); //wyczysc vektor
    snakeY.clear();

    snakeX.shrink_to_fit();
    snakeY.shrink_to_fit();

    dirX = 0;
    dirY = 0;
    spriteSnake.setPosition(304.f, 240.f);
    total = 0;
    snakeX.push_back(304.f);
    snakeY.push_back(240.f);
    lives = 4;
    state = Normal;
}