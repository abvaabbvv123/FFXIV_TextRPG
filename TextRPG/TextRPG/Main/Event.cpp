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


static vector<EventContext> EventList_Original = {
    {1, EventType::QuestEvent, "A Soldier's Breakfast", "Pauline", A_Soldiers_Breakfast},
    {2, EventType::ChoiceEvent, "Heavy Lifting", "Maelstrom Officer", HeavyLifting },
    {3, EventType::ChoiceEvent, "Smash and Grab", "Wood Wailer", BoulderDash},
    {4, EventType::TrapEvent, "Trapped in the Mine", "System", CollapsedTunnel},
    {5, EventType::ChoiceEvent, "Stealthy Retrieval", "Yellowjacket Inspector", StealthyRetrieval},
    {6, EventType::ChoiceEvent, "Archer's Precision", "Godsivern Guard", ArchersMark},
    {7, EventType::TrapEvent, "Tripwire in the Shadows", "System", SpringToadTrap},
    {8, EventType::ChoiceEvent, "A Taste of Poison", "Alchemist Cactuar", PoisonTolerance},
    {9, EventType::ChoiceEvent, "Enduring the Blizzard", "Ishgardian Guard", FreezingBlizzard},
    {10, EventType::TrapEvent, "Toxic Spore Cloud", "System", ToxicGasTrap},
    {11, EventType::ChoiceEvent, "Deciphering Ancient Runes", "Sons of Saint Coinach", DecipherRunes},
    {12, EventType::ChoiceEvent, "Magitek Door Override", "Ironworks Engineer", MagitekOverride},
    {13, EventType::TrapEvent, "Psychic Shockwave", "System", IllusionTrap},
    {14, EventType::ChoiceEvent, "Tracking the Unseen", "Godsivern Ranger", TrackingBeast},
    {15, EventType::ChoiceEvent, "Whispers of the Forest", "Gridanian Conjurer", DecipherEmotion},
    {16, EventType::TrapEvent, "Siren's Bewitching Wail", "System", SirenSongTrap},
    {17, EventType::ChoiceEvent, "Golden Tongue", "Rowena's Representative", MerchantBargain},
    {18, EventType::ChoiceEvent, "Intimidate the Sentry", "Maelstrom Scout", GuardIntimidation},
    {19, EventType::TrapEvent, "Gaze of the Basilisk", "System", CharmingSirenTrap},
    {20, EventType::TradeEvent, "The Mysterious Blacksmith", "Wandering Smith Gerolt", WanderingBlacksmith },
    {21, EventType::TradeEvent, "Potion Alchemy Upgrade", "Alchemist Deimne", AlchemistExchange},
    {22, EventType::TradeEvent, "Old Recipe Scroll", "Herbalist Severian", RecipeTrader},
    
};

vector<EventContext>& EventList() {
    return EventList_Original;
}

EventContext FindEventByID(int id) {
    const auto& events = EventList();
    for (const auto& e : events) {
        if (e.id == id) return e;
    }
    return events[0];
}
// Tools
void TriggerEvent(int id, EventContext event, Player& player) {
    if (event.event)
        event.event(id, player);
}
void DeleteEventById(int id) {
    EventList_Original.erase(
        remove_if(EventList_Original.begin(), EventList_Original.end(),
            [id](const EventContext& e) { return e.id == id; }),
        EventList_Original.end()
    );
}
bool GetYesNo() {
    cout << "[Answer with [y/n]]\n";
    while (true) {
        char answer = _getch();
        if (answer == 'y' || answer == 'Y') {
            return true;
        }
        if (answer == 'n' || answer == 'N') {
            return false;
        }
    }
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
    player.AddItem(recipe.output_ID, recipe.count);
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
    _getch();
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
        player.SetJobNum(GetJobData(job).ID);
        player.AddSkill(0, skillid);
        player.AddEquip(0, weaponid); // auto equip basic weapon on weapon slot
        player.AddEquip(1, armorid);  // auto equip basic armor on armor slot
        player.AddItem(1, 2);
        player.AddItem(6, 2);
        string skillname = GetSkillData(skillid).name;
        string weaponname = GetGearData(weaponid).name;
        string armorname = GetGearData(armorid).name;
        cout << "\nYou gain [" << skillname << "] skill.\n";
        Waitforseconds(1);
        cout << "You gain weapon [" << weaponname << "]\n";
        Waitforseconds(1);
        cout << "You gain armor [" << armorname << "]\n";
        Waitforseconds(1);
        cout << "You gain a couple of potions.\n";
        Waitforseconds(1);
        cout << "You gain a couple of Aethers.\n";
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
    cout << "=========================================================\n";
    Waitforseconds(2);
    cout << "Continue with any key...";
    _getch();
   
}

