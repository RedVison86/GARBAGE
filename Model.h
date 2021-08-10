#pragma once

class Model
{
    public:
    sf::Image img;
    sf::Texture txt;
    sf::Sprite spr;
    std::string file;

    sf::Image mapImg;
    sf::Texture mapTxt;
    sf::Sprite mapSpr;

    float x, y, w, h, dx, dy, speed;
    int dir, inventory, magicNumber;

    Model(std::string F, float X, float Y, float W, float H)
    {
        file = F;
        w = W; h = H; x = X; y = Y;
        dir = 0; speed = 0;
        inventory = 0;

        img.loadFromFile("images/" + file);
        txt.loadFromImage(img);
        spr.setTexture(txt);

        mapImg.loadFromFile("images/maap.png");
        mapTxt.loadFromImage(mapImg);
        mapSpr.setTexture(mapTxt);
    };

    void Logic(float time)
    {
        switch(dir)
        {
            case 0: dx = speed; dy = 0; break;
            case 1: dx = -speed; dy = 0; break;
            case 2: dx = 0; dy = speed; break;
            case 3: dx = 0; dy = -speed; break;
        }

        x += dx * time;
        y += dy * time;

        speed = 0;
        spr.setPosition(x, y);
        CollisionMap();
    }

    void CollisionMap()
    {
        for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if ((Map[i][j] == 'S') || (Map[i][j] == 'H'))
            {
                if (dy > 0)         y = i * 32 - h;
                else if(dy < 0)     y = i * 32 + 32;
                else if (dx > 0)    x = j * 32 - w;
                else if (dx < 0)    x = j * 32 + 32;
            }

            if ((Map[i][j] == 'G') && (inventory == 0)) {
                Map[i][j] = ' ';
                inventory++;
                magicNumber++;


            } else if ((Map[i][j] == 'T') && (inventory > 0)) {
                inventory = 0;
            }
        }
    }
};
