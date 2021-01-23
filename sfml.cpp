#include "classes.h"

int main()
{
    sf::RenderWindow mWindow(sf::VideoMode(640, 480), "Snake", sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i v1(500, 200);
    mWindow.setPosition(v1);

    GameStates CurrentState = HighScoreState;
    GameFont fonts;

    Score gamesScore(fonts);
    Game game(&gamesScore);
    GameOver gameOverScreen(fonts, &gamesScore);
    HighScore highScoreScreen(fonts);

    MainMenu menu(fonts);
    while (mWindow.isOpen())
    {
        switch (CurrentState)
        {
        case ManualState:
            break;
        case MenuState:
            menu.PressedEnter = false;
            menu.run(mWindow, CurrentState);
            break;
        case OptionState:
            break;
        case RunningState:
            game.isAlive = true;
            game.run(mWindow, CurrentState);
            break;
        case GameOverState:
            gameOverScreen.PressedEnter = false;
            gameOverScreen.run(mWindow, CurrentState);
            break;
        case HighScoreState:
            highScoreScreen.setScore(gamesScore.returnScore());
            highScoreScreen.PressedEnter = false;
            highScoreScreen.run(mWindow, CurrentState);
            break;
        }
    }

    return 0;
}
