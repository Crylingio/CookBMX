#include "stdafx.h"
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
	string race = "Human";
	string name;
	int seed;
	double difficulty = 1;
	string difficultyname = "Bicyclist";
	int day = 0;
	int loop = 1;
	int ing = 10;
	int hg = 100;
	int cash = 50;
	int san = 0;
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
	hgLoss = rand() % (13 + RE.hungerLoss) + (Char.difficulty * 3);
	if (hgLoss < 0) {
		hgLoss = 0;
	}
	Char.hg -= hgLoss;
	cout << "You lose " << hgLoss << " hunger." << endl;
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
	if (Char.ing < 0) {
		Char.ing = 0;
	} 
	if (Char.cash < 0) {
		Char.cash = 0;
	}
}



void bikeEvent() {
	int temp;
	int temp2;
	int daylost;
	temp = rand() % 10;
	temp2 = rand() % 5;
	system("CLS");
	cout << "-*- Event While Biking -*-\n" << endl;
	if (temp <= 5) {
		if (Char.san <= 0) {
		if (Char.route == "Sandia Crest") {
			Char.day = 15 * Char.scoremp;
		}
		else if (Char.route == "Himalayas") {
			Char.day = 35 * Char.scoremp;
		}
		else if (Char.route == "The Alps") {
			Char.day = 100 * Char.scoremp;
		}
			cout << "You think you see a bridge up ahead. Instead its a cliff.\nYou bike off the cliff and lose all your supplies and progress." << endl;
			cout << "You have to bike back, you are set back to " << Char.day << " Days." << endl;
			Char.ing = 0;
			Char.hg = 25;
			Char.cash = 0;
			Char.san = 75;
			Char.soul = 75;
			Char.bikeHP = 10;
		}
		else if (Char.san <= 25) {
			daylost = 2 * Char.difficulty;
			cout << "While biking the wrong path, you start to wander even deeper into the\nforest." << endl;
			cout << "Losing " << daylost << " days..." << endl;
			Char.day += daylost;
			Char.score -= 3;
		}
		else if (Char.san <= 65) {
			daylost = 1 * Char.difficulty;
			cout << "You hallucinate while biking, and you follow the wrong path." << endl;
			cout << "Lost " << daylost << " days..." << endl;
			Char.day += daylost;
			Char.score -= 2;
		}
		else if (Char.san >= 66) {
			cout << "You don't see anything unusual on the path.\nOnly some nice trees and fleeing possums." << endl;
		}
		wait_enter();
	}
	else if (temp >= 5) {
		if (temp2 <= 1) {
			cout << "You see some Kobolds up ahead stealing things from a person.\n\n1) Avoid those scalies\n2) Charge in Bike in hand" << endl;



		}
	}

}

void ride() {
	int bikeLoss;
	bikeLoss = rand() % (3 + RE.bikeDMGLoss) + (Char.difficulty * 2);
	if (bikeLoss < 0) {
		bikeLoss = 0;
	}
	system("CLS");
	cout << "-*- COOK BMX! -*-" << endl;
	cout << "\nYou ride..." << endl;
	cout << "Your bike loses " << bikeLoss << " durability." << endl;
	hungerLost();
	wait_enter();
	bikeEvent();	
	Char.day -= 1;
	Char.score += 1;
	Char.totaldaysbiked += 1;
	Char.bikeHP -= bikeLoss;
}

