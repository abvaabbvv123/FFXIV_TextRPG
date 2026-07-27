#include "Monster.h"
#include "Tools.h"
#include <algorithm>

using namespace std;

Monster::Monster(int ID, string name, int hp, DiceCalc attackdice, int armor, int range, int speed,
	int str, int dex, int con, int intel, int wis, int cha, int gil, int exp, int critical, int dodge, int startdistance, int reward_ID, int reward_chance)
	: m_id(ID), m_name(name), m_hp(hp), m_maxhp(hp), m_attack(attackdice),
	m_armor(armor), m_range(range), m_speed(speed), m_str(str), m_dex(dex), m_con(con),
	m_int(intel), m_wis(wis), m_cha(cha), m_gil(gil), m_EXP(exp), m_critical(critical), m_dodge(dodge), startdistance(startdistance), reward_ID(reward_ID), reward_chance(reward_chance)
{
}

	bool Monster::IsAlive() const {
		return m_hp > 0;
	}

	void Monster::TakeDamage(int rawdamage) {
		int finaldamage = rawdamage - m_armor;
		if (finaldamage < 0)
			finaldamage = 0;
		m_hp -= finaldamage;
		if (m_hp < 0)
			m_hp = 0;	
	}
	int Monster::attack() const {
		return DiceRoll(m_attack);
	};

	

