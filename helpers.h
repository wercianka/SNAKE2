#pragma once

const sf::Time TimePerFrame = sf::seconds(1.f / 30.f);

enum GameStates
{
    MenuState = 1,
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

enum CurrentOption
{
    Speed = 1,
    Death,
    Back
};

enum SnakeState
{
    Hurt = 0,
    Normal
};
