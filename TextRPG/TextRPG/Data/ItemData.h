#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

class Player;
class Monster;

enum class EquipType {
	Weapon = 0,
	Gear = 1,
	Acc = 2,
	None = 3
};
enum class ItemType {
	Useable = 0,
	KeyItem = 1,
	Miscellaneous = 2,
	None = 3
};
enum class BonusType {
	None, dicemodifier, dicecount, dicenum, startdistance, dodge, critical, initiative_p, initiative_b, manabonus
};
struct BonusStat {
	BonusType bonustype;
	int amount;
};
struct Target {
	Player* player;
	Monster* monster;
	bool IsApply;
};
struct EquipInfo;
using Equip_func = void(*)(const EquipInfo&, Target& target);
struct EquipInfo {
	int ID;
	EquipType type;
	string name;
	string description;
	int e_HP, e_MP, e_armor;
	int e_str, e_dex, e_con, e_int, e_wis, e_cha;
	int effect_value1, effect_value2;
	int buy_value, sell_value;
	Equip_func equipfunc1, equipfunc2;
	vector<BonusStat> statboost;
};
struct ItemInfo;
using Item_Func = void(*)(const ItemInfo&, Target& target);
struct ItemInfo {
	int ID;
	ItemType type;
	string name;
	string description;
	int modifier, dicecount, dicenum;
	int effect_value;
	int buy_value, sell_value;
	bool IsUseable;
	Item_Func itemfunc;
};
struct ItemSearch {
	bool found;
	int slot;
	int id;
};
struct EquipNameConvert {
	string weapon;
	string armor;
	string acc;
};
struct MixInfo {
	int ID;
	string recipe_name;
	string first, second;
	int count1,count2;
	string output;
	int output_ID;
	int count;
	bool IsOpen;
};
//Equipments
ItemSearch FindEquip(const string& name);
vector<EquipInfo> EquipList();
const unordered_map<int, EquipInfo>& GetEquipMap();
void None_E(const EquipInfo&, Target& target);
void Bonus_Stats(const EquipInfo& equip, Target& target);
EquipNameConvert NameConvert(int weapon, int armor, int acc);
EquipInfo GetGearData(int id);
int FindGear(const string& name);
//Items
int FindItem(const string& name);
vector<ItemInfo> ItemList();
const unordered_map<int, ItemInfo>& GetItemMap();
void None_I(const ItemInfo&, Target& target);
void UseItem(const ItemInfo&, Target& target);
void HPItem (const ItemInfo&, Target& target);
void MPItem (const ItemInfo&, Target& target);
ItemInfo GetItemData(int id);
//mix
vector<MixInfo> MixList();
const unordered_map<int, MixInfo>& GetMixMap();
MixInfo GetMixData(const int id);