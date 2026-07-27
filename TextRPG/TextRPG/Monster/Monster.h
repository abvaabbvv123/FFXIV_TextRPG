#pragma once
#include <string>
#include "Tools.h"

using namespace std;

class Monster
{
public:
	Monster(int ID, string name, int hp, DiceCalc attackdice, int armor, int range, int speed,
		int str, int dex, int con, int intel, int wis, int cha, int gil, int exp, int critical, int dodge, int startdistance,
		int reward_id, int reward_chance
);
	//getters
	string GetName() const { return m_name; };
	int GetID() const { return m_id; };
	int GetHP() const { return m_hp; };
    int GetRange() const { return m_range; };
	int GetSTR() const { return m_str; };
	int GetDex() const { return m_dex; };
	int GetCON() const { return m_con; };
	int GetINT() const { return m_int; };
	int GetWIS() const { return m_wis; };
	int GetCHA() const { return m_cha; };
	int GetSpeed() const { return m_speed; };
	int GetStartDistance() const { return startdistance; }
	int RewardGil() const { return m_gil; };
	int RewardEXP() const { return m_EXP; };
	bool IsAlive() const;
	int GetDodge() const { return m_dodge; }
	int GetCRI() const { return m_critical; }
	int RewardID()const { return reward_ID; }
	int RewardChange() const { return reward_chance; }

	//setters
	void TakeDamage(int rawdamage);
	int attack() const;
	
private:
	int m_id;
	string m_name;
	int m_hp;
	int m_maxhp;
	DiceCalc m_attack;
	int m_armor;
	int m_range;
	int m_speed;
	int m_str, m_dex, m_con, m_int, m_wis, m_cha;
	int m_gil, m_EXP;
	int m_critical;
	int m_dodge;
	int reward_ID;
	int reward_chance;
	int startdistance;
};