#include "ItemSystem.h"
#include "Player.h"
#include <cstdlib>

int ItemSystem::getItemCase(){
	int r = rand() % totalChances;
	int i = 0;
	for(; i < RAND_ITEMS_NUM;i++){
		r -= probList[i];
		if(r <= 0){break;}
	}

	return i;
}

void ItemSystem::generateItem(){
	int itemNum = getItemCase();
	cout << "Item num:" << itemNum << endl;
	chestsOpened++;
	switch(itemNum){
		case 0:
		{
			// Potion + 20 health
			Player::getPlayer()->changeHealth(20);
			break;
		}
		case 1:
		{
			// Potion + 50 health
			Player::getPlayer()->changeHealth(50);
			break;
		}
		case 2:
		{
			// Potion + 100 health
			Player::getPlayer()->changeHealth(100);
			break;
		}
		case 3:
		{
			// + 10 Max health
			Player::getPlayer()->changeMaxHealth(10);
			break;
		}
		case 4:
		{
			// + 20 Max health
			Player::getPlayer()->changeMaxHealth(20);
			break;
		}
		case 5:
		{
			// + 30 Max health
			Player::getPlayer()->changeMaxHealth(30);
			break;
		}
		case 6:
		{
			// + 1 speed
			Player::getPlayer()->modifySpeed(1);
			break;
		}
		case 7:
		{
			// + 10 damage
			Player::getPlayer()->changeDamage(10);
			break;
		}
		case 8:
		{
			// + 20 damage
			Player::getPlayer()->changeDamage(20);
			break;
		}
		case 9:
		{
			// + 0.2 attack speed
			Player::getPlayer()->changeAttackSpeed(0.2);
			break;
		}
		case 10:
		{
			// + 0.5 attack speed
			Player::getPlayer()->changeAttackSpeed(0.5);
			break;
		}
	}

}

void ItemSystem::handleEvent(Event* e){
	string type = e->getType();
	if (type == "CHEST_OPENED") {
		generateItem();
	}
}
