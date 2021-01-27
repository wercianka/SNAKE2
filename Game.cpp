#include "classes.h"

Game::Game(Score *ScoreClass)
{
    textureBackground.loadFromFile("snake/running.png");

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);

    isAlive = true;
    ScoreSprite = ScoreClass;
    isVisible = true;

    timeToChange = sf::Time::Zero;
}

void Game::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    timeSinceLastUpdate = sf::Time::Zero;
    LivesSprite.timeSinceLastUpdate = sf::Time::Zero;

    ScoreSprite->reset();
    SnakeSprite.reset();
    isVisible = true;
    timeToChange = sf::Time::Zero;

    while (mWindow.isOpen() && isAlive) //dopoki nie skonczyly sie zycia
    {
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }

        update(clock.getElapsedTime());
        LivesSprite.setLivesSpritePosition(clock.getElapsedTime());
        render(mWindow);
        clock.restart();
    }
    mWindow.clear();
    CurrentState = GameOverState;
}

void Game::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::W)
    {
        if (!SnakeSprite.checkReverse(0, -1)) //jezeli nie koliduje z cialem weza zaraz za glowa
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
        animate(deltaTime);
        if (SnakeSprite.checkBorder()) //sprawdz czy koliduje z krawedzia
        {
            if (deathOption) //jezeli wlaczona opcja smierci na krawedzi
            {
                if (SnakeSprite.state) //jezeli state == Normal
                {
                    SnakeSprite.lives--;
                    if (SnakeSprite.lives == 0)
                    {
                        isAlive = false;
                    }
                    else
                    {
                        SnakeSprite.state = Hurt;
                    }
                }
            }
            else
            {
                SnakeSprite.moveSnake();
                SnakeSprite.swapAtBorder();
            }
        }
        else
        {
            SnakeSprite.moveSnake();
        }

        if (SnakeSprite.checkCollision()) //kolizja glowy z cialem weza
        {
            if (SnakeSprite.state) //jezeli state == Normal
            {
                SnakeSprite.lives--;
                if (SnakeSprite.lives == 0)
                {
                    isAlive = false;
                }
                else
                {
                    SnakeSprite.state = Hurt;
                }
            }
        }
        else
        {
            checkFruit(); //sprawdz pozycje glowy i owocu
        }
        timeSinceLastUpdate = sf::Time::Zero;
    }
}

void Game::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(spriteBackground);

    switch (SnakeSprite.lives)
    {
    case 4:
        mWindow.draw(LivesSprite.spriteHeart3);
    case 3:
        mWindow.draw(LivesSprite.spriteHeart2);
    case 2:
        mWindow.draw(LivesSprite.spriteHeart);
    }

    ScoreSprite->draw(mWindow);

    if (isVisible)
    {
        SnakeSprite.drawSnake(mWindow);
    }

    AppleSprite.drawApple(mWindow);

    mWindow.display();
}

void Game::checkFruit()
{
    if ((SnakeSprite.snakeX[0] == AppleSprite.appleX) &&
        (SnakeSprite.snakeY[0] == AppleSprite.appleY))
    {
        AppleSprite.generate();
        SnakeSprite.total++;                                 //zwieksz ilosc ciala weza
        SnakeSprite.snakeX.push_back(SnakeSprite.snakeX[0]); //dodaj pozycje do vektora wspolrzednych weza
        SnakeSprite.snakeY.push_back(SnakeSprite.snakeY[0]);
        ScoreSprite->updateNumber(); //zaktualizuj wynik
    }
}

void Game::setSnakeSpeed(int value)
{
    switch (value)
    {
    case 1:
        SnakeSprite.speed = 200;
        break;
    case 2:
        SnakeSprite.speed = 150;
        break;
    case 3:
        SnakeSprite.speed = 100;
        break;
    }
}

void Game::animate(sf::Time deltaTime)
{
    if (SnakeSprite.state == Hurt)
    {
        timeToChange += deltaTime;
        if (isVisible)
        {
            isVisible = false;
        }
        else
        {
            isVisible = true;
        }
        if (timeToChange >= sf::milliseconds(300))
        {
            isVisible = true;
            timeToChange = sf::Time::Zero;
            SnakeSprite.state = Normal;
        }
    }
}