#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

#define MAX_STRING 161

int main()
{
	std::ifstream inputFile("input.txt");
	std::ofstream outputFile("output.txt");
	std::ifstream inputOfCodes("inputOfCodes.txt");
	std::ofstream outputOfCodes("outputOfCodes.txt");
	if (!inputFile.is_open() || !inputOfCodes.is_open() || !outputFile.is_open()) {
		return -1;
	}


	std::string textInputFuel;
	int calcOutput;
	int totalOutput = 0;
	int additionalFuelForFuel = 0;

	int lineNumber = 0;
	while (std::getline(inputFile, textInputFuel)) {
		calcOutput = std::stoi(textInputFuel);
		calcOutput /= 3;
		calcOutput -= 2;
		std::cout << calcOutput << std::endl;

		int additionalFuelPerModule = calcOutput / 3 - 2;
		do {
			std::cout << additionalFuelPerModule << std::endl;
			additionalFuelForFuel += additionalFuelPerModule;
			additionalFuelPerModule /= 3;
			additionalFuelPerModule -= 2;
		} while (additionalFuelPerModule > 0);

		totalOutput += calcOutput;
		lineNumber++;
	}

	std::cout << additionalFuelForFuel << " + " << totalOutput << " = " << std::endl;
	std::cout << totalOutput + additionalFuelForFuel << std::endl;
	outputFile << totalOutput + additionalFuelForFuel << "\n";


	// 
	std::string textInputOfCodes;
	int lineNumberOfNumbers = 0;
	int currentActionArray[MAX_STRING];
	while (std::getline(inputOfCodes, textInputOfCodes)) {
		std::stringstream ofCodesLineStream(textInputOfCodes);
		std::string textOfInputCodesSmallText;

		while (std::getline(ofCodesLineStream, textOfInputCodesSmallText, ',')) {
			currentActionArray[lineNumberOfNumbers] = std::stoi(textOfInputCodesSmallText);
			lineNumberOfNumbers++;
		}
	}
	//std::cout << lineNumberOfNumbers << ": lineNumberOfNumbers" << std::endl;
	//for (int i = 0; i < MAX_STRING; i += 4) {
	//	if (currentActionArray[i] == 1) {
	//		currentActionArray[i + 3] = currentActionArray[currentActionArray[i + 1]] + currentActionArray[currentActionArray[i + 2]];
	//		std::cout << "1: Stored: " << currentActionArray[i + 3] << " at " << i + 3 << std::endl;
	//	}
	//	else if (currentActionArray[i] == 2) {
	//		int multiplication = currentActionArray[currentActionArray[i + 1]] * currentActionArray[currentActionArray[i + 2]];/*
	//		std::cout << currentActionArray[currentActionArray[i + 1]] << " * " << currentActionArray[currentActionArray[i + 2]] << " = " << multiplication << std::endl;
	//		std::cout << currentActionArray[i + 1] << " * " << currentActionArray[i + 2] << " = " << currentActionArray[i + 3] << std::endl;*/
	//		currentActionArray[currentActionArray[i + 3]] = multiplication;
	//		if (currentActionArray[i + 3] < MAX_STRING) {
	//			std::cout << "2: Stored: " << currentActionArray[currentActionArray[i + 3]] << " at " << currentActionArray[i + 3] << std::endl;
	//		}
	//		else {
	//			std::cout << "2: Didn't store at: " << currentActionArray[i + 3] << std::endl;
	//		}
	//	}
	//	else if (currentActionArray[i] == 99) {
	//		std::cout << "99 found at line " << i << std::endl;
	//		break;
	//	}
	//	else {
	//		std::cout << "ERROR" << std::endl;
	//		return -1;
	//	}
	//}
	for (int i = 0; i < lineNumberOfNumbers; i += 4) {
		int opCode = currentActionArray[i];
		int calcOne = currentActionArray[i + 1];
		int calcTwo = currentActionArray[i + 2];
		int* answerLoc = &currentActionArray[i + 3];
		if (opCode == 1) {
			*answerLoc = calcOne + calcTwo;
			std::cout << "1: " << calcOne << " + " << calcTwo << " = " << *answerLoc << std::endl;
		}
		else if (opCode == 2) {
			*answerLoc = calcOne * calcTwo;
			std::cout << "2: " << calcOne << " * " << calcTwo << " = " << *answerLoc << std::endl;
		}
		else {
			std::cout << "Stopped calculating" << std::endl;
			break;
		}
	}

	for (int i = 0; i < lineNumberOfNumbers; i += 4) {
		if (currentActionArray[0] == 99) {
			outputOfCodes << "99, ";
			i -= 4;
		}
		else if (currentActionArray[i] != -858993460 || currentActionArray[i + 1] != -858993460 || currentActionArray[i + 2] != -858993460 || currentActionArray[i + 3] != -858993460) {
			std::cout << currentActionArray[i] << ", " << currentActionArray[i + 1] << ", " << currentActionArray[i + 2] << ", " << currentActionArray[i + 3] << ", " << std::endl;
			outputOfCodes << currentActionArray[i] << ", ";
			outputOfCodes << currentActionArray[i + 1] << ", ";
			outputOfCodes << currentActionArray[i + 2] << ", ";
			outputOfCodes << currentActionArray[i + 3] << ", ";
			outputOfCodes << "\n";
		}
	}

	std::cout << currentActionArray[0] << std::endl;

	// MAKE NEW AND OLD ARRAY ^^

	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}