#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

int calculateFuel(std::ifstream input) {
	std::string textInput;
	int calcOutput;
	int totalOutput = 0;
	int additionalFuelForFuel = 0;

	int lineNumber = 0;
	while (std::getline(input, textInput)) {
		calcOutput = std::stoi(textInput);
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

	return totalOutput + additionalFuelForFuel;
}

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
	int currentActionArray[161]; // Action array
	int newActionArray[161];
	while (std::getline(inputOfCodes, textInputOfCodes)) {
		std::stringstream ofCodesLineStream(textInputOfCodes);
		std::string textOfInputCodesSmallText;

		while (std::getline(ofCodesLineStream, textOfInputCodesSmallText, ',')) {
			currentActionArray[lineNumberOfNumbers] = std::stoi(textOfInputCodesSmallText);
			lineNumberOfNumbers++;
		}
	}
	std::cout << lineNumberOfNumbers << ": lineNumberOfNumbers" << std::endl;
	for (int i = 0; i < 161; i += 4) {
		if (currentActionArray[i] == 1) {
			currentActionArray[i + 3] = currentActionArray[currentActionArray[i + 1]] + currentActionArray[currentActionArray[i + 2]];
		}
		else if (currentActionArray[i] == 2) {

		}
		else if (currentActionArray[i] == 99) {

		}
		outputOfCodes << currentActionArray[i + 3] << "\n";
	}


	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}