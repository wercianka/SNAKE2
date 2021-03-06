#include "classes.h"

int main()
{
    sf::RenderWindow mWindow(sf::VideoMode(640, 480), "Snake", sf::Style::Titlebar | sf::Style::Close);
    sf::Vector2i v1(500, 200);
    mWindow.setPosition(v1);

    GameStates CurrentState = MenuState;
    GameFont fonts;

    Score gamesScore(fonts);
    Game game(&gamesScore);
    GameOver gameOverScreen(fonts, &gamesScore);
    HighScore highScoreScreen(fonts);
    Options options(fonts);
    Manual manual(fonts);
    MainMenu menu(fonts);

    manual.run(mWindow); //wyswietlenie instrukcji obslugi przy starcie

    while (mWindow.isOpen())
    {
        switch (CurrentState)
        {
        case MenuState:
            menu.PressedEnter = false;
            menu.run(mWindow, CurrentState);
            break;
        case OptionState:
            options.PressedEnter = false;
            options.run(mWindow, CurrentState);
            game.setSnakeSpeed(options.currentSpeedOption);
            game.deathOption = options.currentDeathOption;
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
