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
	string name = "";
	int fuel = 100;
	int score = 0;
	bool isOver = false;
	bool isPause = false;
	bool isImport = false;
	string printIF()
	{
		return "Player: " + name + " - Score: " + to_string(score) + "\n";
	}
	void reset()
	{
		name = "";
		fuel = 100;
		score = 0;
		isOver = false;
		isPause = false;
		isImport = false;
	}

};
struct compare
{
	bool operator() (InfoGame i, InfoGame j) { return (i.score < j.score); }
}compare;

vector<InfoGame> listplayer;

Text sco;
Text fuel;
Text intro;

Sprite backgroundFrame;

Sprite backgroundIntroFrame;

Sprite logoFrame;

Sprite processbar;

std::vector<Sprite> assetFrame;

std::vector<Sprite> shipFrame;

std::vector<Sprite> enemyFrame;

std::vector<pair<Sprite, int>> enemystoneFrame;

std::vector<Sprite> plantedFrame;

std::vector<Sprite> friendFrame;

std::vector<Sprite> itemFrame;

std::vector<Sprite> controlFrame;

std::vector<Sprite> bulletFrame;

std::vector<Sprite> bulleteFrame;



void createBackground()
{
	Texture* backgroundTexture = new Texture();
	backgroundTexture->loadFromFile(Resource::getbackground(0));
	backgroundFrame.setTexture(*backgroundTexture);
	backgroundFrame.setScale(0.5, 0.5);
}

void drawBackground(RenderWindow &gw)
{
	gw.draw(backgroundFrame);
}

void createLogo()
{
	Texture* logoTexture = new Texture();
	logoTexture->loadFromFile(Resource::getlogo(1));
	logoFrame.setTexture(*logoTexture);
	logoFrame.setScale(0.3, 0.3);
	logoFrame.setPosition(backgroundFrame.getGlobalBounds().width - logoFrame.getGlobalBounds().width - 5,
		backgroundFrame.getGlobalBounds().height - logoFrame.getGlobalBounds().height - 5);
}

int logoid = 1;
void drawLogo(RenderWindow &gw, int i = 0)
{
	if (logoid != i)
	{
		Texture* logoTexture = new Texture();
		logoTexture->loadFromFile(Resource::getlogo(i));
		delete logoFrame.getTexture();
		logoFrame.setTexture(*logoTexture);
		logoid = i;
	}
	gw.draw(logoFrame);
}

void createBackgoundIntro()
{
	Texture* backgroundIntroTexture = new Texture();
	backgroundIntroTexture->loadFromFile(Resource::getbackground(1));
	backgroundIntroFrame.setTexture(*backgroundIntroTexture);
	backgroundIntroFrame.setScale(0.6, 0.6);
	backgroundIntroFrame.setPosition(backgroundFrame.getGlobalBounds().width / 2 - backgroundIntroFrame.getGlobalBounds().width / 2,
		backgroundFrame.getGlobalBounds().height / 2 - backgroundIntroFrame.getGlobalBounds().height / 2);
}

void drawBackgroundIntro(RenderWindow &gw, Text text, string over="")
{
	if (over!="")
	{
		text.setString(over);
		text.setPosition(backgroundIntroFrame.getPosition().x + backgroundIntroFrame.getGlobalBounds().width/2, backgroundIntroFrame.getPosition().y + 10);
	}
	else
	{
		text.setString(Resource::getintro());
		text.setPosition(backgroundIntroFrame.getPosition().x + 5, backgroundIntroFrame.getPosition().y + 5);
	}
	
	gw.draw(backgroundIntroFrame);
	gw.draw(text);
}

void createControl()
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

	Texture *tempt = new Texture();
	tempt->loadFromFile(Resource::getassetcontrol(1));
	Sprite temp;
	temp.setTexture(*tempt);
	temp.setScale(0.5, 0.5);
	assetFrame.push_back(temp);

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
}

