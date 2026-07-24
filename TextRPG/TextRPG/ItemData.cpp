
#include "ItemData.h"
#include "dice.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

//Equipments
vector<EquipInfo> EquipList() {
    vector<EquipInfo> gears = {
        //Paladin
        {101001, EquipType::Weapon, "Iron Sword", "Just Normal Sword",   0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,      0, 50, None_E, None_E,{},},
        {101002, EquipType::Weapon, "Steel Sword", "Deal Damage +1",   0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,      1800, 180, Bonus_Stats, None_E, {{BonusType::dicemodifier, 1}},},
        {101003, EquipType::Weapon, "Cobalt Winglet", "Increase STR+1, Deal Damage +2",   0,0,0,   1, 0, 0, 0, 0, 0,  2, 0,      5200, 520, Bonus_Stats,None_E,{{BonusType::dicemodifier, 2}},},
        {101004, EquipType::Weapon, "Curtana", "Increase STR+2, Deal Damage +2",   0,0,0,   2, 0, 0, 0, 0, 0,  2, 0,      9999, 999, Bonus_Stats,None_E,{{BonusType::dicemodifier, 2}},},
        {101005, EquipType::Weapon, "Excalibur", "Increase All Stats +2, Deal Damage +2",   2,2,0,   2, 2, 2, 2, 2, 2,  0, 0,      20000, 2000, Bonus_Stats,None_E, {{BonusType::dicemodifier, 2}},},

        {102001, EquipType::Gear,   "Wooden Shield", "Just Normal shield", 0,0,0,    0, 0, 0, 0, 0, 0,  1, 0,   0, 50, None_E,None_E, {},},
        {102002, EquipType::Gear,   "Steel kite Shield", "Just Normal shield", 0,0,1,    0, 0, 0, 0, 0, 0,  1, 0,   1800, 180, None_E,None_E, {},},
        {102003, EquipType::Gear,   "Cobalt Scutum", "Just Normal shield", 0,0,1,    0, 0, 1, 0, 0, 0,  1, 0,   5200, 520, None_E,None_E, {},},
        {102004, EquipType::Gear,   "Holy Shield", "Just Normal shield", 0,0,2,    0, 0, 1, 0, 0, 0,  1, 0,   9999, 999, None_E,None_E, {},},
        {102005, EquipType::Gear,   "Aegis Shield", "Just Normal shield", 0,0,3,    0, 0, 2, 0, 0, 0,  1, 0,   20000, 2000, None_E,None_E, {},},
        //Warrior
        {201001, EquipType::Weapon, "Iron Axe", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,            0, 50, None_E,None_E, {}} ,
        {202001, EquipType::Gear,   "Leather Armor", "Just Normal armor", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,     0, 50, None_E,None_E, {}} ,
        //White Mage                                                                                                                 
        {301001, EquipType::Weapon, "Wooden Staff", "Just Normal staff", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,      0, 50, None_E,None_E, {}} ,
        {302001, EquipType::Gear, "Hempen Lobe", "Just Normal lobe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,          0, 50, None_E,None_E, {}} ,
        //Rouge                                                                                                                       
        {401001, EquipType::Weapon, "Iron Daggers", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,        0, 50, None_E,None_E, {}} ,
        {402001, EquipType::Gear, "Linen Armor", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,           0, 50, None_E,None_E, {}} ,
        //Bard                                                                                                                        
        {501001, EquipType::Weapon, "Wooden Bow", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,          0, 50, None_E,None_E, {}} ,
        {502001, EquipType::Gear,  "Hempen Suit", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,          0, 50, None_E,None_E, {}} ,
        //Black Mage                                                                                                                  
        {601001, EquipType::Weapon, "Wooden Lod", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,          0, 50, None_E,None_E, {}} ,
        {602001, EquipType::Gear,   "Hempen Lobe", "Just Normal Axe", 0,0,0,   0, 0, 0, 0, 0, 0,  1, 0,         0, 50, None_E,None_E, {}} ,
        //acc
        {701001, EquipType::Acc, "Strength Ring", "Increase STR +1 while wearing", 0,0,0,   1, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E,None_E,          {}}  ,
        {701002, EquipType::Acc, "Power Wrist", "Increase STR +2 while wearing", 0,0,0,   2, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,          {}}  ,
        {702001, EquipType::Acc, "Dexterity Ring", "Increase DEX +1 while wearing", 0,0,0,   0, 1, 0, 0, 0, 0,  0, 0,         2500, 250, None_E,None_E,          {}}  ,
        {702002, EquipType::Acc, "Hermes' Shoes", "Increase DEX +2 while wearing", 0,0,0,   0, 2, 0, 0, 0, 0,  0, 0,         10000, 250, None_E,None_E,          {}}  ,
        {703001, EquipType::Acc, "Constitution Ring", "Increase CON +1 while wearing", 0,0,0,   0, 0, 1, 0, 0, 0,  0, 0,          2500, 250, None_E,None_E,      {}}  ,
        {703002, EquipType::Acc, "Champion Belt", "Increase CON +2 while wearing", 0,0,0,   0, 0, 2, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
        {704001, EquipType::Acc, "Intelligence ring", "Increase INT +1 while wearing", 0,0,0,   0, 0, 0, 1, 0, 0,  0, 0,          2500, 250, None_E,None_E,      {}}  ,
        {704002, EquipType::Acc, "Circle", "Increase INT +2 while wearing", 0,0,0,   0, 0, 0, 2, 0, 0,  0, 0,          10000, 1000, None_E,None_E,               {}}  ,
        {705001, EquipType::Acc, "Wisdom Ring", "Increase WIS +1 while wearing", 0,0,0,   0, 0, 0, 0, 1, 0,  0, 0,          2500, 250, None_E,None_E,            {}}  ,
        {705002, EquipType::Acc, "Sage's Ring", "Increase WIS +2 while wearing", 0,0,0,   0, 0, 0, 0, 2, 0,  0, 0,          10000, 1000, None_E,None_E,          {}}  ,
        {706001, EquipType::Acc, "Charisma Ring", "Increase CHA +1 while wearing", 0,0,0,   0, 0, 0, 0, 0, 1,  0, 0,          2500, 250, None_E ,None_E,         {}}  ,
        {706002, EquipType::Acc, "Red Cap", "Increase CHA +2 while wearing", 0,0,0,   0, 0, 0, 0, 0, 2,  0, 0,          10000, 1000, None_E,None_E,              {}}  ,
        {707001, EquipType::Acc, "HP Ring", "Increase Max HP + 6 while wearing", 6,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,     {}}  ,
        {707002, EquipType::Acc, "Muscle Belt", "Increase Max HP +12 while wearing", 12,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E ,None_E,    {}}  ,
        {708001, EquipType::Acc, "MP Ring", "Increase Max MP + 4 while wearing", 0,4,0,   0, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,     {}}  ,
        {708002, EquipType::Acc, "Gold Hairpin", "Increase Max MP + 8 while wearing", 0,8,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E ,None_E,    {}}  ,
        {709001, EquipType::Acc, "Armor Ring", "Increase Armor + 1 while wearing", 0,0,1,   0, 0, 1, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,         {}}  ,
        {709002, EquipType::Acc, "Great Wall", "Increase Armor + 2 while wearing", 0,0,2,   0, 0, 2, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
        {799001, EquipType::Acc, "Ribbon", "Null from all magic", 1,1,1,   1, 1, 1, 1, 1, 1,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
        {799002, EquipType::Acc, "Soul of Thamasa", "Legendary Item, Increase your magic stats", 0,12,0,   0, 0, 0, 4, 4, 2,  0, 0,          99999, 9999, None_E,None_E,        {}}  
    };
	return gears;
}
const unordered_map<int, EquipInfo>& GetEquipMap() {
    static unordered_map<int, EquipInfo> gearmap = []() {
        unordered_map<int, EquipInfo> result;
        for (const auto& gears : EquipList()) {
            result[gears.ID] = gears;
        }
        return result;
        }();
    return gearmap;
}
//items
vector<ItemInfo> ItemList() {
    vector<ItemInfo> items = {
        {1, ItemType::Useable, "Potion", "Heal your HP as 1d6", 0, 1, 6,  0,               250, 50, true,  HPItem },
        {2, ItemType::Useable, "High Potion", "Heal your HP as 1d10", 0, 1, 10,  0,        500, 100, true, HPItem },
        {3, ItemType::Useable, "Mega Potion", "Heal your HP as 2d6", 0, 2, 6,  0,          750, 150, true,  HPItem },
        {4, ItemType::Useable, "X Potion", "Heal your HP as 4d6", 0, 4, 6,  0,             1500, 300, true,  HPItem },
        {5, ItemType::Useable, "Elixir", "Heal all your HP", 9999, 1, 1,  0,               5000, 1000, true,  HPItem },
        {6, ItemType::Useable, "Aether", "Heal your MP as 1d4", 0, 1, 4,  0,               500, 100,true,  MPItem },
        {7, ItemType::Useable, "High Aether", "Heal your MP as 1d8", 0, 1, 8,  0,               1000, 200,true,  MPItem },
        {8, ItemType::Useable, "Mega Aether", "Heal your MP as 1d12", 0, 1, 12,  0,               2000, 400,true,  MPItem },
        {9, ItemType::Useable, "X Aether", "Heal your MP as 2d8", 0, 2, 8,  0,               4000, 800,true,  MPItem }
    };
    return items;
}
const unordered_map<int, ItemInfo>& GetItemMap() {
    static unordered_map<int, ItemInfo> itemmap = []() {
        unordered_map<int, ItemInfo> result;
        for (const auto& items : ItemList()) {
            result[items.ID] = items;
        }
        return result;
        }();
    return itemmap;
}
vector<MixInfo> MixList() {
    vector<MixInfo> mixs = {
        {1, "Potion", "Potion", 1, 1, "Mega Potion", 3, true},
        {2, "Aether", "Aether", 1, 1,"Mega Aether", 8, true},
        {3, "High Potion", "High Potion", 1, 1,"X Potion", 4, false },
        {4, "High Aether", "High Aether", 1, 1,"X Aether", 9, false }
    };
    return mixs;
}
const unordered_map<int, MixInfo>& GetMixMap() {
    static unordered_map<int, MixInfo> mixmap = []() {
        unordered_map<int, MixInfo> result;
        for (const auto& mixs : MixList()) {
            result[mixs.ID] = mixs;
        }
        return result;
        }();
    return mixmap;
}
//Equipments Func
void None_E(const EquipInfo& equip, Target& target) {}
void Bonus_Stats(const EquipInfo& equip, Target& target) {
    if (!target.player) return;

    int plus = target.IsApply ? 1 : -1;
    for (const auto& b : equip.statboost) {
        switch (b.bonustype) {
        case BonusType::dicemodifier: target.player->ChangeDiceModifier(equip.effect_value1 * plus); break;
        }
    }
}
//Item Func
void None_I(const ItemInfo& item, Target& target) {}
void UseItem(const ItemInfo& item, Target& target) {
    item.itemfunc(item, target);
}
void HPItem(const ItemInfo& item, Target& target) {
    if (target.player == nullptr) {
        cout << "Error\n";
        return;
    }
    
    int amount = DiceRoll({ item.modifier, item.dicecount, item.dicenum });
    cout << "--------------------------------------------------------------------\n";
    cout << "You used" << item.name << "!, Healed [" << amount << "]";
    cout << "--------------------------------------------------------------------\n";
    target.player->HealHP(amount);
}
void MPItem(const ItemInfo& item, Target& target) {
    if (target.player == nullptr) {
        cout << "Error\n";
        return;
    }
    int amount = DiceRoll({ item.modifier, item.dicecount, item.dicenum });
    cout << "--------------------------------------------------------------------\n";
    cout << "You used" << item.name << "!, Healed [" << amount << "]";
    cout << "--------------------------------------------------------------------\n";
    target.player->HealMP(amount);
}

//GetData
EquipInfo GetGearData(int id) //convert id -> Vector Info
{
    if (id == -1) return EquipInfo{ -1, EquipType::None, "Empty", "", 0, 0,0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, None_E };
    auto gears = EquipList();
    for (const auto& g : gears) {
        if (g.ID == id) return g;
    }
    return gears[0];
}
ItemInfo GetItemData(int id)
{
    if (id == -1) return ItemInfo{-1, ItemType::None, "Empty", "", 0, 0, 0,  0,               0, 0, false,  None_I };    
    auto items = ItemList();
    for (const auto& i : items) {
        if (i.ID == id) return i;
    }
    return items[0];
}

// auto convert 0:weapon 1:gear 2:acc
static int EquipTypeInt(EquipType type) 
{
    switch (type)
    {
    case EquipType::Weapon: return 0;
    case EquipType::Gear: return 1;
    case EquipType::Acc: return 2;
    default: return -1;
    }
}
//Covert to name from id
EquipNameConvert NameConvert(int weapon, int armor, int acc) 
{
    int weaponid = weapon;
    int armorid = armor;
    int accid = acc;
    string weaponname = GetGearData(weaponid).name;
    string armorname = GetGearData(armorid).name;
    string accname = GetGearData(accid).name;
    return { weaponname, armorname, accname };
}
ItemSearch FindEquip(const string& name) {
    vector<EquipInfo> gears = EquipList();

    for (const auto& g : gears) 
        if (g.name == name)
        {
            int slot = EquipTypeInt(g.type);
            return {true, slot, g.ID};
        }

    return {false, -1, -1};
    
}
int FindItem(const string& name) {
    vector<ItemInfo> items = ItemList();
    for (const auto& i : items) 
        if (i.name == name)
            return i.ID;

     return -1; 
}
int FindGear(const string& name) {
    vector<EquipInfo> gears = EquipList();
    for (const auto& i : gears)
        if (i.name == name)
            return i.ID;

    return -1;
}