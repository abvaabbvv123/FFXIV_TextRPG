#pragma once
#include "Player.h"
#include "Monster.h"
#include "Event.h"
#include "MonsterData.h"
#include "dice.h"

using namespace std;

//Turn-Speed system
struct ObjectInfo {
	string name;
	int dex, dicenum = 4, gauge = 0;
};

class TurnManager {
public:
	TurnManager (vector<ObjectInfo> targets);
	void StartTurn();
	void AdvancedTurn();

	ObjectInfo& GetCurrentTurn();
	ObjectInfo& GetNextTurn();
	const vector<ObjectInfo>& GetEntities() const { return targets; }
	ObjectInfo* FindEntity(const string& name) {
		for (auto& t : targets)
			if (t.name == name) return &t;
		return nullptr;
	}
private:
	struct FirstSecond { ObjectInfo* first; ObjectInfo* second; };
	FirstSecond CalcTurn();

	vector<ObjectInfo> targets;
	ObjectInfo* current_turn = nullptr;
	ObjectInfo* next_turn = nullptr;
};
int ClampTurnDice(int num); // dicenum range (0-12)


int SetInitiative(Player& player, Monster& monster); // Initialize Dice

void RollTurnGauge(ObjectInfo& targets);

void BattleEvent_Normal(Player& player, Monster& monster);
void BattleEvent_Boss(Player& player, Monster& monster);

void ApplyAddSpeed(ObjectInfo& targets, int amount);
void ApplyHaste(ObjectInfo& targets, int amount);

bool PlayerTurn(Player& player, Monster& monster, int& distance, TurnManager& tm);
void MonsterTurn(Player& player, Monster& monster, int& distance);
bool BattleInventory(Player& player, Monster& monster);

bool Retreat(Player& player, Monster& monster);

void WinBattle(Player& player, Monster& monster);
void RetreatBattle();

