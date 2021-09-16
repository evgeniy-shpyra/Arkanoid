#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>


using namespace sf;
using namespace std;

void Table(RenderWindow& window, Sprite& sprite, Font& font) {

	ifstream fin;
	bool isOpen = 1;
	Text back("BACK", font, 30);
	back.setStyle(sf::Text::Bold);
	back.setPosition(10, 557);
	back.setOutlineThickness(0.5);
	back.setOutlineColor(Color(0, 0, 0));
	back.setFillColor(Color(209, 182, 0));

	Text result;
	int x = 4;
	result.setFont(font);
	result.setCharacterSize(22);
	result.setFillColor(Color(209, 182, 0));
	result.setPosition(210, 10);


	string str;
	string s = "\t\t\t\tHistory of all games\n\n";

	fin.open("points.txt");
	if (!fin.is_open()) {
		s = "EROR";
	}
	else {
		while (!fin.eof()) {
			str.clear();
			getline(fin, str);
			s = s + str + "\n";
		}
		fin.close();
	}

	while (isOpen)
	{
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}

		back.setFillColor(Color(209, 182, 0));

		if (IntRect(10, 557, 98, 30).contains(Mouse::getPosition(window))) {
			back.setFillColor(Color(191, 0, 5));
			if (Mouse::isButtonPressed(Mouse::Left))
				isOpen = 0;
		}

		result.setString(s);

		window.clear();
		window.draw(sprite);
		window.draw(result);
		window.draw(back);
		window.display();
	}
	window.clear();
}