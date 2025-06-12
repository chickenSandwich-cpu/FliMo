#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    unsigned int width = 1200;
    unsigned int height = 960;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "FliMo");
	window->setFramerateLimit(60);

	sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/paper_background.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
	//Load the background the size of the window
	backgroundSprite.setScale({ static_cast<float>(width) / backgroundTexture.getSize().x,
        static_cast<float>(height) / backgroundTexture.getSize().y });

	sf::Texture cardBackTexture;
    if (!cardBackTexture.loadFromFile("assets/card_back.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
	}
	sf::Sprite sprite(cardBackTexture);
    sprite.setPosition({ (width - cardBackTexture.getSize().x) / 2.f, (height - cardBackTexture.getSize().y) / 2.f });
    sprite.setScale({ 4.0f, 4.0f }); //Scale the sprite to make it larger

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window->close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                {
                    window->close();
                }
            }
        }

		//Rendering code
		window->clear(sf::Color(135, 206, 235)); //Sky blue color

		//Drawing code would go here
		window->draw(backgroundSprite);
		window->draw(sprite);

		window->display();
    }

    delete window;
    return 0;
}