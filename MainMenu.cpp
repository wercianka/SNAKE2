#include "classes.h"
//#include <iostream>

MainMenu::MainMenu()
{
    if (!textureBackground.loadFromFile("snake/titleScreen.png"))
    {
        // Handle loading error
    }

    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);

    textTitle.setFont(fonts.kongtext);
    textTitle.setString("SNAKE");
    textTitle.setCharacterSize(100);
    textTitle.setFillColor(sf::Color::White);
    textTitle.setPosition(70.f, 44.f);

    textPlay.setFont(fonts.slkscrb);
    textPlay.setString("PLAY");
    textPlay.setCharacterSize(38);
    textPlay.setFillColor(sf::Color(36, 159, 222));
    textPlay.setPosition(86.f, 220.f);

    textOption.setFont(fonts.slkscrb);
    textOption.setString("OPTIONS");
    textOption.setCharacterSize(38);
    textOption.setFillColor(sf::Color::White);
    textOption.setPosition(86.f, 280.f);

    textQuit.setFont(fonts.slkscrb);
    textQuit.setString("QUIT");
    textQuit.setCharacterSize(38);
    textQuit.setFillColor(sf::Color::White);
    textQuit.setPosition(86.f, 340.f);

    current = Play;
    PressedEnter = false;
    dir = 0;
}

void MainMenu::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen() && !PressedEnter)
    {
        //std::cout << "start" << std::endl;
        processEvents(mWindow);

        while (clock.getElapsedTime() < TimePerFrame)
        {
            processEvents(mWindow);
        }

        update();
        render(mWindow);
        clock.restart();
    }
    if (PressedEnter)
    {
        if (current == Quit)
        {
            mWindow.close();
        }
        else if (current == Play)
        {
            CurrentState = RunningState;
        }
        else
        {
            CurrentState = OptionState;
        }
    }
}

void MainMenu::processEvents(sf::RenderWindow &mWindow)
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

void MainMenu::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::W)
    {
        dir = -1;
    }
    else if (key == sf::Keyboard::S)
    {
        dir = 1;
    }
    else if (key == sf::Keyboard::Enter)
    {
        PressedEnter = true;
    }
}

void MainMenu::update()
{
    //std::cout << "update" << std::endl;
    if (dir != 0)
    {
        changeCurrent();
        dir = 0;
    }
}

void MainMenu::changeCurrent()
{
    switch (current)
    {
    case Play:
        textPlay.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Quit;
            textQuit.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Option;
            textOption.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    case Option:
        textOption.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Play;
            textPlay.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Quit;
            textQuit.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    case Quit:
        textQuit.setFillColor(sf::Color::White);
        if (dir == -1)
        {
            current = Option;
            textOption.setFillColor(sf::Color(36, 159, 222));
        }
        else
        {
            current = Play;
            textPlay.setFillColor(sf::Color(36, 159, 222));
        }
        break;
    }
}

void MainMenu::render(sf::RenderWindow &mWindow)
{
    //std::cout << "render" << std::endl;
    mWindow.clear();
    mWindow.draw(spriteBackground);

    mWindow.draw(textTitle);
    mWindow.draw(textPlay);
    mWindow.draw(textOption);
    mWindow.draw(textQuit);

    mWindow.display();
}
