#include <conio.h>
#include <iomanip>
#include <string>
#include <thread> 
#include <chrono> 
#include <cstdlib>
#include <random>
#include <limits>
#include <iostream>
#include <random> 
#include "Tools.h"

using namespace std;

int DiceRoll(const DiceCalc& formula) {

	static random_device rd;
	static mt19937 gen(rd());

	int total = formula.modifier;

	for (int i = 0; i < formula.dicecount; i++)
	{
		uniform_int_distribution<int>dist(1, formula.dicenum);
		total += dist(gen);
	}
	return total;

}
void Waituntilinput() { cout << "Enter any key:";  cin.get(); } // Function to wait for user input
void Waitforseconds(int seconds) { this_thread::sleep_for(chrono::seconds(seconds)); } // Function to wait for a specified number of seconds
void TypeEffect(const string& text, int delay_ms) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    cout << endl;
}
int RandomNum(int min, int max) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int>dist(min, max);

    return dist(gen);
}