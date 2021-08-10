#pragma once

class Controller
{
    private:
    Model *m_model;
    View *v_view;

    public:
    sf::Event c_event;
    int backtime;
    float time;
    sf::Clock clock;

    public:
    Controller(Model *model, View *view)
    {
        m_model = model;
        v_view = view;
        backtime = 20;
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

    sf::Clock gameClock;

    void Reset()
    {
        gameClock.restart();
        v_view->window().close();
    }

    void Run()
    {

        while(v_view->window().isOpen())
        {
            time = clock.getElapsedTime().asMicroseconds();

            clock.restart();

            sf::Time elapsed = gameClock.getElapsedTime();

            std::cout << elapsed.asSeconds() << std::endl;

            time = time / 800;

            if ((elapsed.asSeconds() > 10.f) && (m_model->magicNumber == 13))
            {
                Reset();
            }

            while(v_view->window().pollEvent(c_event))
            {
                if (c_event.type == sf::Event::Closed)
                {
                    v_view->window().close();
                    gameClock.restart();
                }
            }

            ControllPlayer(time);

            v_view->Render();

        }

    }

};
