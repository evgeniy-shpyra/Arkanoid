#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;


void start_of_game(RenderWindow& window, Sprite& map, Sprite& platform, Sprite& ball,vector<RectangleShape> Bricks) {
	bool Start = 0;

	Font font;
	font.loadFromFile("18682.ttf");

	Text start("PRESS SPACE TO START", font, 30);
	start.setStyle(sf::Text::Bold);
	start.setPosition(248, 250);
	start.setOutlineThickness(0.5);
	start.setOutlineColor(Color(0, 0, 0));
	start.setFillColor(Color(209, 182, 0)); 


	while (!Start)
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Space)) 
			Start = 1;
		
		window.clear();
		window.draw(map);
		window.draw(platform);
		window.draw(ball);
		window.draw(start);

		for (int i = 0; i < Bricks.size(); i++)
			window.draw(Bricks[i]);

		window.display();
	}

	window.clear();
}
