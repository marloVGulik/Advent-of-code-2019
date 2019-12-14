#include "main.hpp";

struct coordinate {
	int x, y;
};
class world {
public:
	char display = ' ';
	coordinate loc = {0, 0};
	coordinate difference = {0, 0};
	char sideCheck = ' ';

	int wireNumber = 0;
	bool isCrossed = false;
	bool isX = false;
};

bool crossed(world* hostWorld, std::vector<world> checkedWorld) {
	for (int wordNumber = 0; wordNumber < 20; wordNumber++) {
		std::cout << checkedWorld[wordNumber].sideCheck << std::endl;
		std::cout << hostWorld->sideCheck << std::endl;
		switch (checkedWorld[wordNumber].sideCheck)
		{
		case 'L':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.x * -1; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x - drawLineNumber && hostWorld->loc.y == checkedWorld[wordNumber].loc.y) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					return true;
				}
			}
			break;
		case 'R':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.x; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x + drawLineNumber && hostWorld->loc.y == checkedWorld[wordNumber].loc.y) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					return true;
				}
			}
			break;
		case 'D':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.y * -1; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x && hostWorld->loc.y == checkedWorld[wordNumber].loc.y - drawLineNumber) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					return true;
				}
			}
			break;
		case 'U':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.y; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x && hostWorld->loc.y == checkedWorld[wordNumber].loc.y + drawLineNumber) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					return true;
				}
			}
			break;
		default:
			std::cout << "ERROR NO COMPATIBLE CHARACTER" << std::endl;
			system("pause");
			break;
		}
	}
	return false;
}

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
	bool CALCMODE = true;
	bool DRAWMODE = false;

	// TEST:
	if (CALCMODE) {
		std::string textInputOfWires;
		coordinate currentLoc = { 0, 0 };
		coordinate maxLoc = { 0, 0 };
		std::vector<std::vector<world> >map(2, std::vector<world>(20));
		std::cout << "Created array, filling with data" << std::endl;

		int lineCounter = 0;
		int objectCounter = 0;
		while (std::getline(inputWires, textInputOfWires)) {
			std::stringstream wiresLineStream(textInputOfWires);
			std::string textOfWiresSmallText;

			while (std::getline(wiresLineStream, textOfWiresSmallText, ',')) {
				char side = textOfWiresSmallText[0];
				textOfWiresSmallText.erase(0, 1);
				int amount = std::stoi(textOfWiresSmallText);
				coordinate translation = { 0, 0 };

				map[lineCounter][objectCounter].sideCheck = side;

				switch (side)
				{
				case 'L':
					translation.x -= amount;
					break;
				case 'R':
					translation.x += amount;
					break;
				case 'U':
					translation.y += amount;
					break;
				case 'D':
					translation.y -= amount;
					break;
				default:
					std::cout << "ERROR: Unknown character!" << std::endl;
					system("pause");
					break;
				}
				map[lineCounter][objectCounter].loc = currentLoc;
				map[lineCounter][objectCounter].difference = translation;

				objectCounter++;
			}
			lineCounter++;
		}
		std::cout << "Map read, continue to calc part..." << std::endl;
		for (int lineNumber = 0; lineNumber < 2; lineNumber++) {
			for (int wordNumber = 0; wordNumber < 20; wordNumber++) {
				std::cout << map[lineNumber][wordNumber].sideCheck << std::endl;
				switch (map[lineNumber][wordNumber].sideCheck)
				{
				case 'L':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.x * -1; drawLineNumber++) {
						world* newWorld = &map[lineNumber][wordNumber];
						std::vector<world>* checkWorld = &map[lineNumber * -1 + 1];
						newWorld->loc.x -= drawLineNumber;
						if (crossed(newWorld, checkWorld)) {

							std::cout << "CROSS REEEEEE" << std::endl;
						}
						else {

							std::cout << " NO CROSS REEEEEE" << std::endl;
						}
					}
					break;
				case 'R':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.x; drawLineNumber++) {
						world* newWorld = &map[lineNumber][wordNumber];
						std::vector<world>* checkWorld = &map[lineNumber * -1 + 1];
						newWorld->loc.x += drawLineNumber;
						if (crossed(newWorld, map[drawLineNumber])) {

							std::cout << "CROSS REEEEEE" << std::endl;
						}
						else {

							std::cout << " NO CROSS REEEEEE" << std::endl;
						}
					}
					break;
				case 'D':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.y * -1; drawLineNumber++) {
						world* newWorld = &map[lineNumber][wordNumber];
						std::vector<world>* checkWorld = &map[lineNumber * -1 + 1];
						newWorld->loc.y -= drawLineNumber;
						if (crossed(newWorld, map[drawLineNumber * -1 + 1])) {

							std::cout << "CROSS REEEEEE" << std::endl;
						}
						else {

							std::cout << " NO CROSS REEEEEE" << std::endl;
						}
					}
					break;
				case 'U':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.y; drawLineNumber++) {
						world* newWorld = &map[lineNumber][wordNumber];
						std::vector<world>* checkWorld = &map[lineNumber * -1 + 1];
						newWorld->loc.y += drawLineNumber;
						if (crossed(newWorld, map[drawLineNumber * -1 + 1])) {

							std::cout << "CROSS REEEEEE" << std::endl;
						}
						else {

							std::cout << " NO CROSS REEEEEE" << std::endl;
						}
					}
					break;
				default:
					std::cout << "ERROR NO COMPATIBLE CHARACTER" << std::endl;
					system("pause");
					break;
				}
			}
		}
	}

	if (DRAWMODE) {
		std::string textInputOfWires;
		int lineNumberOfWires = 0;
		int wireNumber = 0;
		std::cout << "Creating map array..." << std::endl;
		std::vector<std::vector<world> >map(MAP_SIZE_X, std::vector<world>(MAP_SIZE_Y));


		/*std::cout << "Filling map array..." << std::endl;
		for (int x = 0; x < MAP_SIZE_X; x++) {
			for (int y = 0; y < MAP_SIZE_Y; y++) {
				world tempWorld;
				tempWorld.loc = { x, y };
				tempWorld.isCrossed = false;
				map[x][y] = tempWorld;
			}
		}*/
		std::cout << "Created map succesfully! Starting to read wire input and creating starting points..." << std::endl;

		while (std::getline(inputWires, textInputOfWires)) {
			std::stringstream wiresLineStream(textInputOfWires);
			std::string textOfWiresCodesSmallText;
			coordinate* currentCoord = new coordinate();
			currentCoord->x = 8000;
			currentCoord->y = 4000;

			lineNumberOfWires = 0;
			while (std::getline(wiresLineStream, textOfWiresCodesSmallText, ',')) {
				world newWorld;
				coordinate oldCoordinate = *currentCoord;
				coordinate diff = { 0, 0 };
				//std::cout << currentCoord->x << ", " << currentCoord->y << std::endl;

				newWorld.sideCheck = textOfWiresCodesSmallText[0];
				textOfWiresCodesSmallText.erase(0, 1);

				switch (newWorld.sideCheck)
				{
				case 'L':
					currentCoord->x -= std::stoi(textOfWiresCodesSmallText);
					diff.x -= oldCoordinate.x - currentCoord->x;
					break;
				case 'R':
					currentCoord->x += std::stoi(textOfWiresCodesSmallText);
					diff.x -= oldCoordinate.x - currentCoord->x;
					break;
				case 'U':
					currentCoord->y += std::stoi(textOfWiresCodesSmallText);
					diff.y -= oldCoordinate.y - currentCoord->y;
					break;
				case 'D':
					currentCoord->y -= std::stoi(textOfWiresCodesSmallText);
					diff.y -= oldCoordinate.y - currentCoord->y;
					break;
				default:
					std::cout << "ERROR: Unknown character!" << std::endl;
					system("pause");
					break;
				}
				//std::cout << diff.x << ", " << diff.y << std::endl;
				std::cout << currentCoord->x << ", " << currentCoord->y << std::endl;



				newWorld.loc = oldCoordinate;
				newWorld.difference = diff;
				newWorld.isX = true;
				newWorld.display = '+';
				newWorld.wireNumber = wireNumber + 1;

				/*if (wireNumber != 0 && lineNumberOfWires == 0) {
					newWorld.isStart = true;
					newWorld.locStart = map[oldCoordinate.x][oldCoordinate.y].loc;
				}*/

				map[oldCoordinate.x][oldCoordinate.y] = newWorld;

				lineNumberOfWires++;
			}
			wireNumber++;
			std::cout << lineNumberOfWires << std::endl;
		}
		std::cout << std::endl;

		std::cout << "Drawing lines..." << std::endl;
		for (int x = 0; x < MAP_SIZE_X; x++) {
			for (int y = 0; y < MAP_SIZE_Y; y++) {
				if (map[x][y].isX) {
					if (map[x][y].sideCheck == 'L') {
						for (int i = 0; i < map[x][y].difference.x * -1; i++) {
							if (!map[x - i][y].isX) {
								if (map[x - i][y].display != '-' && map[x - i][y].wireNumber == map[x][y].wireNumber || map[x - i][y].wireNumber == 0) {
									map[x - i][y].display = '|';
									map[x - i][y].wireNumber = map[x][y].wireNumber;
								}
								else {
									map[x - i][y].display = 'X';
								}
							}
						}
					}
					else if (map[x][y].sideCheck == 'R') {
						for (int i = 0; i < map[x][y].difference.x; i++) {
							if (!map[x + i][y].isX) {
								if (map[x + i][y].display != '-' && map[x + i][y].wireNumber == map[x][y].wireNumber || map[x + i][y].wireNumber == 0) {
									map[x + i][y].display = '|';
									map[x + i][y].wireNumber = map[x][y].wireNumber;
								}
								else {
									map[x + i][y].display = 'X';
								}
							}
						}
					}
					else if (map[x][y].sideCheck == 'U') {
						for (int i = 0; i < map[x][y].difference.y; i++) {
							if (!map[x][y + i].isX) {
								if (map[x][y + i].display != '|' && map[x][y + i].wireNumber == map[x][y].wireNumber || map[x][y + i].wireNumber == 0) {
									map[x][y + i].display = '-';
									map[x][y + i].wireNumber = map[x][y].wireNumber;
								}
								else {
									map[x][y + i].display = 'X';
								}
							}
						}
					}
					else if (map[x][y].sideCheck == 'D') {
						for (int i = 0; i < map[x][y].difference.y * -1; i++) {
							if (!map[x][y - i].isX) {
								if (map[x][y - i].display != '|' && map[x][y - i].wireNumber == map[x][y].wireNumber || map[x][y - i].wireNumber == 0) {
									map[x][y - i].display = '-';
									map[x][y - i].wireNumber = map[x][y].wireNumber;
								}
								else {
									map[x][y - i].display = 'X';
								}
							}
						}
					}
				}
			}
		}

		
		std::cout << "Drawing map..." << std::endl;
		for (int x = 0; x < MAP_SIZE_X; x++) {
			for (int y = 0; y < MAP_SIZE_Y; y++) {
				outputWires << map[x][y].display;
			}
			outputWires << "\n";
		}
		std::cout << "Drew map succesfully!" << std::endl;
		std::cout << "Removing the array..." << std::endl;
		map.clear();
		system("pause");
		// Check for side (Wires are always 1D, they don't change sides. if it's not working try the MAP approach to this problem (map with coordinates, can check if coordinate is already set or not))
	}
	

	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}