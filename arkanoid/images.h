

class Images {
private:
	Image map_image;
	Texture map, play; 

public:
	Sprite s_map, s_play;

	void DownloadImages() {
		map_image.loadFromFile("images/map7.png");
		map.loadFromImage(map_image);
		s_map.setTexture(map);
		s_map.setTextureRect(IntRect(0, 0, 950, 600)); 

		play.loadFromFile("images/play.png");
		s_play.setTexture(play);
		s_play.setPosition(420, 170);
	}
};



