#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

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
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
    void checkFruit();
    Lives LivesSprite;
    Snake SnakeSprite;
    Apple AppleSprite;
    Score ScoreSprite;

private:
    sf::RenderWindow mWindow;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mIsMovingDown;
    bool mIsMovingUp;
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    int count;
    const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);
};
