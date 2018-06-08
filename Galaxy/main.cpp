#include<iostream>
#include<vector>
#include<math.h>
#include<ctime>
#include<string>
#include<SFML\Graphics.hpp>
#include "Resource.h"

using namespace sf;

struct InfoGame
{
	int fuel = 100;
	int score = 0;
	bool isOver = false;
	bool isPause = false;
};

sf::Text sco;
sf::Text fuel;

Sprite backgroundFrame;

Sprite processbar;

std::vector<Sprite> assetFrame;

std::vector<Sprite> shipFrame;

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

	for (int i = 0; i < 2; i++)
	{
		Texture *tempt = new Texture();
		tempt->loadFromFile(Resource::getassetcontrol(i));
		Sprite temp;
		temp.setTexture(*tempt);
		temp.setScale(0.5, 0.5);
		assetFrame.push_back(temp);
	}
}

void drawControl(RenderWindow &gw)
{
	for (int i = 0; i < int(controlFrame.size()); i++)
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
	for (int i = 0; i < int(assetFrame.size()); i++)
	{
		switch (i)
		{
		case 0:
			assetFrame[0].setPosition(10, 5);
			break;
		case 1:
			assetFrame[1].setPosition(10 + assetFrame[i - 1].getGlobalBounds().width * 2, 5);
			break;
		default:
			break;
		}
		gw.draw(assetFrame[i]);
	}
}
int step = 0;
void checkShipframe()
{
	if (step == 3)
	{
		step = 0;
	}
}

void createShip()
{
	for (int i = 0; i < int(Resource::getshipAnimate().size()); i++)
	{
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getshipAnimate()[i]);
		Sprite temp;
		temp.setTexture(*temptx);
		temp.setScale(0.5, 0.5);
		temp.setScale(0.5, 0.5);
		temp.setPosition(10, 250);
		shipFrame.push_back(temp);
	}

}
void drawMainShip(RenderWindow &gw, float x, float y)
{
	for (int i = 0; i < int(shipFrame.size()); i++)
	{
		shipFrame[i].move(x, y);
		if (!backgroundFrame.getGlobalBounds().contains(shipFrame[i].getPosition()))
		{
			shipFrame[i].move(-x, -y);
		}
	}
	gw.draw(shipFrame[step]);

}

void createBullet()
{
	Texture *temptx = new Texture();
	temptx->loadFromFile(Resource::getbullet(0));
	Sprite temp;
	temp.setTexture(*temptx);
	temp.setScale(0.1, 0.1);
	temp.setPosition(shipFrame[step].getPosition().x + shipFrame[step].getGlobalBounds().width,
		shipFrame[step].getPosition().y + (shipFrame[step].getGlobalBounds().height - temp.getGlobalBounds().height) / 2);
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
		if(temp.getGlobalBounds().height>100)
		temp.setScale(0.3, 0.3);
		temp.setPosition(backgroundFrame.getGlobalBounds().width - 1, rand() % (int)backgroundFrame.getGlobalBounds().height - temp.getGlobalBounds().height);
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

void createItem()
{
	if (itemFrame.size() < 3)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomItem());
		Sprite temp;
		temp.setTexture(*temptx);
		temp.setScale(0.3, 0.3);
		temp.setPosition(rand() % (int)backgroundFrame.getGlobalBounds().width - temp.getGlobalBounds().width, 1);
		itemFrame.push_back(temp);
	}
}

void drawItem(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)itemFrame.size(); i++)
	{
		itemFrame[i].move(0, speed);
		gw.draw(itemFrame[i]);
	}
}

void createprocessbar()
{
	Texture *temptx = new Texture();
	temptx->loadFromFile(Resource::getassetprocessbar());
	processbar.setTexture(*temptx);
	processbar.setPosition((int)backgroundFrame.getGlobalBounds().width - processbar.getGlobalBounds().width-10, 10);
	processbar.setTextureRect(IntRect(0, 0, processbar.getGlobalBounds().width, processbar.getGlobalBounds().height));
}

void animateprocessbar(RenderWindow &gw, int percent)
{
	processbar.setTextureRect(IntRect(0, 0, percent < 0 ? 0 : percent, processbar.getGlobalBounds().height));
	gw.draw(processbar);
}

void checkOut()
{
	if (bulletFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(bulletFrame.front().getPosition()))
		{
			bulletFrame.erase(bulletFrame.begin());
		}
	}
	if (friendFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(friendFrame.front().getPosition()))
		{
			friendFrame.erase(friendFrame.begin());
		}
	}
	if (itemFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(itemFrame.front().getPosition()))
		{
			itemFrame.erase(itemFrame.begin());
		}
	}
}

void checkImpactBulletObj(InfoGame &ng)
{
	if (bulletFrame.size() != 0 && friendFrame.size() != 0)
	{
		int bsize = int(bulletFrame.size());
		int i = 0;
		while (i < bsize)
		{
			int f = 0;
			int fsize = int(friendFrame.size());
			while (f < fsize)
			{
				if (friendFrame[f].getGlobalBounds().contains(float(bulletFrame[i].getPosition().x + float(bulletFrame[i].getGlobalBounds().width / 2)), float(bulletFrame[i].getPosition().y + float(bulletFrame[i].getGlobalBounds().height / 2))))
				{
					bulletFrame.erase(bulletFrame.begin() + i);
					friendFrame.erase(friendFrame.begin() + f);
					ng.score += 10;
					break;
				}
				fsize = int(friendFrame.size());
				f++;
			}
			bsize = int(bulletFrame.size());
			i++;
		}
	}
}

