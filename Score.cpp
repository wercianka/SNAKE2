#include "classes.h"

Score::Score(GameFont &fonts)
{
    textScore.setFont(fonts.slkscrb);
    textNumber.setFont(fonts.slkscrb);
    textScore.setString("SCORE");
    textScore.setCharacterSize(32);
    textScore.setFillColor(sf::Color::White);
    textScore.setPosition(50.f, 44.f);

    textNumber.setString("0");
    textNumber.setCharacterSize(32);
    textNumber.setFillColor(sf::Color::White);
    textNumber.setPosition(190.f, 44.f);

    scoreCount = 0;
}

void Score::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(textScore);
    mWindow.draw(textNumber);
}

void Score::updateNumber()
{
    scoreCount++;
    textNumber.setString(std::to_string(scoreCount));
}

void Score::changePositionGameOver()
{
    textScore.setPosition(100.f, 202.f);
    sf::FloatRect bounds = textNumber.getLocalBounds();
    textNumber.setPosition(515.f - bounds.width, 202.f);
}

void Score::reset()
{
    scoreCount = 0;
    textNumber.setString(std::to_string(scoreCount));
    textScore.setPosition(50.f, 44.f);
    textNumber.setPosition(190.f, 44.f);
}

int Score::returnScore()
{
    return scoreCount;
}