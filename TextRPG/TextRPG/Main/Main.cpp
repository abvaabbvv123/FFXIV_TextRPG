#include <iostream>
#include <string> 
#include "JobData.h"
#include "RaceData.h"
#include "Player.h"
#include "Event.h"
#include "ShopData.h"
#include "MonsterData.h"
#include "Battle.h"

using namespace std;


int main() {

    // ShowTest();
    GameIntro();
    Player* player = new Player(CreateCharacterEvent());
    InitShopInventory();
	GameIntro2();
    StatUpMenu(*player);
    static int event_count = 0;
    for (;event_count < 10; ++event_count)
    {
        if (player->IsAlive() == false) {
            EndGame();
            break;
        }
        MainScreen(*player);
        event_count++;
    }
    Monster enemy = CreateMonster(101);
    BattleEvent_Normal(*player, enemy);
    delete player;
    return 0;
}
    