void checkImpactShipItem(InfoGame &ng)
{
	if (itemFrame.size() != 0)
	{
		int isize = int(itemFrame.size());
		int i = 0;
		while (i < isize)
		{
			if (shipFrame[step].getGlobalBounds().contains(itemFrame[i].getPosition()))
			{
				itemFrame.erase(itemFrame.begin() + i);
				ng.fuel >= 90 ? ng.fuel = 100 : ng.fuel += 10;
			}
			isize = int(itemFrame.size());
			i++;
		}
	}
}

void setTextlayout()
{
	Font *font = new Font();
	if (!font->loadFromFile(Resource::getfont(0)))
	{
		std::cout << "Error loading font\n";
	}
	//set up text properties
		
	fuel.setFont(*font);
	fuel.setCharacterSize(12);
	fuel.setStyle(sf::Text::Bold);
	fuel.setFillColor(sf::Color::White);
	fuel.setPosition(processbar.getPosition().x + fuel.getString().getSize()*3, processbar.getPosition().y);

	sco.setFont(*font);
	sco.setCharacterSize(20);
	sco.setStyle(sf::Text::Bold);
	sco.setFillColor(sf::Color::White);
	sco.setPosition(fuel.getPosition().x - 150, fuel.getPosition().y);
	
}

void drawTextlayout(RenderWindow &gw, InfoGame ng)
{
	fuel.setString(String("FUEL: "+to_string(ng.fuel)));
	if (ng.fuel<=20)
	{
		fuel.setFillColor(Color::Red);
	}
	else
	{
		fuel.setFillColor(sf::Color::White);
	}
	fuel.setPosition(processbar.getPosition().x +(50- fuel.getString().getSize()*3), processbar.getPosition().y);
	sco.setString(String("Score: "+to_string(ng.score)));
	gw.draw(fuel);
	gw.draw(sco);
}

int main()
{
	RenderWindow gw(VideoMode(960, 540), "Galaxy");
	gw.setFramerateLimit(30);
	setBackgroud();
	setControl();
	
	createShip();
	createprocessbar();
	setTextlayout();

	srand(NULL);
	Vector2f shipmov;
	InfoGame ng;
	bool checkkey = true;
	time_t before;
	before = time(0);
	while (gw.isOpen())
	{
		//gw.pushGLStates();
		checkShipframe();
		Vector2i pos = Mouse::getPosition(gw);
		bool hover = false;
		Event ge;
		/// Random Planted
		if (rand() % 10 == 4 && rand() % 10 == 5 && !ng.isPause)
		{
			createPlant();
		}
		// Random Item
		if (rand() % 15 == 5 && rand() % 10 == 5 && !ng.isPause)
		{
			createItem();
		}
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
					if (assetFrame[0].getGlobalBounds().contains(pos.x, pos.y))
					{
						ng.isPause = true;
					}
					if (assetFrame[1].getGlobalBounds().contains(pos.x, pos.y))
					{
						ng.isPause = false;
					}
				}
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
					if (checkkey && !ng.isPause)
					{
						createBullet();
					}
					checkkey = false;
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) {
				shipmov.x = 0;
				shipmov.y = -10;
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) {
				shipmov.x = 0;
				shipmov.y = 10;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) {
				shipmov.x = -10;
				shipmov.y = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::Right)) {
				shipmov.x = 10;
				shipmov.y = 0;
			}
			if (ge.type == Event::KeyReleased)
			{
				if (ge.key.code == Keyboard::Space)
				{
					checkkey = true;
				}
				else
				{
					shipmov.x = 0;
					shipmov.y = 0;
				}
			}
		}

		std::cout << "Bullet counter: " << bulletFrame.size();
		std::cout << " + Friend counter: " << friendFrame.size();
		std::cout << " + Item counter: " << itemFrame.size();
		std::cout << " + Memory: " << sizeof backgroundFrame + sizeof shipFrame + sizeof friendFrame + sizeof bulletFrame;
		std::cout << "\n";
		//// Draw ////
		if (!ng.isPause)
		{

			gw.clear();
			checkOut();
			checkImpactBulletObj(ng);
			checkImpactShipItem(ng);
			gw.draw(backgroundFrame);
			drawFriend(gw, 4);
			animateprocessbar(gw, ng.fuel);
			drawTextlayout(gw, ng);
			drawMainShip(gw, shipmov.x, shipmov.y);
			drawBullet(gw, 20);
			drawItem(gw, 1);
			drawControl(gw);
			//gw.popGLStates();
			gw.display();

			if (time(0) - before >= 1)
			{
				ng.fuel-=2;
				before = time(0);
			}
			
		}
		else
		{
			gw.clear();
			gw.draw(backgroundFrame);
			drawFriend(gw, 0);
			animateprocessbar(gw, ng.fuel);
			drawTextlayout(gw, ng);
			drawMainShip(gw, 0, 0);
			drawBullet(gw, 0);
			drawItem(gw, 0);
			drawControl(gw);
			//gw.popGLStates();
			gw.display();
			
		}
		step++;
	}
	return 0;
}