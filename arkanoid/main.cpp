#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath> 
#include <time.h>
#include <fstream>
#include "menu.h" 
#include "images.h" 
#include "text.h" 
#include "start_of_game.h" 

constexpr unsigned WINDOW_WIDTH = 950;
constexpr unsigned WINDOW_HEIGHT = 600;

constexpr unsigned sizePlatW = 151;
constexpr unsigned sizePlatH = 28;

constexpr unsigned sizeBall = 24;

constexpr unsigned sizeBrickW = 80;
constexpr unsigned sizeBrickH = 30;

using namespace sf;
using namespace std;

bool isRestart = 0;

class Brick {
private:
	float x, y, w, h;
	int health, level;

public:
	RectangleShape rect;

	void creature(float x, float y, int health) {
		this->x = x;
		this->y = y;
		this->w = sizeBrickW;
		this->h = sizeBrickH;
		this->health = health;
		level = health;
		rect.setSize(Vector2f(w, h));
		rect.setOutlineThickness(1);
		rect.setPosition(x, y);
		rect.setOutlineColor(Color(53, 27, 26));
		ColorBreck();
	}

	int GetLevel() {
		return level;
	}
	
	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

	friend class Ball;
private:

	int Health() {
		health--;
		return health;
	}

	void ColorBreck() {
		if (health == 1)
			rect.setFillColor(Color(38, 211, 1));
		else if (health == 2)
			rect.setFillColor(Color(223, 128, 21));
		else if (health == 3)
			rect.setFillColor(Color(132, 0, 0));
	}

};

class Platform{
private:
	float speed;
	int dir;
	float x, y, dx, dy;
	int w, h;
	Texture texture;

public:

	Sprite sprite;
	Platform(Image& image, float x, float y, int w, int h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		texture.loadFromImage(image);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, this->w, this->h));
		sprite.setPosition(x, y);
		dir = 1;
		speed = 0;
	}

	void control() {
		speed = 0;
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			dir = -1;
			speed = 340;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			dir = 1;
			speed = 340;
		}

	}

	void update(float time) {
		switch (dir) {
		case 1: dx = speed; dy = 0; break;
		case -1: dx = -speed; dy = 0; break;
		}

		x += dx * time;

		sprite.setPosition(x, y);
		tachWithMap();
	}

	float GetUpdate() {
		return speed * dir;
	}

	friend class Ball;
private:

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

	void tachWithMap() {
		if (x > WINDOW_WIDTH - sizePlatW - 1)
			x = WINDOW_WIDTH - sizePlatW - 1;
		if (x < 1)
			x = 1;
	}
};

class Ball {
private:

	int dir, playerScore, lives;
	float alpha;
	float x, y, dx, dy;
	int w, h;
	float speed;
	Texture texture;
public: 
	Sprite sprite;

	Ball(Image& image, float x, float y, int w, int h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		texture.loadFromImage(image);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, this->w, this->h));
		sprite.setPosition(x, y);
		speed = 400;

		playerScore = 0;
		lives = 3;
		
		Start();
	}

	void update(float time) {
		
		x += dx * time;
		y += dy * time;

		sprite.setPosition(x, y);

		touchWithMap();
	}

	int GetPlayerScore() {
		return playerScore;
	}

	int GetLivesBall() {
		return lives;
	}

	void SetLivesBall(int lives) {
		this->lives = lives;
	}
	

	void TouchWithBriсk(vector<vector<Brick>>& bricks) {
		for(int i = 0; i < bricks.size(); i++)
			for (int j = 0; j < bricks[i].size(); j++) {
				if (bricks[i][j].getRect().contains(x + 12, y)) {
					vecUp();
					Kill_Breck(bricks[i], j);
				}
				else if (bricks[i][j].getRect().contains(x + 12, y + 24)) {
					vecBottom();
					Kill_Breck(bricks[i], j);
				}
				else if (bricks[i][j].getRect().contains(x, y + 12)) {
					vecLeft();
					Kill_Breck(bricks[i], j);
				}
				else if (bricks[i][j].getRect().contains(x + 24, y + 12)) {
					vecRight();
					Kill_Breck(bricks[i], j);
				}
			}
	}
	void TouchWithPlatform(Platform& platfprm) {
		if (platfprm.getRect().intersects(getRect())) {
			if ((platfprm.GetUpdate() > 0 && (dir == 3)) || (platfprm.GetUpdate() < 0 && (dir == 4))) 
				alpha = 1.16; //67
			else if ((platfprm.GetUpdate() > 0 && (dir == 4)) || (platfprm.GetUpdate() < 0 && (dir == 3))) 
				alpha = 0.52; //30		
			else
				alpha = 0.78; //45

			if (platfprm.getRect().contains(x + 12, y + 24))
				vecBottom();
			else if (platfprm.getRect().contains(x, y + 12))
				vecLeft();
			else if (platfprm.getRect().contains(x + 24, y + 12))
				vecRight();
		}
	}

	friend class Brick;
