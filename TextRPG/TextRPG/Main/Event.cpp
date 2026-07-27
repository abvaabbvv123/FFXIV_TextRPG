#include "Event.h"
#include "JobData.h"
#include "RaceData.h"
#include "ItemData.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <thread> 
#include <chrono> 
#include <cstdlib>
#include <random>
#include "Skills.h"
#include "Battle.h"
#include <limits>
#include <conio.h>
#include <iomanip>
#include "Tools.h"
#include "ShopData.h"
using namespace std;




vector<EventContext> EventList() {
    vector<EventContext> events = {
        {1, EventType::StoryEvent, "A Soldier's Breakfast", "Pauline", A_Soldiers_Breakfast},
        
        
        
    };
    return events;
}
//view my inventory
void MyInventory(Player& player) {
    cout << "============================[  Inventory  ]==========================\n";
    cout << "   "
        << left << setw(17) << "::name::"
        << left << setw(18) << "::Quantity::"
        << left << setw(10) << "::Gil::"
        << left << setw(32) << "::Description::" << endl;

    const auto& itemmap = GetItemMap();
    for (const auto& i : player.ViewInven())
    {
        auto item = itemmap.find(i.ID);
        if (item == itemmap.end()) {
            cout << "Empty" << endl;
            continue;
        }
        const ItemInfo& data = item->second;
        cout << "   "
            << left << setw(22) << data.name
            << left << setw(13) << i.count
            << left << setw(10) << data.sell_value
            << left << setw(50) << data.description << endl;
    }
    cout << "=====================================================================\n";
}
void MyArmory(Player& player) {
    cout << "=============================[   Armory   ]=========================\n";
    cout << "Current Equipments\n";
    EquipNameConvert gear = NameConvert(player.GetGearsID(0), player.GetGearsID(1), player.GetGearsID(2));
    cout << "Weapon: [" << gear.weapon << "] Armor:[" << gear.armor << "] Accessory:[" << gear.acc << "]\n";
    cout << "---------------------------------------------------------------------\n";
    cout << "   "
        << left << setw(17) << "::name::"
        << left << setw(18) << "::Quantity::"
        << left << setw(10) << "::Gil::"
        << left << setw(32) << "::Description::" 
        << endl;

    for (const auto& g : player.ViewArmory()) {
        EquipInfo data = GetGearData(g.ID);
        cout << "   "
            << left << setw(22) << data.name
            << left << setw(13) << g.count
            << left << setw(10) << data.sell_value
            << left << setw(50) << data.description 
            << endl;
    }
    cout << "====================================================================\n";
}
void ShowTest() {
    system("cls");
    cout << "---------------------------------------------------------\n";
    TypeEffect("This is for Input Test", 10);
    cout << "---------------------------------------------------------\n";
    TypeEffect("Enter your any number for your HP and MP. (Total 20 - 100)", 10);
    int answer1; int answer2;
    while (true) {
        cin.clear();
        cin >> answer1;
        try {
            if (answer1 <= 0) {
                throw invalid_argument("You have to put more than 1 for HP");
            }
        }
        catch (const exception& e) {
            cout << "\n[Invalid Input]" << e.what() << endl;
            _getch();
            continue;
        }
        cin.clear();
        cin >> answer2;
        try {
            if (answer2 <= 0) {
                throw invalid_argument("You have to put more than 1 for MP");
            }
        }
        catch (const exception& e) {
            cout << "\n[Invalid Input]" << e.what() << endl;
            _getch();
            continue;
        }
        try {
            if (answer1 + answer2 > 100) {
                throw invalid_argument("Try again. (total 20 - 100)");
            }
            if (answer1 + answer2 < 20) {
                throw invalid_argument("Try again. (total 20 - 100)");
            }
        }
        catch (const exception& e) {
            cout << "\n[Invalid Input]" << e.what() << endl;
            _getch();
            continue;
        }
        break;
    }
    cout << "\n---------------------------------------------------------\n";
    cout << "Your HP is [" << answer1 << "]\n";
    cout << "Your MP is [" << answer2 << "]\n";
    cout << "---------------------------------------------------------\n";

TypeEffect("Enter your Attack and Defense. (total 10-30)", 10);
while (true) {
    cin.clear();
    cin >> answer1;
    try {
        if (answer1 <= 0) {
            throw invalid_argument("You have to put more than 1 for Attack");
        }
    }
    catch (const exception& e) {
        cout << "\n[Invalid Input]" << e.what() << endl;
        _getch();
        continue;
    }
    cin.clear();
    cin >> answer2;
    try {
        if (answer2 <= 0) {
            throw invalid_argument("You have to put more than 1 for Defense");
        }
    }
    catch (const exception& e) {
        cout << "\n[Invalid Input]" << e.what() << endl;
        _getch();
        continue;
    }
    try {
        if (answer1 + answer2 > 30) {
            throw invalid_argument("Try again. (total 20 - 30)");
        }
        if (answer1 + answer2 < 10) {
            throw invalid_argument("Try again. (total 20 - 30)");
        }
    }
    catch (const exception& e) {
        cout << "\n[Invalid Input]" << e.what() << endl;
        _getch();
        continue;
    }
    break;
}
    cout << "\n---------------------------------------------------------\n";
    cout << "Your Attack is [" << answer1 << "]\n";
    cout << "Your Defense is [" << answer2 << "]\n";
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);
    cout << "---------------------------------------------------------\n";
    TypeEffect("Succeed Input Test. Now start the game", 10);
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);
}
//menu
void ShowMenu(Player& player) {
    while(true) {
        cin.clear();
        system("cls");
        cout << "============================[    Menu    ]==========================\n";
        player.ShowStatus();
        cout << "[1: Inventory] [2: Armory] [3: Skills] [4: Back] [5:Change Name]" << endl;
        char answer;
        bool IsBack = false;
        answer = _getch();
        switch (answer) {
            case '1': ShowInventory(player); break;
            case '2': ShowArmory(player); break;
            case '3': ShowSkills(player); break;
            case '4': IsBack = true; break;
            case '5': ShowChangeName(player); break;
            default: 
                cout << "---------------------------------------------------------\n";
                cout << "Wrong answer.Try enter right number again: " << endl;
                cout << "---------------------------------------------------------\n";
                Waitforseconds(1);
                break;
        }
        if (IsBack) { break; }
    }
   
}
void ShowInventory(Player& player) {
    while (true) {
        system("cls");
        MyInventory(player);
        cout << "[Item Name: Use Item] [[0]: Back]\nYour Answer: ";
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0") { return; }
        int id = FindItem(answer);

        if (id == -1) {
            cout << "Cannot find item";
            Waitforseconds(1);
            continue;
        }
        ItemInfo data = GetItemData(id);
        if (!CheckItem(player, id, 1)) {
            cout << "You don't have that item.\n";
            Waitforseconds(1);
            continue;
        }
        if (!data.IsUseable) {
            cout << "That item cannot be used.\n";
            Waitforseconds(1);
            continue;
        }
        Target target{ &player, nullptr, true};
        UseItem(data, target);
        player.RemoveItem(id, 1);
        Waitforseconds(1);
        continue;
    }
}
void ShowSkills(const Player& player) {
    system("cls");
    cout << "============================[   Skills   ]==========================\n";
    cout << "    "
        << left << setw(20) << "::name::"
        << left << setw(40) << "::Description::" << endl;
    const auto& skillmap = GetSkillMap();
    for (const auto& s : player.ViewSkill()) {
        auto skill = skillmap.find(s);
        if (skill == skillmap.end()) {
            cout << "  Empty" << endl;
            continue;
        }
        const SkillInfo& data = skill->second;
        cout << "  " 
            << left << setw(18) << data.name 
            << left << setw(40) << data.description << "\n";
    }
    cout << "====================================================================\n";
    cout << "[Enter any key to back to Menu]\n";
    _getch();
}
void ShowArmory(Player& player) {
    while (true) {
        system("cls");
        MyArmory(player);
        cout << "[[Gear name]: Equip gear] [[0]: Back to Menu]" << endl;
        cout << "[Weapon/Armor/Acc: Unequip gear]" << endl;
        cout << "Your Answer: ";
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0")
        {
            break;
        }
        if (answer == "Weapon" || answer == "weapon") { player.RemoveEquip(0); continue; }
        if (answer == "armor" || answer == "Armor") { player.RemoveEquip(1); continue; }
        if (answer == "Acc" || answer == "acc") { player.RemoveEquip(2); continue; }
        ItemSearch result = FindEquip(answer);
        if (!result.found) {
            cout << "---------------------------------------------------------------------\n";
            cout << "Cannot find that name, Try enter right name again: \n";
            cout << "---------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        bool owned = false;
        for (const auto& g : player.ViewArmory())
            if (g.ID == result.id) { owned = true; continue; }

        if (!owned) {
            cout << "---------------------------------------------------------------------\n";
            cout << "You don't have that gear.\n";
            cout << "---------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }

        int id = result.id;
        int slot = result.slot;
        cout << "---------------------------------------------------------------------\n";
        cout << "[" << answer << "] has been equipped." << endl;
        cout << "---------------------------------------------------------------------\n";
        player.AddEquip(slot, id);
        Waitforseconds(1);
        return;
    }
}
void ShowChangeName(Player& player) 
{
    system("cls");
    cout << "=====================[   Change Name   ]=================\n";
    cout << "Current Your Name: [" << player.GetName() << "]\n";
    cout << "---------------------------------------------------------\n";
    string newname;
    cout << "Enter your new name:";
    cin.clear();
    getline(cin >> ws, newname);
    player.ChangeName(newname);
    cout << "---------------------------------------------------------\n";
    cout << "Now your name is: [" << player.GetName() << "]\n";
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);
    return;
}
void ShowMix(Player& player) {
    while (true) {
        system("cls");
        cout << "====================================================================\n";
        cout << "Synthesis Menu\n";
        cout << "--------------------------------------------------------------------\n";
        cout << "[1]: Show my recipes\n";
        cout << "[2]: Search by ingredient\n";
        cout << "[3]: Search by outputs\n";
        cout << "[4]: back\n";
        cout << "====================================================================\n";
        int answer;
        answer = _getch();
        switch (answer) {
        case '1': MixRecipes_All(player); break;
        case '2': MixRecipes_Ing(player); break;
        case '3': MixRecipes_Out(player); break;
        case '4': return;
        default:
            cout << "Wrong answer.Try enter right number again: " << endl;
            _getch();
            break;
        }
       }
    }
void MixRecipes_All(Player& player) {
    while (true)
    {
        system("cls");
        cout << "====================================================================\n";
        cout << "Synthesis Recipes\n";
        cout << "--------------------------------------------------------------------\n";

        for (const auto& m : MixList()) {
            if (m.IsOpen) {
                cout << "No.[" << m.ID << "]: |" << m.first << "| + |" << m.second << "| = |" << m.output << "| \n";
            }
        }
        cout << "====================================================================\n";
        cout << "[[ID]: Synthesize with recipe] [[0]: to menu]\n";
        cout << "Your Answer: ";

        int answer;
        cin >> answer;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "--------------------------------------------------------------------\n";
            cout << "Wrong Input\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }

        if (answer == 0) { return; }

        const auto& mixmap = GetMixMap();
        auto mix = mixmap.find(answer);
        if (mix == mixmap.end() || !mix->second.IsOpen) {
            cout << "--------------------------------------------------------------------\n";
            cout << "This recipe is invalid. you haven't discovered this recipe or doesn't exist.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }

        if (Synthesize(player, mix->second))
        {
            Waitforseconds(1);
        }

        
    }
    }
void MixRecipes_Ing(Player& player) {
    while (true)
    {
        system("cls");
        cout << "====================================================================\n";
        cout << "Search Recipe by Ingredients\n";
        cout << "--------------------------------------------------------------------\n";
        cout << "[Enter Ingredient name] [[0]: back]\nYour Answer: ";
        
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0") { return; }
        vector<int> foundid;
     

        cout << "--------------------------------------------------------------------\n";
        for (const auto& m : MixList()) {
            if (m.IsOpen && (answer == m.first || answer == m.second)) {
                cout << "No.[" << m.ID << "]: |" << m.first << "| + |" << m.second << "| = |" << m.output << "|\n";
                foundid.push_back(m.ID);
            }
        }
        if (foundid.empty()) { 
            cout << "Cannot find any recipes." << endl; 
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        cout << "--------------------------------------------------------------------\n";
        cout << "[Enter recipe ID] [[0]: back]\nYour Answer: ";
        int id;
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (id == 0) continue;
        bool resultcheck = false;
        for (int f : foundid) {
            if (f == id) { resultcheck = true; break; }
        }
        if (!resultcheck) {
            cout << "--------------------------------------------------------------------\n";
            cout << "Invalid Input. Please try again.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        const auto& mixmap = GetMixMap();
        auto mix = mixmap.find(id);
        if (mix == mixmap.end() || !mix->second.IsOpen) {
            cout << "--------------------------------------------------------------------\n";
            cout << "Invalid Input. Please try again.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }

        if (Synthesize(player, mix->second))
        {
            Waitforseconds(1);
        }
    }

}
void MixRecipes_Out(Player& player) {
    while (true)
    {
        system("cls");
        cout << "====================================================================\n";
        cout << "Search Recipe by Output Items\n";
        cout << "--------------------------------------------------------------------\n";
        cout << "[Enter output Item name] [[0]: back]\nYour Answer: ";
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0") { return; }
        vector<int> foundid;
        cout << "--------------------------------------------------------------------\n";
        
        for (const auto& m : MixList()) {
            if (m.IsOpen && answer == m.output) {
                cout << "No.[" << m.ID << "]: |" << m.first << "| + |" << m.second << "| = |" << m.output << "|\n";
                foundid.push_back(m.ID);
            }
        }
        if (foundid.empty()) { 
           
            cout << "Cannot find any recipes." << endl; 
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        cout << "--------------------------------------------------------------------\n";
        cout << "[Enter recipe ID] [[0]: back]\nYour Answer: ";
        int id;
        cin >> id;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (id == 0) continue;
        bool resultcheck = false;
        for (int f : foundid) {
            if (f == id) { resultcheck = true; break; }
        }
        if (!resultcheck) {
            cout << "--------------------------------------------------------------------\n";
            cout << "Invalid Input. Please try again.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        const auto& mixmap = GetMixMap();
        auto mix = mixmap.find(id);
        if (mix == mixmap.end() || !mix->second.IsOpen) {
            
            cout << "Invalid Input. Please try again.\n" << endl;
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }

        if (Synthesize(player, mix->second))
        {
            Waitforseconds(1);
        }
        


    }
}
bool Synthesize(Player& player, const MixInfo& recipe) {
    int firstID = FindItem(recipe.first);
    int secondID = FindItem(recipe.second);
    int firstcount = recipe.count1;
    int secondcount = recipe.count2;
    bool sameID = false;

    if (firstID == secondID) {
        int totalcount = firstcount + secondcount;
        if(!CheckItem(player, firstID, totalcount)) {
            cout << "--------------------------------------------------------------------\n";
            cout << "You don't have enough ingredients.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            return false;
        }
        sameID = true;
        player.RemoveItem(firstID, totalcount);
    }
    else {
        bool hasfirst = CheckItem(player, firstID, firstcount);
        bool hassecond = CheckItem(player, secondID, secondcount);

        if (!hasfirst || !hassecond) {
            cout << "--------------------------------------------------------------------\n";
            cout << "You don't have enough ingredients.\n";
            cout << "--------------------------------------------------------------------\n";
            Waitforseconds(1);
            return false;
        }

        player.RemoveItem(firstID, firstcount);
        player.RemoveItem(secondID, secondcount);
    }
    player.AddItem(recipe.output_ID, 1);
    ItemInfo itemname1 = GetItemData(firstID);
    ItemInfo itemname2 = GetItemData(secondID);
    if (!sameID) {
        cout << "Spent [" << itemname1.name << "] x " << firstcount << endl;
        cout << "Spent [" << itemname2.name << "] x " << secondcount << endl;
    }
    else { cout << "Spent [" << itemname1.name << "] x " << firstcount + secondcount << endl; }
    Waitforseconds(1);
    cout << ".";
    Waitforseconds(1);
    cout << ".";
    Waitforseconds(1);
    cout << ".";
    Waitforseconds(1);
    cout << "\nSucceed Synthesize. you got [" << recipe.output << "]\n";
    Waitforseconds(2);
    return true;
}
bool Merchandise(Player& player, int merchantid) {
    while (true) {
        system("cls");
        ShopInfo merchantdata = GetShopData(merchantid);
        cout << "============================[   Merchant   ]=========================\n";
        cout << "[" << merchantdata.name << "]: \n";
        cout << merchantdata.greeting << endl;
        cout << "---------------------------------------------------------------------\n";
        cout << "   "
            << left << setw(17) << "::name::"
            << left << setw(20) << "::Quantity::"
            << left << setw(20) << "::Gil::"
            << left << setw(50) << "::Description::"
            << endl;
        for (const auto& s : ViewShop(merchantid)) {
            ItemInfo data = GetItemData(s.ID);
                cout << "   "
                << left << setw(22) << data.name
                << left << setw(15) << s.count
                << left << setw(20) << data.buy_value
                << left << setw(50) << data.description
                << endl;
        }
        cout << "---------------------------------------------------------------------\n";
        cout << "Current [" << player.GetGil() << "]\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "[Item name: buy item] [[1]: Sell Item] [[2]: Sell Gears] [[0]: Back]\nYour Answer: ";
        string answer;
        cin.clear();
        getline(cin >> ws, answer);
        if (answer == "1") {
            SellItemMenu(player);
            continue;
        }
        if (answer == "2") {
            SellGearMenu(player);
            continue;
        }
        if (answer == "0") { return false; }
        bool existed = CheckItem(merchantid, answer);
        if (!existed) {
            cout << "---------------------------------------------------------------------\n";
            cout << "Can not find that item\n";
            cout << "---------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        int d = FindItem(answer);
        ItemInfo data = GetItemData(d);
        if (data.buy_value > player.GetGil()) {
            cout << "---------------------------------------------------------------------\n";
            cout << "You don't have enough gil\n";
            cout << "---------------------------------------------------------------------\n";
            Waitforseconds(1);
            continue;
        }
        else {
            cout << "---------------------------------------------------------------------\n";
            cout << "You bought [" << data.name << "]\n";
            cout << "You spent [" << data.buy_value << "] gil\n";
            cout << "---------------------------------------------------------------------\n";
            Waitforseconds(1);
            RemoveGoods(merchantid, d);
            player.AddItem(d, 1);
            player.GainGil(-data.buy_value);
            continue;
        }
    }
}
bool SellItemMenu(Player& player) {
    while (true) {
        system("cls");
        MyInventory(player);
        cout << "[Item Name: Sell Item] [[0]: Back]\nYour Answer: ";
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0") { return false; }
        int id = FindItem(answer);

        if (id == -1) {
            cout << "Cannot find item";
            Waitforseconds(1);
            continue;
        }
        ItemInfo data = GetItemData(id);
        if (!CheckItem(player, id, 1)) {
            cout << "You don't have that item.\n";
            Waitforseconds(1);
            continue;
        }
        cout << "---------------------------------------------------------------------\n";
        cout << "You sold [" << data.name << "]\n";
        cout << "You gain [" << data.sell_value << "]\n";
        cout << "---------------------------------------------------------------------\n";
        player.RemoveItem(id, 1);
        player.GainGil(data.sell_value);
        Waitforseconds(1);
        continue;
    }
    }
bool SellGearMenu(Player& player) {
    while (true) {
        system("cls");
        MyArmory(player);
        cout << "[Gear Name: Sell Gear] [[0]: Back]\nYour Answer: ";
        string answer;
        getline(cin >> ws, answer);
        if (answer == "0") { return false; }
        int id = FindGear(answer);

        if (id == -1) {
            cout << "Cannot find item";
            Waitforseconds(1);
            continue;
        }
        EquipInfo data = GetGearData(id);
        if (!CheckGear(player, id, 1)) {
            cout << "You don't have that item.\n";
            Waitforseconds(1);
            continue;
        }
        cout << "---------------------------------------------------------------------\n";
        cout << "You sold [" << data.name << "]\n";
        cout << "You gain [" << data.sell_value << "]\n";
        cout << "---------------------------------------------------------------------\n";
        player.RemoveGear(id, 1);
        player.GainGil(data.sell_value);
        Waitforseconds(1);
        continue;
    }
}
void StatUpMenu(Player& player) {
    player.StatUp();
}
//Intro
void GameIntro()
{
	cout << "=========================================================\n";
    cout << "???: ";
    TypeEffect("Hear...", 45);
    Waitforseconds(1);
    cout << "???: ";
    TypeEffect("Feel...", 45);
    Waitforseconds(1);
    cout << "???: ";
    TypeEffect("Think...", 45);
    Waitforseconds(1);
	cout << "Continue with any key...";
    Waituntilinput();
}
static string GetPlayerName()
{
    while (true) {
        system("cls");
        string name;
        cout << "=========================================================\n";
        cout << "???: ";
        TypeEffect("By What name are you known. (Enter your Name)", 30);
        cout << "---------------------------------------------------------\n";
        cout << "Your Answer: ";
        cin.clear();
        getline(cin >> ws, name);
        cout << "Are you sure with [" << name << "]? [y/n]: " << endl;
       
        while (true) {
            char answer = _getch();
            if (answer == 'y' || answer == 'Y')
                return name;
            else if (answer == 'n' || answer == 'N') {
                system("cls");
                break;
            }
            else { cout << "Please entery 'y' or 'n' only.\n"; }
        }
    }
}
static RaceType GetPlayerRace()
{
    system("cls");
    while (true)
    {
        cout << "=========================================================\n";
        cout << "???: ";
        TypeEffect("From where have you come. (Choose your race)", 30);
        cout << "[1:Hyur] [2:Elezen] [3:Lalafell] [4:Miqote] [5:Roegadyn] [6:Au Ra]" << endl;
        cout << "---------------------------------------------------------\n";
        cout << "Answer with number\n";
        int input = -1;
        while (true)
        {
            input = _getch();

            if (input >= '1' && input <= '6') {
                input -= '0';
                break;
            }
        }

        RaceType race = intracetype(input);
        raceinfo(race);
   
        cout << "\nAre you sure? [y/n] : ";
        while (true) {
            char confirm = _getch();
            if (confirm == 'y' || confirm == 'Y')
                return race;
            else if (confirm == 'n' || confirm == 'N') {
                system("cls");
                break;
            }
            else { cout << "\nPlease entery 'y' or 'n' only."; }
        }      
    }
}
static JobType GetPlayerjob()
{
    system("cls");
    while (true)
    {
        int input;
        cout << "====================================================================\n";
        cout << "???: ";
        TypeEffect("What is it that you aspired to be. (Choose your job)", 30);
        cout << "[1:Paladin] [2:Warrior] [3:White Mage] [4:Rouge] [5:Bard] [6:Black Mage]" << endl;
        cout << "---------------------------------------------------------\n";
        cout << "Answer with number\n";
        while (true)
        {
            input = _getch();

            if (input >= '1' && input <= '6') {
                input -= '0';
                break;
            }

            cout << "Wrong answer, Try put right number again" << endl;
        }
        JobType job = intjobtype(input);
        jobinfo(job);
        
        cout << "\n" << "Are you sure? [y/n] :";
        while (true) {
            char confirm = _getch();
            if (confirm == 'y' || confirm == 'Y')
                return job;
            else  if (confirm == 'n' || confirm == 'N') {
                system("cls");
                break;
            }
            else { cout << "\nPlease enter 'y' or 'n' only."; }
        }
    }
}
static void PreviewCharacter(const string& name, RaceType race, JobType job) {
    Race racedata = GetRaceData(race);
    Job jobdata = GetJobData(job);
    system("cls");
    cout << "====================================================================\n";
    cout << "???:";
    TypeEffect("Is this truly destiny you choose ?", 30);
    cout << "--------------------------------------------------------------------\n";
    cout << "[Your Name: " << name << "] [Your Race: " << racedata.racename << "] [Your Job: " << jobdata.jobname << "]\n";
    cout << "HP: " << jobdata.base_HP << " MP: " << jobdata.base_MP << "\n";
    cout << "STR:" << jobdata.str + racedata.bonus_str << " DEX:" << jobdata.dex + racedata.bonus_dex << " CON:" << jobdata.con + racedata.bonus_con << " INT:" << jobdata.intel + racedata.bonus_int << " WIS:" << jobdata.wis + racedata.bonus_wis << " CHA:" << jobdata.cha + racedata.bonus_cha << endl;
    cout << "====================================================================";
}
Player CreateCharacterEvent() {
    string name;
    RaceType race;
    JobType job;
    while (true) 
    {
        name = GetPlayerName();
        race = GetPlayerRace();
        job = GetPlayerjob();

        PreviewCharacter(name, race, job);
        bool IsConfirm = false;
        cout << "\n" << "Are you sure? [y/n] : ";
        while (true) {
            char finalanswer = _getch();
            if (finalanswer == 'y' || finalanswer == 'Y')
            {
                IsConfirm = true;
                break;
            }
            else if (finalanswer == 'n' || finalanswer == 'N')
                break;

            else { cout << "\nPlease entery 'y' or 'n' only."; }
        }
        if (!IsConfirm) {
            continue;
        }
        Player player(name, race, job);
        int skillid = GetJobData(job).skill_ID;
        int weaponid = GetJobData(job).weapon_ID;
        int armorid = GetJobData(job).armor_ID;
        player.AddSkill(0, skillid);
        player.AddEquip(0, weaponid); // auto equip basic weapon on weapon slot
        player.AddEquip(1, armorid);  // auto equip basic armor on armor slot
        player.AddItem(1, 5);
        player.AddItem(6, 5);
        string skillname = GetSkillData(skillid).name;
        string weaponname = GetGearData(weaponid).name;
        string armorname = GetGearData(armorid).name;
        cout << "\nYou gain [" << skillname << "] skill.\n";
        Waitforseconds(1);
        cout << "You gain weapon [" << weaponname << "]\n";
        Waitforseconds(1);
        cout << "You gain armor [" << armorname << "]\n";
        Waitforseconds(1);
        cout << "You gain 5 potions.\n";
        Waitforseconds(1);
        cout << "You gain 5 Aether.\n";
        Waitforseconds(2);
        return player;
    }
}
void GameIntro2() {
    
    system("cls");
    cout << "=========================================================\n";
    cout << "Narration: ";
    TypeEffect("Through the encroaching gloom, the faint silhouette of a Lalafellin maiden takes form before your eyes", 15);
    Waitforseconds(1);
    cout << "???: ";
    TypeEffect("We have need of thee... Journey to Mor Dhona, and seek her out within the Rising Stones", 15);
    Waitforseconds(1);
    cout << "Narration: ";
    TypeEffect("Ere a single word can part your lips, the presence that resonated within your mind is vanishing into the ether.", 15);
    Waitforseconds(1);
    cout << "???: ";
	TypeEffect("Follow your light...", 120);
    Waitforseconds(2);
    cout << "=========================================================\n";
    cout << "Continue with any key...";
    Waituntilinput();
   
}
void MainScreen(Player& player) {
    string current_area = "Gridania";
        system("cls");
        cout << "=======================[" << current_area << "]=======================\n";
        cout << "Name: [ " << player.GetName() << " ] " << "HP: [" << player.GetHP() << "] MP: [" << player.GetMP() << "]\n";
        cout << "Job: [ " << player.GetJob() << " ] Level: [" << player.GetLevel() << "]" << endl;
        cout << "---------------------------------------------------------------------\n";
        cout << "[1]: Travel\n";
        cout << "[2]: Show Menu\n";
        cout << "[3]: Synthesize\n";
        cout << "[4]: Merchant\n";
        cout << "[0]: Quit\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "Enter Number: ";
        int answer;
        answer = _getch();
        switch (answer) {
        case '1': { Monster enemy = CreateMonster(RandomNum(1,2)); StartBattle(player, enemy); break; }
        case '2': ShowMenu(player); break;
        case '3': ShowMix(player); break;
        case '4': Merchandise(player, 1); break;
        default:
            cout << "\nWrong answer.Try enter right number again: " << endl;
            Waitforseconds(1);
            break;
        }
}
void Chapter1Event(Player& player, Monster& monster) {

}
void StartBattle(Player& player, Monster& monster) {
    BattleEvent_Normal(player, monster);
}
void EndGame() {
    system("cls");
    cout << "=========================================================\n";
    cout << "                       YOU DIED\n";
    cout << "=========================================================\n";

}
EventContext GetEventData(int id) {
    auto events = EventList();
    for (const auto& e : events) {
        if (e.id == id) return e;
    }
    return events[0];
}
//chapter1
void A_Soldiers_Breakfast(int id) {
    EventContext data = GetEventData(id);

        system("cls");
        cout << "=========================================================\n";
        TypeEffect("[A Soldier's Breakfast]", 20);
        Waitforseconds(1);
        cout << data.npcname << endl;
        TypeEffect("\nUnprovoked anole attacks have broken our meditation upon Naked Rock.", 15);
        Waitforseconds(1);
        cout << data.npcname << endl;
        TypeEffect("\nI ask that you slay a handful of these aggressive scalekin.", 15);
        Waitforseconds(1);
        cout << data.npcname << endl;
        TypeEffect("\nBring me one of their eggs as well, that we may stem their growth and restore balance to the forest.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "[Answer with [y/n]]";

        while (true) {
        string answer = "";
        cin.clear();
        cin >> answer;
            if (answer == "y" || answer == "Y") {
                cout << data.npcname << endl;
                TypeEffect("\nThank you, After find an egg, Please deliver to Tsubh Khamazom.", 15);
                cout << "=========================================================\n";
                Waitforseconds(1);
                EventList.erase[id - 1];
                EventList.push_back({ 1, EventType::BattleEvent, "A Soldier's Breakfast Battle", A_Soldiers_Breakfast_Battle });
                break;
            }
            if (answer == "n" || answer == "N") {
                cout << data.npcname << endl;
                TypeEffect("\nOkay, I understand. Safe your Journey.", 15);
                cout << "=========================================================\n";
                Waitforseconds(1);
                EventList.erase[id - 1];
                break;
            }
    }
}