#include <iostream>
#include <string> 
#include "JobData.h"
#include "RaceData.h"
#include "Player.h"
#include "Event.h"
#include "ShopData.h"

using namespace std;


int main() {

    ShowTest();
    // GameIntro();
    Player* player = new Player(CreateCharacterEvent());
    InitShopInventory();
	// GameIntro2();
    StatUpMenu(*player);
    static int event_count = 0;
    while (true) {
        if (player->IsAlive() == false) {
            EndGame();
            break;
        }
        MainScreen(*player);
    }
    delete player;
    return 0;
}
    