void MainScreen(Player& player) {
    string current_area = "Gridania";
        system("cls");
        if (player.GetEXPToNextLevel() <= 0) {
            player.LevelUp();
        }
        cout << "=======================[" << current_area << "]=======================\n";
        cout << "Name: [ " << player.GetName() << " ] " << "HP: [" << player.GetHP() << "] MP: [" << player.GetMP() << "]\n";
        cout << "Job: [ " << player.GetJob() << " ] Level: [" << player.GetLevel() << "]" << endl;
        cout << "---------------------------------------------------------------------\n";
        cout << "[1]: Travel\n";
        cout << "[2]: Show Menu\n";
        cout << "[3]: Synthesize\n";
        // cout << "[4]: Merchant\n";
        cout << "[0]: Quit\n";
        cout << "---------------------------------------------------------------------\n";
        cout << "Enter Number: ";
        int answer;
        answer = _getch();
        switch (answer) {
        case '1': {
            while (true) {
                int roll = DiceRoll({ 0, 1, 50 });
                if (roll <= EventList_Original.size())
                {
                    TriggerEvent(roll, FindEventByID(roll), player);
                    Waitforseconds(2);
                    break;
                }
                else if (roll >= 45) {
                    Monster enemy = CreateMonster(RandomNum(1, 10));
                    BattleEvent_Normal(player, enemy);

                    break;
                }
                else if (roll >= 40 && roll < 45) {
                    Merchandise(player, RandomNum(1, 3));
                    break;
                }
                continue;
            }
            break;
        };
        case '2': ShowMenu(player); break;
        case '3': ShowMix(player); break;
        //case '4': Merchandise(player, 1); break;
        case '0': EndGame(); break;
        default:
            cout << "\nWrong answer.Try enter right number again: " << endl;
            Waitforseconds(1);
            break;
        }
}
void Chapter1Event(Player& player, Monster& monster) {

}
void EndGame() {
    system("cls");
    Waitforseconds(1);
    cout << "=========================================================\n";
    cout << "                       YOU DIED\n";
    cout << "=========================================================\n";
    Waitforseconds(3);
    exit(0);

}
void WinGame() {
    system("cls");
    Waitforseconds(1);
    cout << "=========================================================\n";
    cout << "                       YOU WIN\n";
    cout << "=========================================================\n";
    Waitforseconds(3);
    exit(0);
}


