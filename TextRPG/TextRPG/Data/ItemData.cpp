
#include "ItemData.h"
#include "Tools.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

//Equipments
vector<EquipInfo> EquipList() {
    vector<EquipInfo> gears = {
                // ==========================================
                // 100000 Paladin
                // ==========================================
                {101001, EquipType::Weapon, "Iron Sword", "Just Normal Sword", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {101002, EquipType::Weapon, "Steel Broadsword", "Deal Damage +1 while wearing", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180,     Bonus_Stats, None_E,     {{BonusType::dicemodifier, 1}}},
                {101003, EquipType::Weapon, "Cobalt Winglet", "Increase STR, Deal Damage +1", 0,0,0, 1,0,0,0,0,0, 1,0, 5200, 520,     Bonus_Stats, None_E,       {{BonusType::dicemodifier, 1}}},
                {101004, EquipType::Weapon, "Curtana", "Increase STR, Deal Damage +2", 0,0,0, 1,0,0,0,0,0, 2,0, 9999, 999,            Bonus_Stats, None_E,       {{BonusType::dicemodifier, 1}}},
                {101005, EquipType::Weapon, "Excalibur", "Increase All Stats, Deal Damage +2", 2,2,0, 2,2,2,2,2,2, 2,0, 20000, 2000, Bonus_Stats, None_E,        {{BonusType::dicemodifier, 2}}},

                {102001, EquipType::Gear,   "Wooden Shield", "Just Normal shield", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {102002, EquipType::Gear,   "Steel Kite Shield", "Increase CON while wearing", 0,0,0, 0,0,1,0,0,0, 0,0, 1800, 180, None_E, None_E, {}},
                {102003, EquipType::Gear,   "Cobalt Scutum", "Get Armor while wearing", 0,0,1, 0,0,0,0,0,0, 0,0, 5200, 520, None_E, None_E, {}},
                {102004, EquipType::Gear,   "Holy Shield", "Get Armor and CON while wearing", 0,0,2, 0,0,1,0,0,0, 0,0, 9999, 999, None_E, None_E, {}},
                {102005, EquipType::Gear,   "Aegis Shield", "Get huge Armor and CON while wearing", 0,0,3, 0,0,3,0,0,0, 1,0, 20000, 2000, None_E, None_E, {}},

                // ==========================================
                // 200000 Warrior
                // ==========================================
                {201001, EquipType::Weapon, "Iron War Axe", "Just Normal Axe", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {201002, EquipType::Weapon, "Steel Labrys", "Deal Damage +1 while wearing", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, Bonus_Stats, None_E,            {{BonusType::dicemodifier, 1}}},
                {201003, EquipType::Weapon, "Cobalt Bardiche", "Increase STR, Stat Dice + 2", 0,0,0, 1,0,0,0,0,0, 1,0, 5200, 520,  Bonus_Stats, None_E,         {{BonusType::dicenum, 2}}},
                {201004, EquipType::Weapon, "Bravura", "Increase STR, Stat Dice + 4", 0,0,0, 2,0,0,0,0,0, 1,0, 9999, 999, Bonus_Stats, None_E,                  {{BonusType::dicenum, 4}}},
                {201005, EquipType::Weapon, "Ragnarok", "Increase STR, Stat Dice + 6", 0,0,0, 3,0,0,0,0,0, 1,0, 20000, 2000, Bonus_Stats, None_E,               {{BonusType::dicenum, 6}}},

                {202001, EquipType::Gear,   "Iron Cuirass", "Just Normal armor", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {202002, EquipType::Gear,   "Steel Scale Mail", "Increase HP while wearing", 3,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, None_E, None_E, {}},
                {202003, EquipType::Gear,   "Cobalt Lorica", "Increase HP and CON while wearing", 6,0,0, 0,0,2,0,0,0, 1,0, 5200, 520, None_E, None_E, {}},
                {202004, EquipType::Gear,   "Fighter's Cuirass", "Increase HP and CON while wearing", 12,0,0, 0,0,2,0,0,0, 1,0, 9999, 999, None_E, None_E, {}},
                {202005, EquipType::Gear,   "Warrior's Cuirass", "Increase HP and CON while wearing", 24,0,0, 0,0,3,0,0,0, 1,0, 20000, 2000, None_E, None_E, {}},

                // ==========================================
                // 300000 White Mage
                // ==========================================
                {301001, EquipType::Weapon, "Maple Cane", "Just Normal staff", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {301002, EquipType::Weapon, "Yew Cane", "Increase INT and WIS", 0,0,0, 0,0,0,1,1,0, 1,0, 1800, 180, None_E, None_E, {}},
                {301003, EquipType::Weapon, "Spruce Cane", "Increase INT and WIS", 0,0,0, 0,0,0,1,2,0, 1,0, 5200, 520, None_E, None_E, {}},
                {301004, EquipType::Weapon, "Thurus", "Increase MP, INT and  WIS", 0,4,0, 0,0,0,2,2,0, 1,0, 9999, 999, None_E, None_E, {}},
                {301005, EquipType::Weapon, "Nirvana", "Increase MP, INT and WIS", 0,8,0, 0,0,0,3,3,0, 1,0, 20000, 2000, None_E, None_E, {}},

                {302001, EquipType::Gear,   "Hempen Robe", "Just Normal robe", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {302002, EquipType::Gear,   "Cotton Robe", "Increase HP while wearing", 3,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, None_E, None_E, {}},
                {302003, EquipType::Gear,   "Velveteen Robe", "Increase HP and MP", 4,4,0, 0,0,0,0,0,0, 1,0, 5200, 520, None_E, None_E, {}},
                {302004, EquipType::Gear,   "Healer's Robe", "Increase HP, MP and WIS", 5,5,0, 0,0,0,0,1,0, 1,0, 9999, 999, None_E, None_E, {}},
                {302005, EquipType::Gear,   "Cleric's Robe", "Increase HP, MP and WIS, Reduce mana cost", 8,8,0, 0,0,0,0,2,0, 1,0, 20000, 2000, Bonus_Stats, None_E, {{BonusType::manabonus, 2}}},

                // ==========================================
                // 400000 Rogue 
                // ==========================================
                {401001, EquipType::Weapon, "Iron Daggers", "Just Normal daggers", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {401002, EquipType::Weapon, "Steel Daggers", "Increase critical chance", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, Bonus_Stats, None_E,                       {{BonusType::critical, 1}}},
                {401003, EquipType::Weapon, "Cobalt Knives", "Increase DEX and critical chance while wearing", 0,0,0, 0,1,0,0,0,0, 0,0, 5200, 520, Bonus_Stats, None_E, {{BonusType::critical, 2}}},
                {401004, EquipType::Weapon, "Yoshimitsu", "Increase Dice Count + 1", 0,0,0, 0,0,0,0,0,0, 0,0, 9999, 999, Bonus_Stats, None_E,                           {{BonusType::dicecount, 1}}},
                {401005, EquipType::Weapon, "Sasaki", "Increase huge DEX and critical chance while wearing", 0,0,0, 0,3,0,0,0,0, 0,0, 20000, 2000, Bonus_Stats, None_E, {{BonusType::critical, 4}}},

                {402001, EquipType::Gear,   "Leather Jacket", "Just Normal armor", 0,0,0, 0,0,0,0,0,0, 0,0, 0, 50, None_E, None_E, {}},
                {402002, EquipType::Gear,   "Toadskin Jacket", "Increase chance to preemtive attack", 0,0,0, 0,0,0,0,0,0, 0,0, 1800, 180, Bonus_Stats, None_E,      {{BonusType::dicemodifier, 1}}},
                {402003, EquipType::Gear,   "Boarskin Harness", "Increase chance to dodge enemy's attack", 2,0,0, 0,0,0,0,0,0, 0,0, 5200, 520, Bonus_Stats, None_E, {{BonusType::dodge, 2}}},
                {402004, EquipType::Gear,   "Ninja Chainmail", "Increase Con+2 INT+2", 4,0,0, 0,0,2,2,0,0, 1,0, 9999, 999, None_E, None_E, {}},
                {402005, EquipType::Gear,   "Shinobi Chainmail", "Increase huge chance to dodge enemy's attack", 6,0,0, 0,0,0,0,0,0, 1,0, 20000, 2000, Bonus_Stats, None_E, {{BonusType::dodge, 5}}},

                // ==========================================
                // 500000 Bard
                // ==========================================
                {501001, EquipType::Weapon, "Maple Shortbow", "Just Normal bow", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {501002, EquipType::Weapon, "Ash Longbow", "Deal Damage +1 while wearing", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, Bonus_Stats, None_E,             {{BonusType::dicemodifier, 1}}},
                {501003, EquipType::Weapon, "Yew Composite Bow", "Increase Deal more damage", 0,0,0, 0,0,0,0,0,0, 1,0, 5200, 520, Bonus_Stats, None_E,          {{BonusType::dicenum, 3}}},
                {501004, EquipType::Weapon, "Artemis Bow", "Increase DEX, CHA, WIS+2", 0,0,0, 0,2,0,0,2,2, 1,0, 9999, 999, None_E, None_E, {}},                
                {501005, EquipType::Weapon, "Yoichi Bow", "Increase many stats while wearing", 0,2,0, 0,2,0,0,2,0, 0,0, 20000, 2000, Bonus_Stats, None_E,       {{BonusType::dicenum, 4}}},

                {502001, EquipType::Gear,   "Hempen Shirt", "Just Normal shirt", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {502002, EquipType::Gear,   "Cotton Acton", "Increase chance to dodge enemy's attack", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, Bonus_Stats, None_E, {{BonusType::dodge, 1}}},
                {502003, EquipType::Gear,   "Velveteen Acton", "Increase WIS and CHA", 0,0,0, 0,0,0,0,2,2, 1,0, 5200, 520, None_E, None_E, {}},
                {502004, EquipType::Gear,   "Choral Shirt", "Increase MP and huge CHA", 0,4,0, 0,0,0,0,1,3, 1,0, 9999, 999, Bonus_Stats, None_E,                {{BonusType::dodge, 1}}},
                {502005, EquipType::Gear,   "Bard's Shirt", "Increase MP and huge CHA", 0,8,0, 0,0,0,0,2,5, 0,0, 20000, 2000, Bonus_Stats, None_E,              {{BonusType::dodge, 2}}},

                // ==========================================
                // 600000 Black Mage0
                // ==========================================
                {601001, EquipType::Weapon, "Maple Wand", "Just Normal rod", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {601002, EquipType::Weapon, "Ash Rod", "Deal Damage +1 while wearing", 0,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, None_E, None_E, {}},
                {601003, EquipType::Weapon, "Yew Staff", "Increase MP and INT", 0,2,0, 0,0,0,1,0,0, 1,0, 5200, 520, None_E, None_E, {}},
                {601004, EquipType::Weapon, "Stardust Rod", "Increase MP and INT, Deal Damage +2", 0,2,0, 0,0,0,2,0,0, 1,0, 9999, 999, Bonus_Stats, None_E, {{BonusType::dicemodifier, 2}}},
                {601005, EquipType::Weapon, "Lilith Rod", "Increase INT and Dice Count", 0,6,0, 0,0,0,2,0,0, 0,0, 20000, 2000, Bonus_Stats, None_E,         {{BonusType::dicecount, 1}}},

                {602001, EquipType::Gear,   "Hempen Cowl", "Just Normal cowl", 0,0,0, 0,0,0,0,0,0, 1,0, 0, 50, None_E, None_E, {}},
                {602002, EquipType::Gear,   "Cotton Cowl", "Increase HP while wearing", 4,0,0, 0,0,0,0,0,0, 1,0, 1800, 180, None_E, None_E, {}},
                {602003, EquipType::Gear,   "Velveteen Robe", "Increase HP and MP while wearing", 6,2,0, 0,0,0,1,0,0, 1,0, 5200, 520, None_E, None_E, {}},
                {602004, EquipType::Gear,   "Wizard's Coat", "Incrase HP and reduce mana cost", 8,0,0, 0,0,0,0,0,0, 1,0, 9999, 999, Bonus_Stats, None_E, {{BonusType::manabonus, 1}}},
                {602005, EquipType::Gear,   "Sorcerer's Coat", "Increase MP, INT and reduce mana cost", 0,10,0, 0,0,0,2,0,0, 1,0, 20000, 2000, Bonus_Stats, None_E, {{BonusType::manabonus, 2}}},

                // ==========================================
                // ACC
                // ==========================================
                {701001, EquipType::Acc, "Strength Ring", "Increase STR while wearing", 0,0,0,   1, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E,None_E,          {}}  ,
                {701002, EquipType::Acc, "Power Wrist", "Increase STR while wearing", 0,0,0,   2, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,          {}}  ,
                {702001, EquipType::Acc, "Dexterity Ring", "Increase DEX while wearing", 0,0,0,   0, 1, 0, 0, 0, 0,  0, 0,         2500, 250, None_E,None_E,          {}}  ,
                {702002, EquipType::Acc, "Hermes' Shoes", "Increase DEX while wearing", 0,0,0,   0, 2, 0, 0, 0, 0,  0, 0,         10000, 250, None_E,None_E,          {}}  ,
                {703001, EquipType::Acc, "Constitution Ring", "Increase CON while wearing", 0,0,0,   0, 0, 1, 0, 0, 0,  0, 0,          2500, 250, None_E,None_E,      {}}  ,
                {703002, EquipType::Acc, "Champion Belt", "Increase CON while wearing", 0,0,0,   0, 0, 2, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
                {704001, EquipType::Acc, "Intelligence ring", "Increase INT while wearing", 0,0,0,   0, 0, 0, 1, 0, 0,  0, 0,          2500, 250, None_E,None_E,      {}}  ,
                {704002, EquipType::Acc, "Circle", "Increase INT while wearing", 0,0,0,   0, 0, 0, 2, 0, 0,  0, 0,          10000, 1000, None_E,None_E,               {}}  ,
                {705001, EquipType::Acc, "Wisdom Ring", "Increase WIS while wearing", 0,0,0,   0, 0, 0, 0, 1, 0,  0, 0,          2500, 250, None_E,None_E,            {}}  ,
                {705002, EquipType::Acc, "Sage's Ring", "Increase WIS while wearing", 0,0,0,   0, 0, 0, 0, 2, 0,  0, 0,          10000, 1000, None_E,None_E,          {}}  ,
                {706001, EquipType::Acc, "Charisma Ring", "Increase CHA while wearing", 0,0,0,   0, 0, 0, 0, 0, 1,  0, 0,          2500, 250, None_E ,None_E,         {}}  ,
                {706002, EquipType::Acc, "Red Cap", "Increase CHA while wearing", 0,0,0,   0, 0, 0, 0, 0, 2,  0, 0,          10000, 1000, None_E,None_E,              {}}  ,
                {707001, EquipType::Acc, "HP Ring", "Increase Max HP while wearing", 6,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,     {}}  ,
                {707002, EquipType::Acc, "Muscle Belt", "Increase Max HP while wearing", 12,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E ,None_E,    {}}  ,
                {708001, EquipType::Acc, "MP Ring", "Increase Max MP while wearing", 0,4,0,   0, 0, 0, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,     {}}  ,
                {708002, EquipType::Acc, "Gold Hairpin", "Increase Max MP while wearing", 0,8,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E ,None_E,    {}}  ,
                {709001, EquipType::Acc, "Armor Ring", "Increase Armor while wearing", 0,0,1,   0, 0, 1, 0, 0, 0,  0, 0,          2500, 250, None_E ,None_E,         {}}  ,
                {709002, EquipType::Acc, "Great Wall", "Increase huge Armor while wearing", 0,0,2,   0, 0, 2, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
                {710001, EquipType::Acc, "Dodge Ring", "Increase chance to dodge while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          4000, 400, Bonus_Stats, None_E,    {{BonusType::dodge, 2}}},
                {710002, EquipType::Acc, "Elven Cloak", "Increase chance to dodge while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, Bonus_Stats, None_E, {{BonusType::dodge, 4}}},
                {710003, EquipType::Acc, "Critical Ring", "Increase chance to critical while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          4000, 400, Bonus_Stats, None_E, {{BonusType::critical, 2}}},
                {710004, EquipType::Acc, "Hyper Wrist", "Increase chance to critical while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, Bonus_Stats, None_E, {{BonusType::critical, 4}}},
                {710005, EquipType::Acc, "Gale Hairpin", "Increase chance to preemtive attack while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          2000, 200, Bonus_Stats, None_E, {{BonusType::initiative_b, 3}}},
                {710006, EquipType::Acc, "Alarm Earring", "Increase chance to avoid ambushed attack while wearing", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          2000, 200, Bonus_Stats, None_E, {{BonusType::initiative_p, 3}}},
                {799001, EquipType::Acc, "Ribbon", "Null from all magic", 0,0,0,   0, 0, 0, 0, 0, 0,  0, 0,          10000, 1000, None_E,None_E,        {}}  ,
                {799002, EquipType::Acc, "Soul of Thamasa", "Legendary Item, Increase your magic stats", 0,12,0,   0, 0, 0, 4, 4, 2,  0, 0,          99999, 9999, None_E,None_E,        {}} ,
                {799003,EquipType::Acc, "Hero's Ring", "Legendary Item, Increase your all stats", 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 99999, 9999, None_E, None_E, {} }
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
        {9, ItemType::Useable, "X Aether", "Heal your MP as 2d8", 0, 2, 8,  0,               4000, 800,true,  MPItem },


        {1001, ItemType::Miscellaneous, "Scalekin Egg", "Scalekin's Egg, Some merchant buy this with high value", 0, 0, 0,  0,               0, 50, false,  None_I },
        {1002, ItemType::Miscellaneous, "Fire Shard",  "A tiny crytalline manifestation of aetheric fire energy", 0, 0, 0,  0,               0, 50, false,  None_I },
        {1003, ItemType::Miscellaneous, "Water Shard", "A tiny crytalline manifestation of aetheric Water energy", 0, 0, 0,  0,               0, 50, false,  None_I },
        {1004, ItemType::Miscellaneous, "Earth Shard", "A tiny crytalline manifestation of aetheric Earth energy", 0, 0, 0,  0,               0, 50, false,  None_I },
        {1005, ItemType::Miscellaneous, "Ice Shard",   "A tiny crytalline manifestation of aetheric Ice energy", 0, 0, 0,  0,               0, 50, false,  None_I },
        {1006, ItemType::Miscellaneous, "Thunder Shard",   "A tiny crytalline manifestation of aetheric Thunder energy", 0, 0, 0,  0,               0, 50, false,  None_I },
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
        {1, "Mega Potion Mix Recipe", "Potion", "Potion", 1, 1, "Mega Potion", 3, 1, true},
        {2, "Mega Aether Mix Recipe","Aether", "Aether", 1, 1,"Mega Aether", 8, 1, true},
        {3, "X Potion Mix Recipe","High Potion", "High Potion", 1, 1,"X Potion", 4, 1,false },
        {4, "X Aether Mix Recipe","High Aether", "High Aether", 1, 1,"X Aether", 9, 1,false },
        {5, "Mega Aether Convert Recipe","Potion", "Potion", 1, 1,"Mega Aether", 8, 1,false},
        {6, "X Aether Convert Recipe","High Potion", "High Potion", 1, 1,"X Aether", 9, 1,false },
        {7, "Mega Potion Duplicate Recipe","Potion", "Mega Potion", 1, 2,"Mega Potion", 3, 3,false },
        {8, "Aether Emission Recipe","Mega Aether", "Mega Aether", 1, 1,"Aether", 6, 4,false },



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
        case BonusType::dicemodifier: target.player->ChangeDiceModifier(b.amount * plus); break;
        case BonusType::dicecount:    target.player->ChangeDiceCount(b.amount * plus); break;
        case BonusType::dicenum:      target.player->ChangeDiceNum(b.amount * plus); break;
        case BonusType::startdistance: target.player->ChangeDistance(b.amount * plus); break;
        case BonusType::dodge:        target.player->ChangeDodge(b.amount * plus); break;
        case BonusType::critical:     target.player->ChangeCritical(b.amount * plus); break;
        case BonusType::initiative_p: target.player->ChangeInit_P(b.amount * plus); break;
        case BonusType::initiative_b: target.player->ChangeInit_B(b.amount * plus); break;
        case BonusType::manabonus: target.player->ChangeManaBonus(b.amount * plus); break;
        default: break;
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
    cout << "You used" << item.name << "!, Healed [" << amount << "]\n";
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
    cout << "You used" << item.name << "!, Healed [" << amount << "]\n";
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
MixInfo GetMixData(const int id) 
{
    auto recipe = MixList();
    for (const auto& r : recipe) {
        if(r.ID == id) return r;
    }
    return recipe[0];
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