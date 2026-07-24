#include "dice.h"
#include <random>
using namespace std;

int DiceRoll(const DiceCalc& formula) {

	static random_device rd;
	static mt19937 gen(rd());

	int total = formula.modifier;

	for (int i = 0; i < formula.dicecount;  i++)
	{
		uniform_int_distribution<int>dist(1, formula.dicenum);
		total += dist(gen);
	}
	return total;
}