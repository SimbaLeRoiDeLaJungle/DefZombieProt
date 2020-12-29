#include <SFML/Graphics.hpp>
#include "SDAA.h"
#include "GameEngine.h"
#include "TextureHolder.h"
#include "LoadingScreen.h"
#include "GameRender.h"

int main()
{

    sf::RenderWindow app(sf::VideoMode(800, 600), "Zombies Defenses");
    app.setFramerateLimit(50);


    TextureHolder textures;
    textures.load(Textures::CHARACTER,"images/perso.png");
    textures.load(Textures::TILESET,"images/tiles.png");
    textures.load(Textures::ZOMBIE,"images/zombie.png");
    sf::Font font;
    if(!font.loadFromFile("font/Motorblock.ttf"))
        return EXIT_FAILURE;

    sf::Mouse mouse;
    sf::Vector2i mousePos;


    GameEngine gameEngine;
    gameEngine.importTexture(textures);
    gameEngine.addCharacter(0,0);
    gameEngine.addCharacter(2,2);
    gameEngine.addZombie(15,15);

    LoadingScreen loadingScreen(800,600,font);
    sf::Thread loadingThread(&GameEngine::loadGame,&gameEngine);
    loadingThread.launch();
    GameRender gameRender(2000,2000);


    while (app.isOpen())
    {
        mousePos = mouse.getPosition(app);
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }

        if(gameEngine.getIsReady())
        {
            gameEngine.leftButton(mouse.isButtonPressed(sf::Mouse::Left),mousePos);
            gameEngine.rightButton(mouse.isButtonPressed(sf::Mouse::Right),mousePos);


            gameEngine.update();


            gameRender.setTexture(gameEngine.getRender());
            app.clear();
            app.draw(gameRender);
            app.display();
        }
        else
        {
            loadingScreen.update();

            app.clear();
            app.draw(loadingScreen);
            app.display();
        }

    }

    return EXIT_SUCCESS;
}