int psid = 1;
void drawPScontrol(RenderWindow &gw, int i = 0)
{
	if (psid != i)
	{
		Texture* psTexture = new Texture();
		psTexture->loadFromFile(Resource::getassetcontrol(i));
		delete assetFrame[0].getTexture();
		assetFrame[0].setTexture(*psTexture);
		psid = i;
	}
	gw.draw(assetFrame[0]);
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
		temp.setScale(0.3, 0.3);
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

void createBullete(Sprite enemy)
{
	Texture *temptx = new Texture();
	temptx->loadFromFile(Resource::getbullet(1));
	Sprite temp;
	temp.setTexture(*temptx);
	temp.setScale(0.1, 0.1);
	temp.setPosition(enemy.getPosition().x + enemy.getGlobalBounds().width,
		enemy.getPosition().y + (enemy.getGlobalBounds().height - temp.getGlobalBounds().height) / 2);
	bulleteFrame.push_back(temp);
}

void drawBullete(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)bulleteFrame.size(); i++)
	{
		bulleteFrame[i].move(-speed, 0);
		gw.draw(bulleteFrame[i]);
	}
}

void createenemyShip()
{
	if (enemyFrame.size() < 10)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomEnemyShip());
		Sprite temp;
		temp.setTexture(*temptx);
		temp.setScale(0.5, 0.5);
		temp.setPosition(backgroundFrame.getGlobalBounds().width - 1, rand() % (int)backgroundFrame.getGlobalBounds().height + shipFrame[0].getGlobalBounds().height);
		enemyFrame.push_back(temp);
	}
}

int animateenemy = 0;
void drawenemyShip(RenderWindow &gw, float speed)
{
	if (animateenemy == 4) animateenemy = 0;
	for (int i = 0; i < int(enemyFrame.size()); i++)
	{
		enemyFrame[i].move(-speed, 0);
		enemyFrame[i].setTextureRect(IntRect(animateenemy * 80, 0, 80, 80));
		gw.draw(enemyFrame[i]);
		if (rand() % 25 == 4)
		{
			createBullete(enemyFrame[i]);
		}
	}
}

void createfriendShip()
{
	if (friendFrame.size() < 10)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomFriendShip());
		Sprite temp;
		temp.setTexture(*temptx);
		temp.setScale(0.5, 0.5);
		temp.setPosition(backgroundFrame.getGlobalBounds().width - 1, rand() % (int)backgroundFrame.getGlobalBounds().height + shipFrame[0].getGlobalBounds().height);
		friendFrame.push_back(temp);
	}
}

int animatefriend = 0;
void drawfriendShip(RenderWindow &gw, float speed)
{
	if (animatefriend == 4) animatefriend = 0;
	for (int i = 0; i < int(friendFrame.size()); i++)
	{
		friendFrame[i].move(-speed, 0);
		friendFrame[i].setTextureRect(IntRect(animatefriend * 80, 0, 80, 80));
		gw.draw(friendFrame[i]);
	}
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
	if (plantedFrame.size() < 25)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomPlanted());
		Sprite temp;
		temp.setTexture(*temptx);
		if (temp.getGlobalBounds().height > 100)
			temp.setScale(0.3, 0.3);
		temp.setPosition(backgroundFrame.getGlobalBounds().width - 1, rand() % (int)backgroundFrame.getGlobalBounds().height - temp.getGlobalBounds().height);
		plantedFrame.push_back(temp);
	}
}

void drawPlant(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)plantedFrame.size(); i++)
	{
		plantedFrame[i].move(-speed, 0);
		gw.draw(plantedFrame[i]);
	}
}

void createEnemystone()
{
	if (enemystoneFrame.size() < 10)
	{
		srand(NULL);
		Texture *temptx = new Texture();
		temptx->loadFromFile(Resource::getrandomEnemyStone());
		Sprite temp;
		temp.setTexture(*temptx);
		if (temp.getGlobalBounds().height > 100)
			temp.setScale(0.3, 0.3);
		temp.setPosition(backgroundFrame.getGlobalBounds().width - 1,
			rand() % (int)backgroundFrame.getGlobalBounds().height + temp.getGlobalBounds().height);
		enemystoneFrame.push_back(make_pair(temp, 1));
	}
}

