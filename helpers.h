#pragma once

const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);

enum GameStates
{
    ManualState = 1,
    MenuState,
    OptionState,
    RunningState,
    GameOverState,
    HighScoreState
};

enum CurrentMenu
{
    Play = 1,
    Option,
    Quit
};