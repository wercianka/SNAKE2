#include "classes.h"

int main()
{
    sf::RenderWindow mWindow(sf::VideoMode(640, 480), "Snake", sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i v1(500, 200);
    mWindow.setPosition(v1);

    GameStates CurrentState = MenuState;
    Game game;
    MainMenu menu;
    while (mWindow.isOpen())
    {
        switch (CurrentState)
        {
        case ManualState:
            break;
        case MenuState:
            menu.run(mWindow, CurrentState);
            break;
        case OptionState:
            break;
        case RunningState:
            game.run(mWindow, CurrentState);
            break;
        case GameOverState:
            break;
        case HighScoreState:
            break;
        }
    }

    return 0;
}
