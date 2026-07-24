#pragma once

struct DiceCalc {
	int modifier;
	int dicecount;
	int dicenum;
};

int DiceRoll(const DiceCalc& formula);

