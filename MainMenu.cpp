#include "classes.h"

MainMenu::MainMenu()
{
    textTitle.setFont(fonts.kongtext);
    textTitle.setString("SNAKE");
    textTitle.setCharacterSize(100);
    textTitle.setFillColor(sf::Color::White);
    textTitle.setPosition(50.f, 44.f);

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
}

void MainMenu::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(textTitle);
    mWindow.draw(textPlay);
    mWindow.draw(textOption);
    mWindow.draw(textQuit);
}