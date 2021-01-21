#include "classes.h"

Score::Score()
{
    textScore.setFont(fontSlk.slkscrb);
    textNumber.setFont(fontSlk.slkscrb);
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