void stats() {
	system("CLS");
	cout << "-*- Stats -*-" << endl;
	cout << "\nName: " << Char.name << "\nRace: " << Char.race << "\n\nDifficulty: " << Char.difficultyname << "\n\nScore: " << Char.score << "\nScore Multiplier: " << Char.scoremp << "x" << endl;
	cout << "\nRoute: " << Char.route << "\nDays Left: " << Char.day << "\nTotal Days Biked: " << Char.totaldaysbiked << "\n\nEnemies Killed: " << Char.enemiesk << "\nIngredients: " << Char.ing << endl;
	wait_enter();
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
	int intGain;
	int intLoss;
	int cashLost;
	system("CLS");

	cout << "-*- COOK BMX! -*- " << endl;
	cout << "\nWhat would you like to do?" << endl;
	cout << "\n1) Hunt Small Creatures\n - Less chance of being attacked, less rewards.\n\n2) Hunt Big Boys\n - Higher chance of being attacked, more rewards.\n\n3) I didn't mean it... Let me out" << endl;
	cin >> inputy;
	switch (inputy) {
	case 1:
		system("CLS");
		chance = rand() % 10;
		if (chance == 5) {
			goldChance = rand() % 50 / Char.difficulty;
			intGain = rand() % (15 + RE.ingGain) / Char.difficulty;
			cout << "You bring back a bear, giving you " << intGain << " ingredients.\nYou also find " << goldChance << " cash." << endl;
			Char.ing += intGain;
			Char.cash += goldChance;
			if (Char.race != "IPC") {
				Char.soul -= 1;
			}
			hungerLost();
			Char.enemiesk += 1;
			Char.score += 3;
			sanityLost();
			wait_enter();
		}
		else if (chance == 4) {
			intLoss = rand() % 5 * Char.difficulty;
			goldChance = rand() % 30 * Char.difficulty;
			cout << "You get attacked and lose some supplies...\n-" << intLoss << " ING\n-" << goldChance << " Cash" << endl;
			Char.cash -= goldChance;
			Char.ing -= intLoss;
			Char.soul -= 1;
			hungerLost();
			Char.score -= 10;
			sanityLost();
			wait_enter();
		}
		else if (chance < 4) {
			intGain = rand() % (5 + RE.ingGain) / Char.difficulty;
			cout << "You find a possum and kill it. You gain " << intGain << " ingredients." << endl;
			Char.ing += intGain;
			if (Char.race == "IPC") {
				Char.soul -= 3;
			}
			else {
				Char.soul -= 1;
			}
			hungerLost();
			sanityLost();
			Char.enemiesk += 1;
			Char.score += 1;
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
		if (chance < 4) {
			goldChance = rand() % 50 / Char.difficulty;
			intGain = rand() % (15 + RE.ingGain) / Char.difficulty;
			cout << "You bring back a bear, giving you " << intGain << " ingredients.\nYou also find " << goldChance << " cash." << endl;
			Char.ing += intGain;
			Char.cash += goldChance;
			if (Char.race != "IPC") {
				Char.soul -= 1;
			}
			hungerLost();
			Char.enemiesk += 1;
			Char.score += 3;
			sanityLost();
			wait_enter();
		}
		else if (chance > 5) {
			intLoss = rand() % 5 * Char.difficulty;
			goldChance = rand() % 30 * Char.difficulty;
			cout << "You get attacked and lose some supplies...\n-" << intLoss << " ING\n-" << goldChance << " Cash" << endl;
			Char.cash -= goldChance;
			Char.ing -= intLoss;
			Char.soul -= 1;
			hungerLost();
			Char.score -= 10;
			sanityLost();
			wait_enter();
		}
		else if (chance == 5) {
			intGain = rand() % (5 + RE.ingGain) / Char.difficulty;
			cout << "You find a possum and kill it. You gain " << intGain << " ingredients." << endl;
			Char.ing += intGain;
			if (Char.race == "IPC") {
				Char.soul -= 3;
			}
			else {
				Char.soul -= 1;
			}
			hungerLost();
			sanityLost();
			Char.enemiesk += 1;
			Char.score += 1;
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
	cout << (Char.score * Char.scoremp) * Char.difficulty;
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
	switch (looptest) {
	case 1:
		if (Char.route == "Sandia Crest") {
			Char.scoremp += .1;
			Char.day = 15 * Char.scoremp;
		}
		else if (Char.route == "Himalayas") {
			Char.scoremp += .25;
			Char.day = 35 * Char.scoremp;
		}
		else if (Char.route == "The Alps") {
			Char.scoremp += 1;
			Char.day = 100 * Char.scoremp;
		}
		break;
	}


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
			stats();
			break;
		}
	}
}

void cookStart() {
	int input1;
	system("CLS");
	cout << "-*- Choose Route -*-" << endl;
	cout << "\n1) Sandia Crest - 15 Days\n2) Himalayas - 35 Days\n3) The Alps - 100 Days" << endl;
	cin >> input1;
	switch (input1) {
	case 1:
		Char.route = "Sandia Crest";
		Char.day = 15;
		Char.scoremp = 1;
		break;
	case 2:
		Char.route = "Himalayas";
		Char.day = 35;
		Char.scoremp = 1.25;
		break;
	case 3:
		Char.route = "The Alps";
		Char.day = 100;
		Char.scoremp = 2.5;
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
	cout << "-*- Choose Your Difficulty -*-" << endl;
	cout << "\n1) Starter\n2) Bicyclist\n3) Veteran\n4) War Bicyclist\n5) Brutal Nightmare Hell-Bicyclist" << endl;
	cin >> input1;
	switch (input1) {
	case 1:
		Char.difficulty = .75;
		Char.difficultyname = "Starter";
		break;
	case 2:
		Char.difficulty = 1;
		Char.difficultyname = "Bicyclist";
		break;
	case 3:
		Char.difficulty = 1.75;
		Char.difficultyname = "Veteran";
		break;
	case 4:
		Char.difficulty = 2.25;
		Char.difficultyname = "War Bicyclist";
		break;
	case 5:
		Char.difficulty = 3;
		Char.difficultyname = "Brutal Nightmare Hell-Bicyclist";
		break;
	}
	system("CLS");
	cout << "-*- Choose Your Name -*-" << endl;
	cout << "\nWhats your name?" << endl;
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
