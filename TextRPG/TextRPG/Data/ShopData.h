#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ItemData.h"
#include "Inventory.h"
using namespace std;

struct StockInfo {
	int ID, count;
};
struct ShopInfo {
	int ID;
	string name;
	string greeting;
};

extern unordered_map<int, Inventory<StockInfo>> shopinventory;
void InitShopInventory();
vector<ShopInfo> ShopList();
vector<StockInfo> ShopStock(int merchantID);
const vector<StockInfo>& ViewShop(int merchantID);
ShopInfo GetShopData(int id);
bool CheckItem(int merchantid, string answer);

//maintanance Merchandise
void RemoveGoods(int merchantid, int goodsid);
void AddGoods(int merchantid, int goodsid);