#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    unsigned int WIDTH = 1200;
    unsigned int HEIGHT = 960;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ WIDTH, HEIGHT }), "FliMo");
	window->setFramerateLimit(60);

	bool isPressed = false;

	sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/paper_background.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
	//Load the background the size of the window
	backgroundSprite.setScale({ static_cast<float>(WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(HEIGHT) / backgroundTexture.getSize().y });

	sf::Texture cardBackTexture;
    if (!cardBackTexture.loadFromFile("assets/card_back.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
	}
	sf::Sprite cardBackSprite(cardBackTexture);
    cardBackSprite.setPosition({ (WIDTH - cardBackTexture.getSize().x) / 2.f, (HEIGHT - cardBackTexture.getSize().y) / 2.f });
    cardBackSprite.setScale({ 4.0f, 4.0f }); //Scale the sprite to make it larger

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                if (!isPressed)
                {
                    std::cout << "Debug" << std::endl;
                }
                isPressed = true;
            }
            else
            {
                isPressed = false;
            }
        }

		//Rendering code
		window->clear(sf::Color(135, 206, 235)); //Sky blue color

		//Drawing code would go here
		window->draw(backgroundSprite);
		window->draw(cardBackSprite);

		window->display();
    }

    delete window;
    return 0;
}