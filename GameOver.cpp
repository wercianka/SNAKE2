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

    textGameOver.setFont(fonts.kongtext);
    textGameOver.setString("GAME OVER");
    textGameOver.setCharacterSize(62);
    textGameOver.setFillColor(sf::Color::White);
    textGameOver.setPosition(42.f, 95.f);

    textInstruction.setFont(fonts.slkscrb);
    textInstruction.setString("press enter");
    textInstruction.setCharacterSize(14);
    textInstruction.setFillColor(sf::Color::White);
    textInstruction.setPosition(258.f, 268.f);

    PressedEnter = false;
    isVisible = true;
}

void GameOver::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    clock.restart();
    ScoreSprite->changePositionGameOver();
    timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen() && !PressedEnter)
    {
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }
        animate(clock.getElapsedTime());
        render(mWindow);
        clock.restart();
    }
    mWindow.clear();
    CurrentState = HighScoreState;
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
    mWindow.draw(textGameOver);
    if (isVisible)
    {
        mWindow.draw(textInstruction);
    }
    mWindow.display();
}

void GameOver::animate(sf::Time deltaTime)
{
    timeSinceLastUpdate += deltaTime;
    if (timeSinceLastUpdate >= sf::milliseconds(800))
    {
        if (isVisible)
        {
            isVisible = false;
        }
        else
        {
            isVisible = true;
        }
        timeSinceLastUpdate = sf::Time::Zero;
    }
}
