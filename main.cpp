//#include "stdafx.h"
#include "HUD.h"
#include "windows.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;

int k;

struct Charac {
	string route = "None";
	string race = "HAH";
	string name;
	int seed;
	int day = 0;
	int loop = 1;
	int ing = 10;
	int hg = 100;
	int cash = 50;
	int san = 100;
	int soul = 100;
	int enemiesk = 0;
	double scoremp = 0.00;
	double score = 0;
	int bikeHP = 100;
	int totaldaysbiked = 0;
} Char;

struct Effects {
	int foodCost[3] = { 10, 20, 30 };
	int foodRestore[3] = { 25, 50, 100 };
	int hungerLoss = 0;
	int sanityLoss = 0;
	int ingGain = 0;
	int bikeDMGLoss = 0;
	bool foodPoisonImm = false;
} RE;

void wait_enter(void) //Method of wait_enter, call it to create a Press Enter to continue screen.
{
	cin.ignore();
	cout << "Press ENTER to continue...";
	cin.ignore();
}

void hungerLost() {
	int hgLoss;
	hgLoss = rand() % 13 + RE.hungerLoss;
	if (hgLoss < 0) {
		hgLoss = 0;
	}
	Char.hg -= hgLoss;
}

void sanityLost() {
	int snLoss;
	snLoss = rand() % 3 + RE.sanityLoss;
	if (snLoss < 0) {
		snLoss = 0;
	}
	Char.san -= snLoss;
}

void statCheck() {
	if (Char.hg > 100) {
		Char.hg = 100;
	}
	if (Char.san > 100) {
		Char.san = 100;
	}
	if (Char.soul > 100) {
		Char.soul = 100;
	}
}

void ride() {
	int bikeLoss;
	bikeLoss = rand() % 3 + RE.bikeDMGLoss;
	if (bikeLoss < 0) {
		bikeLoss = 0;
	}
	system("CLS");
	cout << "-*- COOK BMX! -*-" << endl;
	cout << "\nYou ride..." << endl;
	cout << "Your bike loses " << bikeLoss << " durability." << endl;
	wait_enter();
	hungerLost();
	Char.day -= 1;
	Char.score += 1;
	Char.totaldaysbiked += 1;
	Char.bikeHP -= bikeLoss;
}

void cooky() {
	int cookput;

	system("CLS");
	cout << "-*- COOK BMX! -*-" << endl;
	cout << "\nWhat would you like to cook?\n\n0) Exit\n\n1) Steak - " << RE.foodCost[0] << " ING\n2) Pizza - " << RE.foodCost[1] << " ING\n3) NUGGIES - " << RE.foodCost[2] << " ING" << endl;
	cout << "\nIngredients: " << Char.ing << endl;
	cout << "Hunger: " << Char.hg << endl;
	cin >> cookput;
	switch (cookput) {
	case 1:
		if (Char.ing < RE.foodCost[0]) {
			cout << "Not enough Ingredients!" << endl;
			wait_enter();
		}
		else {
			cout << "You make a steak and restore " << RE.foodRestore[0] << " hunger back!" << endl;
			Char.hg += RE.foodRestore[0];
			Char.ing -= RE.foodCost[0];
			Char.score += 1;
			wait_enter();
		}
		break;
	case 2:
		if (Char.ing < RE.foodCost[1]) {
			cout << "Not enough Ingredients!" << endl;
			wait_enter();
		}
		else {
			cout << "You make a pizza and restore " << RE.foodRestore[1] << " hunger back!" << endl;
			Char.hg += RE.foodRestore[1];
			Char.ing -= RE.foodCost[1];
			Char.score += 2;
			wait_enter();
		}
		break;
	case 3:
		if (Char.ing < RE.foodCost[2]) {
			cout << "Not enough Ingredients!" << endl;
			wait_enter();
		}
		else {
			cout << "You make a NUGGIES!!! and restore " << RE.foodRestore[2] << " hunger back!" << endl;
			Char.hg += RE.foodRestore[2];
			Char.ing -= RE.foodCost[2];
			Char.score += 3;
			wait_enter();
		}
		break;



	}

}

