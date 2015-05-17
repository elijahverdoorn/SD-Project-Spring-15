#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <string>

main()
{
    sf::RenderWindow *window = new sf::RenderWindow (sf::VideoMode(500, 500), "SFML window");
    sf::Font font;
    if (!font.loadFromFile("Cantarell-Regular.otf"))
        return EXIT_FAILURE;
    std::string userInput;
    sf::Text userText(userInput, font, 50);   

    while (window->isOpen())
    {
        // Process events
        sf::Event event;
        while (window->pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window->close();
            //is a text entered event
            if (event.type == sf::Event::TextEntered)
            {
                    if (event.text.unicode < 128)
                    {
                           if (event.text.unicode == 8)
                           {
                               if (userInput.size() > 0)
                               {
                                   userInput.pop_back();
                               }
                           }else{
                               userInput += static_cast<char>(event.text.unicode);
                           }
                           // std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
                        userText.setString(userInput);
                        std::cout << userInput << std::endl;
                    }
            }
        }
        // Clear screen
        window->clear();
        window->draw(userText);
        // Update the window
        window->display();
    }
    return EXIT_SUCCESS;
}
