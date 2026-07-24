#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Player;
class Monster;
struct ObjectInfo;

enum class SkillType {
	Physical = 1,Elemental = 2,	Healing = 3,Debuff = 4,Buff = 5,None = 6
};
enum class StatsType {
	STR, DEX, CON, INT, WIS, CHA, HP, MP, Speed, None
};
enum class Modifier {
	Add, Subtract, Multiply, Divide
};
struct SkillContext {
	Player& caster;
	Monster* target;
	int& distance;
	ObjectInfo& target_entity;
};

struct SkillInfo;
using skill_func = void(*)(const SkillInfo&, SkillContext& context);
using ModifierCalc = int(*)(int a, int b, Modifier mod);
struct SkillInfo {
	int ID;
	SkillType type;
	StatsType status;
	string name;
	int modifier, dicecount, dicenum;
	Modifier dicemod; int modvalue;
	int HP_cost, MP_cost, range, addspeed, haste;
	int effectvalue, duration;
	string description;
	skill_func effectfunc_1;
	skill_func effectfunc_2;
};

void UseSkill(const SkillInfo& skill, SkillContext& context);
void None(const SkillInfo& skill, SkillContext& context);
void DealDamage(const SkillInfo& skill, SkillContext& context);
void Heal(const SkillInfo& skill, SkillContext& context);
void ChangeDistance(const SkillInfo& skill, SkillContext& context);
void ChangeSpeed(const SkillInfo& skill, SkillContext& context);
void ApplyHaste(const SkillInfo& skill, SkillContext& context);
void DOT(const SkillInfo& skill, SkillContext& context);

vector<SkillInfo> SkillList();
const unordered_map<int, SkillInfo> GetSkillMap();
SkillType IntToSkillType(int num);
SkillInfo GetSkillData(int id);
