#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

class Card
{
public:
    sf::Sprite sprite;
    sf::Texture frontTexture;
    bool isFlipped = false;
    int id = 0; //Unique identifier for the card

    // Parameterized constructor to initialize the card with a front texture and ID  
    Card(const sf::Texture& _backTexture, const sf::Texture& _frontTexture, int _id)
        : sprite(_backTexture), frontTexture(_frontTexture), id(_id)
    {
        // No need to set the texture again, already set in initializer list
    }

    void Flip(const sf::Texture& backTexture)
    {
        isFlipped = !isFlipped;
        if (isFlipped)
        {
            sprite.setTexture(frontTexture);
            sprite.setScale({ 4.0f, 4.0f }); //Scale the front texture
        }
        else
        {
            sprite.setTexture(backTexture);
            sprite.setScale({ 4.0f, 4.0f }); //Reset to the back texture scale
        }
    }
};

int main()
{
    unsigned int WIDTH = 1200;
    unsigned int HEIGHT = 960;
    const int ROWS = 4;
    const int COLUMNS = 4;
	float cardSpacingWidth = WIDTH / 9.0f; //Spacing between cards
	float cardSpacingHeight = HEIGHT / 9.0f; //Spacing between cards
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

    std::vector<sf::Texture> cardFrontTextures(8);
    const char* textureFiles[8] = {
        "assets/card_tomato.png",
        "assets/card_grapes.png",
        "assets/card_apple.png",
        "assets/card_banana.png",
        "assets/card_orange.png",
        "assets/card_hippo.png",
        "assets/card_penguin.png",
        "assets/card_frog.png"
    };

    for (int i = 0; i < 8; ++i)
    {
        if (!cardFrontTextures[i].loadFromFile(textureFiles[i]))
        {
            std::cerr << "Failed to load texture: " << textureFiles[i] << std::endl;
            return -1;
        }
	}

    std::vector<Card> cards;
	int textureId = 0;

    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
			const sf::Texture& frontTexture = cardFrontTextures[textureId % cardFrontTextures.size()];
            cards.emplace_back(cardBackTexture, frontTexture, textureId);

            // Calculate position for this card
            float cardWidth = cardBackTexture.getSize().x * 4.0f;
            float cardHeight = cardBackTexture.getSize().y * 4.0f;
            float startX = WIDTH / 9.0f;
			float startY = HEIGHT / 9.0f;
            float x = startX + column * (cardWidth + cardSpacingWidth);
            float y = startY + row * (cardHeight + cardSpacingHeight);

            cards.back().sprite.setPosition({ x, y });
            cards.back().sprite.setScale({ 4.0f, 4.0f });

            ++textureId;
        }
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

                    for (auto& card : cards) {
                        if (card.sprite.getGlobalBounds().contains(worldPos)) {
                            card.Flip(cardBackTexture);
                            std::cout << "Card flipped!" << std::endl;
                            break;
                        }
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

        for (const auto& card : cards) {
            window->draw(card.sprite);
        }

		window->display();
    }

    delete window;
    return 0;
}