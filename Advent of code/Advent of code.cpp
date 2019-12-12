#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>

#define MAX_STRING 161

int main()
{
	// Day one in/out
	std::ifstream inputFile("data/input/input.txt");
	std::ofstream outputFile("data/output/output.txt");

	// Day two in/out
	std::ifstream inputOfCodes("data/input/inputOfCodes.txt");
	std::ofstream outputOfCodes("data/output/outputOfCodes.txt");

	// Day three in/out
	if (!inputFile.is_open() || !inputOfCodes.is_open() || !outputFile.is_open() || !outputOfCodes.is_open()) {
		throw std::runtime_error("ERROR: FILES DIDN'T OPEN!");
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
		//std::cout << calcOutput << std::endl;

		int additionalFuelPerModule = calcOutput / 3 - 2;
		do {
			//std::cout << additionalFuelPerModule << std::endl;
			additionalFuelForFuel += additionalFuelPerModule;
			additionalFuelPerModule /= 3;
			additionalFuelPerModule -= 2;
		} while (additionalFuelPerModule > 0);

		totalOutput += calcOutput;
		lineNumber++;
	}

	std::cout << additionalFuelForFuel << " + " << totalOutput << " = " << totalOutput + additionalFuelForFuel << std::endl;
	//std::cout << totalOutput + additionalFuelForFuel << std::endl;
	outputFile << totalOutput + additionalFuelForFuel << "\n";

	std::cout << std::endl;
	// Day 2
	int defaultActionArray[MAX_STRING];
	std::string textInputOfCodes;
	int lineNumberOfNumbers = 0;
	while (std::getline(inputOfCodes, textInputOfCodes)) {
		std::stringstream ofCodesLineStream(textInputOfCodes);
		std::string textOfInputCodesSmallText;

		while (std::getline(ofCodesLineStream, textOfInputCodesSmallText, ',')) {
			defaultActionArray[lineNumberOfNumbers] = std::stoi(textOfInputCodesSmallText);
			lineNumberOfNumbers++;
		}
	}

	int counter = 0;
	for (int noun = 0; noun < 100; noun++) {
		for (int verb = 0; verb < 100; verb++) {
			int currentActionArray[MAX_STRING];
			for (int i = 0; i < MAX_STRING; i++) {
				currentActionArray[i] = defaultActionArray[i];
			}

			currentActionArray[1] = noun;
			currentActionArray[2] = verb;
			//std::cout << currentActionArray[1] << ", " << currentActionArray[2] << std::endl;


			for (int i = 0; i < lineNumberOfNumbers; i += 4) {
				int* initialValues[4] = { &currentActionArray[i], &currentActionArray[currentActionArray[i + 1]], &currentActionArray[currentActionArray[i + 2]], &currentActionArray[currentActionArray[i + 3]] };
				int* opCode = initialValues[0];
				int* calcOne = initialValues[1];
				int* calcTwo = initialValues[2];
				int* answerLoc = &currentActionArray[currentActionArray[i + 3]];

				// What to do with the intcodes?
				if (*opCode == 1) {
					*answerLoc = *calcOne + *calcTwo;
					//std::cout << "1: " << *calcOne << " + " << *calcTwo << " = " << *answerLoc << "; Saving at: " << currentActionArray[i + 3] << std::endl;
				}
				else if (*opCode == 2) {
					*answerLoc = *calcOne * *calcTwo;
					//std::cout << "2: " << *calcOne << " * " << *calcTwo << " = " << *answerLoc << "; Saving at: " << currentActionArray[i + 3] << std::endl;
				}
				else {
					//std::cout << "Stopped calculating" << std::endl;
					i = lineNumberOfNumbers;
				}
			}
			//std::cout << std::endl;

			for (int i = 0; i < lineNumberOfNumbers; i += 4) {
				if (currentActionArray[i] == 99) {
					//outputOfCodes << "99, ";
					//std::cout << "99, " << std::endl;
					i -= 3;
				}
				else if (currentActionArray[i] != -858993460 || currentActionArray[i + 1] != -858993460 || currentActionArray[i + 2] != -858993460 || currentActionArray[i + 3] != -858993460) {
					//std::cout << currentActionArray[i] << ", " << currentActionArray[i + 1] << ", " << currentActionArray[i + 2] << ", " << currentActionArray[i + 3] << ", " << std::endl;
					/*outputOfCodes << currentActionArray[i] << ", ";
					outputOfCodes << currentActionArray[i + 1] << ", ";
					outputOfCodes << currentActionArray[i + 2] << ", ";
					outputOfCodes << currentActionArray[i + 3] << ", ";
					outputOfCodes << "\n";*/
				}
			}
			int* answerDay2 = &currentActionArray[0];
			if (noun == 12 && verb == 2) {
				std::cout << *answerDay2 << std::endl;
			}
			if (*answerDay2 == 19690720) {
				std::cout << "Noun: " << noun << ", verb: " << verb << ", answer: " << 100 * noun + verb << std::endl;
				break;
			}
			else {
				//std::cout << counter << ": " << currentActionArray[0] << ", " << currentActionArray[1] << ", " << currentActionArray[2] << std::endl;
			}
			counter++;
			outputOfCodes << currentActionArray[0] << "\n";
		}
	}


	// MAKE NEW AND OLD ARRAY ^^

	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}