void A_Soldiers_Breakfast(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20); 
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Unprovoked anole attacks have broken our meditation upon Naked Rock.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I ask that you slay a handful of these aggressive scalekin.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Bring me one of their eggs as well, that we may stem their growth and restore balance to the forest.", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";
    cout << "[Answer with [y/n]]\n";
    while (true) {
        char answer = _getch();
        if (answer == 'y' || answer == 'Y') {
            cout << data.npcname << ": ";
            TypeEffect("Thank you, After find an egg, Please deliver to Tsubh Khamazom.", 15);
            cout << "=========================================================\n";
            Waitforseconds(1);
            DeleteEventById(id);
            EventList_Original.push_back(EventContext{ 1, EventType::BattleEvent, "A Soldier's Breakfast", "", A_Soldiers_Breakfast_Battle});
            break;
        }
        if (answer == 'n' || answer == 'N') {
            cout << data.npcname << ": ";
            TypeEffect("Okay, I understand. Safe your Journey.", 15);
            cout << "=========================================================\n";
            Waitforseconds(1);
            DeleteEventById(id);
            break;
        }
    }
}
void A_Soldiers_Breakfast_Battle(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    TypeEffect("You found Scaleskin's Nest. There is an egg and a scalekin", 15);
    Waitforseconds(1);
    TypeEffect("Do you want to fight then that?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";
    cout << "[Answer with [y/n]]\n";
    while (true) {
        char answer = _getch();
        if (answer == 'y' || answer == 'Y') {
            TypeEffect("Thank you, After find an egg, Please deliver to Tsubh Khamazom.", 15);
            cout << "=========================================================\n";
            Waitforseconds(1);
            Monster enemy = CreateMonster(7);
            BattleEvent_Normal(player, enemy);
            system("cls");
            cout << "=========================================================\n";
            TypeEffect("You won the battle. You can go back to Tsubh Khamazom whenever you can ", 15);
            cout << "=========================================================\n";
            DeleteEventById(id);

            EventList_Original.push_back(EventContext{ 1, EventType::CompleteEvent, "A Soldier's Breakfast", "Tsubh Khamazom", A_Soldiers_Breakfast_Complete });
            break;
        }
        if (answer == 'n' || answer == 'N') {
            TypeEffect("You decided run away for now, if you lucky, .", 15);
            cout << "=========================================================\n";
            Waitforseconds(1);
            break;
        }
    }
}
void A_Soldiers_Breakfast_Complete(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    bool required = CheckItem(player, 1001, 1);
    if (required) {
        cout << "=========================================================\n:::";
        TypeEffect(data.questname, 20);
        Waitforseconds(1);
        cout << data.npcname << ": ";
        TypeEffect("Ah, you have returned! And you brought the scalekin egg as requested.", 15);
        Waitforseconds(1);
        cout << data.npcname << ": ";
        TypeEffect("With this, balance will return to Naked Rock. You have our deepest gratitude.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        TypeEffect("You delivered the Scalekin Egg to Tsubh Khamazom.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int expreward = RandomNum(20, 40);
        player.GainEXP(expreward);
        cout << "You gain [" << expreward << "] exp" << endl;
        Waitforseconds(1);
        int gilreward = 200;
        player.GainGil(gilreward);
        cout << "You gain [" << gilreward << "] Gil" << endl;
        Waitforseconds(2);
    }
    else {
        cout << "=========================================================\n:::";
        TypeEffect(data.questname, 20);
        Waitforseconds(1);
        cout << data.npcname << ": ";
        TypeEffect("Ah, you have returned! But where is the scalekin egg?", 15);
        Waitforseconds(1);
        cout << data.npcname << ": ";
        TypeEffect("Did you forgot to bring egg or something? Whatever I can't give you any reward then.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        TypeEffect("You failed this quest.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int expreward = RandomNum(1, 10);
        player.GainEXP(expreward);
        cout << "You gain [" << expreward << "] exp" << endl;
        Waitforseconds(2);
    }
    // 이벤트 완료 처리 (목록에서 삭제)
    DeleteEventById(id);
}
void HeavyLifting(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Hey you, mind lending that muscular frame for a moment?", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("These iron-bound supply crates are far too heavy for our tired recruits.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("If you have enough Strength, haul them to the quartermaster down the dock.", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";
    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetSTR() >= dice) {
            TypeEffect("By Halone! You lifted those without even breaking a sweat. Outstanding work!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 2 * DiceRoll({ 0, 1, player.GetSTR() });
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(100, 1400);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Ugh... you strained your back trying to lift it. Train your Strength and return later.", 15);
            int penalty = DiceRoll({ 0, 1, player.GetSTR() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("No stamina for heavy work, eh? Fair enough. Pass along then.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void BoulderDash(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("The Ixal have rolled a massive boulder to block our patrol route through the Canopy.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Standard pickaxes won't break it in time. We need brute force to shatter the stone.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Are you strong enough to smash through that blockade with your bare arms or weapon?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";
    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetSTR() >= dice) {
            TypeEffect("CRASH! The boulder turns into rubble under your overwhelming might! Well done!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 30;
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(250, 500);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Clang! Your weapon bounces off, leaving only a scratch. You need greater Strength.", 15);
            int penalty = DiceRoll({ 0, 1, player.GetSTR() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Understood. We shall await the siege engineers then.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void CollapsedTunnel(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("As you step inside the abandoned Copperbell Mine, the ceiling suddenly trembles!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("A giant wooden beam breaks, dropping a shower of heavy rocks right above your head!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing a Strength Saving Throw to hold back the falling debris...", 15);
    cout << "=========================================================\n";
    Waitforseconds(2);

    
    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetSTR() });
    int total = roll + statroll;
    int goal = 22;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);
    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] You catch the falling rock with your sheer muscle and hurl it aside!", 15);
        cout << "System: ";
        TypeEffect("You safely escape the cave collapse and find a hidden treasure chest on the ground.", 15);
        cout << "=========================================================\n";
        int expreward = 2 + (total / 2);
        player.GainEXP(expreward);
        cout << "You gain [" << expreward << "] exp" << endl;
        Waitforseconds(1);
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] The weight is too overwhelming! You get pinned down by the rubble.", 15);
        cout << "System: ";
        TypeEffect("You barely crawl out of the mine, suffering a minor injury.", 15);
        player.TakeDamage(3);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [3] HP." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();
    DeleteEventById(id);
}
void StealthyRetrieval(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Shh! Keep your voice down. A pirate smuggler is resting nearby.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("He took our stolen ledger, but attacking him outright will alert his crew.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("If your Dexterity is high enough, slip past his guard and swipe the book.", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetDEX() >= dice) {
            TypeEffect("Like a shadow in the night! You retrieved the ledger without making a sound.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 2 * DiceRoll({ 0, 1, player.GetDEX() });
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(100, 100 * DiceRoll({0, 1, player.GetDEX()}));
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Clack! You stepped on a dry branch! The smuggler wakes up and slashes at you!", 15);
            int penalty = DiceRoll({ 0, 1, player.GetDEX() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Tch, fine. We'll wait for back-up then.", 15);
    }
    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void ArchersMark(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Greetings, adventurer. We are testing a new swift-moving training dummy.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("It weaves back and forth quickly. Only those with keen eyes and deft hands can hit it.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Care to demonstrate your Dexterity and strike the target's bullseye?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetDEX() >= dice) {
            TypeEffect("Thwack! A clean hit right in the center! Splendid marksmanship!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 32;
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(200, 600);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Whiff! Your attack completely missed the target, striking the wooden frame instead.", 15);
            int penalty = DiceRoll({ 0, 1, player.GetDEX() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("A pity. Return if you ever feel confident in your hands.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void SpringToadTrap(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("While navigating the dimly lit forest trail, your foot catches on a thin wire!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("SNAP! A concealed crossbow trap triggers, firing poisoned darts from the bushes!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing a Dexterity Saving Throw to dodge the incoming darts...", 15);
    cout << "=========================================================\n";


    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetDEX() });
    int total = roll + statroll;
    int goal = 23;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);

    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] With lightning reflex, you somersault backwards as darts fly past your face!", 15);
        cout << "System: ";
        TypeEffect("You safely avoid the trap and spot a small pouch dropped by the trap maker.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int gilreward = RandomNum(300, 1000);
        player.GainGil(gilreward);
        cout << "You gain [" << gilreward << "] Gil" << endl;
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] You couldn't react in time! A dart grazes your arm before you duck.", 15);
        int penalty = 4;
        player.TakeDamage(penalty);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [" << penalty << "] HP from the trap's poison." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();
    DeleteEventById(id);
}
void PoisonTolerance(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Greetings! I am testing a new antitoxin recipe, but I lack a sturdy subject.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I need someone with high Constitution to drink a diluted paralytic brew.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("If your body withstands the toxins, I shall compensate you handsomely for the data.", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetCON() >= dice) {
            TypeEffect("Astonishing! Your stomach didn't even churn. Your constitution is formidable!", 15);
            Waitforseconds(1);
            TypeEffect("Take this, Here's your reward.", 15);
            cout << "=========================================================\n";
            int gilreward = RandomNum(1000, 3000);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Ugh... your face turns pale and you vomit instantly. That toxin was too potent for you.", 15);
            int penalty = DiceRoll({ 0, 1, player.GetCON() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("A sensible choice. Poison testing is not for the faint of heart.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void FreezingBlizzard(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("A sudden blizzard has swept over the Coerthas highlands.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Our sentries are shivering violently, but we cannot abandon this outpost.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Do you have the Constitution to stand watch with us through this freezing gale?", 15);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetCON() >= dice) {
            TypeEffect("Unbelievable! You stood firm as a statue in that howling ice storm. Respect, adventurer!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = RandomNum(10, 30);
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(300, 600);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Teeth chattering... you couldn't take the frostbite and collapsed to your knees.", 15);
            int penalty = 4;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP from severe hypothermia." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Wise. Seek the campfire inside if you don't wish to freeze.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void ToxicGasTrap(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("While stepping into the damp cavern, your boot crushed a giant glowing bulb!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("PFFFFT! Thick purple spores erupt, filling the narrow corridor with noxious fumes!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing a Constitution Saving Throw to resist the lethal spores...", 15);

    cout << "=========================================================\n";


    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetCON() });
    int total = roll + statroll;
    int goal = 22;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);

    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] Your lungs hold strong! You cough briefly and charge out of the gas cloud unharmed!", 15);
        cout << "System: ";
        TypeEffect("On the other side of the cloud, you discover a pouch left behind by a dead explorer.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int gilreward = RandomNum(400, 1200);
        player.GainGil(gilreward);
        cout << "You gain [" << gilreward << "] Gil" << endl;
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] The spores burn your throat! You choke heavily as toxic poison seeps into your blood.", 15);
        int penalty = DiceRoll({ 0, 1, 4});
        player.TakeDamage(penalty);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [" << penalty << "] HP from severe airway damage." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();

    DeleteEventById(id);
}
void DecipherRunes(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Greetings, scholar. We found an ancient Allagan tablet in these ruins.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("The arcane geometry is incredibly complex. One wrong translation could trigger a mana backfire.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("If your Intelligence is up to the task, could you attempt to decipher these runes for us?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetINT() >= dice) {
            TypeEffect("Fascinating! You recognized the etheric equations instantly! Brilliant work!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 3 * DiceRoll({ 0, 1, player.GetINT() });
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(350, 1200);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Gah! You messed up everything!", 15);
            int penalty = -RandomNum(350, 600);
            player.GainGil(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << abs(penalty) << "] HP from mana feedback." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Wise to be cautious. Ancient Allagan magic is not something to be toyed with.", 15);
    }
    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void MagitekOverride(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("The Garlean imperial forces locked down this vault with a Magitek security terminal.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("We need to bypass the ceruleum circuit logic before the reinforcement alarm triggers.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Do you possess enough Intelligence to override the system panel?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetINT() >= dice) {
            TypeEffect("BEEP! The terminal flashes green and the heavy iron doors slide open!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = RandomNum(10,40);
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
        }
        else {
            TypeEffect("SPARK! Short-circuiting the wires triggered a defensive electrical shock!", 15);
            int penalty = DiceRoll({ 0, 1, player.GetINT() }) / 3;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP from high-voltage electricity." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Right, we better locate an explosive charges instead.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void IllusionTrap(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("As you touch an ancient stone altar, a sinister glyph blazes with crimson light!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("A powerful psychic shockwave penetrates your mind, summoning terrifying illusions!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing an Intelligence Saving Throw to discern reality from illusion...", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";


    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetINT() });
    int total = roll + statroll;
    int goal = 23;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);

    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] You logically analyze the flow of ether and shatter the mental illusion!", 15);
        cout << "System: ";
        TypeEffect("The altar crumbles, revealing an ancient sage's coin pouch hidden inside.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int gilreward = RandomNum(100, 1200);
        player.GainGil(gilreward);
        cout << "You gain [" << gilreward << "] Gil" << endl;
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] The terrifying illusions overwhelm your mind, causing severe psychic trauma!", 15);
        int penalty = DiceRoll({ 0, 1, player.GetINT() }) / 2;
        player.TakeDamage(penalty);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [" << penalty << "] HP from psychic damage." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();
    DeleteEventById(id);
}
void TrackingBeast(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("A wounded monster escaped deeper into the Black Shroud forest.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("The tracks are faint, washed away by the rain. Only keen Wisdom can discern the path.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Will you rely on your instincts and track down the beast's lair?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetWIS() >= dice) {
            TypeEffect("A broken twig, a scent in the wind! You found the lair with ease!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 3 * DiceRoll({ 0, 1, player.GetWIS() }) + 5;
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
        }
        else {
            TypeEffect("Ouch! You misjudged the trail and stumbled into a poisonous thorn bush!", 15);
            int penalty = DiceRoll({ 0, 1, player.GetWIS() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP from venomous thorns." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Rushing in blindly is dangerous anyway. Good call.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void DecipherEmotion(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("The elementals of this grove are restless, but their will is hard to attune to.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I need someone with deep spiritual Wisdom to commune with the flow of ether.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Can you quiet your mind and listen to what the forest seeks?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetWIS() >= dice) {
            TypeEffect("The spirits calm down as you channel harmony! They bestow a gentle blessing upon you.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = RandomNum(1,50);
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(1, 1500);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Gah! The enraged elementals reject your spirit, blasting you with a shockwave!", 15);
            int penalty = DiceRoll({ 0, 1, player.GetWIS() }) / 3;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP from spiritual dissonance." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Indeed, offending the elementals could lead to disaster.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void SirenSongTrap(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("As you walk along the foggy shore, an hauntingly beautiful melody echoes through the mist!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("It's a Siren's Wail! The melody seeks to compel you to walk into the jagged rocks!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing a Wisdom Saving Throw to maintain mental clarity...", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetWIS() });
    int total = roll + statroll;
    int goal = 21;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);

    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] Your steadfast willpower breaks the illusion! You plug your ears in time!", 15);
        cout << "System: ";
        TypeEffect("Near the shore, you find a wrecked treasure chest left behind by entranced sailors.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        player.AddItem(1, 3);
        cout << "You gain [Potion] x 3" << endl;
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] The song mesmerizes your mind! You wander blindly and cut yourself on sharp rocks!", 15);
        int penalty = abs(DiceRoll({ 0, 1, player.GetWIS() }) - 6);
        player.TakeDamage(penalty);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [" << penalty << "] HP from jagged rock cuts." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();

    DeleteEventById(id);
}
void MerchantBargain(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Welcome, adventurer! These rare potion ingredients normally cost a fortune.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("However, if you have a charming personality, perhaps we can strike a special deal...", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Care to test your Charisma and negotiate a bulk reward?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetCHA() >= dice) {
            TypeEffect("Haha! Your silver tongue wins me over! Here is your extra cut, pleasure doing business!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 3 * DiceRoll({ 0, 1, player.GetCHA() });
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = RandomNum(200, 1600);
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("You offended my pride! Pay the disrespect fee or get out of my sight!", 15);
            int penalty = DiceRoll({ 0, 1, player.GetCHA() }) / 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP from a physical scuffle with the bodyguards." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Hmph, fair prices for fair buyers then.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void GuardIntimidation(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Halt! This gate is restricted to authorised personnel only.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Unless... you have the presence and Charisma to convince me you are on urgent official duty.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Will you attempt to intimidate or persuade the guard into letting you pass?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        int dice = DiceRoll({ 0, 1, 20 });

        if (player.GetCHA() >= dice) {
            TypeEffect("Eek! Forgive me, noble warrior! Right this way, please don't hurt me!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            int expreward = 20 + player.GetLevel() * 4;
            player.GainEXP(expreward);
            cout << "You gain [" << expreward << "] exp" << endl;
            Waitforseconds(1);
            int gilreward = expreward * 26;
            player.GainGil(gilreward);
            cout << "You gain [" << gilreward << "] Gil" << endl;
        }
        else {
            TypeEffect("Insolent rogue! Impersonating an officer is a crime! En garde!", 15);
            int penalty = player.GetLevel() * 2;
            player.TakeDamage(penalty);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You lost [" << penalty << "] HP fighting off the guard's counterattack." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Good. Turn around and leave quietly.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(1);
    DeleteEventById(id);
}
void CharmingSirenTrap(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("You open a polished obsidian mirror inside the crypt!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("A sudden cursed aura bursts forth, attempting to dominate your presence and freeze your soul!", 15);
    Waitforseconds(1);
    cout << "System: ";
    TypeEffect("[EMERGENCY] Performing a Charisma Saving Throw to project force of personality...", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    int roll = DiceRoll({ 0, 1, 20 });
    int statroll = DiceRoll({ 0, 1, player.GetCHA() });
    int total = roll + statroll;
    int goal = 20;
    cout << "Continue with any key...\n";
    _getch();
    cout << "---------------------------------------------------------\n";
    cout << ">> [Saving Throw Dice]: ";
    Waitforseconds(1);
    cout << roll;
    Waitforseconds(1);
    cout << "\n>> [Stat Bonus Dice]: ";
    Waitforseconds(1);
    cout << statroll;
    cout << "\n>> [Total]: " << total << " / [Required]: " << goal << endl;
    cout << "---------------------------------------------------------\n";
    Waitforseconds(1);

    if (total >= goal) {
        cout << "System: ";
        TypeEffect("[SUCCESS] Your overwhelming force of presence shatters the curse! The mirror breaks!", 15);
        cout << "System: ";
        TypeEffect("A pile of ancient gems spills out from behind the shattered mirror.", 15);
        Waitforseconds(1);
        cout << "=========================================================\n";
        int gilreward = RandomNum(600, 1400);
        player.GainGil(gilreward);
        cout << "You gain [" << gilreward << "] Gil" << endl;
    }
    else {
        cout << "System: ";
        TypeEffect("[FAIL] Your spirit falters! The curse suppresses your vitality!", 15);
        int penalty = DiceRoll({ 0, 1, player.GetCHA() }) / 2;
        player.TakeDamage(penalty);
        Waitforseconds(1);
        cout << "=========================================================\n";
        cout << "You lost [" << penalty << "] HP from spiritual suppression." << endl;
    }

    cout << "=========================================================\n";
    cout << "[Press any key to continue...]";
    _getch();

    DeleteEventById(id);
}
void WanderingBlacksmith(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Clang... clang... Ah, a traveler on these dangerous paths.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I am Gerolt, a blacksmith seeking rare funds to forge my masterwork weapon.", 15);
    Waitforseconds(1);
    int requiredGil = 5852 - (212 * player.GetCHA());
    EquipInfo rewardItem;
    if (player.GetCHA() >= 16) { rewardItem = GetGearData((player.GetJobNum() * 100000) + 1004); }
    else { rewardItem = GetGearData((player.GetJobNum() * 100000) + 1003); }
    

    cout << data.npcname << ": ";
    TypeEffect("I happen to have a fine weapon with me. I'll pass it to you for some Gil.", 15);
    Waitforseconds(1);
    cout << "---------------------------------------------------------------------\n";
    cout << "[" << data.npcname << "]'s Offer: " << requiredGil << endl;
    cout << "Reward Item: [" << rewardItem.name << "]" << endl;
    cout << "---------------------------------------------------------------------\n";
    TypeEffect("What do you say? A fair price for legendary craftsmanship, isn't it?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        if (player.GetGil() >= requiredGil) {
            player.GainGil(-requiredGil); 
            player.AddGear(rewardItem.ID, 1);  
            TypeEffect("Pleasure doing business! Take care of this fine steel.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You spent [" << requiredGil << "] Gil." << endl;
            cout << "You received [" << rewardItem.name << "]!" << endl;
        }
        else {
            TypeEffect("Hmph! You don't even have enough Gil. Come back when your purse is full.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "Trade failed: Not enough Gil." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Tch... blind to true quality. Farewell then.", 15);
    }
    cout << "=========================================================\n";
    Waitforseconds(2);
    DeleteEventById(id);
}
void AlchemistExchange(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Ah, greetings traveler. Are you carrying dilute, standard Healing Potions?", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I can distill and refine their impurities into a much more potent elixir for you.", 15);
    Waitforseconds(1);

    int requiredAmount;
    if (player.GetCHA() > 15) { requiredAmount = 2; }
    else if (player.GetCHA() > 13) { requiredAmount = 3; }
    else if (player.GetCHA() > 10) { requiredAmount = 4; }

    ItemInfo rewardItem = GetItemData(5);

    cout << data.npcname << ": ";
    TypeEffect("Bring me the raw materials and a small fee, and I'll brew it right away.", 15);
    Waitforseconds(1);
    cout << "---------------------------------------------------------------------\n";
    cout << "[" << data.npcname << "]'s Requirement: [Potion] x" << requiredAmount << endl;
    cout << "Reward Item: [" << rewardItem.name << "]" << endl;
    cout << "---------------------------------------------------------------------\n";
    TypeEffect("Would you like to exchange your lower-grade potions?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        if (CheckItem(player, 1, requiredAmount)) {
            player.RemoveItem(1, requiredAmount); 
            player.AddItem(rewardItem.ID, 1);        

            TypeEffect("Splendid! Stand back... *bubble bubble* Here is your refined potion!", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You spent [" << requiredAmount << "] Basic Potions." << endl;
            cout << "You received [" << rewardItem.name << "]!" << endl;
        }
        else {
            TypeEffect("Hmm, you don't seem to have enough basic potions for distillation.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "Trade failed: Not enough materials." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Safe travels then. Let me know if you change your mind.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(2);
    DeleteEventById(id);
}
void RecipeTrader(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Shh... I have obtained rare manuscript scrolls from the Alchemist Guild.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("These pages contain ancient secrets for crafting advanced restoration potions.", 15);
    Waitforseconds(1);

    int requiredGil = 4500 - (180 * player.GetCHA());
    MixInfo rewardItem;

    if (player.GetCHA() >= 12) {
        rewardItem = GetMixData(6);     }
    else {
        rewardItem = GetMixData(5); 
    }

    cout << data.npcname << ": ";
    TypeEffect("I can part with one of these scrolls if you compensate me well.", 15);
    Waitforseconds(1);
    cout << "---------------------------------------------------------------------\n";
    cout << "[" << data.npcname << "]'s Offer: " << requiredGil << " Gil" << endl;
    cout << "Reward Recipe: [High Aether Recipe]" << endl;
    cout << "---------------------------------------------------------------------\n";
    TypeEffect("Knowledge isn't free, friend. Are you willing to purchase it?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        if (player.GetGil() >= requiredGil) {
            player.GainGil(-requiredGil);
            player.AddGear(rewardItem.ID, 1);

            TypeEffect("A wise investment! Guard this knowledge with your life.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You spent [" << requiredGil << "] Gil." << endl;
            cout << "You learned/received [" << rewardItem.recipe_name << "]!" << endl;
        }
        else {
            TypeEffect("You lack the Gil. I cannot give away guild secrets for free.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "Trade failed: Not enough Gil." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("Your loss. Ignorance is expensive in the wilderness.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(2);
    DeleteEventById(id);
}
void HerbCollectorRecipe(int id, Player& player) {
    EventContext data = FindEventByID(id);
    system("cls");
    cout << "=========================================================\n:::";
    TypeEffect(data.questname, 20);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("Greetings. I have lived in these woods for decades studying rare flora.", 15);
    Waitforseconds(1);
    cout << data.npcname << ": ";
    TypeEffect("I am looking for 'Mandragora Roots' to finish my life's work.", 15);
    Waitforseconds(1);

    ItemInfo requiredID = GetItemData(5);
    MixInfo rewardItem;

    if (player.GetWIS() >= 15) { 
        rewardItem = GetMixData(8); 
    }
    else {
        rewardItem = GetMixData(7); 
    }

    cout << data.npcname << ": ";
    TypeEffect("Bring me those roots, and I shall teach you a secret potion recipe.", 15);
    Waitforseconds(1);
    cout << "---------------------------------------------------------------------\n";
    cout << "[" << data.npcname << "]'s Offer: [" << requiredID.name << "]" << endl;
    cout << "Reward Recipe: [" << rewardItem.recipe_name << "]" << endl;
    cout << "---------------------------------------------------------------------\n";
    TypeEffect("Do you have the Exlixir I require?", 15);
    Waitforseconds(1);
    cout << "=========================================================\n";

    if (GetYesNo()) {
        cout << data.npcname << ": ";
        if (CheckItem(player,requiredID.ID, 1)) {
            player.RemoveItem(requiredID.ID, 1);
            player.AddGear(rewardItem.ID, 1);

            TypeEffect("Ah! Excellent quality! As promised, take this handwritten recipe formula.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "You handed over [" << requiredID.name << "]." << endl;
            cout << "You received [" << rewardItem.recipe_name << "]!" << endl;
        }
        else {
            TypeEffect("You don't have enough Mandragora Roots. Come back when you gather them.", 15);
            Waitforseconds(1);
            cout << "=========================================================\n";
            cout << "Trade failed: Missing required herbs." << endl;
        }
    }
    else {
        cout << data.npcname << ": ";
        TypeEffect("May the woods keep you safe then.", 15);
    }

    cout << "=========================================================\n";
    Waitforseconds(2);
    DeleteEventById(id);
}