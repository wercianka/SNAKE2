#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include "helpers.h"

class Lives
{
public:
    Lives();
    sf::Sprite spriteHeart;
    sf::Sprite spriteHeart2;
    sf::Sprite spriteHeart3;
    void setLivesSpritePosition(sf::Time deltaTime); //ustawia obszar z tekstury do wyswietlenia
    sf::Time timeSinceLastUpdate;                    //czas animacji

private:
    sf::Texture textureHeart;
    sf::IntRect rectSourceSprite = sf::IntRect(0, 0, 32, 32);
};

class GameFont
{
public:
    GameFont();
    sf::Font slkscrb; //czcionki uzyte w grze
    sf::Font kongtext;
    sf::Font chary;
};

class Apple
{
public:
    Apple();
    int appleX; //wspolrzedna X polozenia owocu
    int appleY; //wspolrzedna Y polozenia owocu
    sf::Sprite spriteApple;
    void drawApple(sf::RenderWindow &mWindow);
    void generate(); //generuje polozenie owocu

private:
    sf::Texture textureApple;
};

class Score
{
public:
    Score(GameFont &fonts);
    sf::Text textScore;
    sf::Text textNumber;
    void draw(sf::RenderWindow &mWindow);
    void updateNumber();           //aktualizuje tekst do wyswielenia aktualnego wyniku
    void changePositionGameOver(); //zmiena polozenie tekstu dla stanu GameOver
    void reset();                  //resetuje wartosci
    int returnScore();             //zwraca scoreCount

private:
    int scoreCount; //aktualny wynik
};

class Manual
{
public:
    Manual(GameFont &fonts);
    void run(sf::RenderWindow &mWindow);

private:
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    bool isVisible; //czy ma byc wyswietlony napis "press enter"
    bool PressedEnter;
    void animate(sf::Time deltaTime); //animacja migania "pressed enter"
    sf::Text textManual;
    sf::Text textEnter;

    sf::Time timeSinceLastUpdate; //czas od ostaniej zmiany isVisible
};

class MainMenu
{
public:
    MainMenu(GameFont &fonts);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;

private:
    sf::Text textTitle;
    sf::Text textPlay;
    sf::Text textOption;
    sf::Text textQuit;

    sf::Texture textureBackground;
    sf::Sprite spriteBackground;

    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void update(); //wywoluje changeCurrent()
    void handlePlayerInput(sf::Keyboard::Key key);
    void changeCurrent(); //zmiena aktualnie podswietlana pozycje

    CurrentMenu current; //aktualnie podswietlana pozycja
    int dir;             //kierunek pionowy do zmiany aktualnie podswietlanej pozycji
};

class Options
{
public:
    Options(GameFont &fonts);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;
    int currentSpeedOption;
    bool currentDeathOption;

private:
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void update(); //wywoluje changeCurrent()
    void handlePlayerInput(sf::Keyboard::Key key);
    void changeCurrent(); //zmiena aktualnie podswietlana pozycje
    void changeOption();  //zmiena wartosc opcji aktualnie podswietlanej

    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    sf::Text textTitle;
    sf::Text textSpeed;
    sf::Text textDeath;
    sf::Text textBack;

    sf::Text textSpeedOption;
    sf::Text textDeathOption;

    int dir;  //kierunek pionowy do zmiany aktualnie podswietlanej pozycji
    int dirY; //kierunek poziomy do zmiany opcji dla aktualnie podswietlanej pozycji

    CurrentOption current; //aktualnie podswietlana pozycja
};

class GameOver
{
public:
    GameOver(GameFont &fonts, Score *ScoreClass);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;

private:
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void animate(sf::Time deltaTime); //animacja migania "pressed enter"
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    Score *ScoreSprite;
    bool isVisible; //czy ma byc wyswietlony napis "press enter"
    sf::Text textGameOver;
    sf::Text textInstruction;
    sf::Time timeSinceLastUpdate; //czas od ostaniej zmiany isVisible
};

