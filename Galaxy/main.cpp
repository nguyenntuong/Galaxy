#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
#include<SFML\Graphics.hpp>
#include "Resource.h"

using namespace sf;



Sprite backgroundFrame;

std::vector<Sprite> assetFrame;

Sprite shipFrame;

std::vector<Sprite> enemyFrame;

std::vector<Sprite> friendFrame;

std::vector<Sprite> itemFrame;

std::vector<Sprite> controlFrame;

std::vector<Sprite> bulletFrame;


void setBackgroud()
{
	Texture* backgroundTexture = new Texture();
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
		Sprite temp;
		temp.setTexture(*tempt);
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
			controlFrame[1].setPosition(91, 490 - 39);
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
	Texture* shipTexture = new Texture();
	shipTexture->loadFromFile(Resource::getshipAnimate());
	shipFrame.setTexture(*shipTexture);
	shipFrame.setScale(0.5, 0.5);
}

void createShip()
{
	Texture* shipTexture = new Texture();
	shipTexture->loadFromFile(Resource::getshipAnimate());
	shipFrame.setTexture(*shipTexture);
	shipFrame.setScale(0.5, 0.5);
	shipFrame.setPosition(10, 250);
}
void drawMainShip(RenderWindow &gw, float x, float y)
{
	shipFrame.move(x, y);
	if (!backgroundFrame.getGlobalBounds().contains(shipFrame.getPosition()))
	{
		shipFrame.move(-x, -y);
	}
	gw.draw(shipFrame);
}

void createBullet()
{
	Texture *temptx = new Texture();
	temptx->loadFromFile(Resource::getbullet(0));
	Sprite temp;
	temp.setTexture(*temptx);
	temp.setScale(0.1, 0.1);
	temp.setPosition(shipFrame.getPosition().x + shipFrame.getGlobalBounds().width,
		shipFrame.getPosition().y+(shipFrame.getGlobalBounds().height-temp.getGlobalBounds().height)/2);
	bulletFrame.push_back(temp);
}

void drawBullet(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)bulletFrame.size(); i++)
	{
		bulletFrame[i].move(speed, 0);
		gw.draw(bulletFrame[i]);
	}
}

void createPlant()
{
	if (friendFrame.size() < 25)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomPlanted());
		Sprite temp;
		temp.setTexture(*temptx);
		temp.setScale(0.3, 0.3);
		temp.setPosition(backgroundFrame.getGlobalBounds().width-1, rand() % (int)backgroundFrame.getGlobalBounds().height-temp.getGlobalBounds().height);
		friendFrame.push_back(temp);
	}
}

void drawFriend(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)friendFrame.size(); i++)
	{
		friendFrame[i].move(-speed, 0);
		gw.draw(friendFrame[i]);
	}
}

void checkOut()
{
	if (bulletFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(bulletFrame.front().getPosition()))
		{
			bulletFrame[0].setTexture(Texture());
			bulletFrame.erase(bulletFrame.begin());
		}
	}
	if (friendFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(friendFrame.front().getPosition()))
		{
			friendFrame[0].setTexture(Texture());
			friendFrame.erase(friendFrame.begin());
		}
	}
}
int main()
{
	RenderWindow gw(VideoMode(960, 540), "Galaxy");
	gw.setFramerateLimit(30);
	setBackgroud();
	setControl();
	createShip();

	srand(NULL);
	Vector2f shipmov;
	bool checkkey = true;
	while (gw.isOpen())
	{
		animateShip();
		Vector2i pos = Mouse::getPosition(gw);
		bool hover = false;
		Event ge;
		if (rand() % 10 == 4 && rand() % 10 == 5)
		{
			createPlant();
		}
		while (gw.pollEvent(ge))
		{
			if (ge.type == Event::Closed)
			{
				gw.close();
			}
			if (ge.type == Event::MouseMoved)
			{
				for (int i = 0; i < 4; i++)
				{
					if (controlFrame[i].getGlobalBounds().contains(pos.x, pos.y))
					{
						hover = true;
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
						}
						break;
					}
				}
				if (!hover)
				{
					shipmov.x = 0;
					shipmov.y = 0;
				}
			}
			if (ge.type == Event::KeyPressed)
			{
				if (ge.key.code == Keyboard::Space)
				{ 
					if (checkkey)
					{
						createBullet();
					}
					checkkey = false;
				}
			}
			if (ge.type == Event::KeyReleased)
			{
				if (ge.key.code == Keyboard::Space)
				{					
					checkkey = true;
				}
			}
		}
	cout << "Bullet counter: " << bulletFrame.size();
	cout << " + Friend counter: " << friendFrame.size();
	cout << " + Memory: " << sizeof backgroundFrame + sizeof shipFrame  + sizeof friendFrame  + sizeof bulletFrame ;
	cout << endl;
	//// Draw ////
	gw.clear();
	checkOut();
	gw.draw(backgroundFrame);
	drawMainShip(gw, shipmov.x, shipmov.y);
	drawFriend(gw, 4);
	drawBullet(gw, 20);
	drawControl(gw);
	gw.display();
}

return 0;
}