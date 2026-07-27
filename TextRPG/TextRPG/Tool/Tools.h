#pragma once

#include <string>

using namespace std;

struct DiceCalc {
	int modifier;
	int dicecount;
	int dicenum;
};

int DiceRoll(const DiceCalc& formula);

void Waituntilinput();
void Waitforseconds(int seconds);
void TypeEffect(const string& text, int delay_ms);
int RandomNum(int min, int max);