
#include "Skills.h"
#include "Player.h"
#include "Monster.h"
#include "dice.h"
#include "Event.h"
#include "Battle.h"
#include "Tools.h"

using namespace std;

vector<SkillInfo> SkillList() {
	vector<SkillInfo> skills = {
		//                                                              modifier | dicecount | dicenum |      dicemod     |modvalue| HPcost | MPcost | range | addspeed | haste | effectvalue | duration |
		//Paladin
		{101, SkillType::Physical, StatsType::STR, "Fast Blade"         ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    0    ,  0    ,    20    ,   0   ,      0       ,    0     , "Delivers an physical attack with your strength. ( 1d(str) )", DealDamage, None},
		{102, SkillType::Physical, StatsType::STR, "Riot Blade"         ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        4   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers an physical attack with your strength. ( 1d(str+4) )", DealDamage, None},
		{103, SkillType::Physical, StatsType::STR, "Rage of Halone"     ,    3    ,     2     ,/*STR*/0 ,Modifier::Divide,	   2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers an powerful physical attack with your strength. ( 3+2d(str/2) )", DealDamage, None},
		{111, SkillType::Physical, StatsType::None, "Shield Bash"	    ,    0    ,     1     ,    4    ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,    150       ,    0     , "Delivers an physical attack and stun target enmey. ( 1d4 )", DealDamage, ChangeSpeed},
		{112, SkillType::Physical, StatsType::STR, "Intervene"          ,    0    ,     0     ,/*STR*/0 ,Modifier::Divide,     3   ,   0    ,    0   ,   5   ,    20    ,   0   ,      5       ,    0     , "Delivers an fatal physical attack with your strength. ( 1d(str) )", DealDamage, ChangeDistance},
		{121, SkillType::Healing , StatsType::WIS, "Clemency"		    ,    0    ,     1     ,/*WIS*/0 ,Modifier::Divide,     2   ,   0    ,    5   ,   5   ,    -10   ,   0   ,      0       ,    0     , "Restores HP myself. ( 1d(wis) )", Heal, None},
		{122, SkillType::Elemental, StatsType::INT, "Holy Spirit"       ,    0    ,     2     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   2   ,    -20   ,   0   ,      0       ,    0     , "Delivers an fatal physical attack with your strength. ( 1d(str) )", DealDamage, None},
		{131, SkillType::Physical, StatsType::STR, "Royal Authority"    ,    4    ,     2     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    -40   ,   0   ,      30       ,    0     , "Delivers an fatal physical attack with your strength. ( 1d(str) )", DealDamage, ChangeSpeed},
		{132, SkillType::Physical, StatsType::STR, "Goring Blade"       ,    0    ,     2     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    0     ,   0   ,      4       ,    2     , "Delivers an fatal physical attack with your strength. ( 1d(str) )", DealDamage, DOT},
		
		
		{105, SkillType::Physical, StatsType::STR, "Atonement"          ,    2    ,     2     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    -20   ,   0   ,      0       ,    0     , "Delivers an fatal physical attack with your strength. ( 1d(str) )", DealDamage, None},
		//Warrior
		{201, SkillType::Physical, StatsType::STR, "Heavy Swing"	    ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      20     ,    0     , "Delivers an physical attack and make enemy to slow. ( 1d(str) )", DealDamage, ChangeSpeed},
		//White Mage 
		{301, SkillType::Physical, StatsType::INT, "Stone"	            ,    1    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    2   ,   3   ,    0     ,   0   ,      0       ,    0     , "Delivers an earth magic. ( 1+1d(int) )", DealDamage, None},
		//Rouge
		{401, SkillType::Physical, StatsType::DEX, "Royal Authority"    ,    0    ,     2     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    -20   ,   0   ,      0       ,    0     , "Delivers an fatal physical attack with your strength.", DealDamage, None},
		//Bard
		{501, SkillType::Physical, StatsType::DEX, "Royal Authority"    ,    0    ,     1     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    -20   ,   0   ,      0       ,    0     , "Delivers an fatal physical attack with your strength.", DealDamage, None},
		//Black Mage
		{601, SkillType::Physical, StatsType::INT, "Royal Authority"    ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    -20   ,   0   ,      0       ,    0     , "Delivers an fatal physical attack with your strength.", DealDamage, None},
		//normal
		{901, SkillType::None, StatsType::None, "Go forward"		    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    35    ,   0   ,      1       ,    0     , "Go forward to the enemy with 1 distance.", ChangeDistance, None },
		{902, SkillType::None, StatsType::None, "Rush"				    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    0     ,   0   ,      2       ,    0     , "Go forward to the enemy with 2 distance.", ChangeDistance, None },
		{903, SkillType::None, StatsType::None, "Charge"			    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    -20   ,   0   ,      3       ,    0     , "Go forward to the enemy with 3 distance.", ChangeDistance, None },
		{904, SkillType::None, StatsType::None, "Go back"		        ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    35    ,   0   ,      1       ,    0     ,    "Go back from the enemy with 1 distance.", ChangeDistance, None },
		{905, SkillType::None, StatsType::None, "Withdrawal"		    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    0     ,   0   ,      2       ,    0     , "Go back from the enemy with 2 distance.", ChangeDistance, None },
		{906, SkillType::None, StatsType::None, "a"					    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    -20   ,   0   ,      3       ,    0     , "Go back from the enemy with 3 distance.", ChangeDistance, None },
	};
	return skills;
}
const unordered_map<int, SkillInfo> GetSkillMap() {
	static unordered_map<int, SkillInfo> skillmap = []() {
		unordered_map<int, SkillInfo> result;
		for (const auto& skill : SkillList()) {
			result[skill.ID] = skill;
		}
		return result;
		}();
	return skillmap;
}


SkillType IntToSkillType(int num)
{
	return static_cast<SkillType>(num);
}

static int GetStatsValue(Player& player, StatsType stats) {
	switch (stats) {
	case StatsType::STR: return player.GetSTR();
	case StatsType::DEX: return player.GetDex();
	case StatsType::CON: return player.GetCON();
	case StatsType::INT: return player.GetINT();
	case StatsType::WIS: return player.GetWIS();
	case StatsType::CHA: return player.GetCHA();
	case StatsType::HP: return player.GetHP();
	case StatsType::MP: return player.GetMP();
	case StatsType::Speed: return player.GetSpeed();
	default: return 4;
	}
}
static int GetMonsterStats(Monster& monster, StatsType stats) {
	switch (stats) {
	case StatsType::STR: return monster.GetSTR();
	case StatsType::DEX: return monster.GetDex();
	case StatsType::CON: return monster.GetCON();
	case StatsType::INT: return monster.GetINT();
	case StatsType::WIS: return monster.GetWIS();
	case StatsType::CHA: return monster.GetCHA();
	case StatsType::Speed: return monster.GetSpeed();
	default: return 4;
	}
}
static int GetModCalc(int a, int b, Modifier mod) {
	switch (mod) {
	case Modifier::Add: return a + b;
	case Modifier::Subtract: return a - b;
	case Modifier::Multiply: return a * b;
	case Modifier::Divide: return (b != 0) ? a / b : 1;
	default: return 1;
	}
}

void UseSkill(const SkillInfo& skill, SkillContext& context) 
{
	if(skill.effectfunc_1)
		skill.effectfunc_1(skill, context);
	if(skill.effectfunc_2 && skill.effectfunc_2 != None)
		skill.effectfunc_2(skill, context);
}

void None(const SkillInfo& skill, SkillContext& context) {
}

void DealDamage(const SkillInfo& skill, SkillContext& context)
{
	if (context.target == nullptr) {
		cout << "Cannot find target.\n";
		return;
	}
	int dicenum = skill.dicenum;
	if (skill.status != StatsType::None)
		dicenum = GetModCalc(GetStatsValue(context.caster, skill.status), skill.modvalue, skill.dicemod);
	int dice20 = DiceRoll({ 0, 1, 20 });
	int damage = DiceRoll({ skill.modifier + context.caster.GetBonusModifier(), skill.dicecount + context.caster.GetBonusCount(), dicenum + context.caster.GetBonusNum()});

	if (dice20 >= context.caster.GetCri()) {
		damage += DiceRoll({ skill.modifier + context.caster.GetBonusModifier(), skill.dicecount + context.caster.GetBonusCount(), dicenum + context.caster.GetBonusNum() });
		context.target->TakeDamage(damage);
		cout << "=====================================================================\n";
		cout << "You used [" << skill.name << "]!" << endl;
		Waitforseconds(1);
		TypeEffect("CRITICAL!!", 120);
		cout << "You deal " << damage << " points of damage to the " << context.target->GetName() << ".\n";
		cout << "====================================================================\n";
		Waitforseconds(1);
	}
    else if (dice20 <= context.target->GetDodge()) {
		cout << "=====================================================================\n";
		cout << "You used [" << skill.name << "]!" << endl;
		Waitforseconds(1);
		cout << "But " << context.target->GetName() << " dodged your attack" << ".\n";
		cout << "====================================================================\n";
		Waitforseconds(1);
	}
	else {
		context.target->TakeDamage(damage);
		cout << "=====================================================================\n";
		cout << "You used [" << skill.name << "]!" << endl;
		Waitforseconds(1);
		cout << "You deal " << damage << " points of damage to the " << context.target->GetName() << ".\n";
		cout << "====================================================================\n";
		Waitforseconds(1);
	}


}

void ChangeDistance(const SkillInfo& skill, SkillContext& context) {
	cout << "=====================================================================\n";
	cout << "You used [" << skill.name << "]!" << endl;
	Waitforseconds(1);
	if (skill.effectvalue > 0) {
		context.distance = min(4, context.distance + skill.effectvalue);
		cout << "====================================================================\n";
		cout << "You leap backward, creating a distance of [" << skill.effectvalue << "]" << (skill.effectvalue == 1 ? "yalm" : "yalms") << "from the target.\n";
		cout << "====================================================================\n";
	}
	else if (skill.effectvalue < 0) {
		int effectvalue = abs(skill.effectvalue);
		context.distance = min(0, context.distance + skill.effectvalue);
		cout << "====================================================================\n";
		cout << "You rush forward, closing the distance by [" << effectvalue << "]" << (effectvalue == 1 ? "yalm" : "yalms") << "toward the target.\n";
		cout << "====================================================================\n";
	}
	Waitforseconds(1);
	cout << "Current Distance: [" << context.distance << "]\n";
	cout << "====================================================================\n";
	Waitforseconds(1);
}
void Heal(const SkillInfo& skill, SkillContext& context) {
    int dicenum = skill.dicenum;
    if (skill.status != StatsType::None)
		dicenum = GetModCalc(GetStatsValue(context.caster, skill.status), skill.modvalue, skill.dicemod);

    int amount = DiceRoll({ skill.modifier, skill.dicecount, dicenum });
    context.caster.HealHP(amount); 
	cout << "=====================================================================\n";
	cout << "You used [" << skill.name << "]!" << endl;
	Waitforseconds(1);
	cout << "You restore [" << amount << "] HP.\n";
	cout << "====================================================================\n";
	Waitforseconds(1);
}
void ChangeSpeed(const SkillInfo& skill, SkillContext& context) {
	if (context.target == nullptr) {
		cout << "Cannot find target.\n";
		return;
	}
	int playernum = 10;
	int monsternum = 10;
	if (skill.status != StatsType::None) {
		playernum = GetStatsValue(context.caster, skill.status);
		monsternum = GetMonsterStats(*context.target, skill.status);
	}
	while (true) {
	int playerdice = DiceRoll({ 0, 1, playernum});
	int monsterdice = DiceRoll({ 0, 1, monsternum });

	if (playerdice > monsterdice) { 
		context.target_entity.gauge -= skill.effectvalue; 
		Waitforseconds(1);
		cout << "The enemy's movemonet has been slowed. \n";
		cout << "====================================================================\n";
		Waitforseconds(1);
		break; }
	if (playerdice < monsterdice) {  
		Waitforseconds(1);
		cout << "The enemy resisted!. \n";
		cout << "====================================================================\n";
		Waitforseconds(1);
		break; }

	}

}
void ApplyHaste(const SkillInfo& skill, SkillContext& context) {}
void DOT(const SkillInfo& skill, SkillContext& context) {}
SkillInfo GetSkillData(int id)
{
	vector<SkillInfo> skills = SkillList();
	for (const auto& s : skills)
		if (s.ID == id) 
			return s;

	return skills[0];
}

