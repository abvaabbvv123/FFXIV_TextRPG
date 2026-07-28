#include "MonsterData.h"
#include "Player.h"
#include "Event.h"
#include "Tools.h"
using namespace std;

vector<MonsterData> MonsterList() {
	vector<MonsterData> monsters = {
		//Chapter 1
		{1, MonsterType::FieldMonster, "Little Ladybug", 15, 0, 0, 1,  {0, 1, 3},     6, 6, 6 ,6, 6, 6,  20, 1, 0,	250, 12, 1, 2, "Rush", Normal_Melee},
		{2, MonsterType::FieldMonster, "Water Spirits",  21, 2, 0, 1,  {0, 1, 4},     6, 6, 6 ,8, 6, 6,  20, 1, 3,	0, 20, 1003, 1, "Water Cannon", Normal_Ranged},
		{3, MonsterType::FieldMonster, "Fire Spirits",  21, 2, 0, 1,  {0, 1, 4},     6, 6, 6 ,8, 6, 6,  20, 1, 3,	0, 20, 1002, 1, "Fire", Normal_Ranged},
		{4, MonsterType::FieldMonster, "Earth Spirits",  21, 2, 0, 1,  {0, 1, 4},     6, 6, 6 ,8, 6, 6,  20, 1, 3,	0, 20, 1004, 1, "Stone", Normal_Ranged},
		{5, MonsterType::FieldMonster, "Ice Spirits",  21, 2, 0, 1,  {0, 1, 4},     6, 6, 6 ,8, 6, 6,  20, 1, 3,	0, 20, 1005, 1, "Blizzard", Normal_Ranged},
		{6, MonsterType::FieldMonster, "Thunder Spirits",  21, 2, 0, 1,  {0, 1, 4},     6, 6, 6 ,8, 6, 6,  20, 1, 13,	0, 20, 1006, 1, "Thunder", Normal_Ranged},
		{7, MonsterType::FieldMonster, "Cactuar",  30, 1, 0, 2,  {0, 1, 10},     8, 6, 8 ,4, 4, 6,  20, 1, 1,	1000, 10, 2, 2, "10 Needle", Sabotender},
		{8, MonsterType::FieldMonster, "Goblin Hunter",  18, 3, 0, 1,  {0, 1, 4},     6, 8, 6 ,4, 4, 6,  20, 1, 2,	300, 12, 1, 2, "Shot Arrow", Normal_Ranged},
		{9, MonsterType::FieldMonster, "Coblyn",  22, 1, 1, 1,  {0, 1, 5},     6, 6, 6 ,8, 6, 6,  20, 1, 0,	400, 16, 5, 2, "Electric Field", Normal_Melee},
		{10, MonsterType::FieldMonster, "Marmot",  18, 0, 0, 1,  {0, 1, 3},     6, 6, 6 ,8, 6, 6,  20, 1, 0,	250, 12, 5, 2, "Rush", Normal_Melee},
		
		
		{101, MonsterType::QuestMonster, "Scalekin", 32, 0, 0, 2,  {0, 1, 6},     8, 8, 8 ,4, 4, 4,  19, 2, 0,	520, 22, 101, 1, "Rush", Normal_Melee},
		{1001, MonsterType::Boss, "King Tonberry", 64, 0, 0, 1,  {0, 1, 5},     10, 6, 10 ,2, 2, 2,  19, 1, 0,	9999, 99, 799003, 1, "Step", Normal_Melee}
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
		data.str, data.dex, data.con, data.intel, data.wis, data.cha, data.gil, data.exp, data.critical, data.dodge, data.startdistance, data.rewardID, data.reward_chance, 0);
}

/////////////////////////////::Skills
void NormalAttack(int id, Player& player) {
	MonsterData data = GetMonsterDataByID(id);
	int rawdamage = DiceRoll(data.attackdice);
    
	cout << "====================================================================\n";
	Waitforseconds(1);
	cout << "[" << data.name << "] used ["<< data.skill_name << "]!" << endl;
	int roll = DiceRoll({ 0, 1, 20 });
	// cout << "Roll result: " << roll << endl;
	Waitforseconds(1);
	if (roll <= player.GetDodge()) {
		cout << "You dodged. Didn't get hit by ["<< data.name <<"]."  << endl;
		
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
void Needle(int id, Player& player, int& distance) {
	MonsterData data = GetMonsterDataByID(id);
	int rawdamage = 10;

	cout << "====================================================================\n";
	Waitforseconds(1);
	cout << "[" << data.name << "] casted" << data.skill_name << "]!" << endl;
	
	Waitforseconds(1);
	if (distance > data.range) {
		cout << "You dodged. Didn't get hit by [" << data.name << "]." << endl;

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
/////////////////////////////::AI
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
void Sabotender(Player& player, Monster& monster, int& distance) {
	MonsterData data = GetMonsterDataByID(monster.GetID());

	if (monster.GetCharge() > 0) {
		if (monster.GetCharge() >= 2) {
			Needle(data.ID, player, distance);
			monster.ChargeReset();
			Waitforseconds(1);
		}
		else {
			cout << "[" << data.name << "] is casting [" << data.skill_name << "]...\n";
			Waitforseconds(1);
			monster.ChargeUP();
		}
		return;
	}
	if (distance > data.range) {
		Forward(monster, distance, data.speed);
		Waitforseconds(1);
	}
	else {
		cout << "[" << data.name << "] is casting [" << data.skill_name << "]...\n";
		Waitforseconds(1);
		monster.ChargeUP();
	}
}



