#include "classes.h"

GameOver::GameOver(GameFont &fonts, Score *ScoreClass)
{
    if (!textureBackground.loadFromFile("snake/gameOver.png"))
    {
        // Handle loading error
    }
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);
    ScoreSprite = ScoreClass;

    PressedEnter = false;
}

void GameOver::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    clock.restart();
    ScoreSprite->changePositionGameOver();
    while (mWindow.isOpen() && !PressedEnter)
    {
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }
        render(mWindow);
        clock.restart();
    }
    //CurrentState = HighScoreState;
    CurrentState = MenuState;
}

void GameOver::processEvents(sf::RenderWindow &mWindow)
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

void GameOver::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Enter)
    {
        PressedEnter = true;
    }
}

void GameOver::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(spriteBackground);
    ScoreSprite->draw(mWindow);
    mWindow.display();
}