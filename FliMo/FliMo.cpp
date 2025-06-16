#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    unsigned int WIDTH = 1200;
    unsigned int HEIGHT = 960;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ WIDTH, HEIGHT }), "FliMo");
	window->setFramerateLimit(60);

	bool isPressed = false;

	bool isFlipped = false;

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
	sf::Sprite cardBackSprite1(cardBackTexture);
    cardBackSprite1.setPosition({ (WIDTH / 9.0f), (cardBackTexture.getSize().y * 4.0f) });
    cardBackSprite1.setScale({ 4.0f, 4.0f }); //Scale the sprite to make it larger
	sf::Sprite cardBackSprite2(cardBackTexture);
    cardBackSprite2.setPosition({ (WIDTH / 9.0f * 3.0f), (cardBackTexture.getSize().y * 4.0f) });
	cardBackSprite2.setScale({ 4.0f, 4.0f }); //Scale the sprite to make it larger

	sf::Texture cardFrontTextureTomato;
    if (!cardFrontTextureTomato.loadFromFile("assets/card_tomato.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
	}

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
					sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
					sf::Vector2f worldPos = window->mapPixelToCoords(mousePos);

                    if (cardBackSprite1.getGlobalBounds().contains(worldPos))
                    {
                        isFlipped = !isFlipped;
                        if (isFlipped)
                        {
                            cardBackSprite1.setTexture(cardFrontTextureTomato);
                            cardBackSprite1.setScale({ 4.0f, 4.0f }); //Ensure the front texture is also scaled
                        }
                        else
                        {
                            cardBackSprite1.setTexture(cardBackTexture);
                            cardBackSprite1.setScale({ 4.0f, 4.0f }); //Reset to the back texture scale
						}
						std::cout << "Card flipped!" << std::endl;
					}
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
		window->draw(cardBackSprite1);
        window->draw(cardBackSprite2);

		window->display();
    }

    delete window;
    return 0;
}