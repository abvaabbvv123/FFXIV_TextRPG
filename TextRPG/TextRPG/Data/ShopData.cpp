#include "ShopData.h"
#include "Tools.h"
#include "dice.h"

using namespace std;

vector<ShopInfo> ShopList() {
	vector<ShopInfo> shops = {
		{1, "Kikipu",     "Looking to buy something? Horizon's got all a traveler needs!"},
		{2, "Enghelhart", "Welcome to my forge, friend. Need fine steel for the road?"},
		{3, "Memeroon",   "Welcome, welcome! Memeroon sells good goods for shine-shines!"},
		{4, "Giselbert",  "Greetings, traveler. Mind the desert heat and rest a spell."},
		{5, "Nettly",     "Safe travels through the wood. What supplies do you require?"},
		{6, "Blenheim",   "Brr... It is freezing out there. Step inside and inspect my wares."},       // coerthas
		{7, "Roderich",   "Ah, an adventurer! Looking to trade for your journey in Mor Dhona?"},       // Mor dona NPC
		{8, "J'jhazhi",   "Well met, adventurer! Take a look at my finest tools and sundries."}         // HiddenNPC
	};
	return shops;
}
unordered_map<int, Inventory<StockInfo>> shopinventory;
void InitShopInventory() {
	for (const auto& s : ShopList())
	{
		for (const auto& stock : ShopStock(s.ID))
			shopinventory[s.ID].Add(stock.ID, stock.count);
	}
}
vector<StockInfo> ShopStock(int merchantID) {
	if (merchantID == 1) //Kikipu
	{
		return {
			{1, DiceRoll({1, 1, 5})},
			{2, DiceRoll({1, 1, 2}) },
			{6, DiceRoll({1, 1, 3}) },
			{7, 1},
		};
	}
	return{};
}

ShopInfo GetShopData(int id)
{
	auto shops = ShopList();
	for (const auto& s : shops) {
		if (s.ID == id) return s;
	}
	return shops[0];
}
void AddGoods(int merchantid, int goodsid) {
	shopinventory[merchantid].Add(goodsid, 1);
}
void RemoveGoods(int merchantid, int goodsid) {
	shopinventory[merchantid].Remove(goodsid, 1);
}
const vector<StockInfo>& ViewShop(int merchantID) {
	return shopinventory[merchantID].ViewInventory();
}
bool CheckItem(int merchantid, string answer) {
	int checkvalue = FindItem(answer);
	if (checkvalue == -1) return false;

	for (const auto& s : ViewShop(merchantid)) 
		if (s.ID == checkvalue && s.count > 0) { return true; }

	return false;
}