class HighScore
{
public:
    HighScore(GameFont &fonts);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool PressedEnter;
    void setScore(int score); //ustawia wynik do zmiennej scoreCount

private:
    int scoreCount; //uzyskany wynik
    void render(sf::RenderWindow &mWindow);
    void processEvents(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void animate(sf::Time deltaTime); //animacja migania "pressed enter"
    void readFromFile();              //wczytywanie z pliku jesli istnieje wynikow do tabeli
    void updateScoreArray();          //dodaje nowy wynik do tabeli
    void sort();                      //sortowanie wynikow w tabeli
    void setTextSprites();            //ustawia tekst spritow dla wynikow w tabeli
    void resetHighlight();            //resetuje podswietlenie dla nowego wyniku w tabeli
    void writeToFile();               //zapisuje tabele wynikow do pliku
    int numDigits(int number);        //zlicza ilosc cyfr w przekazanej liczbie

    int updated;       //pozycja w tabeli wynikow na ktora ma trafic uzyskany wynik
    int scoreArray[5]; //tabela wynikow
    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    bool isVisible; //czy ma byc wyswietlony napis "press enter"
    std::string const dots = "......................";

    sf::Text textHighScore;
    sf::Text textInstruction;
    sf::Text textScore1;
    sf::Text textScore2;
    sf::Text textScore3;
    sf::Text textScore4;
    sf::Text textScore5;

    sf::Time timeSinceLastUpdate; //czas od ostaniej zmiany isVisible
};

class Snake
{
public:
    Snake();
    std::vector<int> snakeX; //wektor ze wspolrzedna X
    std::vector<int> snakeY; //wektor ze wspolrzedna Y
    sf::Sprite spriteSnake;
    void drawSnake(sf::RenderWindow &mWindow);
    void moveSnake();                      //przesuwa polozenie weza
    bool checkBorder();                    //sprawdza kolizje z krawedzami
    void swapAtBorder();                   //przemieszcza weza na drugi koniec
    bool checkCollision();                 //sprawdza kolizja glowy weza z jego cialem
    void reset();                          //resetuje wartosci
    int dirX;                              //kierunek X poruszania sie weza
    int dirY;                              //kierunek Y poruszania sie weza
    int total;                             //ilosc kawalkow weza
    int speed;                             //szybkosc z jaka ma poruszac sie waz wyrazana w ms
    int lives;                             //ilosc zyc
    bool checkReverse(int keyX, int keyY); //uniemozliwia cofanie sie weza, zwraca true jesli bedzie kolizja glowy z cialem w podanym kierunku
    SnakeState state;                      //Normal, Hurt - okres po utracie zycia, w ktorym nie moze ponownie go utracic

private:
    sf::Texture textureSnake;
};

class Game
{
public:
    Game(Score *ScoreClass);
    void run(sf::RenderWindow &mWindow, GameStates &CurrentState);
    bool isAlive;                  //czy skonczyc gre
    bool deathOption;              //czy jest wlaczona opcja smierci po dotknieciu krawedzi
    void setSnakeSpeed(int value); //ustawia szybkosc poruszania sie weza

private:
    void processEvents(sf::RenderWindow &mWindow);
    void update(sf::Time deltaTime);
    void render(sf::RenderWindow &mWindow);
    void handlePlayerInput(sf::Keyboard::Key key);
    void checkFruit();                //sprawdza czy glowa weza znajduje sie w tym samym miejscu co owoc
    void animate(sf::Time deltaTime); //animacja migania po utracie zycia

    Lives LivesSprite;
    Snake SnakeSprite;
    Apple AppleSprite;
    Score *ScoreSprite;

    sf::Texture textureBackground;
    sf::Sprite spriteBackground;
    bool isVisible;               //czy waz ma byc renderowany
    sf::Time timeSinceLastUpdate; //czas od ostatniego wywolania funkcji update()
    sf::Time timeToChange;        //czas od zmianu stanu weza z Normal na Hurt
};
