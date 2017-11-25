#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test");

	sf::Texture texture;
	sf::Sprite sprite;

	if (!texture.loadFromFile("../../assets/textures/zoimbie1_hold.png"))
    {
        std::cout << "Error al cargar zoimbie1_hold1.png" << std::endl;
    }
	sprite.setTexture(texture);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y);
		}

		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
	}

	return 0;
}