void drawEnemystone(RenderWindow &gw, float speed)
{
	for (int i = 0; i < (int)enemystoneFrame.size(); i++)
	{
		enemystoneFrame[i].first.move(-speed, 0);
		gw.draw(enemystoneFrame[i].first);
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
	processbar.setPosition((int)backgroundFrame.getGlobalBounds().width - processbar.getGlobalBounds().width - 10, 10);
	processbar.setTextureRect(IntRect(0, 0, processbar.getGlobalBounds().width, processbar.getGlobalBounds().height));
}

void animateprocessbar(RenderWindow &gw, int percent)
{
	processbar.setTextureRect(IntRect(0, 0, percent < 0 ? 0 : percent, processbar.getGlobalBounds().height));
	gw.draw(processbar);
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
	fuel.setPosition(processbar.getPosition().x + fuel.getString().getSize() * 3, processbar.getPosition().y);

	sco.setFont(*font);
	sco.setCharacterSize(20);
	sco.setStyle(sf::Text::Bold);
	sco.setFillColor(sf::Color::White);
	sco.setPosition(fuel.getPosition().x - 150, fuel.getPosition().y);

	intro.setFont(*font);
	intro.setCharacterSize(14);
	intro.setStyle(sf::Text::Bold);
	intro.setFillColor(sf::Color::Black);
}

void drawTextlayout(RenderWindow &gw, InfoGame ng)
{
	fuel.setString(String("FUEL: " + to_string(ng.fuel)));
	if (ng.fuel <= 20)
	{
		fuel.setFillColor(Color::Red);
	}
	else
	{
		fuel.setFillColor(sf::Color::White);
	}
	fuel.setPosition(processbar.getPosition().x + (50 - fuel.getString().getSize() * 3), processbar.getPosition().y);
	sco.setString(String("Score: " + to_string(ng.score)));
	gw.draw(fuel);
	gw.draw(sco);
}

void checkOut()
{
	if (bulletFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(bulletFrame.front().getPosition()))
		{
			delete bulletFrame[0].getTexture();
			bulletFrame.erase(bulletFrame.begin());
		}
	}
	if (plantedFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(plantedFrame.front().getPosition()))
		{
			delete plantedFrame[0].getTexture();
			plantedFrame.erase(plantedFrame.begin());
		}
	}
	if (itemFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(itemFrame.front().getPosition()))
		{
			delete itemFrame[0].getTexture();
			itemFrame.erase(itemFrame.begin());
		}
	}
	if (enemyFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(enemyFrame.front().getPosition()))
		{
			delete enemyFrame[0].getTexture();
			enemyFrame.erase(enemyFrame.begin());
		}
	}
	if (enemystoneFrame.size() != 0)
	{
		if (!backgroundFrame.getGlobalBounds().contains(enemystoneFrame.front().first.getPosition()))
		{
			delete enemystoneFrame[0].first.getTexture();
			enemystoneFrame.erase(enemystoneFrame.begin());
		}
	}
}

void checkImpactBulletObj(InfoGame &ng)
{
	if (bulletFrame.size() != 0 && (enemystoneFrame.size() != 0 || enemyFrame.size() != 0 || friendFrame.size() != 0))
	{
		int bsize = int(bulletFrame.size());
		int i = 0;
		while (i < bsize)
		{
			bool flag = false;
			int f = 0;
			int fsize = int(enemyFrame.size());
			while (f < fsize)
			{
				if (enemyFrame[f].getGlobalBounds().contains(float(bulletFrame[i].getPosition().x + float(bulletFrame[i].getGlobalBounds().width / 2)), float(bulletFrame[i].getPosition().y + float(bulletFrame[i].getGlobalBounds().height / 2))))
				{
					delete bulletFrame[i].getTexture();
					delete enemyFrame[f].getTexture();
					bulletFrame.erase(bulletFrame.begin() + i);
					enemyFrame.erase(enemyFrame.begin() + f);
					ng.score += 5;
					flag = true;
					break;
				}
				fsize = int(enemyFrame.size());
				f++;
			}
			if (flag)
			{
				bsize = int(bulletFrame.size());
				i++;
				continue;
			}
			f = 0;
			fsize = int(friendFrame.size());
			while (f < fsize)
			{
				if (friendFrame[f].getGlobalBounds().contains(float(bulletFrame[i].getPosition().x + float(bulletFrame[i].getGlobalBounds().width / 2)), float(bulletFrame[i].getPosition().y + float(bulletFrame[i].getGlobalBounds().height / 2))))
				{
					delete bulletFrame[i].getTexture();
					delete friendFrame[f].getTexture();
					bulletFrame.erase(bulletFrame.begin() + i);
					friendFrame.erase(friendFrame.begin() + f);
					ng.fuel -= 5;
					flag = true;
					break;
				}
				fsize = int(friendFrame.size());
				f++;
			}
			if (flag)
			{
				bsize = int(bulletFrame.size());
				i++;
				continue;
			}
			f = 0;
			fsize = int(enemystoneFrame.size());
			while (f < fsize)
			{
				if (enemystoneFrame[f].first.getGlobalBounds().contains(float(bulletFrame[i].getPosition().x + float(bulletFrame[i].getGlobalBounds().width / 2)),
					float(bulletFrame[i].getPosition().y + float(bulletFrame[i].getGlobalBounds().height / 2))))
				{
					if (!enemystoneFrame[f].second)
					{
						delete bulletFrame[i].getTexture();
						bulletFrame.erase(bulletFrame.begin() + i);
						delete enemystoneFrame[f].first.getTexture();
						enemystoneFrame.erase(enemystoneFrame.begin() + f);
						ng.score += 10;
					}
					else
					{
						delete bulletFrame[i].getTexture();
						bulletFrame.erase(bulletFrame.begin() + i);
						enemystoneFrame[f].second--;
					}
					break;
				}
				fsize = int(enemystoneFrame.size());
				f++;
			}
			bsize = int(bulletFrame.size());
			i++;
		}
	}
}

