#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <Windows.h>
#include <vector>

#define MAX_STRING 161
#define MAP_SIZE 1500


struct coordinate {
	int x, y;
};
class wire {
public:
	coordinate currentCoordinate;
	coordinate newCoordinate;
	char sideCheck;
	int makeLine(world* map) {
		this->calcDifferenceCoordinate();
		if (this->sideCheck == 'L' || this->sideCheck == 'R') {
			for (int i = 0; i < difference.x; i++) {

			}
		}
		else if (this->sideCheck == 'U' || this->sideCheck == 'D') {
			for (int i = 0; i < difference.y; i++) {

			}
		}
	}
private:
	coordinate difference = {0, 0};
	int calcDifferenceCoordinate() {
		switch (this->sideCheck)
		{
		case 'U':
			this->difference.y = this->newCoordinate.y - this->currentCoordinate.y;
			break;
		case 'D':
			this->difference.y = this->newCoordinate.y - this->currentCoordinate.y;
			break;
		case 'L':
			this->difference.x = this->newCoordinate.x - this->currentCoordinate.x;
			break;
		case 'R':
			this->difference.x = this->newCoordinate.x - this->currentCoordinate.x;
			break;
		default:
			std::cout << "ERROR: No value compatible!" << std::endl;
			break;
		}
		std::cout << "(" << this->difference.x << ", " << this->difference.y << ")" << std::endl;
	}
};
class world {
public:
	char display = '.';
	coordinate loc;
	bool isCrossed = false;
	bool isX = false;
	wire currentWire;
};

int main()
{
	// Day one in/out
	std::ifstream inputFile("data/input/input.txt");
	std::ofstream outputFile("data/output/output.txt");

	// Day two in/out
	std::ifstream inputOfCodes("data/input/inputOfCodes.txt");
	std::ofstream outputOfCodes("data/output/outputOfCodes.txt");

	// Day three in/out
	std::ifstream inputWires("data/input/inputWires.txt");
	std::ofstream outputWires("data/output/outputWires.txt");

	if (!inputFile.is_open() || !inputOfCodes.is_open() || !inputWires.is_open()) {
		std::cout << "Error opening files! Program aborted." << std::endl;
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

	// DAY THREE:
	std::string textInputOfWires;
	int lineNumberOfWires = 0;
	int wireNumber = 0;
	std::vector<std::vector<world> >map(MAP_SIZE, std::vector<world>(MAP_SIZE));

	std::cout << "Creating map..." << std::endl;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			world tempWorld;
			tempWorld.loc = { x, y };
			tempWorld.isCrossed = false;
			wire tempWire;
			tempWorld.currentWire = tempWire;
			map[x][y] = tempWorld;
		}
	}
	std::cout << "Created maps succesfully! Starting to read wire input..." << std::endl;

	while (std::getline(inputWires, textInputOfWires)) {
		std::stringstream wiresLineStream(textInputOfWires);
		std::string textOfWiresCodesSmallText;
		coordinate* currentCoord = new coordinate();
		currentCoord->x = MAP_SIZE / 2;
		currentCoord->y = MAP_SIZE / 2;

		while (std::getline(wiresLineStream, textOfWiresCodesSmallText, ',')) {
			world newWorld;
			wire newWire;
			coordinate oldCoordinate = *currentCoord;

			newWire.sideCheck = textOfWiresCodesSmallText[0];
			textOfWiresCodesSmallText.erase(0, 1);

			newWire.currentCoordinate = *currentCoord;

			switch (newWire.sideCheck)
			{
			case 'L':
				currentCoord->x -= std::stoi(textOfWiresCodesSmallText);
				break;
			case 'R':
				currentCoord->x += std::stoi(textOfWiresCodesSmallText);
				break;
			case 'U':
				currentCoord->y += std::stoi(textOfWiresCodesSmallText);
				break;
			case 'D':
				currentCoord->y -= std::stoi(textOfWiresCodesSmallText);
				break;
			default:
				std::cout << "ERROR: Unknown character!" << std::endl;
				system("pause");
				break;
			}
			std::cout << currentCoord->x << ", " << currentCoord->y << std::endl;
			newWire.newCoordinate = *currentCoord;

			newWorld.currentWire = newWire;
			newWorld.loc = *currentCoord;
			newWorld.isX = true;
			map[oldCoordinate.x][oldCoordinate.y] = newWorld;

			lineNumberOfWires++;
		}
		wireNumber++;
		std::cout << lineNumberOfWires << std::endl;
	}
	std::cout << std::endl;

	std::cout << "Drawing lines..." << std::endl;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			if (map[x][y].isX) {
				map[x][y].currentWire.makeLine(&map);
			}
		}
	}

	std::cout << "Drawing map..." << std::endl;
	for (int x = 0; x < MAP_SIZE; x++) {
		for (int y = 0; y < MAP_SIZE; y++) {
			outputWires << map[x][y].display;
		}
		outputWires << "\n";
	}
	std::cout << "Drew map succesfully!" << std::endl;
	// Check for side (Wires are always 1D, they don't change sides. if it's not working try the MAP approach to this problem (map with coordinates, can check if coordinate is already set or not))


	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}