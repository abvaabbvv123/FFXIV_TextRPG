#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
enum class JobType {
	Paladin = 1,
	Warrior = 2,
	WhiteMage = 3,
	Rouge = 4,
	Bard =5,
	BlackMage = 6
};
struct Job
{
	int ID;
	JobType jobnum;
	string jobname;
	string description;
	string recommendstatus;
	string statusinfo;
	string difficulty;

	int base_HP, base_MP;
	int str, dex, con, intel, wis, cha;
	int startdistance;
	int skill_ID, weapon_ID, armor_ID;
};
vector<Job> JobList();
unordered_map<int, Job> JobMap();
Job GetJobData(JobType type);
void jobinfo(JobType jobtype);
JobType intjobtype(int num);