void hunty() {
	int inputy;
	int chance;
	int goldChance;
	int hgLoss;
	system("CLS");

	cout << "-*- COOK BMX! -*- " << endl;
	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1) Hunt Small Creatures\n - Less chance of being attacked, less rewards.\n\n2) Hunt Big Boys\n - Higher chance of being attacked, more rewards.\n\n3) I didn't mean it... Let me out" << endl;
	cin >> inputy;
	switch (inputy) {
	case 1:
		system("CLS");
		chance = rand() % 10;
		goldChance = rand() % 50;
		if (chance == 5) {
			cout << "You bring back a bear, giving you " << 15 + RE.ingGain << " ingredients.\nYou also find " << goldChance << " cash." << endl;
			Char.ing += 15 + RE.ingGain;
			Char.cash += goldChance;
			if (Char.race != "IPC") {
				Char.soul -= 1;
			}
			hungerLost();
			sanityLost();
			Char.score += 5;
			Char.enemiesk += 1;
			wait_enter();
		}
		else if (chance == 4) {
			cout << "You get attacked and lose some supplies...\n-5 ING\n-30 Cash" << endl;
			Char.cash -= 30;
			Char.ing -= 5;
			Char.soul -= 1;
			hungerLost();
			sanityLost();
			Char.score -= 10;
			Char.enemiesk += 1;
			wait_enter();
		}
		else if (chance < 4) {
			cout << "You find a possum and kill it. You gain " << 5 + RE.ingGain << " ingredients." << endl;
			Char.ing += 5 + RE.ingGain;
			if (Char.race == "IPC") {
				Char.soul -= 3;
			}
			else {
				Char.soul -= 1;
			}
			hungerLost();
			Char.score += 1;
			Char.enemiesk += 1;
			sanityLost();
			wait_enter();
		}
		else if (chance > 5) {
			cout << "You find nothing." << endl;
			hungerLost();
			sanityLost();
			Char.score -= 1;
			wait_enter();
		}
		break;
	case 2:
		system("CLS");
		chance = rand() % 10;
		goldChance = rand() % 50;
		if (chance < 4) {
			cout << "You bring back a bear, giving you " << 15 + RE.ingGain << " ingredients.\nYou also find " << goldChance << " cash." << endl;
			Char.ing += 15 + RE.ingGain;
			Char.cash += goldChance;
			if (Char.race != "IPC") {
				Char.soul -= 1;
			}
			hungerLost();
			Char.enemiesk += 1;
			sanityLost();
			wait_enter();
		}
		else if (chance > 5) {
			cout << "You get attacked and lose some supplies...\n-5 ING\n-30 Cash" << endl;
			Char.cash -= 30;
			Char.ing -= 5;
			Char.soul -= 1;
			hungerLost();
			sanityLost();
			wait_enter();
		}
		else if (chance == 5) {
			cout << "You find a possum and kill it. You gain " << 5 + RE.ingGain << " ingredients." << endl;
			Char.ing += 5 + RE.ingGain;
			if (Char.race == "IPC") {
				Char.soul -= 3;
			}
			else {
				Char.soul -= 1;
			}
			hungerLost();
			sanityLost();
			Char.enemiesk += 1;
			wait_enter();
		}
		break;
	}

}

void victory() {
	int looptest;
	system("CLS");
	cout << "-*- VICTORY! -*-" << endl;
	cout << "\nYour score is: ";
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << Char.score * Char.scoremp;
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << "!\n\nCreatures Killed: ";
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << Char.enemiesk;
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << "..." << "\n\nTotal Days Biked: ";
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << Char.totaldaysbiked;
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << " Days\n\nStats: \nName: ";
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << Char.name; 
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << "\nRace: ";
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << Char.race;
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << "\n\nWould you like to loop?" << endl;
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << "\n1";
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << ") Yes!" << endl;
	k = 11;
	SetConsoleTextAttribute(hConsole, k);
	cout << "2";
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	cout << ") NO." << endl;
	cin >> looptest;

	

}

