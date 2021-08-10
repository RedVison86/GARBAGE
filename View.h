#pragma once

class View
{
    private:
    Model *m_model;
    sf::RenderWindow m_window;

    public:

    sf::Font font;
    sf::Text text;


    View(Model *model)
    {
        m_model = model;
        Init();
    };

    sf::RenderWindow &window() { return m_window; }

    bool Init()
    {
        window().create(sf::VideoMode(600, 400), "GARBAGE");
        font.loadFromFile("Arial.ttf");
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
        DrawMap();
        DrawText();
        DrawCar();
    }

    void DrawMap()
    {
        /* draw map */
        for (int i = 0; i < H_MAP; i++)
        for (int j = 0; j < W_MAP; j++)
        {
            switch(Map[i][j])
            {
                case 'S':
                    m_model->mapSpr.setTextureRect(sf::IntRect(96,0,32,32));
                    break;
                case 'H':
                    m_model->mapSpr.setTextureRect(sf::IntRect(32,0,32,32));
                    break;
                case 'G':
                    m_model->mapSpr.setTextureRect(sf::IntRect(64,0,32,32));
                    break;
                case 'T':
                    m_model->mapSpr.setTextureRect(sf::IntRect(128,0,32,32));
                    break;
                case ' ':
                    m_model->mapSpr.setTextureRect(sf::IntRect(0,0,32,32));
                    break;
                default:
                    break;
            }

            m_model->mapSpr.setPosition(j * 32, i *32);
            window().draw(m_model->mapSpr);
        }

    }

    void DrawText()
    {
        std::ostringstream magicNumString;
        magicNumString << m_model->magicNumber;

        text.setFont(font);
        text.setCharacterSize(25);
        text.setString("Get bags:" + magicNumString.str());

        window().draw(text);
    }

    void DrawCar()
    {
        /* draw car */
        switch(m_model->dir)
        {
            case 1:
                m_model->spr.setTextureRect(sf::IntRect(68, 17, 34, 17));
                break;
            case 0:
                m_model->spr.setTextureRect(sf::IntRect(68, 0, 34, 17));
                break;
            case 3:
                m_model->spr.setTextureRect(sf::IntRect(34, 0, 17, 34));
                break;
            case 2:
                m_model->spr.setTextureRect(sf::IntRect(51, 0, 17, 34));
                break;
            default:
                break;
        }

        window().draw(m_model->spr);

    }

};
