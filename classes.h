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
    void setLivesSpritePosition(sf::Time deltaTime);
    sf::Time timeSinceLastUpdate;

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
    Score(GameFont &fonts);
    sf::Text textScore;
    sf::Text textNumber;
    void draw(sf::RenderWindow &mWindow);
    void updateNumber();
    void changePositionGameOver();
    void reset();
    int returnScore();

private:
    int scoreCount;
};

class MainMenu
{
public:
    MainMenu(GameFont &fonts);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;

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

    CurrentMenu current;
    int dir;
};

class GameOver
{
public:
    GameOver(GameFont &fonts, Score *ScoreClass);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;

private:
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void animate(sf::Time deltaTime);
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    Score *ScoreSprite;
    bool isVisible;
    sf::Text textGameOver;
    sf::Text textInstruction;
    sf::Time timeSinceLastUpdate;
};

class HighScore
{
public:
    HighScore(GameFont &fonts);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;
    void setScore(int score);

private:
    int scoreCount;
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void animate(sf::Time deltaTime);
    void readFromFile();
    void updateScoreArray();
    void sort();
    void setTextSprites();
    void resetHighlight();
    void writeToFile();

    int updated;
    int scoreArray[5];
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    bool isVisible;

    sf::Text textHighScore;
    sf::Text textInstruction;
    sf::Text textScore1;
    sf::Text textScore2;
    sf::Text textScore3;
    sf::Text textScore4;
    sf::Text textScore5;

    sf::Time timeSinceLastUpdate;
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
    bool checkCollision();
    void reset();
    int dirX;
    int dirY;
    int total;
    int speed;
    bool checkReverse(int keyX, int keyY);

private:
    sf::Texture textureSnake;
};

class Game
{
public:
    Game(Score *ScoreClass);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool isAlive;

private:
    void processEvents(sf::RenderWindow &mWindow);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void checkFruit();
    Lives LivesSprite;
    Snake SnakeSprite;
    Apple AppleSprite;
    Score *ScoreSprite;

private:
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mIsMovingDown;
    bool mIsMovingUp;

    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    int count;
    sf::Time timeSinceLastUpdate;
};
