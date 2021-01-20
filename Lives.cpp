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

    count = 0;
}

void Lives::setLivesSpritePosition()
{
    count++;
    if ((count % 1200) == 0)
    {
        if (rectSourceSprite.left == 32)
        {
            if (rectSourceSprite.top == 32)
            {
                rectSourceSprite.top = 0;
                rectSourceSprite.left = 0;
                count = 0;
            }
            else
            {
                rectSourceSprite.top += 32;
                count -= 120;
            }
        }
        else
        {
            rectSourceSprite.left += 32;
            count -= 120;
        }

        spriteHeart.setTextureRect(rectSourceSprite);
        spriteHeart2.setTextureRect(rectSourceSprite);
        spriteHeart3.setTextureRect(rectSourceSprite);
    }
}