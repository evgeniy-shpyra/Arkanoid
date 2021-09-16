#include <string>
using namespace sf;

class Texts { 
public:
	Font font;
	Text points, lives, menu, restart, gameover, victory;
public:
	Texts() { 
		font.loadFromFile("18682.ttf");
        
		points.setFont(font);
		points.setCharacterSize(25);
		points.setStyle(Text::Bold);
		points.setFillColor(Color(244, 244, 244));
		points.setPosition(4, 568); 

		lives.setFont(font);
		lives.setCharacterSize(25);
		lives.setStyle(Text::Bold);
		lives.setFillColor(Color(244, 244, 244));
		lives.setPosition(795, 568);

		menu.setFont(font); 
		menu.setCharacterSize(60);
		menu.setFont(font); 
		menu.setStyle(Text::Bold);
		menu.setPosition(376, 240);
		menu.setOutlineThickness(1);
		menu.setOutlineColor(Color(0, 0, 0));
		menu.setString("MENU");
		
		restart.setFont(font);
		restart.setCharacterSize(60);
		restart.setStyle(Text::Bold);
		restart.setPosition(308, 315);
		restart.setOutlineThickness(1);
		restart.setOutlineColor(Color(0, 0, 0));
		restart.setString("RESTART");

		gameover.setFont(font);
		gameover.setCharacterSize(95);
		gameover.setStyle(Text::Bold);
		gameover.setFillColor(Color(191, 0, 5));
		gameover.setOutlineThickness(1);
		gameover.setOutlineColor(Color(0, 0, 0));
		gameover.setPosition(166, 100);
		gameover.setString("GAME OVER");

		victory.setFont(font);
		victory.setCharacterSize(95);
		victory.setStyle(Text::Bold);
		victory.setFillColor(Color(38, 211, 1));
		victory.setOutlineThickness(1);
		victory.setOutlineColor(Color(0, 0, 0));
		victory.setPosition(224, 100);
		victory.setString("VICTORY");
	}
};