void checkImpactShipObjec(InfoGame &ng)
{
	if (itemFrame.size() != 0)
	{
		int isize = int(itemFrame.size());
		int i = 0;
		while (i < isize)
		{
			if (shipFrame[step].getGlobalBounds().contains(itemFrame[i].getPosition()))
			{
				delete itemFrame[i].getTexture();
				itemFrame.erase(itemFrame.begin() + i);
				ng.fuel >= 90 ? ng.fuel = 100 : ng.fuel += 10;
			}
			isize = int(itemFrame.size());
			i++;
		}
	}

	if (bulleteFrame.size() != 0)
	{
		int isize = int(bulleteFrame.size());
		int i = 0;
		while (i < isize)
		{
			if (shipFrame[step].getGlobalBounds().contains(bulleteFrame[i].getPosition()))
			{
				delete bulleteFrame[i].getTexture();
				bulleteFrame.erase(bulleteFrame.begin() + i);
				ng.fuel <= 10 ? ng.isOver = true : ng.fuel -= 5;
			}
			isize = int(bulleteFrame.size());
			i++;
		}
	}

	if (enemyFrame.size() != 0)
	{
		int isize = int(enemyFrame.size());
		int i = 0;
		while (i < isize)
		{
			if (enemyFrame[i].getGlobalBounds().contains(shipFrame[step].getPosition().x + shipFrame[step].getGlobalBounds().width / 2,
				shipFrame[step].getPosition().y + shipFrame[step].getGlobalBounds().height / 2))
			{
				delete enemyFrame[i].getTexture();
				enemyFrame.erase(enemyFrame.begin() + i);
				ng.fuel <= 5 ? ng.isOver = true : ng.fuel -= 5;
			}
			isize = int(enemyFrame.size());
			i++;
		}
	}

	if (enemystoneFrame.size() != 0)
	{
		int isize = int(enemystoneFrame.size());
		int i = 0;
		while (i < isize)
		{
			if (enemystoneFrame[i].first.getGlobalBounds().contains(shipFrame[step].getPosition().x + shipFrame[step].getGlobalBounds().width / 2,
				shipFrame[step].getPosition().y + shipFrame[step].getGlobalBounds().height / 2))
			{
				ng.fuel <= 5 * enemystoneFrame[i].second ? ng.isOver = true : ng.fuel -= 5 * enemystoneFrame[i].second;
				delete enemystoneFrame[i].first.getTexture();
				enemystoneFrame.erase(enemystoneFrame.begin() + i);
			}
			isize = int(enemystoneFrame.size());
			i++;
		}
	}
}

