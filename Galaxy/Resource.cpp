#include "Resource.h"



Resource::Resource()
{
}
string Resource::docs[1] = { "./Asset/docs/Instructions.txt" };
string Resource::getdocs()
{	
	return string(docs[0]);
}
string Resource::backgrounds[1] = { "./Asset/images/background-1.jpg" };
string Resource::getbackground()
{	
	return string(backgrounds[0]);
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

string Resource::enemy[4] = { "./Asset/images/enemy/aestroid_brown.png","./Asset/images/enemy/aestroid_dark.png"
, "./Asset/images/enemy/aestroid_gray.png","./Asset/images/enemy/aestroid_gray_2.png" };
string Resource::getrandomEnemy()
{	
	srand(time(NULL));	
	return string(enemy[rand() % 4]);
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


Resource::~Resource()
{
}
