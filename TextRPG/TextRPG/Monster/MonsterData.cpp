#include "MonsterData.h"
#include "Player.h"
#include "Event.h"
#include "Tools.h"
using namespace std;

vector<MonsterData> MonsterList() {
	vector<MonsterData> monsters = {
		//Chapter 1
		{1, MonsterType::Ladybug, "Little Ladybug", 18, 0, 0, 1,  {0, 1, 4},     6, 6, 6 ,6, 6, 6,  20, 1, 0,	100, 10, 1, 2, Normal_Melee},
		{2, MonsterType::Spirits, "Water Spirits",  22, 2, 0, 1,  {0, 1, 3},     6, 6, 6 ,8, 6, 6,  20, 1, 1,	100, 10, 1, 2, Normal_Ranged},
		{7, MonsterType::QuestMonster, "Scalekin", 32, 0, 0, 2,  {0, 1, 6},     8, 8, 8 ,4, 4, 4,  19, 2, 0,	520, 22, 101, 1, Normal_Melee},
		{101, MonsterType::Boss, "King Tonberry", 120, 0, 0, 1,  {0, 1, 5},     10, 6, 10 ,2, 2, 2,  19, 1, 0,	9999, 99, 799003, 1, Normal_Melee}
	};
	return monsters;
}


MonsterData GetMonsterDataByID(int id) {
	auto monsters = MonsterList();
	for (const auto& m : monsters) {
		if (m.ID == id) return m;
	}
	return monsters.empty() ? MonsterData{} : monsters[0];
}

Monster CreateMonster(int id) {
	MonsterData data = GetMonsterDataByID(id);
	return Monster(id, data.name, data.hp, data.attackdice, data.armor, data.range, data.speed,
		data.str, data.dex, data.con, data.intel, data.wis, data.cha, data.gil, data.exp, data.critical, data.dodge, data.startdistance, data.rewardID, data.reward_chance);
}

void NormalAttack(int id, Player& player) {
	MonsterData data = GetMonsterDataByID(id);
	int rawdamage = DiceRoll(data.attackdice);
    
	cout << "====================================================================\n";
	Waitforseconds(1);
	cout << "[" << data.name << "] attacked you!" << endl;
	int roll = DiceRoll({ 0, 1, 20 });
	// cout << "Roll result: " << roll << endl;
	Waitforseconds(1);
	if (roll <= player.GetDodge()) {
		cout << "You dodged. Didn't get hit by "<< data.name <<"."  << endl;
		
	}
	else if (roll >= data.critical) {
		rawdamage += DiceRoll(data.attackdice);
		cout << "CRITICAL!! you got damaged [" << rawdamage << "]!" << endl;
		player.TakeDamage(rawdamage);
	}
	else {
		cout << "you got damaged [" << rawdamage << "]." << endl;
		player.TakeDamage(rawdamage);
	}
	cout << "====================================================================\n";
}

void Forward(Monster& monster,  int& distance, int speed) {
	distance = max(0, distance - speed);
	cout << "====================================================================\n";
	cout << "The [" << monster.GetName() << "] draws near to you\n";
	Waitforseconds(1);
	cout << "Current Distnace: [" << distance << "]\n";
	cout << "====================================================================\n";
	

}
void Retreat(Monster& monster,  int& distance, int speed) {
	distance = min(4, distance + speed);
	cout << "====================================================================\n";
	cout << "The [" << monster.GetName() << "] move away from you\n";
	Waitforseconds(1);
	cout << "Current Distnace: [" << distance << "]\n";
	cout << "====================================================================\n";
}

void MonsterAction(Player& player, Monster& monster, int& distance) {
    MonsterData data = GetMonsterDataByID(monster.GetID());
    if (data.AIname) {
        data.AIname(player, monster, distance);
    }
}
void Normal_Melee(Player& player, Monster& monster, int& distance) {
	MonsterData data = GetMonsterDataByID(monster.GetID());
	if (distance <= data.range) {
		NormalAttack(data.ID, player);
	}
	else {
		Forward(monster, distance, data.speed);
	}
}
void Normal_Ranged(Player& player, Monster& monster, int& distance) {
	MonsterData data = GetMonsterDataByID(monster.GetID());
		if (distance == 0) {
		int change = DiceRoll({ 0, 1, 2 });
		if (change == 1)
			Retreat(monster, distance, data.speed);
		else if (change == 2)
			NormalAttack(data.ID, player);
	}
		else if (distance <= data.range) {
			NormalAttack(data.ID, player);
		}
		else {
			Forward(monster, distance, data.speed);
		}
}



