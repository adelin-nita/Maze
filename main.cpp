#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

#define n 10

// Declararea variabilelor globale
sf::Sprite player;  // imaginea (sprite ul) jucatorului
sf::VertexArray pereti(sf::Lines);  // peretele labirintului
float viteza = 140.0f;  // viteza de deplasare a jucatorului

void handleEvents(sf::Time timpRamasUltimulFrame)
{
    // facem jucatorul sa se miste 
    sf::Vector2f playerMove(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    
    {
        playerMove += sf::Vector2f(0.0f, -0.8f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerMove += sf::Vector2f(1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerMove += sf::Vector2f(0.0f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerMove += sf::Vector2f(-0.8f, 0.0f);
    }

    
    player.move(playerMove * timpRamasUltimulFrame.asSeconds() * viteza);
}

void update(sf::Time timpRamasUltimulFrame)
{
    int a[n][n];
    sf::Vector2f playerMove(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))    
    {
        playerMove += sf::Vector2f(0.0f, -0.8f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerMove += sf::Vector2f(1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerMove += sf::Vector2f(0.0f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerMove += sf::Vector2f(-0.8f, 0.0f);
    }

     sf::Vector2f pozitie = player.getPosition() + playerMove * timpRamasUltimulFrame.asSeconds() * viteza;

     int posX = pozitie.x / 80.0f;
     int posY = pozitie.y / 80.0f;

     if (a[posX][posY] == 0)
     {
         player.move(playerMove * timpRamasUltimulFrame.asSeconds() * viteza);
     }


}

void render(sf::RenderWindow& window, int a[n][n])
{
      
    
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        { 
            if (a[i][j] == 1)  // daca exista un perete (1 în matrice)
            {
                //  liniile verticale
                pereti.append(sf::Vertex(sf::Vector2f(j * 80.0f, i * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f(j * 80.0f, (i + 1) * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f((j + 1) * 80.0f, i * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f((j + 1) * 80.0f, (i + 1) * 80.0f), sf::Color::Green));

                //  liniile orizontale
                pereti.append(sf::Vertex(sf::Vector2f(j * 80.0f, i * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f((j + 1) * 80.0f, i * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f(j * 80.0f, (i + 1) * 80.0f), sf::Color::Green));
                pereti.append(sf::Vertex(sf::Vector2f((j + 1) * 80.0f, (i + 1) * 80.0f), sf::Color::Green));  
            }
        }
    }

    // desenam peretii 
    window.draw(pereti);
}

int main()
{
    int a[n][n];  // matricea labirintului

    
    std::ifstream f("matrice.in");
    if (!f)  
    { 
        std::cout << "Matricea nu s-a deschis !" << std::endl;
        return -1;
    }

    // incarcam matricea din fisier 
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            f >> a[i][j];
        }
    }

    // cream fereastra jocului
    sf::RenderWindow window(sf::VideoMode(800, 800), "Adelin's Maze");

    // setam iconita pentru jocul nostru
    sf::Image icon;
    icon.loadFromFile("imagine/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // incarcam imaginea jucatorului
    sf::Texture PlayerTexture;
    PlayerTexture.loadFromFile("imagine/jucator.jpg");
    player.setTexture(PlayerTexture);

    // pozitia initiala a jucatorului
    player.setScale(0.1f, 0.1f);
    player.setPosition(110.0f, 50.0f);

    
    sf::Clock clock;

    while (window.isOpen())
    {
        // obtinem timpul scurs de la ultimul frame
        sf::Time timpRamasUltimulFrame = clock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        
        handleEvents(timpRamasUltimulFrame);

        update(timpRamasUltimulFrame);

        // stergem fereastra
        window.clear();

        // incarcam jocul
        render(window, a);

        // desenam jucatorul
        window.draw(player);

        // afisam continutul pe ecran
        window.display();
    }

    return 0;
}
