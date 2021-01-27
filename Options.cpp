#include "classes.h"

Options::Options(GameFont &fonts)
{
    textureBackground.loadFromFile("snake/options.png");

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);

    textTitle.setFont(fonts.kongtext);
    textTitle.setString("OPTIONS");
    textTitle.setCharacterSize(80);
    textTitle.setFillColor(sf::Color::White);
    textTitle.setPosition(38.f, 30.f);

    textSpeed.setFont(fonts.slkscrb);
    textSpeed.setString("SPEED");
    textSpeed.setCharacterSize(38);
    textSpeed.setFillColor(sf::Color(36, 159, 222));
    textSpeed.setPosition(70.f, 170.f);

    textDeath.setFont(fonts.slkscrb);
    textDeath.setString("DEATH ON \nEDGE");
    textDeath.setCharacterSize(38);
    textDeath.setFillColor(sf::Color::White);
    textDeath.setPosition(70.f, 245.f);

    textBack.setFont(fonts.slkscrb);
    textBack.setString("BACK");
    textBack.setCharacterSize(38);
    textBack.setFillColor(sf::Color::White);
    textBack.setPosition(250.f, 370.f);

    textSpeedOption.setFont(fonts.slkscrb);
    textSpeedOption.setString("1");
    textSpeedOption.setCharacterSize(38);
    textSpeedOption.setFillColor(sf::Color::White);
    textSpeedOption.setPosition(470.f, 170.f);

    textDeathOption.setFont(fonts.slkscrb);
    textDeathOption.setString("OFF");
    textDeathOption.setCharacterSize(38);
    textDeathOption.setFillColor(sf::Color::White);
    textDeathOption.setPosition(470.f, 258.f);

    current = Speed;
    dir = 0;
    dirY = 0;
    PressedEnter = false;
    currentSpeedOption = 1;
    currentDeathOption = false;
}

void Options::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    clock.restart();
    while (mWindow.isOpen() && !PressedEnter)
    {
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }

        update();
        render(mWindow);
        clock.restart();
    }

    CurrentState = MenuState;
}

void Options::processEvents(sf::RenderWindow &mWindow)
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

void Options::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::W)
    {
        dir = -1;
    }
    else if (key == sf::Keyboard::S)
    {
        dir = 1;
    }
    else if (key == sf::Keyboard::D)
    {
        dirY = 1;
    }
    else if (key == sf::Keyboard::A)
    {
        dirY = -1;
    }
    else if (key == sf::Keyboard::Enter)
    {
        if (current == Back)
        {
            PressedEnter = true;
        }
    }
}

void Options::update()
{
    if (dir != 0)
    {
        changeCurrent();
        dir = 0;
    }

    if (dirY != 0)
    {
        changeOption();
        dirY = 0;
    }
}

void Options::changeCurrent()
{
    switch (current)
    {
    case Speed:
        textSpeed.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Back;
            textBack.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Death;
            textDeath.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    case Death:
        textDeath.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Speed;
            textSpeed.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Back;
            textBack.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    case Back:
        textBack.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Death;
            textDeath.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Speed;
            textSpeed.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    }
}

void Options::changeOption()
{
    switch (current)
    {
    case Speed:
        switch (currentSpeedOption)
        {
        case 1:
            if (dirY == 1)
            {
                currentSpeedOption = 2;
                textSpeedOption.setString("2");
            }
            else
            {
                currentSpeedOption = 3;
                textSpeedOption.setString("3");
            }
            break;
        case 2:
            if (dirY == 1)
            {
                currentSpeedOption = 3;
                textSpeedOption.setString("3");
            }
            else
            {
                currentSpeedOption = 1;
                textSpeedOption.setString("1");
            }
            break;
        case 3:
            if (dirY == 1)
            {
                currentSpeedOption = 1;
                textSpeedOption.setString("1");
            }
            else
            {
                currentSpeedOption = 2;
                textSpeedOption.setString("2");
            }
            break;
        }
        break;
    case Death:
        if (currentDeathOption)
        {
            currentDeathOption = false;
            textDeathOption.setString("OFF");
        }
        else
        {
            currentDeathOption = true;
            textDeathOption.setString("ON");
        }
        break;
    }
}

void Options::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(spriteBackground);

    mWindow.draw(textTitle);
    mWindow.draw(textSpeed);
    mWindow.draw(textDeath);
    mWindow.draw(textBack);

    mWindow.draw(textSpeedOption);
    mWindow.draw(textDeathOption);

    mWindow.display();
}
