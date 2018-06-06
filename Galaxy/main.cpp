#include<iostream>
#include<list>
#include<SFML\Graphics.hpp>

using namespace sf;

Sprite backgroundFrame;
Texture backgroundTexture;

std::list<Sprite> assetFrame;
std::list<Texture> assetTexture;

std::list<Sprite> shipFrame;
std::list<Texture> shipTexture;

std::list<Sprite> enemyFrame;
std::list<Texture> enemyTexture;

std::list<Sprite> friendFrame;
std::list<Texture> friendTexture;

std::list<Sprite> itemFrame;
std::list<Texture> itemTexture;

std::list<Sprite> controlFrame;
std::list<Texture> controlTexture;

std::list<Sprite> bulletFrame;
std::list<Texture> bulletTexture;


int main()
{
	RenderWindow gw(VideoMode(960, 540), "Galaxy");
	gw.setFramerateLimit(60);

	while (gw.isOpen())
	{
		Event ge;

		while (gw.pollEvent(ge))
		{
			if (ge.type == Event::Closed)
			{
				gw.close();
			}
		}

		//// Draw ////
		gw.clear();
		gw.draw();
		gw.display();
	}
	
	return 0;
}