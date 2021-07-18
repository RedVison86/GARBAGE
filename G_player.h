
class Player
{
    private:
        float x, y;

    public:
        float w, h, dx, dy, speed = 0;
        int dir, playerScore = 0;
        std::string file;
        Image image;
        Texture texture;
        Sprite sprite;

        Player(std::string F, float X, float Y, float W, float H);
        void Update(float time);
        void InteractTheMap();
        float GetPlayerCoordX();
        float GetPlayerCoordY();

};

Player::Player(std::string F, float X, float Y, float W, float H)
{
    file = F;
    w = W; h = H; x = X; y = Y;
    image.loadFromFile("images/" + file);
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(IntRect(0, 0, w, h));
    dir = 0; speed = 0; playerScore = 0;
}

void Player::Update(float time)
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
    sprite.setPosition(x,y);
    InteractTheMap();
}

void Player::InteractTheMap()
{
    for (int i = y / 32; i < (y + h) / 32; i++)
    for (int j = x / 32; j < (x + w) / 32; j++)
    {
        if ((tileMap[i][j] == 'S') || (tileMap[i][j] == 'H')) // если стоит стена то проверяем направление скорости
        {
            if (dy > 0)
            {
                y = i * 32 - h; // если идем вниз, то остановим игрока
            }

            if (dy < 0)
            {
                y = i * 32 + 32; // если идем вверх, останавливаем игрока
            }

            if (dx > 0)
            {
                x = j * 32 - w; // если идем вправо то останавливаем. Х равен стене минус ширина игрока
            }

            if (dx < 0)
            {
                x = j * 32 + 32;
            }
        }




        if (tileMap[i][j] == 'G')
        {
            playerScore++;
            tileMap[i][j] = ' ';
        }

    }

}

float Player::GetPlayerCoordX()
{
    return x;
}

float Player::GetPlayerCoordY()
{
    return y;
}


