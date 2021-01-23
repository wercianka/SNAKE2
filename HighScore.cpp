#include "classes.h"
#include <fstream>
#include <iostream>

HighScore::HighScore(GameFont &fonts)
{
    if (!textureBackground.loadFromFile("snake/highScore.png"))
    {
        // Handle loading error
    }
    spriteBackground.setTexture(textureBackground);
    spriteBackground.setPosition(0.f, 0.f);

    textHighScore.setFont(fonts.kongtext);
    textHighScore.setString("HIGH SCORE");
    textHighScore.setCharacterSize(58);
    textHighScore.setFillColor(sf::Color::White);
    textHighScore.setPosition(32.f, 30.f);

    textInstruction.setFont(fonts.slkscrb);
    textInstruction.setString("wcisnij enter");
    textInstruction.setCharacterSize(14);
    textInstruction.setFillColor(sf::Color::White);
    textInstruction.setPosition(242.f, 400.f);

    textScore1.setFont(fonts.slkscrb);
    textScore1.setCharacterSize(30);
    textScore1.setFillColor(sf::Color::White);
    textScore1.setPosition(390.f, 140.f);

    textScore2.setFont(fonts.slkscrb);
    textScore2.setCharacterSize(30);
    textScore2.setFillColor(sf::Color::White);
    textScore2.setPosition(390.f, 190.f);

    textScore3.setFont(fonts.slkscrb);
    textScore3.setCharacterSize(30);
    textScore3.setFillColor(sf::Color::White);
    textScore3.setPosition(390.f, 240.f);

    textScore4.setFont(fonts.slkscrb);
    textScore4.setCharacterSize(30);
    textScore4.setFillColor(sf::Color::White);
    textScore4.setPosition(390.f, 290.f);

    textScore5.setFont(fonts.slkscrb);
    textScore5.setCharacterSize(30);
    textScore5.setFillColor(sf::Color::White);
    textScore5.setPosition(390.f, 340.f);

    for (int i = 0; i < 5; i++)
    {
        scoreArray[i] = 0;
    }

    readFromFile();
    sort();

    PressedEnter = false;
    isVisible = true;
    updated = 0;
}

void HighScore::run(sf::RenderWindow &mWindow, GameStates &CurrentState)
{
    sf::Clock clock;
    clock.restart();
    timeSinceLastUpdate = sf::Time::Zero;
    updated = 0;
    updateScoreArray();
    setTextSprites();
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
    CurrentState = MenuState;
}

void HighScore::processEvents(sf::RenderWindow &mWindow)
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

void HighScore::handlePlayerInput(sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Enter)
    {
        PressedEnter = true;
    }
}

void HighScore::render(sf::RenderWindow &mWindow)
{
    mWindow.clear();
    mWindow.draw(spriteBackground);

    mWindow.draw(textScore1);
    mWindow.draw(textScore2);
    mWindow.draw(textScore3);
    mWindow.draw(textScore4);
    mWindow.draw(textScore5);

    mWindow.draw(textHighScore);
    if (isVisible)
    {
        mWindow.draw(textInstruction);
    }
    mWindow.display();
}

void HighScore::animate(sf::Time deltaTime)
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

void HighScore::readFromFile()
{
    std::ifstream readFile("highScore.txt");
    if (readFile.is_open())
    {
        int i = 0;
        int amount;
        while (!readFile.eof() && (i < 5))
        {
            readFile >> amount;
            scoreArray[i] = amount;
            i++;
        }
    }
    readFile.close();
}

void HighScore::sort()
{
    int i, key, j;
    for (i = 1; i < 5; i++)
    {
        key = scoreArray[i];
        j = i - 1;
        while (j >= 0 && scoreArray[j] > key)
        {
            scoreArray[j + 1] = scoreArray[j];
            j = j - 1;
        }
        scoreArray[j + 1] = key;
    }
}

void HighScore::updateScoreArray()
{
    int i = 0;
    while ((scoreCount > scoreArray[i]) && (i != 5))
    {
        i++;
        //std::cout << i << " " << scoreCount << " " << scoreArray[i - 1] << std::endl;
    }
    i--;
    if (i < 5)
    {
        int temp = scoreArray[i];
        scoreArray[i] = scoreCount;
        updated = i + 1;
        //std::cout << updated << std::endl;
        for (int j = i - 1; j >= 0; j--)
        {
            int temp2 = scoreArray[j];
            std::cout << "temp2 " << temp2 << std::endl;
            scoreArray[j] = temp;
            std::cout << "temp " << temp << std::endl;
            temp = temp2;
        }
    }
}

void HighScore::setScore(int score)
{
    scoreCount = score;
}

void HighScore::setTextSprites()
{
    int i = 0;
    textScore5.setString(std::to_string(scoreArray[i]));
    sf::FloatRect bounds = textScore5.getLocalBounds();
    textScore5.setPosition(480.f - bounds.width, 340.f);
    i++;
    textScore4.setString(std::to_string(scoreArray[i]));
    bounds = textScore4.getLocalBounds();
    textScore4.setPosition(480.f - bounds.width, 290.f);
    i++;
    textScore3.setString(std::to_string(scoreArray[i]));
    bounds = textScore3.getLocalBounds();
    textScore3.setPosition(480.f - bounds.width, 240.f);
    i++;
    textScore2.setString(std::to_string(scoreArray[i]));
    bounds = textScore2.getLocalBounds();
    textScore2.setPosition(480.f - bounds.width, 190.f);
    i++;
    textScore1.setString(std::to_string(scoreArray[i]));
    bounds = textScore1.getLocalBounds();
    textScore1.setPosition(480.f - bounds.width, 140.f);
    i++;

    if (updated)
    {
        switch (updated)
        {
        case 1:
            textScore5.setFillColor(sf::Color(36, 159, 222));
            break;
        case 2:
            textScore4.setFillColor(sf::Color(36, 159, 222));
            break;
        case 3:
            textScore3.setFillColor(sf::Color(36, 159, 222));
            break;
        case 4:
            textScore2.setFillColor(sf::Color(36, 159, 222));
            break;
        case 5:
            textScore1.setFillColor(sf::Color(36, 159, 222));
            break;
        }
    }
}
