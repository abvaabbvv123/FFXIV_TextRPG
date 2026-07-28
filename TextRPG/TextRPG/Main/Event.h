#pragma once
#include "Player.h"

enum class EventType {
    StoryEvent = 1,
    ChoiceEvent = 2,
    QuestEvent = 3,
    BattleEvent = 4,
    CompleteEvent = 5,
    StatEvent = 6,
    MerchantEvent = 7,
    TrapEvent = 8,
    TradeEvent = 9
};
struct EventContext;
using EncounterEvent = void(*)(int id, Player& player);
struct EventContext {
    int id;
    EventType type;
    string questname;
    string npcname;
    EncounterEvent event;
};
vector<EventContext>& EventList();
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

void WinGame();
void EndGame();
//MainEvents
void MainScreen(Player& player);
void StartBattle(Player& player, Monster& monster);
void Chapter1Event(Player& player, Monster& monster);

//Events Func
EventContext FindEventByID(int id);
void TriggerEvent(int id, EventContext event, Player& player);
//Events Detail
void A_Soldiers_Breakfast_Complete(int id, Player& player);
void A_Soldiers_Breakfast_Battle(int id, Player& player);
void A_Soldiers_Breakfast(int id, Player& player);
void HeavyLifting(int id, Player& player);
void BoulderDash(int id, Player& player);
void CollapsedTunnel(int id, Player& player);
void StealthyRetrieval(int id, Player& player);
void ArchersMark(int id, Player& player);
void SpringToadTrap(int id, Player& player);
void PoisonTolerance(int id, Player& player);
void FreezingBlizzard(int id, Player& player);
void ToxicGasTrap(int id, Player& player);
void DecipherRunes(int id, Player& player);
void MagitekOverride(int id, Player& player);
void IllusionTrap(int id, Player& player);
void TrackingBeast(int id, Player& player);
void DecipherEmotion(int id, Player& player);
void SirenSongTrap(int id, Player& player);
void MerchantBargain(int id, Player& player);
void GuardIntimidation(int id, Player& player);
void CharmingSirenTrap(int id, Player& player);
void WanderingBlacksmith(int id, Player& player);
void AlchemistExchange(int id, Player& player);     
void RecipeTrader(int id, Player& player);          
void HerbCollectorRecipe(int id, Player& player);   
