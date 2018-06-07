#pragma once
#include<iostream>
#include<ctime>
#include<vector>
using namespace std;
class Resource
{
private:
	static string docs[1];
	static string backgrounds[1];
	static string ship[3];
	static string control[4];
	static string enemy[4];
	static string bullet[2];
	static string planted[7];
public:
	Resource();
	static string getdocs();
	static string getbackground();
	static string getbullet(int type);
	static string getcontrol(int type);
	static string getrandomEnemy();
	static string getrandomPlanted();
	static vector<string> getshipAnimate();
	~Resource();
};