void cookSGO() {
	while (true) {
		if (Char.day <= 0) {
			victory();
		}
		int input1;
		statCheck();
		HUD hungerHud(Char.hg);
		HUD soulHud(Char.soul);
		HUD sanityHud(Char.san);
		HUD bikeHud(Char.bikeHP);
		system("CLS");
		cout << "-*- COOK BMX! -*-" << endl;
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		cout << "\n1";
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << ") Ride\n";
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		cout << "2";
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << ") Cook\n";
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		cout << "3";
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << ") Hunt\n";
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		cout << "4";
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << ") Full Stats" << endl;
		cout << "\nHunger: ";
		k = 10;
		SetConsoleTextAttribute(hConsole, k);
		hungerHud.draw();
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << " " << Char.hg << "%" << endl;
		cout << "\nSanity: ";
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		sanityHud.draw();
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << " " << Char.san << "%\n\nSoul:   ";
		k = 9;
		SetConsoleTextAttribute(hConsole, k);
		soulHud.draw();
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << " " << Char.soul << "%\n\nBikeHP: ";
		k = 12;
		SetConsoleTextAttribute(hConsole, k);
		bikeHud.draw();
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		cout << " " << Char.bikeHP << "%" << endl;
		cout << "\nDays Left: ";
		k = 11;
		SetConsoleTextAttribute(hConsole, k);
		cout << Char.day;
		k = 15;
		SetConsoleTextAttribute(hConsole, k);
		if (Char.day == 1) {
			cout << " Day" << endl;
		}
		else
		{
			cout << " Days" << endl;
		}
		cin >> input1;
		switch (input1) {
		case 1:
			ride();
			break;
		case 2:
			cooky();
			break;
		case 3:
			hunty();
			break;
		case 4:
			break;
		}
	}
}

void cookStart() {
	int input1;
	system("CLS");
	cout << "-*- Choose Route -*-" << endl;
	cout << "\n1) Sandia Crest - 15 Days\n2) Himilayas - 35 Days\n3) The Alps - 100 Days" << endl;
	cin >> input1;
	switch (input1) {
	case 1:
		Char.route = "Sandia Crest";
		Char.day = 15;
		Char.scoremp = .5;
		break;
	case 2:
		Char.route = "Himilayas";
		Char.day = 35;
		Char.scoremp = 1;
		break;
	case 3:
		Char.route = "The Alps";
		Char.day = 100;
		Char.scoremp = 2;
		break;
	}
	system("CLS");
	cout << "-*- Choose Race -*-" << endl;
	cout << "\n1) Human\n - Loses less hunger, loses less sanity.\n\n2) Goblin\n - Can eat trash in cities, loses extra hunger while biking\n   Immune to food poisoning\n\n3) Intelligent Possum Creature (IPC, Possum Man)\n - Loses less soul when killing bears, and more when killing possums.\n   Gains more ING from all creatures" << endl;
	cout << "\n4) Skeltin\n - Bike takes less damage overall, eats less. Lose more sanity\n\n5) Robot\n - Can repair bike for free, all food costs extra to make." << endl;
	cin >> input1;
	switch (input1) {

	case 1:
		Char.race = "Human";
		RE.hungerLoss = -2;
		RE.sanityLoss = -1;
		break;

	case 2:
		Char.race = "Goblin";
		RE.hungerLoss = -3;
		RE.foodPoisonImm = true;
		break;

	case 3:
		Char.race = "IPC";
		RE.ingGain = 3;
		break;

	case 4:
		Char.race = "Skeltin";
		RE.hungerLoss = -3;
		RE.sanityLoss = 4;
		RE.bikeDMGLoss = -1;
		break;

	case 5:
		Char.race = "Robot Friend";
		RE.foodCost[0] = 20;
		RE.foodCost[1] = 30;
		RE.foodCost[2] = 40;
		break;
	}
	system("CLS");
	cout << "Whats your name?" << endl;
	cin.ignore();
	getline(cin, Char.name);
	for (size_t i = 0; i < Char.name.size(); i++) {
		Char.seed += int(Char.name[i]);
	}
	srand(Char.seed);
	cookSGO();
}


int main()
{
	k = 15;
	SetConsoleTextAttribute(hConsole, k);
	int start;
	cout << "-*- COOK BMX -*-\n\n1) Start" << endl;
	cin >> start;
	switch (start) {
	case 1:
		cookStart();
		break;

	}
	return 0;
}

