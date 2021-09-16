#include <SFML/Graphics.hpp>
#include "table.h" 

using namespace sf;
using namespace std;


bool menu(RenderWindow& window) { 

	Font font;  
	font.loadFromFile("18682.ttf");

	Text start("START", font, 60);
	Text exit("EXIT", font, 45);
	Text arkanoid("ARKANOID", font, 110);
	Text table("RESULTS TABLE", font, 25); 

	Texture fon;
	fon.loadFromFile("images/menu3.png"); 
	Sprite spr_menu(fon);

	Text back("BACK", font, 30);
	back.setStyle(sf::Text::Bold);
	back.setPosition(10, 557);
	back.setOutlineThickness(0.5);
	back.setOutlineColor(Color(0, 0, 0));
	back.setFillColor(Color(209, 182, 0));

	table.setStyle(sf::Text::Bold);
	table.setPosition(695, 565);
	table.setOutlineThickness(0.5);
	table.setOutlineColor(Color(0, 0, 0));

	start.setStyle(sf::Text::Bold);
	start.setPosition(352, 250);
	start.setOutlineThickness(0.5);
	start.setOutlineColor(Color(0, 0, 0));

	exit.setStyle(sf::Text::Bold);
	exit.setPosition(400, 320);
	exit.setOutlineThickness(0.5);
	exit.setOutlineColor(Color(0, 0, 0));

	
	arkanoid.setStyle(sf::Text::Bold);
	arkanoid.setPosition(158, 20);
	arkanoid.setFillColor(Color(3, 3, 201));
	arkanoid.setOutlineThickness(1);
	arkanoid.setOutlineColor(Color(0, 0, 0));
	

	bool isExit = 0 ,isMenu = 1, openTable = 0; 
	int menuNum = 0;
	


	while (isMenu)
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}


		exit.setFillColor(Color(209, 182, 0));
		start.setFillColor(Color(209, 182, 0));
		table.setFillColor(Color(209, 182, 0));

		menuNum = 0;
		window.clear();

		if (IntRect(352, 250, 230, 55).contains(Mouse::getPosition(window))) {
			start.setFillColor(Color(191, 0, 5));
			menuNum = 1;
		}
		else if (IntRect(400, 320, 117, 45).contains(Mouse::getPosition(window))) { 
			exit.setFillColor(Color(191, 0, 5));
			menuNum = 2;
		}
		else if (IntRect(695, 565, 245, 25).contains(Mouse::getPosition(window))) {
			table.setFillColor(Color(191, 0, 5));
			menuNum = 3;
		}

		if (Mouse::isButtonPressed(Mouse::Left)){
			if (menuNum == 1)
				isMenu = 0;
			else if (menuNum == 2) {
				window.close(); 
				isMenu = 0;
				isExit = 1;
			}
			else if (menuNum == 3)
				Table(window, spr_menu, font);
		}

		window.draw(spr_menu);
		window.draw(start);
		window.draw(exit);
		window.draw(table);
		window.draw(arkanoid);
		window.display();
	}
	
	return isExit;
}

