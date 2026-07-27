
#include "Skills.h"
#include "Player.h"
#include "Monster.h"
#include "Tools.h"
#include "Event.h"
#include "Battle.h"
#include "Tools.h"

using namespace std;

vector<SkillInfo> SkillList() {
	vector<SkillInfo> skills = {
		//                                                              modifier | dicecount | dicenum |      dicemod     |modvalue| HPcost | MPcost | range | addspeed | haste | effectvalue | duration |  Description                                                   | Effect1, Effect2|
		//Paladin
		{101, SkillType::Physical, StatsType::STR, "Fast Blade"         ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    0    ,  0    ,    20    ,   0   ,      0       ,    0     , "Delivers a physical attack with your strength. ( 1d(str) )", DealDamage, None},
		{102, SkillType::Physical, StatsType::STR, "Riot Blade"         ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        4   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a physical attack with your strength. ( 1d(str+4) )", DealDamage, None},
		{103, SkillType::Physical, StatsType::STR, "Rage of Halone"     ,    3    ,     2     ,/*STR*/0 ,Modifier::Divide,	   2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a powerful physical attack with your strength. ( 3+2d(str/2) )", DealDamage, None},
		{111, SkillType::Physical, StatsType::None,"Shield Bash"	    ,    0    ,     1     ,    4    ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,    150       ,    0     , "Delivers a physical attack and stuns the enemy. ( 1d4 )", DealDamage, ChangeSpeed},
		{112, SkillType::Physical, StatsType::STR, "Intervene"          ,    0    ,     0     ,/*STR*/0 ,Modifier::Divide,     3   ,   0    ,    0   ,   5   ,    20    ,   0   ,      -5       ,    0     , "Rushes toward the target.", DealDamage, ChangeDistance},
		{121, SkillType::Healing , StatsType::WIS, "Clemency"		    ,    0    ,     1     ,/*WIS*/0 ,Modifier::Divide,     2   ,   0    ,    5   ,   5   ,    -10   ,   0   ,      0       ,    0     , "Restores your own HP. ( 1d(wis/2) )", RestoreHP, None},
		{122, SkillType::Elemental, StatsType::INT, "Holy Spirit"       ,    0    ,     2     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   2   ,    -20   ,   0   ,      0       ,    0     , "Delivers a holy attack with your intelligence. ( 2d(int) )", DealDamage, None},
		{131, SkillType::Physical, StatsType::STR, "Royal Authority"    ,    4    ,     2     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    -40   ,   0   ,      30       ,    0     , "Delivers a powerful physical attack with your strength and slows the enemy. ( 4+2d(str) )", DealDamage, ChangeSpeed},
		{132, SkillType::Physical, StatsType::STR, "Goring Blade"       ,    0    ,     2     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    0     ,   0   ,      4       ,    2     , "Delivers a physical attack with your strength and inflicts a damage-over-time effect. ( 2d(str), plus 4 damage over 2 turns )", DealDamage, DOT},
		{133, SkillType::Physical, StatsType::STR, "Atonement"          ,    0    ,     3     ,/*STR*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    -20   ,   0   ,      0       ,    0     , "Delivers a physical attack with your strength. ( 3d(str) )", DealDamage, None},
		//Warrior
		{201, SkillType::Physical, StatsType::STR, "Heavy Swing"	    ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        4   ,   0    ,    0   ,   0   ,    -25   ,   0   ,       25     ,    0     , "Delivers a physical attack with your strength and slows the enemy. ( 1d(str+4) )", DealDamage, ChangeSpeed},
		{202, SkillType::Physical, StatsType::STR, "Malm"	            ,    0    ,     1     ,/*STR*/0 ,Modifier::Add,        8   ,   0    ,    0   ,   0   ,    -25   ,   0   ,       25     ,    0     , "Delivers a physical attack with your strength and slows the enemy ( 1d(str+8) )", DealDamage, ChangeSpeed},
		{203, SkillType::Physical, StatsType::STR, "Storm's Parth"	    ,    0    ,     2     ,/*STR*/0 ,Modifier::Subtract,   4   ,   0    ,    0   ,   0   ,    20     ,   0   ,       0     ,    0     , "Delivers a physical attack with your strength. ( 2d(str-4) )", DealDamage, None},
		{211, SkillType::Physical, StatsType::None, "Low Blow"	        ,    0    ,     1     ,    4    ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      150    ,    0     , "Delivers a physical attack. ( 1d4 )", DealDamage, ChangeSpeed},
		{212, SkillType::Physical, StatsType::STR, "Tomahawk"	        ,    0    ,     1     ,/*STR*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   3   ,    20    ,   0   ,       0     ,    0     , "Throw weapon and delivers a physical attack. ( 1d(str/2) )", DealDamage, None},
		{213, SkillType::Physical, StatsType::STR, "Onslaught"	        ,    0    ,     1     ,/*STR*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   3   ,    20    ,   0   ,       -5     ,    0     , "Rushes toward the target. ( 1d(str/2) )", DealDamage, ChangeDistance},
		{221, SkillType::Healing , StatsType::CON, "Equillbrium"	    ,    0    ,     1     ,/*CON*/0 ,Modifier::Divide,     2   ,   0    ,    3   ,   0   ,    0     ,   0   ,       0     ,    0     , "Restores your own HP. ( 1d(con/2) )", RestoreHP, None},
		{233, SkillType::Buff, StatsType::CON, "Vengeance"	            ,    0    ,     1     ,/*CON*/0 ,Modifier::Add,        0   ,   0    ,    3   ,   0   ,    0     ,   0   ,       0     ,    0     , "Delivers a physical attack based on your constitution. ( 1d(con) )", DealDamage, None},
		{231, SkillType::Physical, StatsType::STR, "Fell Cleave"	    ,    0    ,     3     ,/*STR*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,       0     ,    0     , "Delivers a powerful physical attack with your strength. ( 3d(str/2) )", DealDamage, None},
		{232, SkillType::Physical, StatsType::STR, "Inner Chaos"	    ,    2    ,     1     ,/*STR*/0 ,Modifier::Multiply,   2   ,   0    ,    0   ,   0   ,    0     ,   0   ,       0     ,    0     , "Delivers a devastating physical attack with your strength. ( 2+1d(str*2) )", DealDamage, None},
		//White Mage
		{301, SkillType::Elemental, StatsType::INT, "Stone"	            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    2   ,   3   ,    -20   ,   0   ,      0       ,    0     , "Delivers an earth attack with your intelligence. ( 1d(int) )", DealDamage, None},
		{302, SkillType::Elemental, StatsType::INT, "Stone II"	        ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        4   ,   0    ,    3   ,   3   ,    -20   ,   0   ,      0       ,    0     , "Delivers an earth attack with your intelligence. ( 1d(int+4) )", DealDamage, None},
		{303, SkillType::Elemental, StatsType::INT, "Glare"	            ,    0    ,     1     ,/*INT*/0 ,Modifier::Multiply,   2   ,   0    ,    4   ,   3   ,    -20   ,   0   ,      0       ,    0     , "Delivers a powerful earth attack with your intelligence. ( 1d(int*2) )", DealDamage, None},
		{311, SkillType::Healing ,  StatsType::WIS, "Cure"	            ,    0    ,     1     ,/*WIS*/0 ,Modifier::Divide,     2   ,   0    ,    2   ,   5   ,    -20   ,   0   ,      0       ,    0     , "Restores your own HP. ( 1d(wis/2) )", RestoreHP, None},
		{312, SkillType::Healing ,  StatsType::WIS, "Cure II"	        ,    0    ,     1     ,/*WIS*/0 ,Modifier::Subtract,   4   ,   0    ,    3   ,   5   ,    -20   ,   0   ,      0       ,    0     , "Restores your own HP. ( 1d(wis-4) )", RestoreHP, None},
		{313, SkillType::Healing ,  StatsType::WIS, "Tetragrammaton"    ,    0    ,     1     ,/*WIS*/0 ,Modifier::Add,        0   ,   0    ,    4   ,   5   ,    0     ,   0   ,      0       ,    0     , "Restores your own HP without casting. ( 1d(wis) )", RestoreHP, None},
		{321, SkillType::None,      StatsType::None, "Aetherial Shift"	,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    0     ,   0   ,      3       ,    0     , "Move back as 3 distance.",  ChangeDistance, None},
		{331, SkillType::Elemental, StatsType::INT, "Holy"	            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    4   ,   3   ,    -25   ,   0   ,      85       ,    0     ,"Delivers a holy attack and slows enemy. ( 1d(int) )", DealDamage, ChangeSpeed},
		{332, SkillType::Elemental, StatsType::INT, "Dia"	            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    2   ,   3   ,    0     ,   0   ,      0       ,    0     , "Delivers a holy attack with your intelligence. ( 1d(int) )", DealDamage, DOT},
		{333, SkillType::Elemental, StatsType::WIS, "Assize"	        ,    0    ,     1     ,/*WIS*/0 ,Modifier::Add,        0   ,   0    ,    6   ,   3   ,    0     ,   0   ,      0       ,    0     , "Delivers a holy attack and Restore own HP and MP. ( 1d(wis) )", Assize, None},
		//Rouge
		{401, SkillType::Physical, StatsType::DEX, "Spinning Edge"      ,    0    ,     1     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    20     ,   0   ,      0       ,    0     , "Delivers a physical attack with your dexterity. ( 1d(dex) )", DealDamage, None},
		{402, SkillType::Physical, StatsType::DEX, "Gust Slash"         ,    0    ,     1     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    35     ,   0   ,      0       ,    0     , "Delivers a physical attack with your dexterity. ( 1d(dex) )", DealDamage, None},
		{403, SkillType::Physical, StatsType::DEX, "Aeolian Edge"       ,    0    ,     1     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    50     ,   0   ,      0       ,    0     , "Delivers a physical attack with your dexterity. ( 1d(dex) )", DealDamage, None},
		{411, SkillType::Physical, StatsType::None, "Mug"			    ,    0    ,     1     ,       4 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    20     ,   0   ,      0       ,    0     , "Delivers a physical attack and steal gil from enemy. ( 1d4 )", DealDamage, Steal},
		{412, SkillType::Physical, StatsType::None, "Leg Sweep"         ,    0    ,     1     ,       4 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      120       ,    0     ,"Delivers a physical attack and stun the enemy ( 1d4 )", DealDamage, ChangeSpeed},
		{421, SkillType::Healing , StatsType::INT, "Meisui"             ,    0    ,     1     ,/*INT*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Restores your own HP. ( 1d(int/2 )", DealDamage, None},
		{422, SkillType::Buff,     StatsType::None, "BunShin"           ,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    2     , "Delivers additional damage when yu attack enemy for next 2 turn", DealDamage, None},
		{431, SkillType::Physical, StatsType::DEX, "Fuma Shuriken"      ,    0    ,     2     ,/*DEX*/0 ,Modifier::Divide,     2   ,   2    ,    0   ,   3   ,    25     ,   0  ,      0       ,    0     , "Delivers a ranged attack with your dexterity. ( 2d(dex/2) )", DealDamage, None},
		{432, SkillType::Elemental, StatsType::INT, "Raiton"            ,    0    ,     2     ,/*INT*/0 ,Modifier::Multiply,   2   ,   4    ,    4   ,   2   ,    0     ,   0   ,      0       ,    0     , "Delivers a lightning attack with your intelligence. ( 2d(int*2) )", DealDamage, None},
		{433, SkillType::Buff,     StatsType::None, "Huton"             ,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    2   ,   0   ,    0     ,   0   ,      0       ,    3     , "Increase your speed.", DealDamage, None},
		//Bard
		{501, SkillType::Physical, StatsType::DEX, "Heavy Shot"         ,    0    ,     2     ,/*DEX*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a physical attack with your dexterity. ( 2d(dex/2) )", DealDamage, None},
		{502, SkillType::Physical, StatsType::DEX, "Straight Shot"      ,    4    ,     2     ,/*DEX*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a physical attack with your dexterity. ( 4+2d(dex/2) )", DealDamage, None},
		{503, SkillType::Physical, StatsType::DEX, "Burst Shot"         ,    0    ,     3     ,/*DEX*/0 ,Modifier::Divide,     3   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a powerful physical attack with your dexterity. ( 3d(dex/3) )", DealDamage, None},
		{511, SkillType::Buff, StatsType::None, "Raging Strikes"        ,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    3     , "Increase your damage for 3 turns. ( 1d0 )", DealDamage, None},
		{512, SkillType::None, StatsType::None, "Repelling Shot"        ,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    35     ,   0   ,      3       ,    0     , "Gp back from the enemy with 3 distance. ( 1d0 )", None,  ChangeDistance},
		{521, SkillType::Healing, StatsType::CHA, "Mage's Ballad"       ,    0    ,     1     ,/*CHA*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Restore MP when start every turn.", Ballad, None},
		{522, SkillType::Healing, StatsType::CHA, "Army's Paeon"        ,    0    ,     1     ,/*CHA*/0 ,Modifier::Divide,     2   ,   0    ,    4   ,   0   ,    0     ,   0   ,      0       ,    0     , "Restore HP when start every turn", Paeon, None},
		{523, SkillType::Buff, StatsType::CHA, "The Wanderer's Minuet"  ,    0    ,     1     ,/*CHA*/0 ,Modifier::Divide,     2   ,   0    ,    6   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a additional damage when you attack", Minuet, None},
		{531, SkillType::Physical, StatsType::DEX, "Venomous Bite"      ,    0    ,     1     ,/*DEX*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a physical attack with poisonous damage. ( 1d(dex) )", DealDamage, DOT},
		{532, SkillType::Physical, StatsType::None, "Bloodletter"       ,    0    ,     1     ,       4 ,Modifier::Subtract,   0   ,   0    ,    1   ,   0   ,    75    ,   0   ,      0       ,    0     , "Delivers a physical attack with high speeed. ( 1d4 )", DealDamage, None},
		{533, SkillType::Physical, StatsType::DEX, "Resonant Arrow"     ,    0    ,     4     ,/*DEX*/0 ,Modifier::Divide,     2   ,   0    ,    0   ,   0   ,    0     ,   0   ,      0       ,    0     , "Delivers a powerful physical attack with your dexterity. ( 4d(dex/2) )", DealDamage, None},
		//Black Mage
		{601, SkillType::Elemental, StatsType::INT, "Scathe"             ,    0    ,     1     ,/*INT*/0 ,Modifier::Divide,     3   ,   0    ,    0   ,   0   ,   20    ,   0   ,      0       ,    0     , "Delivers a magic attack with your intelligence. ( 1d(int/3) )", DealDamage, None},
		{602, SkillType::Elemental, StatsType::INT, "Fire"               ,    0    ,     2     ,/*INT*/0 ,Modifier::Multiply,   2   ,   0    ,    6   ,   0   ,    -25  ,   0   ,      0       ,    0     , "Delivers a fire attack with your intelligence. ( 2d(int*2) )", DealDamage, None},
		{603, SkillType::Elemental, StatsType::INT, "Blizzard"           ,    0    ,     1     ,/*INT*/0 ,Modifier::Subtract,   4   ,   0    ,    0   ,   0   ,    0    ,   0   ,      0       ,    0     , "Delivers an ice attack with your intelligence. ( 1d(int-4) )", DealDamage, None},
		{604, SkillType::Elemental, StatsType::INT, "Thunder"            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    2   ,   0   ,    0    ,   0   ,      0       ,    2     , "Delivers a lightning attack with your intelligence. ( 1d(int) )", DealDamage, DOT},
		{611, SkillType::Healing , StatsType::INT, "Manaward"            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0    ,   0   ,      0       ,    0     , "Restores your own HP. ( 1d(int) )", RestoreHP, None},
		{612, SkillType::Healing, StatsType::INT, "Manafont"             ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0    ,   0   ,      0       ,    0     , "Restores fully your own MP. ( 1d(int) )", RestoreMP, None},
		{613, SkillType::Buff, StatsType::None, "Ley Lines"              ,    0    ,     1     ,       0 ,Modifier::Add,        0   ,   0    ,    0   ,   0   ,    0    ,   6   ,      0       ,    0     , "Haste your speed, Until you change distance. ( 1d0 )", DealDamage, None},
		{631, SkillType::Elemental, StatsType::INT, "Paradox"            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    4   ,   0   ,    0    ,   0   ,      0       ,    0     , "Delivers a magic attack with your intelligence. ( 1d(int) )", DealDamage, None},
		{632, SkillType::Elemental, StatsType::INT, "Despair"            ,    0    ,     1     ,/*INT*/0 ,Modifier::Add,        0   ,   0    ,    0  ,   0   ,    0    ,   0   ,      0       ,    0     , "Delivers an ice attack with your intelligence. ( 1d(int) )", DealDamage, None},
		//normal
		{901, SkillType::None, StatsType::None, "Go forward"		    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    35    ,   0   ,      -1      ,    0     , "Go forward to the enemy with 1 distance.", ChangeDistance, None },
		{902, SkillType::None, StatsType::None, "Rush"				    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    0     ,   0   ,      -2      ,    0     , "Go forward to the enemy with 2 distance.", ChangeDistance, None },
		{903, SkillType::None, StatsType::None, "Charge"			    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    -20   ,   0   ,      -3      ,    0     , "Go forward to the enemy with 3 distance.", ChangeDistance, None },
		{904, SkillType::None, StatsType::None, "Go back"		        ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    35    ,   0   ,      1       ,    0     ,    "Go back from the enemy with 1 distance.", ChangeDistance, None },
		{905, SkillType::None, StatsType::None, "Withdrawal"		    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    0     ,   0   ,      2       ,    0     , "Go back from the enemy with 2 distance.", ChangeDistance, None },
		{906, SkillType::None, StatsType::None, "a"					    ,    0    ,     0     , 0       ,Modifier::Add,        0   ,   0    ,    0   ,   5   ,    -20   ,   0   ,      3       ,    0     , "Go back from the enemy with 3 distance.", ChangeDistance, None }
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

static int GetPlayerStats(Player& player, StatsType stats) {
	switch (stats) {
	case StatsType::STR: return player.GetSTR();
	case StatsType::DEX: return player.GetDEX();
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
		dicenum = GetModCalc(GetPlayerStats(context.caster, skill.status), skill.modvalue, skill.dicemod);
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
void RestoreHP(const SkillInfo& skill, SkillContext& context) {
    int dicenum = skill.dicenum;
    if (skill.status != StatsType::None)
		dicenum = GetModCalc(GetPlayerStats(context.caster, skill.status), skill.modvalue, skill.dicemod);

    int amount = DiceRoll({ skill.modifier, skill.dicecount, dicenum });
    context.caster.HealHP(amount); 
	cout << "=====================================================================\n";
	cout << "You used [" << skill.name << "]!" << endl;
	Waitforseconds(1);
	cout << "You restore [" << amount << "] HP.\n";
	cout << "====================================================================\n";
	Waitforseconds(1);
}
void RestoreMP(const SkillInfo& skill, SkillContext& context) {
	int dicenum = skill.dicenum;
	if (skill.status != StatsType::None)
		dicenum = GetModCalc(GetPlayerStats(context.caster, skill.status), skill.modvalue, skill.dicemod);

	int amount = DiceRoll({ skill.modifier, skill.dicecount, dicenum });
	context.caster.HealMP(amount);
	cout << "=====================================================================\n";
	cout << "You used [" << skill.name << "]!" << endl;
	Waitforseconds(1);
	cout << "You restore [" << amount << "] MP.\n";
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
		playernum = GetPlayerStats(context.caster, skill.status);
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
//special skills
void Assize(const SkillInfo& skill, SkillContext& context) {
	DealDamage(skill, context);
	RestoreHP(skill, context);
	RestoreMP(skill, context);
}
void Steal(const SkillInfo& skill, SkillContext& context) {
	int amount = DiceRoll({ 0, 1, 5 * context.caster.GetDEX() });
	cout << "=====================================================================\n";
	cout << "You used [" << skill.name << "]!" << endl;
	Waitforseconds(1);
	cout << "You Steal [" << amount << "] Gil from enemy.\n";
	cout << "====================================================================\n";
	context.caster.GainGil(amount);
	Waitforseconds(1);

}
void ApplyHaste(const SkillInfo& skill, SkillContext& context) {}
void DOT(const SkillInfo& skill, SkillContext& context) {}
void Ballad (const SkillInfo& skill, SkillContext& context) {}
void Paeon(const SkillInfo& skill, SkillContext& context) {}
void Minuet(const SkillInfo& skill, SkillContext& context) {}
SkillInfo GetSkillData(int id)
{
	vector<SkillInfo> skills = SkillList();
	for (const auto& s : skills)
		if (s.ID == id) 
			return s;

	return skills[0];
}

