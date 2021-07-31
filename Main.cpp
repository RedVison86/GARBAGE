#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>

const int H_MAP = 10;
const int W_MAP = 15;
sf::String Map[H_MAP] =
{
    "SSSSSSSSSSSSSSS",
    "S            HS",
    "SG            S",
    "S         G   S",
    "S             S",
    "S         G   S",
    "S             S",
    "S G           S",
    "S      TT    HS",
    "SSSSSSSSSSSSSSS",
};

///////////////////////////////////////////


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
    int dir;

    Model(std::string F, float X, float Y, float W, float H)
    {
        file = F;
        w = W; h = H; x = X; y = Y;
        dir = 0; speed = 0;

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
                if (dy > 0)
                {
                    y = i * 32 - h;
                }

                if (dy < 0)
                {
                    y = i * 32 + 32;
                }

                if (dx > 0)
                {
                    x = j * 32 - w;
                }

                if (dx < 0)
                {
                    x = j * 32 + 32;
                }

            }

            if (Map[i][j] == 'G')
            {
                Map[i][j] = ' ';
            }
        }
    }
};

class View
{
    private:
    Model *m_model;
    sf::RenderWindow m_window;

    public:
    View(Model *model)
    {
        m_model = model;
        Init();
    };

    sf::RenderWindow &window()
    {
        return m_window;
    }

    bool Init()
    {
        window().create(sf::VideoMode(600, 400), "GARBAGE");
        return true;
    }

    void Render()
    {
        window().clear();
        Draw();
        window().display();
    }

    void Draw()
    {
        /* draw map */
        for (int i = 0; i < H_MAP; i++)
        for (int j = 0; j < W_MAP; j++)
        {
            if (Map[i][j] == 'S')
                m_model->mapSpr.setTextureRect(sf::IntRect(96,0,32,32));

            if (Map[i][j] == ' ')
                m_model->mapSpr.setTextureRect(sf::IntRect(0,0,32,32));

            if (Map[i][j] == 'H')
                m_model->mapSpr.setTextureRect(sf::IntRect(32,0,32,32));

            if (Map[i][j] == 'G')
                m_model->mapSpr.setTextureRect(sf::IntRect(64,0,32,32));

            if (Map[i][j] == 'T')
                m_model->mapSpr.setTextureRect(sf::IntRect(128,0,32,32));


            m_model->mapSpr.setPosition(j * 32, i *32);
            window().draw(m_model->mapSpr);
        }

        /* draw car */
        if (m_model->dir == 1)
        {
            m_model->spr.setTextureRect(sf::IntRect(68, 17, 34, 17));
        }

        if (m_model->dir == 0)
        {
            m_model->spr.setTextureRect(sf::IntRect(68, 0, 34, 17));
        }

        if (m_model->dir == 3)
        {
            m_model->spr.setTextureRect(sf::IntRect(34, 0, 17, 34));
        }

        if (m_model->dir == 2)
        {
            m_model->spr.setTextureRect(sf::IntRect(51, 0, 17, 34));
        }

        window().draw(m_model->spr);

    }


};

class Controller
{
    private:
    Model *m_model;
    View *v_view;

    public:
    sf::Event C_event;
    float time;
    sf::Clock clock;

    public:
    Controller(Model *model, View *view)
    {
        m_model = model;
        v_view = view;
    };

    void ControllPlayer(float time)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
        {
            m_model->dir = 0;
            m_model->speed = 0.1;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
        {
            m_model->dir = 1;
            m_model->speed = 0.1;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
        {
			m_model->dir = 3;
            m_model->speed = 0.1;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
        {
			m_model->dir = 2;
            m_model->speed = 0.1;
		}

        m_model->Logic(time);
    }

    void Run()
    {
        while(v_view->window().isOpen())
        {
            time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            while(v_view->window().pollEvent(C_event))
            {
                if (C_event.type == sf::Event::Closed)
                    v_view->window().close();
            }

            ControllPlayer(time);

            v_view->Render();

        }

    }

};

int main()
{
    Model model("car.png", 100, 100, 34.0, 17.0);
    View view(&model);
    Controller controller(&model, &view);
    controller.Run();
    return 0;
}

