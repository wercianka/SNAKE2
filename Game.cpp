#include "classes.h"

Game::Game(Score *ScoreClass)
{
    if (!textureBackground.loadFromFile("snake/Sprite-0005.png"))
    {
        // Handle loading error
    }

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);
    count = 0;
    isAlive = true;
    ScoreSprite = ScoreClass;
}
void Game::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    timeSinceLastUpdate = sf::Time::Zero;

    ScoreSprite->reset();
    SnakeSprite.reset();

    while (mWindow.isOpen() && isAlive)
    {
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }

        update(clock.getElapsedTime());
        render(mWindow);
        clock.restart();
    }
    CurrentState = GameOverState;
}

void Game::handlePlayerInput(sf::Keyboard::Key key)
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

void Game::processEvents(sf::RenderWindow &mWindow)
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code);
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

        if (SnakeSprite.checkCollision())
        {
            isAlive = false;
        }
        else
        {
            checkFruit();
        }
        timeSinceLastUpdate = sf::Time::Zero;
    }
}

void Game::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(spriteBackground);

    LivesSprite.setLivesSpritePosition();

    mWindow.draw(LivesSprite.spriteHeart);
    mWindow.draw(LivesSprite.spriteHeart2);
    mWindow.draw(LivesSprite.spriteHeart3);

    ScoreSprite->draw(mWindow);

    SnakeSprite.drawSnake(mWindow);

    AppleSprite.drawApple(mWindow);

    //MainMenuSprite.draw(mWindow);

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
        ScoreSprite->updateNumber();
    }
}