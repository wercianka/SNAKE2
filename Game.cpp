#include "classes.h"

Game::Game()
    : mWindow(sf::VideoMode(640, 480), "Snake", sf::Style::Titlebar | sf::Style::Close)
{
    sf::Vector2i v1(500, 200);
    mWindow.setPosition(v1);

    if (!textureBackground.loadFromFile("snake/Sprite-0005.png"))
    {
        // Handle loading error
    }

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);
    count = 0;
}
void Game::run()
{
    timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        processEvents();

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents();
        }

        update(clock.getElapsedTime());
        render();
        clock.restart();
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::W)
    {
        if (!SnakeSprite.checkReverse(0, -1))
        {
            SnakeSprite.dirX = 0;
            SnakeSprite.dirY = -1;
        }
    }
    else if (key == sf::Keyboard::S)
    {
        if (!SnakeSprite.checkReverse(0, 1))
        {
            SnakeSprite.dirX = 0;
            SnakeSprite.dirY = 1;
        }
    }
    else if (key == sf::Keyboard::A)
    {
        if (!SnakeSprite.checkReverse(-1, 0))
        {
            SnakeSprite.dirX = -1;
            SnakeSprite.dirY = 0;
        }
    }
    else if (key == sf::Keyboard::D)
    {
        if (!SnakeSprite.checkReverse(1, 0))
        {
            SnakeSprite.dirX = 1;
            SnakeSprite.dirY = 0;
        }
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::update(sf::Time deltaTime)
{
    timeSinceLastUpdate += deltaTime;
    if (timeSinceLastUpdate >= sf::milliseconds(SnakeSprite.speed))
    {

        if (SnakeSprite.checkBorder())
        {
            SnakeSprite.moveSnake();
            SnakeSprite.swapAtBorder();
        }
        else
        {
            SnakeSprite.moveSnake();
        }
        checkFruit();
        timeSinceLastUpdate = sf::Time::Zero;
    }
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(spriteBackground);
    LivesSprite.setLivesSpritePosition();

    mWindow.draw(LivesSprite.spriteHeart);
    mWindow.draw(LivesSprite.spriteHeart2);
    mWindow.draw(LivesSprite.spriteHeart3);

    ScoreSprite.draw(mWindow);

    SnakeSprite.drawSnake(mWindow);

    AppleSprite.drawApple(mWindow);

    mWindow.display();
}

void Game::checkFruit()
{
    if ((SnakeSprite.snakeX[0] == AppleSprite.appleX) &&
        (SnakeSprite.snakeY[0] == AppleSprite.appleY))
    {
        AppleSprite.generate();
        SnakeSprite.total++;
        SnakeSprite.snakeX.push_back(SnakeSprite.snakeX[0]);
        SnakeSprite.snakeY.push_back(SnakeSprite.snakeY[0]);
        ScoreSprite.updateNumber();
    }
}