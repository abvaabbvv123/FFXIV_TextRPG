#include "RaceData.h"


using namespace std;

vector<Race> RaceList() {
	vector<Race> races = {
		{1, RaceType::Hyur, "Hyur", "This hominin race is average in height and build. The Hyur are the most populous and widespread of the playable races.", "CHA + 1", "Size: Medium", 1, 1, 0, 0, 0, 0, 0, 1},
		{2, RaceType::Elezen,"Elezen", "This elfin race is tall and slender. They have slightly longer life spans when compared to the other races.", "CON + 1", "Size: Large" , 2, 1, 0 ,0, 1, 0, 0, 0},
		{3, RaceType::Lalafell,"Lalafell", "The Lalafell are a diminutive race from seas south of Eorzea. They possess child-like appearances and cheerful attitudes.", "INT + 1", "Size: Small" , 0, 0, 0, 0, 0, 1, 0, 0},
		{4, RaceType::Miqote, "Miqote", "This feline race possesses large ears and furred tails. They migrated to Eorzea during the Age of Endless Frost in the Fifth Umbral Era.", "DEX + 1", "Size: Medium" ,1, 0, 0, 1, 0, 0, 0, 0},
		{5, RaceType::Roegadyn,"Roegadyn", "The Roegadyn's massive muscular frames make them distinguishable from afar. Descended from maritime people that roamed the northern seas, they are sometimes considered a barbaric race.", "STR + 1", "Size: Large", 2, 0, 1, 0, 0, 0, 0, 0},
		{6, RaceType::AuRa,"Au Ra", "Introduced in Heavensward, the Au Ra are a superficially reptilian race with horns, scales and tails.", "WIS + 1", "Size: Medium" ,1, 1, 0, 0, 0, 0, 1, 0}
	};
	return races;
}
unordered_map<int, Race> RaceMap() {
	unordered_map<int, Race> result;
	for (const auto& race : RaceList())
		result[race.ID] = race;
	return result;
}


void raceinfo(RaceType racetype) {
	vector<Race> races = RaceList();
	bool racefound = false;

	for (const auto& race : races) {
		if (race.racenum == racetype) {

			cout << "====================================================================\n";
			cout << "Your pick: [" << race.racename << "]" << endl;
			cout << "Bouns Status: [" << race.AddStats << "] Size: [" << race.Ainfo << "]\n";
			cout << race.description << "\n";
			cout << "====================================================================";
			racefound = true;
			break;
		}
	}
	if (!racefound) {
		cout << "Error:Race data not found.\n";
	}
}
RaceType intracetype(int num)
{
	return static_cast<RaceType>(num);
}

Race GetRaceData(RaceType racetype) {
	auto races = RaceList();
    for (const auto& r : races) {
        if (r.racenum == racetype) return r;
    }
    return races.empty() ? Race{} : races[0];
}