void newgame()
{
	enemyFrame.clear();

	enemystoneFrame.clear();

	plantedFrame.clear();

	friendFrame.clear();

	itemFrame.clear();

	bulletFrame.clear();

	bulleteFrame.clear();
}
int main()
{
	RenderWindow gw(VideoMode(960, 540), "Galaxy");
	gw.setFramerateLimit(30);
	createBackground();
	createBackgoundIntro();
	createControl();
	createLogo();

	createShip();
	createprocessbar();
	setTextlayout();

	srand(NULL);
	Vector2f shipmov;
	InfoGame ng;
	bool checkkey = true;
	bool firstplay = true;
	time_t before;
	before = time(0);
	while (gw.isOpen())
	{
		checkShipframe();
		Vector2i pos = Mouse::getPosition(gw);
		bool hover = false;
		Event ge;
		/// Random Planted
		if (rand() % 10 == 4 && rand() % 10 == 5 && !ng.isPause && !firstplay)
		{
			createPlant();
		}
		// Random Item
		if (rand() % 15 == 5 && rand() % 10 == 5 && !ng.isPause && !firstplay)
		{
			createItem();
		}
		/// Random enemy
		if (rand() % 15 == 6 && rand() % 10 == 5 && !ng.isPause && !firstplay)
		{
			createenemyShip();
		}
		/// Random friend
		if (rand() % 15 == 7 && rand() % 10 == 5 && !ng.isPause && !firstplay)
		{
			createfriendShip();
		}
		/// Random enemyStone
		if (rand() % 15 == 3 && rand() % 10 == 5 && !ng.isPause && !firstplay)
		{
			createEnemystone();
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
						ng.isPause = !ng.isPause;
					}
					if (backgroundIntroFrame.getGlobalBounds().contains(pos.x, pos.y))
					{
						if (ng.isOver)
						{
							ng.reset();
							newgame();
						}
						else
						{
							firstplay = false;
							ng.isPause = false;
						}						
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
					if (checkkey && !ng.isPause && !firstplay)
					{
						createBullet();
					}
					checkkey = false;
				}
				if (ge.key.code == Keyboard::P)
				{
					ng.isPause = !ng.isPause;
				}
				if (ge.key.code != Keyboard::P)
				{
					if (ng.isOver)
					{
						ng.reset();
						newgame();
					}
					else
					{
						firstplay = false;
						ng.isPause = false;
					}
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
		std::cout << " + Friend counter: " << plantedFrame.size();
		std::cout << " + Item counter: " << itemFrame.size();
		std::cout << " + Enemy counter: " << enemyFrame.size();
		std::cout << "\n";
		//// Draw ////
		if (ng.isOver)
		{
			if (!ng.isImport)
			{
				listplayer.push_back(ng);
				ng.isImport = true;
				sort(listplayer.begin(), listplayer.end(), compare);
			}
			string s = "\t\t\t\t Summary\n";
			for (int i = 0; i < int(listplayer.size()); i++)
			{
				s += listplayer[i].printIF();
			}
			s += "\t\t\t\t Click aor Press Any key to restart";
			gw.clear();
			drawBackground(gw);
			drawPlant(gw, 0);
			drawEnemystone(gw, 0);
			drawenemyShip(gw, 0);
			drawfriendShip(gw, 0);
			drawMainShip(gw, 0, 0);
			drawBullet(gw, 0);
			drawBullete(gw, 0);
			drawItem(gw, 0);
			animateprocessbar(gw, ng.fuel);
			drawTextlayout(gw, ng);
			drawLogo(gw, 1);
			drawControl(gw);
			drawPScontrol(gw, 1);
			drawBackgroundIntro(gw, intro,s);
			gw.display();
		}
		else if (!ng.isPause && !firstplay)
		{
			gw.clear();
			checkOut();
			checkImpactBulletObj(ng);
			checkImpactShipObjec(ng);
			drawBackground(gw);
			drawPlant(gw, 4);
			drawEnemystone(gw, 3);
			drawenemyShip(gw, 5);
			drawfriendShip(gw, 4);
			drawMainShip(gw, shipmov.x, shipmov.y);
			drawBullet(gw, 20);
			drawBullete(gw, 15);
			drawItem(gw, 1);
			animateprocessbar(gw, ng.fuel);
			drawTextlayout(gw, ng);
			drawLogo(gw);
			drawControl(gw);
			drawPScontrol(gw);
			gw.display();

			if (time(0) - before >= 1)
			{
				ng.fuel -= 2;
				if (ng.fuel <= 0)
					ng.isOver = true;
				before = time(0);
			}
		}
		else
		{
			gw.clear();
			drawBackground(gw);
			drawPlant(gw, 0);
			drawEnemystone(gw, 0);
			drawenemyShip(gw, 0);
			drawfriendShip(gw, 0);
			drawMainShip(gw, 0, 0);
			drawBullet(gw, 0);
			drawBullete(gw, 0);
			drawItem(gw, 0);
			animateprocessbar(gw, ng.fuel);
			drawTextlayout(gw, ng);
			drawLogo(gw, 1);
			drawControl(gw);
			drawPScontrol(gw, 1);
			drawBackgroundIntro(gw, intro);
			gw.display();
		}
		step++;
		animateenemy++;
		animatefriend++;
	}
	return 0;
}