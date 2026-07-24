#include "Player.h"
#include "Monster.h"
#include "Event.h"
#include "MonsterData.h"
#include "dice.h"
#include "Battle.h"
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include "Tools.h"

using namespace std;


TurnManager::TurnManager(vector<ObjectInfo> targets)
	: targets(targets)
{}

//Initiative, RollDice with each DEX
int SetInitiative(Player& player, Monster& monster)
{
	int initiative = DiceRoll({ 0, 1, 20 });
	int result = 0; // 0: None, 1:ambushed,  2:preemptive

	cout << "\n====================================================================\n";
	if (initiative < 3 + player.GetPenaltyInitiative())
	{
		TypeEffect("Got Ambushed!\n", 45);
		Waitforseconds(1);
		result = 1;
	}
	else if (initiative > 18 - player.GetBonusInitiative())
	{
		TypeEffect("Preemptive Attack!\n", 45);
		Waitforseconds(1);
		result = 2;
	}
	cout << "You encounter a [" << monster.GetName() << "]!\n";
	cout << "--------------------------------------------------------------------\n";
	Waitforseconds(2);
	return result;
}

//Make Dice clamp 0~12
int ClampTurnDice(int num) 
{
	if (num < 0) return 0;
	else if (num > 12) return 12;
		else return num;
}

void ApplyAddSpeed(ObjectInfo& targets, int amount) 
{ 
	targets.gauge += amount;
}

void ApplyHaste(ObjectInfo& targets, int amount) 
{
	targets.dicenum = ClampTurnDice(targets.dicenum + amount);
}

void RollTurnGauge(ObjectInfo& targets) 
{
	targets.dicenum = ClampTurnDice(targets.dicenum);
	targets.gauge += targets.dex + DiceRoll({ 0, 1, targets.dicenum });
}

TurnManager::FirstSecond TurnManager::CalcTurn() {
	while (true) {
		for (auto& t : targets)
			RollTurnGauge(t);

		bool got_turn = false;

		for (auto& t : targets)
			if (t.gauge >= 100) {got_turn = true; break;}
		
		if (!got_turn) continue;

		ObjectInfo* first = nullptr;
		ObjectInfo* second = nullptr;

		for (auto& t : targets) {
			if (!first || t.gauge > first->gauge) { second = first; first = &t; }
			else if (!second || t.gauge > second->gauge) { second = &t; }
		}
		return { first, second };
	}
}

void TurnManager::StartTurn() {
	FirstSecond result = CalcTurn();
	current_turn = result.first;
	next_turn = result.second;
}
void TurnManager::AdvancedTurn() {
	current_turn->gauge -= 100;
	FirstSecond result = CalcTurn();
	current_turn = result.first;
	next_turn = result.second;
}
ObjectInfo& TurnManager::GetCurrentTurn() { return *current_turn; }
ObjectInfo& TurnManager::GetNextTurn() { return *next_turn; }

void BattleEvent_Normal(Player& player, Monster& monster) 
{
	int startdistance = player.GetStartDistance() + monster.GetStartDistance();
	int distance = clamp(RandomNum(startdistance - 1, startdistance + 1), 0 , 4);

	ObjectInfo playerentity{ player.GetName(), player.GetDex()};
	ObjectInfo monsterentity{ monster.GetName(), monster.GetDex()};
	vector<ObjectInfo> entities = { playerentity, monsterentity };

	int init_result = SetInitiative(player, monster);
	if (init_result == 1)
		ApplyAddSpeed(monsterentity, 100);
	if (init_result == 2)
		ApplyAddSpeed(playerentity, 100);


	TurnManager tm({ playerentity, monsterentity });
	tm.StartTurn();

	while (player.IsAlive() && monster.IsAlive()) {

		ObjectInfo& target = tm.GetCurrentTurn();	
		string current_name = target.name;
		system("cls");
		cout << "====================================================================\n";
		cout << "[" << player.GetName() << "]:  HP[" << player.GetHP() << "] MP[" << player.GetMP() << "]\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "[Enemy List]\n";
		cout << monsterentity.name << " HP: [" << monster.GetHP() <<"]\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "[Turn Gauge]\n";
		for (const auto& e : tm.GetEntities())
			cout << e.name << "'s turn gauge: " << e.gauge << "\n";
		cout << "--------------------------------------------------------------------\n";
		cout << "Current Distance: [" << distance << "]\n";
		cout << "====================================================================\n";
		cout << "Now [" << current_name << "]'s Turn!\n";
		
		

		if (current_name == player.GetName()) {
			player.SetGuard(false);
			bool IsEscaped = PlayerTurn(player, monster, distance, tm);
			if (IsEscaped) { return; }
			Waitforseconds(1);
		}
		else {
			MonsterTurn(player, monster, distance);
			Waitforseconds(1);
		}

		tm.AdvancedTurn();

		if (player.IsAlive() == false) { EndGame(); break; }
	}
	if (player.IsAlive()) 
		WinBattle(player, monster);
	

	}

void BattleEvent_Boss(Player& player, Monster& monster) {}

