#include "classes.h"
#include <iostream>

Manual::Manual(GameFont &fonts)
{

    textManual.setFont(fonts.slkscrb);
    textManual.setString("use a w s d keys to move\n     enter to confirm");
    textManual.setCharacterSize(18);
    textManual.setFillColor(sf::Color::White);
    sf::FloatRect bounds = textManual.getLocalBounds();
    textManual.setPosition(320.f - (bounds.width / 2), 170.f);

    textEnter.setFont(fonts.slkscrb);
    textEnter.setString("press enter");
    textEnter.setCharacterSize(14);
    textEnter.setFillColor(sf::Color::White);
    textEnter.setPosition(258.f, 268.f);

    PressedEnter = false;
    isVisible = true;
}

void Manual::run(sf::RenderWindow &mWindow)
{
    sf::Clock clock;
    clock.restart();
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
}

void Manual::processEvents(sf::RenderWindow &mWindow)
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

void Manual::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Enter)
    {
        PressedEnter = true;
    }
}

void Manual::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(textManual);
    if (isVisible)
    {
        mWindow.draw(textEnter);
    }
    mWindow.display();
}

void Manual::animate(sf::Time deltaTime)
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