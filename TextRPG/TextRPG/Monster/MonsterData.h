#pragma once
#include <string>
#include <vector>
#include "Monster.h"
#include "Tools.h"
#include <iostream>
using namespace std;

class Player;

enum class MonsterType {
	Ladybug = 1,
	Spirits = 2,
	FieldMonster = 3,
	QuestMonster = 4,
	Boss = 10,
	};
struct MonsterData;
using MonsterAI = void(*)(Player& player, Monster& monster, int& distance);
struct MonsterData
{
	int ID;
	MonsterType type;
	string name;

	int hp, range, armor, speed;
	DiceCalc attackdice;
	int str, dex, con, intel, wis, cha;
	int critical;
	int dodge;
	int startdistance;
	int gil, exp;
	int rewardID, reward_chance;
	string skill_name;
	MonsterAI AIname;
	};

vector<MonsterData> MonsterList();
MonsterData GetMonsterDataByID(int id);
Monster CreateMonster(int id);

//skills
void NormalAttack(int id, Player& player);
void Needle(int id, Player& player, int& distance);
void Forward(Monster& monster, int& distance, int speed);
void Retreat(Monster& monster, int& distance, int speed);

//AIs
void MonsterAction(Player& player, Monster& monster, int& distance);
void Normal_Melee(Player& player, Monster& monster, int& distance);
void Normal_Ranged(Player& player, Monster& monster, int& distance);

void Sabotender(Player& player, Monster& monster, int& distance);