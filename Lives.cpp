#include "classes.h"

Lives::Lives()
{
    if (!textureHeart.loadFromFile("snake/heartsprite64W.png"))
    {
        // Handle loading error
    }

    spriteHeart.setTexture(textureHeart, false);
    spriteHeart.setTextureRect(rectSourceSprite);
    spriteHeart.setPosition(450.f, 52.f);

    spriteHeart2.setTexture(textureHeart, false);
    spriteHeart2.setTextureRect(rectSourceSprite);
    spriteHeart2.setPosition(500.f, 52.f);

    spriteHeart3.setTexture(textureHeart, false);
    spriteHeart3.setTextureRect(rectSourceSprite);
    spriteHeart3.setPosition(550.f, 52.f);
}

void Lives::setLivesSpritePosition(sf::Time deltaTime)
{
    timeSinceLastUpdate += deltaTime;
    if (timeSinceLastUpdate >= sf::seconds(4))
    {
        if (rectSourceSprite.left == 32)
        {
            if (rectSourceSprite.top == 32)
            {
                rectSourceSprite.top = 0;
                rectSourceSprite.left = 0;
                timeSinceLastUpdate = sf::Time::Zero;
            }
            else
            {
                rectSourceSprite.top += 32;
                timeSinceLastUpdate -= sf::milliseconds(600);
            }
        }
        else
        {
            rectSourceSprite.left += 32;
            timeSinceLastUpdate -= sf::milliseconds(600);
        }

        spriteHeart.setTextureRect(rectSourceSprite);
        spriteHeart2.setTextureRect(rectSourceSprite);
        spriteHeart3.setTextureRect(rectSourceSprite);
    }
}