bool PlayerTurn(Player& player, Monster& monster, int& distance, TurnManager& tm) {
	int answer = 0;
	const auto& skillmap = GetSkillMap();
	const auto& skillslot = player.ViewSkill();
	cout << "====================================================================\n";
	cout << "Player's turn! Do action with number.\n";
	cout << "--------------------------------------------------------------------\n";

	for (int i = 0; i < 6; i++) {
		int slot = skillslot[i];
		if (slot == -1) {
			cout << "[" << (i + 1) << "]: [Empty Slot]" << endl;
		}
		else {
			auto skill = skillmap.find(slot);
			cout << "[" << (i + 1) << "]: " << skill->second.name << " Range: [" << skill->second.range << "]" << endl;
		}
	}
	cout << "[7]: " << "Use Item" << endl;
	cout << "[8]: " << "Guard" << endl;
	cout << "[9]: " << "Retreat" << endl;
	cout << "--------------------------------------------------------------------\n";
	while (true) {
		cin >> answer;
		if (answer >= 1 && answer <= 6) {
			int slot = skillslot[answer - 1];
			if (slot == -1) {
				cout << "Empty skill slot, Please enter right number.";
				continue;
			}

			auto skill = skillmap.find(slot);
			const SkillInfo& selected = skill->second;
			if (distance > selected.range) {
				cout << "====================================================================\n";
				cout << "The enemy is too far away to execute that skill.\n";
				cout << "====================================================================\n";
				Waitforseconds(1);
			}
			else {
				ObjectInfo* monsters = tm.FindEntity(monster.GetName());
				SkillContext target{ player, &monster, distance, *monsters };
				UseSkill(selected, target);
				ObjectInfo& caster = tm.GetCurrentTurn();
				ApplyAddSpeed(caster, selected.addspeed);
				ApplyHaste(caster, selected.haste);
				return false;
			}

		}
		if (answer == 7) { 
			bool useditem = BattleInventory(player, monster);
			if (useditem) { return false; }
			else { return false; }
		}
		if (answer == 8) { 
			player.SetGuard(true);
			cout << "====================================================================\n";
			cout << "You take up a defensive guard. (Damage taken reduced by 50% for 1 turn).\n";
			cout << "====================================================================\n";
			return false; }

		if (answer == 9) {
			bool escaped = Retreat(player, monster);
			return escaped;
		}

		}
	}
bool BattleInventory(Player& player, Monster& monster) {
	while (true) {
		system("cls");
		MyInventory(player);
		cout << "[Item Name: Use Item] [[0]: Back]\nYour Answer: ";
		string answer;
		getline(cin >> ws, answer);
		if (answer == "0") { return false; }

		int id = FindItem(answer);
		
		if (id == -1) {
			cout << "Cannot find item";
			Waitforseconds(1);
			continue;
		}
		ItemInfo data = GetItemData(id);
		if (!CheckItem(player, id, 1)) {
			cout << "You don't have that item.\n";
			Waitforseconds(1);
			continue;
		}
		if (!data.IsUseable) {
			cout << "That item cannot be used.\n";
			Waitforseconds(1);
			continue;
		}
		Target target{ &player, &monster };
		UseItem(data, target);
		player.RemoveItem(id, 1);
		Waitforseconds(1);
		return true;
	}
}

void MonsterTurn(Player& player, Monster& monster, int& distance) {
	MonsterAction(player, monster, distance);
	Waitforseconds(2);
}

bool Retreat(Player& player, Monster& monster) {
	int p_diceamount = DiceRoll({ 0, 1, player.GetDex()});
	int m_diceamount = DiceRoll({ 0, 1, monster.GetDex()});

	if (p_diceamount > m_diceamount) 
	{
		RetreatBattle();
		return true;
	}
	if (p_diceamount < m_diceamount) 
	{
		return false;
	}
		
	return Retreat(player, monster);
}

void WinBattle(Player& player, Monster& monster)
{
	int rewardgil = monster.RewardGil();
	int rewardexp = monster.RewardEXP();
	int rewardID = monster.RewardID();
	int rewardChance = monster.RewardChange();
	cout << "====================================================================\n";
	TypeEffect("YOU WON THE BATTLE!", 60);
	Waitforseconds(1);
	cout << "You beat [" << monster.GetName() << "]\n";
	Waitforseconds(1);
	cout << "You gain [" << rewardgil << "] Gils. ";
	Waitforseconds(1);
	player.GainGil(rewardgil);
	cout << "Current Gils: [" << player.GetGil() << "]\n";
	Waitforseconds(1);
	cout << "You gain [" << rewardexp << "] EXP.  ";
	Waitforseconds(1);
	player.GainEXP(rewardexp);
	cout << "Current EXP: [" << player.GetEXP() << "].\n"; 
	Waitforseconds(1);
	cout << "You need[" << player.GetEXPToNextLevel() << "] to next level.\n";
	if (rewardID > 0) {
		int result = DiceRoll({ 0, 1, rewardChance });
		if (result == 1) {
			if (rewardID < 100000) {
				Waitforseconds(1);
				ItemInfo itemname = GetItemData(rewardID);
				cout << "you get [" << itemname.name << "]\n";
				player.AddItem(rewardID, 1);
			}
			else {
				Waitforseconds(1);
				EquipInfo equipname = GetGearData(rewardID);
				cout << "you get [" << equipname.name << "]\n";
				player.AddGear(rewardID, 1);
			}
		}
	}
	cout << "====================================================================\n";
	if (player.GetEXP() >= player.GetEXPToNextLevel()) {
		cout << "\nLEVEL UP!!";
		cout << "====================================================================\n";
		player.LevelUp();
	}
	Waitforseconds(2);
	return;
}

void RetreatBattle() 
{
	cout << "====================================================================\n";
	TypeEffect("You retreated from the battle", 30);
	cout << "====================================================================\n";
	Waitforseconds(2);
	return;
}
