#include "Resource.h"

Resource::Resource()
{
}
string Resource::docs[1] = { "./Asset/docs/Instructions.txt" };
string Resource::getdocs()
{	
	return string(docs[0]);
}
string Resource::backgrounds[2] = { "./Asset/images/background-1.jpg" ,"./Asset/images/background-intro.png"};
string Resource::getbackground(int i)
{	
	return string(backgrounds[i]);
}
string Resource::bullet[2] = { "./Asset/images/bullet/bullet.png","./Asset/images/bullet/bullet-e.png" };
string Resource::getbullet(int type)
{	
	return bullet[type];
}
string Resource::control[4] = { "./Asset/images/control/up.png","./Asset/images/control/down.png","./Asset/images/control/left.png"
,"./Asset/images/control/right.png" };
string Resource::getcontrol(int type)
{	
	return string(control[type]);		
}
string Resource::enemystone[4] = { "./Asset/images/enemy/aestroid_brown.png","./Asset/images/enemy/aestroid_dark.png"
, "./Asset/images/enemy/aestroid_gray.png","./Asset/images/enemy/aestroid_gray_2.png" };
string Resource::getrandomEnemyStone()
{	
	srand(time(NULL));	
	return string(enemystone[rand() % 4]);
}
string Resource::enemyship[1] = { "./Asset/images/e-ship/ship_1.png" };
string Resource::getrandomEnemyShip()
{
	srand(time(NULL));
	return string(enemyship[rand() % 1]);
}
string Resource::friendship[1] = { "./Asset/images/e-ship/ship_2.png" };
string Resource::getrandomFriendShip()
{
	srand(time(NULL));
	return string(friendship[rand() % 1]);
}
string Resource::planted[7] = {"./Asset/images/planets/001-global.png"
,"./Asset/images/planets/002-travel.png"
, "./Asset/images/planets/005-science.png"
, "./Asset/images/planets/006-mars.png"
, "./Asset/images/planets/008-earth-globe.png"
, "./Asset/images/planets/011-planet-earth.png"
, "./Asset/images/planets/012-jupiter.png" };
string Resource::getrandomPlanted()
{
	srand(time(NULL));
	return string(planted[rand() % 7]);
}
string Resource::ship[3] = { "./Asset/images/ship/main-1.png","./Asset/images/ship/main-2.png","./Asset/images/ship/main-3.png" };
vector<string> Resource::getshipAnimate()
{
	return vector<string>(ship, ship + sizeof(ship) / sizeof(ship[0]));
}
string Resource::item[1] = { "./Asset/images/support/fuel.png" };
string Resource::getrandomItem()
{
	srand(time(NULL));
	return string(item[rand() % 1]);
}
string Resource::assetcontrol[6] = { "./Asset/images/control/pause.png","./Asset/images/control/play.png" ,"./Asset/images/control/score.png","./Asset/images/control/time.png","./Asset/images/control/on.png","./Asset/images/control/off.png" };
string Resource::getassetcontrol(int i)
{
	return string(assetcontrol[i]);
}
string Resource::processbar[1] = { "./Asset/images/control/process.png" };
string Resource::getassetprocessbar()
{
	return string(processbar[0]);
}
string Resource::font[1] = { "./Asset/font/Oregano-Regular.ttf" };
string Resource::getfont(int i)
{
	return string(font[i]);
}
string Resource::intro[1] = { "./Asset/docs/Instructions.txt" };
string Resource::getintro()
{
	fstream f;
	string outp = "";
	f.open(intro[0]);
	while (!f.eof())
	{
		char temp[255];
		f.getline(temp,255);
		outp += temp;
		outp += "\n";
	}
	return string(outp);
}
string Resource::logo[2] = {"./Asset/images/logos/logo-01.png","./Asset/images/logos/logo-02.png"};
string Resource::getlogo(int i)
{
	return string(logo[i]);
}
string Resource::sound[3] = { "./Asset/sound/background.wav","./Asset/sound/destroyed.wav","./Asset/sound/shoot.wav" };
string Resource::getsound(int i)
{
	return string(sound[i]);
}
Resource::~Resource()
{
}
