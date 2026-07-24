#include "JobData.h"


using namespace std;

vector<Job> JobList() {
	vector<Job> jobs = {
		{1, JobType::Paladin, "Paladin", "Balanced melee attacker with a sword and shield. Perfect balance of offense and defense.", "STR, CON", "HP:20 MP:10 / STR:12 DEX:10 CON:12 INT:6 WIS:10 CHA:10 ", "¡Ú ¡Ú ¡Ù", 20, 10, 12, 10, 12, 6, 10, 10, -1, 101/*skill ID*/, 101001 /*Weapon ID*/, 102001 /*Armor ID*/},
		{2, JobType::Warrior, "Warrior", "Powerful melee attacker with two-handed greataxes. Every single strikes delivers devastating power but slow   ", "HP, STR", "HP:26 MP:6 / STR:14 DEX:8 CON:12 INT:6 WIS:6 CHA:10 ", "¡Ú ¡Ú ¡Ù", 26, 6, 14, 8, 12, 6, 6, 10, -1,  201/*skill ID*/, 201001 /*Weapon ID*/, 202001 /*Armor ID*/},
		{3, JobType::WhiteMage, "White mage", "Sacred ranged supporter and wield holy magic. Vulnerable in solo combat but provide invaluable help to the others ","MP, WIS", "HP:12 MP:20 / STR:6 DEX:8 CON:10 INT:10 WIS:14 CHA:10", "¡Ú ¡Ú ¡Ú", 12, 20, 6, 8, 10, 10, 14, 10, 2,  301/*skill ID*/, 301001 /*Weapon ID*/, 302001 /*Armor ID*/},
		{4, JobType::Rouge, "Rouge", "Sneaky and swift melee attaker with two Daggers. Easily evade danger and slip out of tight spots","DEX", "HP:18 MP:12 / STR:10 DEX:14 CON:10 INT:8 WIS:8 CHA:10", "¡Ú ¡Ù ¡Ù", 18, 12, 10, 14, 10, 8, 8, 10, -2, 401/*skill ID*/, 401001 /*Weapon ID*/, 402001 /*Armor ID*/},
		{5, JobType::Bard, "Bard", "Versatile ranged attaker with instrument bow. Bards are highly adaptable so handle any situation with ease.","DEX, CHA", "HP:16 MP:14 / STR:8 DEX:12 CON:8 INT:8 WIS:12 CHA:12", "¡Ú ¡Ù ¡Ù", 16, 14, 8, 12, 8, 8, 12, 12,  2, 501/*skill ID*/, 501001 /*Weapon ID*/, 502001 /*Armor ID*/},
		{6, JobType::BlackMage, "Black Mage", "Destructive range attaker and wield black magic. Possess high-power from afar, but defenseless in close quarters","Int", "HP:14 MP:18 / STR:6 DEX:10 CON:6 INT:14 WIS:10 CHA:12", "¡Ú ¡Ú ¡Ú", 14, 18, 6, 10, 6, 14, 10, 12, 2, 601/*skill ID*/, 601001 /*Weapon ID*/, 602001 /*Armor ID*/}
	};
	return jobs;
}
unordered_map<int, Job> JobMap() {
	unordered_map<int, Job> result;
	for (const auto& job : JobList()) {
		result[job.ID] = job;
	}
	return result;
}

void jobinfo(JobType jobtype) {
	vector<Job> jobs = JobList();
	bool jobfound = false;

	for (const auto& job : jobs) {
		if (job.jobnum == jobtype) {

			cout << "====================================================================\n";
			cout << "[" << job.jobname << "]" << "\nRecommend Status: " << job.recommendstatus << " / Difficulty: " << job.difficulty << "\n";
			cout << job.description << "\n";
			cout << "Status: " << job.statusinfo << "\n";
			cout << "====================================================================";
			jobfound = true;
			break;
		}
	}
	if (!jobfound)
		cout << "Error: Job data not found.\n";
}
JobType intjobtype(int num)
{
	return static_cast<JobType>(num);
}
Job GetJobData(JobType type) {
	auto jobs = JobList();
	for (const auto& j : jobs) {
		if (j.jobnum == type) return j;
	}
		return jobs.empty() ? Job{} : jobs[0];
	
}

