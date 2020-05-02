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
			// Potion + 4 health
			Player::getPlayer()->changeHealth(4);
			Player::getPlayer()->newMessage("Looks like a minor health potion.");
			break;
		}
		case 1:
		{
			// Potion + 8 health
			Player::getPlayer()->changeHealth(8);
				Player::getPlayer()->newMessage("Looks like a major health potion.");
			break;
		}
		case 2:
		{
			// Potion + 100 health
			Player::getPlayer()->changeHealth(100);
			Player::getPlayer()->newMessage("A gift from the Fates, an ancient restorative position");
			break;
		}
		case 3:
		{
			// + 2 Max health
			Player::getPlayer()->changeMaxHealth(2);
			Player::getPlayer()->newMessage("My vitality has slightly increased, a minor constitution potion");
			break;
		}
		case 4:
		{
			// + 4 Max health
			Player::getPlayer()->changeMaxHealth(4);
			Player::getPlayer()->newMessage("My vitality has increased, a constitution potion");
			break;
		}
		case 5:
		{
			// + 8 Max health
			Player::getPlayer()->changeMaxHealth(8);
			Player::getPlayer()->newMessage("My vitality has greatly increased, a major constitution potion");

			break;
		}
		case 6:
		{
			// + 1 speed
			Player::getPlayer()->modifySpeed(1);
			Player::getPlayer()->newMessage("By the grace of Hermes, I feel fleeter of foot.");
			break;
		}
		case 7:
		{
			// + 10 damage
			Player::getPlayer()->changeDamage(2);
			Player::getPlayer()->newMessage("A little more power with which to exact my revenge.");

			break;
		}
		case 8:
		{
			// + 20 damage
			Player::getPlayer()->changeDamage(5);
			Player::getPlayer()->newMessage("A much greater power with which to exact my revenge.");
			break;
		}
		case 9:
		{
			// + 0.2 attack speed
			Player::getPlayer()->changeAttackSpeed(0.2);
			Player::getPlayer()->newMessage("A trinket to summon the flames even swifter.");
			break;
		}
		case 10:
		{
			// + 0.5 attack speed
			Player::getPlayer()->changeAttackSpeed(0.5);
			Player::getPlayer()->newMessage("A charm to summon the flames even swifter.");
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
