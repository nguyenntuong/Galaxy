#pragma once
#include<iostream>
#include<ctime>
#include<vector>
#include<fstream>
using namespace std;
class Resource
{
private:
	static string docs[1];
	static string backgrounds[2];
	static string logo[2];
	static string ship[3];
	static string control[4];
	static string enemystone[4];
	static string enemyship[2];
	static string bullet[2];
	static string planted[7];
	static string item[1];
	static string assetcontrol[2];
	static string processbar[1];
	static string font[1];
	static string intro[1];
public:
	Resource();
	static string getdocs();
	static string getbackground(int i);
	static string getbullet(int type);
	static string getcontrol(int type);
	static string getrandomEnemyStone();
	static string getrandomEnemyShip();
	static string getrandomPlanted();
	static vector<string> getshipAnimate();
	static string getrandomItem();
	static string getassetcontrol(int i);
	static string getassetprocessbar();
	static string getfont(int i);
	static string getintro();
	static string getlogo(int i);
	~Resource();
};

