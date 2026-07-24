#pragma once
#include "Player.h"

enum class EventType {
	BattleEvent = 1,
	StoryEvent = 2,
	TrapEvent = 3,
	MerchantEvent = 4,
	MainEvent = 5
};

struct EventContext {
	EventType type;
	int id;
	string EventName;
};
vector<EventContext> eventlist();
//Menu
void ShowTest();

void ShowMenu(Player& player);
void ShowInventory(Player& player);
void MyInventory(Player& player);
void ShowArmory(Player& player);
void MyArmory(Player& player);
void ShowSkills(const Player& player);
void ShowChangeName(Player& player);
void ShowMix(Player& player);
void MixRecipes_All(Player& player);
void MixRecipes_Ing(Player& player);
void MixRecipes_Out(Player& player);
bool Synthesize(Player& player, const MixInfo& recipe);
bool Merchandise(Player& player, int merchantid);
bool SellItemMenu(Player& player);
bool SellGearMenu(Player& player);
void RestEvent();
void StatUpMenu(Player& player);
//intro
void GameIntro();
void GameIntro2();
Player CreateCharacterEvent();
Player Chapther1Event();

void EndGame();
//MainEvents
void MainScreen(Player& player);
void StartBattle(Player& player, Monster& monster);
void Chapter1Event(Player& player, Monster& monster);

//Events Detail