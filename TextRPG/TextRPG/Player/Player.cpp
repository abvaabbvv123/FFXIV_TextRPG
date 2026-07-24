#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <algorithm>
#include "RaceData.h"
#include "JobData.h"
#include <string>
#include "Tools.h"
using namespace std;

Player::Player(string name, RaceType race, JobType job)
	: p_name(name)
{
	ApplyJob(job);
	ApplyRace(race);
	equipment.assign(3, -1);
	skills.assign(6, -1);
	skills[4] = 901;
	skills[5] = 904;
}

bool Player::IsAlive() const {return current_HP > 0;}
void Player::ApplyJob(JobType job) 
{
	Job data = GetJobData(job);
	p_job = data.jobname;
	max_HP = data.base_HP;
	current_HP = data.base_HP;
	max_MP = data.base_MP;
	current_MP = data.base_MP;
	s_str = data.str;
	s_dex = data.dex;
	s_con = data.con;
	s_int = data.intel;
	s_wis = data.wis;
	s_cha = data.cha;
	startdistance = data.startdistance;
};
void Player::ApplyRace(RaceType race) 
{
	Race data = GetRaceData(race);
	p_race = data.racename;
	s_str += data.bonus_str;
	s_dex += data.bonus_dex;
	s_con += data.bonus_con;
	s_int += data.bonus_int;
	s_wis += data.bonus_wis;
	s_cha += data.bonus_cha;
};
void Player::ApplyGear(int id) 
{
	EquipInfo gear_bonus = GetGearData(id);
	max_HP += gear_bonus.e_HP;
	max_MP += gear_bonus.e_MP;
	s_str += gear_bonus.e_str;
	s_dex += gear_bonus.e_dex;
	s_con += gear_bonus.e_con;
	s_int += gear_bonus.e_int;
	s_wis += gear_bonus.e_wis;
	s_cha += gear_bonus.e_cha;
	armor += gear_bonus.e_armor;

	Target target{ this, nullptr, true };
	if (gear_bonus.equipfunc1 == Bonus_Stats)
		gear_bonus.equipfunc1(gear_bonus, target);


}
void Player::RemoveGear(int id) 
{
	EquipInfo gear_bonus = GetGearData(id);
	max_HP -= gear_bonus.e_HP;
	current_HP = min(current_HP, max_HP);
	max_MP -= gear_bonus.e_MP;
	current_MP = min(current_MP, max_MP);
	s_str -= gear_bonus.e_str;
	s_dex -= gear_bonus.e_dex;
	s_con -= gear_bonus.e_con;
	s_int -= gear_bonus.e_int;
	s_wis -= gear_bonus.e_wis;
	s_cha -= gear_bonus.e_cha;
	armor -= gear_bonus.e_armor;

	Target target{ this, nullptr, false };
	if (gear_bonus.equipfunc1 == Bonus_Stats)
		gear_bonus.equipfunc1(gear_bonus, target);
}
//Add Remove
void Player::AddSkill(int slot, int id) 
{
	skills[slot] = id;
}
void Player::RemoveSkill(int slot) 
{
	skills[slot] = -1;
}
void Player::AddEquip(int slot, int id) 
{
		if (equipment[slot] != -1)
		{
			armory.Add(equipment[slot], 1);
			RemoveGear(equipment[slot]);
		}
		
		armory.Remove(id, 1);

		equipment[slot] = id;
		ApplyGear(id);
	}

void Player::RemoveEquip(int slot)
{
	if (equipment[slot] == -1) return;

	RemoveGear(equipment[slot]);
	armory.Add(equipment[slot], 1);
	equipment[slot] = -1;
}

void Player::LevelUp() {
	system("cls");
	exp_goal = 50 + (level * (50 + (level * 5)));
	level++;
	max_HP += s_con / 2;
	current_HP = max_HP;
	max_MP += s_int / 2;
	current_MP = max_MP;
	bonus_stat++;
	cout << "====================================================================\n";
	TypeEffect("LEVEL UP.\n", 30);
	Waitforseconds(1);
	cout << "Your level is [" << level << "] now.\n";
	Waitforseconds(1);
	cout << "Your Max HP is [" << max_HP << "] now.\n";
	Waitforseconds(1);
	cout << "Your Max MP is [" << max_MP << "] now.\n";
	cout << "====================================================================\n";
	if (bonus_stat < 2) {
		Waitforseconds(1);
		cout << "You can Increase any stat when next Level UP\n";
		cout << "====================================================================\n";
	}
	else {
		StatUp();
		bonus_stat = 0;
	}
}

bool CheckItem(const Player& player, int id, int count) {
	for (const auto& i : player.ViewInven()) {
		if (i.ID == id)
			return i.count >= count;
	}
	return false;
}
bool CheckGear(const Player& player, int id, int count) {
	for (const auto& i : player.ViewArmory()) {
		if (i.ID == id)
			return i.count >= count;
	}
	return false;
}
void Player::ShowStatus() const {
	EquipNameConvert gear = NameConvert(equipment[0], equipment[1], equipment[2]);
	cout << "====================================================================\n";
	cout << "Name:[" << p_name << "]  Race:[" << p_race << "]  Job:[" << p_job << "]\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "Level: [" << level << "]  EXP: [" << exp << "]  Exp to Next Level: [" << GetEXPToNextLevel() << "]\n";
	cout << "Weapon: [" << gear.weapon << "] Armor: [" << gear.armor << "] ACC: [" << gear.acc << "]" << endl;
	cout << "Status: HP[" << current_HP << "/" << max_HP << "]  MP[" << current_MP << "/" << max_MP << "]\n";
	cout << "STR:" << s_str << " DEX:" << s_dex << " CON:" << s_con << " INT:" << s_int << " WIS:" << s_wis << " CHA:" << s_cha <<"\n";
	cout << Gil << "GILS" << "\n";
	cout << "====================================================================\n";
}
void Player::StatUp() {
	while (true) {
	int answer = 0;
	system("cls");
	cout << "====================================================================\n";
	TypeEffect( "An awakening strength stirs within your very soul.\n", 30);
	TypeEffect( "Select number of attribute to augment (+1):\n", 30);
	cout << "--------------------------------------------------------------------\n";
	cout << "[Current Stats]\n";
	cout << "STR: " << s_str << " DEX: " << s_dex << " CON: " << s_con << " INT: " << s_int << " WIS: " << s_wis << " CHA: " << s_cha << "\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "[Answer with Number]\n";
	cout << "[1: STR] " << "[2: DEX] " << "[3: CON] " << "[4: INT] " << "[5: WIS] " << "[6: CHA]\n";
	cout << "====================================================================\nYour Answer: ";
	cin.clear();
	bool IsSuccess = true;
	string result;
	cin >> answer;
	
		

		switch (answer) {
		case 1: s_str++; result = "STR"; break;
		case 2: s_dex++; result = "DEX"; break;
		case 3: s_con++; result = "CON"; break;
		case 4: s_int++; result = "INT"; break;
		case 5: s_wis++; result = "WIS"; break;
		case 6: s_cha++; result = "CHA"; break;
		default:
			cout << "\n--------------------------------------------------------------------\n";
			cout << "Wrong answer.Try enter right number again:\n";
			cout << "--------------------------------------------------------------------\n";
			IsSuccess = false;
			Waitforseconds(1);
			continue;
		}
		if (IsSuccess) {
			cout << "\n--------------------------------------------------------------------\n";
			cout << "Increased your [" << result << "] +1\n";
			cout << "--------------------------------------------------------------------\n";
			Waitforseconds(2);
			break; }
	}
}