#pragma once
#include <string>
#include "RaceData.h"
#include "JobData.h"
#include "dice.h"
#include "Skills.h"
#include "ItemData.h"
#include "Inventory.h"
#include <algorithm>

using namespace std;


class Player
{
public:
    Player(string name, RaceType race, JobType job);


    struct InventoryInfo {
        int ID;
        int count;
    };

    //getters
    void ShowStatus() const;
    bool IsAlive() const;
    string GetName() const { return p_name; };
    int GetHP() const { return current_HP; }
    int GetMaxHP() const { return max_HP; }
    int GetMP() const { return current_MP; }
    int GetMaxMP() const { return max_MP; }
    string GetJob() const { return p_job; }
    int GetLevel() const { return level; }
    int GetEXP() const { return exp; }
    int GetEXPToNextLevel() const { return exp_goal - exp; }
    int GetArmor() const { return armor; }
    int GetSTR() const { return s_str; }
    int GetDex() const { return s_dex; }
    int GetCON() const { return s_con; }
    int GetINT() const { return s_int; }
    int GetWIS() const { return s_wis; }
    int GetCHA() const { return s_cha; }
    int GetSize() const { return a_size; }
    int GetSpeed() const { return a_speed; }
    int GetPenaltyInitiative() const { return a_initiative_p; }
    int GetBonusInitiative() const { return a_initiative_b; }
    int GetDodge() const { return dodge; }
    int GetCri() const { return critical; }
    int GetStartDistance() const { return startdistance; }
    int GetGil() const { return Gil; }
    int GetBonusModifier() const { return b_modifier; }
    int GetBonusCount() const { return b_dicecount; }
    int GetBonusNum() const { return b_dicenum; }
    

    //setters
    int ChangeSize(int bonus) { a_size = clamp(a_size + bonus, 0, 2); return a_size; }
    int ChangeSpeed(int bonus) { a_speed = clamp(a_speed + bonus, 0, 2); return a_speed; }
    int ChangeRange(int bonus) { a_range = clamp(a_range + bonus, -5, 5); return a_range; }
    int ChangeInit_P(int bonus) { a_initiative_p = clamp(a_initiative_p + bonus, 0, 6); return a_initiative_p; }
    int ChangeInit_B(int bonus) { a_initiative_b = clamp(a_initiative_b + bonus, 0, 6); return a_initiative_b; }
    int ChangeDodge(int bonus) { dodge = clamp(dodge + bonus, 0, 7); return dodge; }
    int ChangeCritical(int bonus) { critical = clamp(critical + bonus, 0, 7); return critical; }
    int ChangeDistance(int bonus) { startdistance = clamp(startdistance + bonus, -5, 5); return startdistance; }
    int ChangeDiceModifier(int bonus) { b_modifier = clamp(b_modifier + bonus, 0, 20); return b_modifier; }
    int ChangeDiceCount(int bonus) { b_dicecount = clamp(b_dicecount + bonus, 0, 2); return b_dicecount; }
    int ChangeDiceNum(int bonus) { b_dicenum = clamp(b_dicenum + bonus, 0, 20); return b_dicenum; }

    bool SetGuard(bool onoff) {
        guard = onoff;
        return guard;
        }

    void ChangeName(string inputname) { p_name = inputname; }
    void TakeDamage(int rawdamage) 
    { 
        int finaldamage = rawdamage - armor; 
        if (finaldamage < 0) { finaldamage = 0; }
        if (guard) { finaldamage /= 2; }
        current_HP -= finaldamage;
        if (current_HP < 0) { current_HP = 0; };
    }
    void HealHP(int amount) { current_HP = min(current_HP + amount, max_HP); }
    void HealMP(int amount) { current_MP = min(current_MP + amount, max_MP); }
    bool UseMP(int amount) {
        current_MP -= amount;
        if (current_MP < 0) {
            current_MP = 0;
            return false; // Not enough MP
        }
        return true;
    }
    void GainEXP(int amount) { exp += amount; }
    void GainGil(int amount) { Gil += amount; }
    bool UseGil(int amount) {
        if (Gil < amount) {
            return false; // Not enough Gil
        }
        Gil -= amount;
        return true;
    }

    //getters for Item & skills
    int GetGearsID(int slot) const { return equipment[slot]; }
    const vector<int>& ViewSkill() const { return skills; };
    const vector<InventoryInfo>& ViewArmory() const { return armory.ViewInventory(); }
    const vector<InventoryInfo>& ViewInven() const { return inventory.ViewInventory(); }    //setter for Item & skills                      
    void AddSkill(int slot, int ID);
    void RemoveSkill(int slot);
    void AddEquip(int slot, int ID);
    void RemoveEquip(int slot);
    void AddItem(int ID, int count) { inventory.Add(ID, count); }
    void RemoveItem(int ID, int count) { inventory.Remove(ID, count); }
    void AddGear(int ID, int count) { armory.Add(ID, count); }
    void RemoveGear(int ID, int count) { armory.Remove(ID, count); }
    void LevelUp();
    void StatUp();
private:
    void ApplyJob(JobType job);
    void ApplyRace(RaceType race);
    void ApplyGear(int id);
    void RemoveGear(int id);

    //Main
    string p_name;
    string p_race;
    string p_job;
    //Main Status
    int max_HP = 20;
    int current_HP = 20;
    int max_MP = 10;
    int current_MP = 10;
    int level = 1;
    int exp = 0;
    int exp_goal = 50;
    int bonus_stat = 0; //start with 0, increase 1 when level up, can raise one stat +1 when it's become 2. after raise stat, reset to 0
    int armor = 0;
    //Sub Status
    int s_str = 10;
    int s_dex = 10;
    int s_con = 10;
    int s_int = 10;
    int s_wis = 10;
    int s_cha = 10;
    //Attributes
    int a_size = 0; // 0:small,1:medium 2:big
    int a_speed = 0;// 0:fast, 1:medium 2:slow
    int a_range = 0;
    int a_initiative_p = 0;
    int a_initiative_b = 0;
    int dodge = 1; // bonus-> +1
    int critical = 20; // bonus -> -1
    int startdistance = 0; // melee bonus = minus, ranged bonus = plus
    int b_modifier = 0;
    int b_dicecount = 0;
    int b_dicenum = 0;
    bool guard = false;
    bool Ribbon = false;

    //items
    int Gil = 5000;
    //skills / Equipment / Inventory

    vector<int> skills; //0: firstskill, 1: secondskill, 2:thridskill, 3:Fourthskill, 4:Forwardskill, 5:backskill

    vector<int> equipment;  //0: Weapon, 1: gear, 2: Acc

    Inventory<InventoryInfo> inventory;

    Inventory<InventoryInfo> armory;
};
bool CheckItem(const Player& player, int id, int count);
bool CheckGear(const Player& player, int id, int count);