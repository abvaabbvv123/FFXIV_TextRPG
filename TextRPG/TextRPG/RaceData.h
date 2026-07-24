#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
enum class RaceType {
	Hyur = 1,
	Elezen = 2,
	Lalafell = 3,
	Miqote = 4,
	Roegadyn = 5,
	AuRa = 6
};
struct Race
{
	int ID;
	RaceType racenum;
	string racename;
	string description;
	string AddStats;
	string Ainfo;

	int a_size;
	int a_speed;
	int bonus_str, bonus_dex, bonus_con, bonus_int, bonus_wis, bonus_cha;
};

vector<Race> RaceList();
unordered_map<int, Race> RaceMap();
Race GetRaceData(RaceType racetype);
void raceinfo(RaceType racetype);
RaceType intracetype(int num);

