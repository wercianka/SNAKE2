#include "classes.h"
#include <fstream>

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

    textScore1.setFont(fonts.chary);
    textScore1.setCharacterSize(36);
    textScore1.setFillColor(sf::Color::White);

    textScore2.setFont(fonts.chary);
    textScore2.setCharacterSize(36);
    textScore2.setFillColor(sf::Color::White);

    textScore3.setFont(fonts.chary);
    textScore3.setCharacterSize(36);
    textScore3.setFillColor(sf::Color::White);

    textScore4.setFont(fonts.chary);
    textScore4.setCharacterSize(36);
    textScore4.setFillColor(sf::Color::White);

    textScore5.setFont(fonts.chary);
    textScore5.setCharacterSize(36);
    textScore5.setFillColor(sf::Color::White);

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
    resetHighlight();
    updateScoreArray();
    setTextSprites();
    writeToFile();
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
    }
    i--;
    if (i < 5)
    {
        int temp = scoreArray[i];
        scoreArray[i] = scoreCount;
        updated = i + 1;

        for (int j = i - 1; j >= 0; j--)
        {
            int temp2 = scoreArray[j];
            scoreArray[j] = temp;
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
    std::string temp = dots;
    int digits = numDigits(scoreArray[i]);
    temp = temp.replace((temp.size() - digits), digits, std::to_string(scoreArray[i]));
    textScore5.setString(temp);
    sf::FloatRect bounds = textScore5.getLocalBounds();
    textScore5.setPosition(510.f - bounds.width, 335.f);
    i++;

    temp = dots;
    digits = numDigits(scoreArray[i]);
    temp = temp.replace((temp.size() - digits), digits, std::to_string(scoreArray[i]));
    textScore4.setString(temp);
    bounds = textScore4.getLocalBounds();
    textScore4.setPosition(510.f - bounds.width, 285.f);
    i++;

    temp = dots;
    digits = numDigits(scoreArray[i]);
    temp = temp.replace((temp.size() - digits), digits, std::to_string(scoreArray[i]));
    textScore3.setString(temp);
    bounds = textScore3.getLocalBounds();
    textScore3.setPosition(510.f - bounds.width, 235.f);
    i++;

    temp = dots;
    digits = numDigits(scoreArray[i]);
    temp = temp.replace((temp.size() - digits), digits, std::to_string(scoreArray[i]));
    textScore2.setString(temp);
    bounds = textScore2.getLocalBounds();
    textScore2.setPosition(510.f - bounds.width, 185.f);
    i++;

    temp = dots;
    digits = numDigits(scoreArray[i]);
    temp = temp.replace((temp.size() - digits), digits, std::to_string(scoreArray[i]));
    textScore1.setString(temp);
    bounds = textScore1.getLocalBounds();
    textScore1.setPosition(510.f - bounds.width, 135.f);

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

void HighScore::resetHighlight()
{
    if (updated)
    {
        switch (updated)
        {
        case 1:
            textScore5.setFillColor(sf::Color::White);
            break;
        case 2:
            textScore4.setFillColor(sf::Color::White);
            break;
        case 3:
            textScore3.setFillColor(sf::Color::White);
            break;
        case 4:
            textScore2.setFillColor(sf::Color::White);
            break;
        case 5:
            textScore1.setFillColor(sf::Color::White);
            break;
        }
    }
    updated = 0;
}

void HighScore::writeToFile()
{
    std::ofstream writeFile("highScore.txt");
    if (writeFile.is_open())
    {
        for (int i = 0; i < 5; i++)
        {
            writeFile << scoreArray[i] << '\n';
        }
    }
    writeFile.close();
}

int HighScore::numDigits(int number)
{
    int digits = 0;
    while (number)
    {
        number /= 10;
        digits++;
    }
    return digits;
}