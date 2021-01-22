#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include "helpers.h"

class Lives
{
public:
    Lives();
    sf::Sprite spriteHeart;
    sf::Sprite spriteHeart2;
    sf::Sprite spriteHeart3;
    void setLivesSpritePosition();

private:
    sf::Texture textureHeart;

    sf::IntRect rectSourceSprite = sf::IntRect(0, 0, 32, 32);
    int count;
};

class GameFont
{
public:
    GameFont();
    sf::Font slkscrb;
    sf::Font kongtext;
};

class Apple
{
public:
    Apple();
    int appleX;
    int appleY;
    sf::Sprite spriteApple;
    void drawApple(sf::RenderWindow &mWindow);
    void generate();

private:
    sf::Texture textureApple;
};

class Score
{
public:
    Score();
    sf::Text textScore;
    sf::Text textNumber;
    void draw(sf::RenderWindow &mWindow);
    void updateNumber();

private:
    GameFont fontSlk;
    int scoreCount;
};

class MainMenu
{
public:
    MainMenu();
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);

private:
    sf::Text textTitle;
    sf::Text textPlay;
    sf::Text textOption;
    sf::Text textQuit;

    sf::Texture textureBackground;
    sf::Sprite spriteBackground;

    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void update();
    void handlePlayerInput(sf::Keyboard::Key key);
    void changeCurrent();
    GameFont fonts;

    CurrentMenu current;
    bool PressedEnter;
    int dir;
};

class Snake
{
public:
    Snake();
    std::vector<int> snakeX;
    std::vector<int> snakeY;
    sf::Sprite spriteSnake;
    void drawSnake(sf::RenderWindow &mWindow);
    void moveSnake();
    bool checkBorder();
    void swapAtBorder();
    int dirX;
    int dirY;
    int total;
    int count;
    int speed;
    bool checkReverse(int keyX, int keyY);

private:
    sf::Texture textureSnake;
};

class Game
{
public:
    Game();
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);

private:
    void processEvents(sf::RenderWindow &mWindow);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void checkFruit();
    Lives LivesSprite;
    Snake SnakeSprite;
    Apple AppleSprite;
    Score ScoreSprite;

private:
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mIsMovingDown;
    bool mIsMovingUp;
    bool isAlive;
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    int count;
    sf::Time timeSinceLastUpdate;
};