private:

	void Start() {
		x = 300 + sizePlatW / 2;
		y = 536;
		dir = 4;
		alpha = 1.39;
		vecBottom();
	}

	void touchWithMap()//ф-ция взаимодействия с картой
	{
		// Вылетел в низ
		if (y > WINDOW_HEIGHT) {
			lives--;
			Start();
		}

		//прво
		if (x > WINDOW_WIDTH - sizeBall) vecRight();

		//лево
		if (x < 0) vecLeft();

		//верх
		if (y < 0) vecUp();
	}

	float directionX(float alpha) {
		return speed * cos(alpha);
	}

	float directionY(float alpha) {
		return speed * sin(alpha);
	}

	void vecUp() {
		if (dir == 1) {
			dir = 4;
			dx = directionX(alpha);
			dy = directionY(alpha);
		}
		if (dir == 2) { 
			dir = 3;
			dx = -directionX(alpha);
			dy = directionY(alpha);
		}
		
	}

	void vecBottom() {
		if (dir == 4) {
			dir = 1;
			dx = directionX(alpha);
			dy = -directionY(alpha);
		}
		if (dir == 3) { 
			dir = 2;
			dx = -directionX(alpha);
			dy = -directionY(alpha);
		}
	}

	void vecRight() {
		if (dir == 1) {
			dir = 2; 
			dx = -directionX(alpha);
			dy = -directionY(alpha);
		}
		if (dir == 4) {
			dir = 3;
			dx = -directionX(alpha);
			dy = directionY(alpha);
		}
	}

	void vecLeft() {
		if (dir == 3) { 
			dir = 4; 
			dx = directionX(alpha);
			dy = directionY(alpha);
		}
		if (dir == 2) {
			dir = 1;
			dx = directionX(alpha);
			dy = -directionY(alpha);
		}
	}

	void Kill_Breck(vector<Brick>& bricks, int i) {
		if (bricks[i].Health() == 0) {
			playerScore += bricks[i].GetLevel();
			bricks.erase(bricks.begin() + i);
		}
	}

	FloatRect getRect() {
		return FloatRect(x, y, w, h);
	}

};


void MakingBrick(int x, int y, vector<vector<Brick>>& bricks) {
	int health = 3;

	for (int i = 0; i < bricks.size(); i++) {
		for (int j = 0; j < bricks[i].size(); j++)
			bricks[i][j].creature(x + (sizeBrickW + 2) * j, y + (sizeBrickH + 2) * i, health);
			if(i != 1 && i != 3)
				health--;
	}
}

void WriteResult(Clock& allTime, int points) { 
	ofstream fout;
	ifstream fin;
	string text;
	float time = allTime.getElapsedTime().asSeconds();
	if (time > 60) {
		time = time / 60.;
		text = " min";
	}
	else
		text = " sec";

	fout.open("points.txt", ios_base::app);
	if (fout.is_open()) {
		fout.precision(2);
		fout << "Points:" << points << "    Time of the game: " << fixed << time << text << endl; 
		fout.close();
	}
}


