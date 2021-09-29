#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    int width = 900;
    int height = 900;
    int block = 20;
    int point = 200;
    int characterPositionX = 0;
    int characterPositionY = 0;

    sf::RenderWindow window(sf::VideoMode(width, height+40), "Altın Toplama");

    sf::RectangleShape shapeList[block][block];
    sf::Text textList[block][block];

    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text;
    text.setFont(font);
    text.setString("Puan : " + point);
    text.setCharacterSize(block);
    text.setFillColor(sf::Color::White);
    text.setPosition(0,height);

    sf::RectangleShape character(sf::Vector2f(width/block, height/block));
    sf::Texture texture;
    texture.loadFromFile("images/character.png");
    character.setTexture(&texture);
    character.setPosition(characterPositionX,characterPositionY);


    for(int i = 0; i < block; i++) {
        for(int y = 0; y < block ; y++) {
            sf::RectangleShape rectangle(sf::Vector2f(width/block, height/block));
            if(i % 2 == 0) {
                if(y % 2 == 0) {
                    rectangle.setFillColor(sf::Color::Blue);
                } else {
                    rectangle.setFillColor(sf::Color::Red);
                }

            } else {
                if(y % 2 == 0) {
                    rectangle.setFillColor(sf::Color::Red);
                } else {
                    rectangle.setFillColor(sf::Color::Blue);
                }
            }
            rectangle.setPosition( (i * (width/block)), (y * (height/block)));
            shapeList[i][y] = rectangle;
        }
    }

    srand(time(0));
    int goldCount = (block * block) * (rand() % 10 + 10) / 100;
    sf::CircleShape goldList[goldCount];

    for(int i = 0; i < goldCount; i++) {
        int x = rand() % block;
        int y = rand() % block;

        sf::CircleShape shape((width / (block * 2)));
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition( (x * (width/block)), (y * (height/block )));

        goldList[i] = shape;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Left && characterPositionX >= (width / block)) {
                    characterPositionX = characterPositionX - (width / block);
                }
                if (event.key.code == sf::Keyboard::Right && characterPositionX < width - (block * 3)) {
                    characterPositionX = characterPositionX + (width / block);
                }
                if (event.key.code == sf::Keyboard::Up && characterPositionY >= (height / block)) {
                    characterPositionY = characterPositionY - (height / block);
                }
                if (event.key.code == sf::Keyboard::Down && characterPositionY < height - (block * 3)) {
                    characterPositionY = characterPositionY + (height / block);
                }
                character.setPosition(characterPositionX,characterPositionY);
                point = point - 5;
                for(int i = 0; i < goldCount; i++) {
                    sf::Vector2f goldPosition = goldList[i].getPosition();
                    if(goldPosition.x == characterPositionX && goldPosition.y == characterPositionY) {
                        point = point + (rand() % 4 + 1) * 5;
                        goldList[i].setPosition(-100,-100);
                    }
                }
                text.setString("Puan : " + point);
            }
        }

        window.clear();
        for(int i = 0; i < block; i++) {
            for(int y = 0; y < block ; y++) {
                window.draw(shapeList[i][y]);
                window.draw(textList[i][y]);
            }
        }
        for(int i = 0; i < goldCount; i++) {
            window.draw(goldList[i]);
        }
        window.draw(text);
        window.draw(character);

        window.display();
    }

    return 0;
}
