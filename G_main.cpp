#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

#include "G_map.h"

#include "G_player.h"

int main()
{
    RenderWindow window(VideoMode(640, 480), "Garbage 0.0.1");

    // float currentFrame;
    Clock clock;

    Player player("car.png", 100, 100, 32.0, 15.0);

    Image mapImage;
    mapImage.loadFromFile("images/maap.png");
    Texture mapTexture;
    mapTexture.loadFromImage(mapImage);
    Sprite mappSprite;
    mappSprite.setTexture(mapTexture);


    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;

        Event event;

        while(window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // управление персом
        if ((Keyboard::isKeyPressed(Keyboard::Right))) {
			player.dir = 0;
            player.speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Left))) {
			player.dir = 1;
            player.speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up))) {
			player.dir = 3;
            player.speed = 0.1;
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down))) {
			player.dir = 2;
            player.speed = 0.1;
		}

		player.Update(time);

        window.clear();

        // рисуем карту
        for (int i = 0; i < H_MAP; i++)
        for (int j = 0; j < W_MAP; j++)
        {
            if (tileMap[i][j] == ' ')
                mappSprite.setTextureRect(IntRect(0,0,32,32));

            if (tileMap[i][j] == 'H')
                mappSprite.setTextureRect(IntRect(32, 0, 32, 32 ));

            if (tileMap[i][j] == 'G')
                mappSprite.setTextureRect(IntRect(64, 0, 32, 32));

            if (tileMap[i][j] == 'S')
                mappSprite.setTextureRect(IntRect(96, 0, 32, 32));

            if (tileMap[i][j] == 'T')
                mappSprite.setTextureRect(IntRect(128, 0, 32, 32));

            mappSprite.setPosition(j * 32, i * 32);
            window.draw(mappSprite);
        }

        window.draw(player.sprite);
        window.display();
    }

    return 0;
}
