#include <iostream>
#include <SFML/Graphics.hpp>

int main()
{
    unsigned int width = 800;
    unsigned int height = 640;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ width, height }), "FliMo");

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

		//Rendering code Color sky blue
		window->clear(sf::Color(135, 206, 235)); // Sky blue color

		//Drawing code would go here

		window->display();
    }

    delete window;
    return 0;
}