bool launchGame(RenderWindow& window) {

	if (!isRestart) {
		if (menu(window)) {
			return 0;
		}
	}
	isRestart = 0;

	Image plat_image;
	plat_image.loadFromFile("images/platform6.png");
	plat_image.createMaskFromColor(Color(255, 255, 255));

	Image ball_image;
	ball_image.loadFromFile("images/ball2.png");
	ball_image.createMaskFromColor(Color(255, 255, 255));

	Platform platfprm(plat_image, 300, 560, sizePlatW, sizePlatH);
	Ball ball(ball_image, 300 + sizePlatW/2, 536, sizeBall, sizeBall);

	Images img; 
	img.DownloadImages();
	Texts text;
	
	
	vector<vector<Brick>> bricks(4, vector<Brick>(11));
	vector<RectangleShape> rect;

	MakingBrick(24, 17, bricks);

	//Старт игры 
	for (int i = 0; i < bricks.size(); i++) 
		for (int j = 0; j < bricks[i].size(); j++)
			rect.push_back(bricks[i][j].rect);
	start_of_game(window, img.s_map, platfprm.sprite, ball.sprite, rect);
	rect.clear();
	//---------

	Clock clock, allTime;
	bool PAUSE = 0, STOP = 0, write = 0;

	while (window.isOpen()) {

		float time = clock.getElapsedTime().asSeconds();  
		clock.restart();
		Event event;

		while (window.pollEvent(event))
			if (event.type == Event::Closed) {
				window.close();
				return 0;
			}


		if (!STOP) {
			platfprm.control();
			platfprm.update(time); 
			ball.update(time);   
			ball.TouchWithPlatform(platfprm);
			ball.TouchWithBriсk(bricks);
		}

		//----Пауза----------------------------------
		if (PAUSE) 
			img.s_play.setColor(Color::White);
		

		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			STOP = 1;
			PAUSE = 1;
		}

		if (IntRect(420, 170, 145, 165).contains(Mouse::getPosition(window))) {
			img.s_play.setColor(Color(214, 223, 32));
			if (Mouse::isButtonPressed(Mouse::Left)) {
				STOP = 0;
				PAUSE = 0;
			}
		}

		window.clear();
		window.draw(img.s_map);

		for (int i = 0; i < bricks.size(); i++)
			for (int j = 0; j < bricks[i].size(); j++) 
				window.draw(bricks[i][j].rect); 
			

		ostringstream ScoreString, LivesBall;
		ScoreString << ball.GetPlayerScore();
		LivesBall << ball.GetLivesBall();
		text.points.setString("Lives:" + LivesBall.str());
		text.lives.setString("Points:" + ScoreString.str());

		window.draw(text.lives);
		window.draw(text.points);
		window.draw(platfprm.sprite);
		window.draw(ball.sprite);

		if (PAUSE)
			window.draw(img.s_play);



		if (ball.GetLivesBall() == 0 || (bricks[0].empty() && bricks[1].empty() && bricks[2].empty() && bricks[3].empty())) {
			STOP = 1;
			window.draw(text.menu);
			window.draw(text.restart);
			if (ball.GetLivesBall() == 0)
				window.draw(text.gameover);
			else 
				window.draw(text.victory);

			if (!write) {
				WriteResult(allTime, ball.GetPlayerScore()); 
				write = 1;
			}

			if (IntRect(376, 240, 183, 60).contains(Mouse::getPosition(window))) {
				text.menu.setFillColor(Color(191, 0, 5));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					if (menu(window)) {
						return 0;
					}
					return 1;
				}
			}
			else
				text.menu.setFillColor(Color(247, 228, 4));


			if (IntRect(308, 315, 324, 60).contains(Mouse::getPosition(window))) {
				text.restart.setFillColor(Color(191, 0, 5));
				if (Mouse::isButtonPressed(Mouse::Left)) {
					isRestart = 1;
					allTime.restart(); 
					write = 0;
					return 1;
				}
			}
			else
				text.restart.setFillColor(Color(247, 228, 4));
		}

		window.display();
	}
}


int main() {
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid", Style::Close);
	while (launchGame(window));

	return 0;
}