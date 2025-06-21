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
			sprite.setPosition({ 210.0f, 120.0f });
            sprite.setScale({ 4.0f, 4.0f }); //Scale the front texture
        }
        else
        {
            sprite.setTexture(backTexture);
            sprite.setPosition({ 120.0f, 210.0f });
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
	float cardSpacing = WIDTH / 9.0f; //Spacing between cards
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

	sf::Texture cardFrontTextureTomato;
    if (!cardFrontTextureTomato.loadFromFile("assets/card_tomato.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
	}
	sf::Texture cardFrontTextureGrapes;
    if (!cardFrontTextureGrapes.loadFromFile("assets/card_grapes.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
    }

    std::vector<Card> cards;
	int textureId = 0;

	//float cardWidth = cardBackTexture.getSize().x * 4.0f;
    //float cardHeight = cardBackTexture.getSize().y * 4.0f; 
	//float startX = (WIDTH - (COLUMNS * cardWidth + (COLUMNS - 1) * cardSpacing)) / 2.0f;
    //float startY = (HEIGHT - (ROWS * cardHeight + (ROWS - 1) * cardSpacing)) / 2.0f;

	//std::vector<sf::Texture> cardFrontTextures = { cardFrontTextureTomato, cardFrontTextureGrapes };
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            const sf::Texture& frontTexture = (textureId % 2 == 0) ? cardFrontTextureTomato : cardFrontTextureGrapes;
            cards.emplace_back(cardBackTexture, frontTexture, textureId);
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