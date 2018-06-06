#include<iostream>
#include<vector>
#include<SFML\Graphics.hpp>
#include "Resource.h"

using namespace sf;



Sprite backgroundFrame;
Texture *backgroundTexture;

std::vector<Sprite> assetFrame;
std::vector<Texture> assetTexture;

Sprite shipFrame;
Texture* shipTexture;

std::vector<Sprite> enemyFrame;
std::vector<Texture> enemyTexture;

std::vector<Sprite> friendFrame;
std::vector<Texture> friendTexture;

std::vector<Sprite> itemFrame;
std::vector<Texture> itemTexture;

std::vector<Sprite> controlFrame;
std::vector<Texture*> controlTexture;

std::vector<Sprite> bulletFrame;
std::vector<Texture> bulletTexture;

void setBackgroud()
{
	backgroundTexture = new Texture();
	backgroundTexture->loadFromFile(Resource::getbackground());
	backgroundFrame.setTexture(*backgroundTexture);
	backgroundFrame.setScale(0.5, 0.5);
}

void setControl()
{
	for (int i = 0; i < 4; i++)
	{
		Texture *tempt = new Texture();
		tempt->loadFromFile(Resource::getcontrol(i));
		controlTexture.push_back(tempt);
		Sprite temp;
		temp.setTexture(*controlTexture.at(i));
		temp.setScale(0.5, 0.5);
		controlFrame.push_back(temp);
	}	
}

void drawControl(RenderWindow &gw)
{
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			controlFrame[0].setPosition(91, 355);
			break;
		case 1:
			controlFrame[1].setPosition(91, 490-39);
			break;
		case 2:
			controlFrame[2].setPosition(40, 405);
			break;
		case 3:
			controlFrame[3].setPosition(137, 405);
			break;
		default:
			break;
		}
		gw.draw(controlFrame[i]);
	}
}

void animateShip()
{
		shipTexture = new Texture();
		shipTexture->loadFromFile(Resource::getshipAnimate());
		controlTexture.push_back(shipTexture);
		shipFrame.setTexture(*shipTexture);
		shipFrame.setScale(0.5, 0.5);	
}

void createShip()
{
	shipTexture = new Texture();
	shipTexture->loadFromFile(Resource::getshipAnimate());
	controlTexture.push_back(shipTexture);
	shipFrame.setTexture(*shipTexture);
	shipFrame.setScale(0.5, 0.5);
	shipFrame.setPosition(10,250);
}
void drawMainShip(RenderWindow &gw,float x, float y)
{
	if()
	shipFrame.move(x, y);
	gw.draw(shipFrame);
}
int main()
{
	RenderWindow gw(VideoMode(960, 540), "Galaxy");
	gw.setFramerateLimit(60);
	setBackgroud();
	setControl();
	createShip();

	Vector2f shipmov;
	while (gw.isOpen())
	{
		animateShip();
		Vector2i pos = Mouse::getPosition(gw);

		Event ge;

		while (gw.pollEvent(ge))
		{
			if (ge.type == Event::Closed)
			{
				gw.close();
			}
			if (ge.type == Event::MouseButtonPressed)
			{
				if (ge.key.code == Mouse::Left)
				{
					for (int i = 0; i < 4; i++)
					{
						if (controlFrame[i].getGlobalBounds().contains(pos.x,pos.y))
						{
							switch (i)
							{
							case 0:
								shipmov.x = 0;
								shipmov.y = -10;
								break;
							case 1:
								shipmov.x = 0;
								shipmov.y = 10;
								break;
							case 2:
								shipmov.x = -10;
								shipmov.y = 0;
								break;
							case 3:
								shipmov.x = 10;
								shipmov.y = 0;
								break;
							default:
								shipmov.x = 0;
								shipmov.y = 0;
								break;

							}
						}
					}
				}
			}

			if (ge.type == Event::MouseButtonReleased)
			{
				if (ge.key.code == Mouse::Left)
				{
					shipmov.x = 0;
					shipmov.y = 0;
				}
			}
		}
		cout << pos.x << "-" << pos.y << endl;
		//// Draw ////
		gw.clear();		
		gw.draw(backgroundFrame);
		drawMainShip(gw, shipmov.x, shipmov.y);
		drawControl(gw);
		gw.display();
	}
	
	return 0;
}