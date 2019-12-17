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
	int steps = 0;

	int wireNumber = 0;
	bool isCrossed = false;
	bool isX = false;
};
std::vector<int> numbersToArray(int number) {
	std::vector<int> numberOutput(6);
	for (int i = 5; i > -1; i--) {
		numberOutput[i] = number % 10;
		number /= 10;
	}
	return numberOutput;
}

std::vector<coordinate> crossed(world* hostWorld, std::vector<world> &checkedWorld) {
	//std::cout << "Checking: " << hostWorld->loc.x << ", " << hostWorld->loc.y << std::endl; // FUN LINE XD
	/*for (int i = 0; i < 20; i++) {
		std::cout << checkedWorld[i].loc.x << ", " << checkedWorld[i].loc.y << std::endl;
	}
	system("pause");*/
	std::vector<coordinate>crosses;
	for (int wordNumber = 0; wordNumber < 301; wordNumber++) {
		/*std::cout << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y << std::endl;
		std::cout << hostWorld->loc.x << ", " << hostWorld->loc.y << std::endl;*/
		//system("pause");
		switch (checkedWorld[wordNumber].sideCheck)
		{
		case 'L':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.x * -1; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x - drawLineNumber && hostWorld->loc.y == checkedWorld[wordNumber].loc.y) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x - drawLineNumber << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					crosses.push_back({ checkedWorld[wordNumber].loc.x - drawLineNumber, checkedWorld[wordNumber].loc.y });
				}
			}
			break;
		case 'R':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.x; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x + drawLineNumber && hostWorld->loc.y == checkedWorld[wordNumber].loc.y) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x + drawLineNumber << ", " << checkedWorld[wordNumber].loc.y << std::endl;
					crosses.push_back({ checkedWorld[wordNumber].loc.x + drawLineNumber, checkedWorld[wordNumber].loc.y });
				}
			}
			break;
		case 'D':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.y * -1; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x && hostWorld->loc.y == checkedWorld[wordNumber].loc.y - drawLineNumber) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y - drawLineNumber << std::endl;
					crosses.push_back({ checkedWorld[wordNumber].loc.x, checkedWorld[wordNumber].loc.y - drawLineNumber });
				}
			}
			break;
		case 'U':
			for (int drawLineNumber = 0; drawLineNumber < checkedWorld[wordNumber].difference.y; drawLineNumber++) {
				if (hostWorld->loc.x == checkedWorld[wordNumber].loc.x && hostWorld->loc.y == checkedWorld[wordNumber].loc.y + drawLineNumber) {
					std::cout << "Crossed at: " << checkedWorld[wordNumber].loc.x << ", " << checkedWorld[wordNumber].loc.y + drawLineNumber << std::endl;
					crosses.push_back({ checkedWorld[wordNumber].loc.x, checkedWorld[wordNumber].loc.y + drawLineNumber });
				}
			}
			break;
		default:

			break;
		}
	}
	/*for (int i = 0; i < crosses.size(); i++) {
		std::cout << crosses[i].x << ", " << crosses[i].y << std::endl;
	}*/
	return crosses;
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
	bool CALCMODE = false;
	bool DRAWMODE = false;

	// CALCMODE:
	if (CALCMODE) {
		std::string textInputOfWires;
		coordinate currentLoc = { 0, 0 };
		coordinate maxLoc = { 0, 0 };
		std::vector<std::vector<world> >map(2, std::vector<world>(301));
		std::vector<std::vector<int> >stepMap(2, std::vector<int>(301));
		std::cout << "Created array, filling with data" << std::endl;

		int lineCounter = 0;
		while (std::getline(inputWires, textInputOfWires)) {
			std::stringstream wiresLineStream(textInputOfWires);
			std::string textOfWiresSmallText;
			int objectCounter = 0;
			currentLoc = { 0, 0 };

			while (std::getline(wiresLineStream, textOfWiresSmallText, ',')) {
				char side = textOfWiresSmallText[0];
				textOfWiresSmallText.erase(0, 1);
				int amount = std::stoi(textOfWiresSmallText);
				coordinate translation = { 0, 0 };
				coordinate old = currentLoc;

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

				//std::wcout << old.x << ", " << old.y << std::endl;
				//std::cout << "Run number: " << objectCounter << std::endl;
				map[lineCounter][objectCounter].loc = old;
				map[lineCounter][objectCounter].difference = translation;

				if (objectCounter - 1 > 0) {
					map[lineCounter][objectCounter].steps = map[lineCounter][objectCounter - 1].steps;
				}
				else {
					map[lineCounter][objectCounter].steps = amount;
				}

				std::wcout << "Adding " << amount << " to map " << lineCounter << std::endl;
				if (objectCounter - 1 >= 0) {
					stepMap[lineCounter][objectCounter] = stepMap[lineCounter][objectCounter - 1] + amount;
				}
				else {	
					stepMap[lineCounter][objectCounter] += amount;
				}

				currentLoc.x += translation.x;
				currentLoc.y += translation.y;

				objectCounter++;
			}
			lineCounter++;
		}
		std::cout << "Map read, continue to calc part..." << std::endl;

		/*for (int j = 0; j < 2; j++) {
			std::cout << "Wire " << j << std::endl;
			for (int i = 0; i < map[j].size(); i++) {
				if (i != 0) {
					if (map[j][i].loc.x != 0 && map[j][i].loc.y != 0) {
						std::cout << map[j][i].loc.x << ", " << map[j][i].loc.y << std::endl;
					}
				}
				else {
					std::cout << map[j][i].loc.x << ", " << map[j][i].loc.y << std::endl;
				}
			}
		}*/
		//system("pause");
		std::vector<std::vector<coordinate> >crosses(2, std::vector<coordinate>());
		std::vector<std::vector<int> >crossLocs(2, std::vector<int>());
		int step = 0;
		for (int lineNumber = 0; lineNumber < 2; lineNumber++) {
			std::cout << "Wire " << lineNumber << ": " << std::endl;
			std::vector<world> newCheckedWorld = map[lineNumber * -1 + 1];
			step = 0;
			for (int wordNumber = 0; wordNumber < 301; wordNumber++) {
				//std::cout << "Checking: " << map[lineNumber][wordNumber].loc.x << ", " << map[lineNumber][wordNumber].loc.y << std::endl;
				//std::cout << "Numbers: " << lineNumber << ", " << wordNumber << std::endl;
				switch (map[lineNumber][wordNumber].sideCheck)
				{
				case 'L':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.x * -1; drawLineNumber++) {
						world newWorld = map[lineNumber][wordNumber];
						newWorld.loc.x -= drawLineNumber;
						std::vector<coordinate>localCoord = crossed(&newWorld, newCheckedWorld);
						bool increaseStep = true;
						for (int i = 0; i < localCoord.size(); i++) {
							crosses[lineNumber].push_back(localCoord[i]);
							crossLocs[lineNumber].push_back(step);
						}
						step++;
					}
					break;
				case 'R':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.x; drawLineNumber++) {
						world newWorld = map[lineNumber][wordNumber];
						newWorld.loc.x += drawLineNumber;
						std::vector<coordinate>localCoord = crossed(&newWorld, newCheckedWorld);
						bool increaseStep = true;
						for (int i = 0; i < localCoord.size(); i++) {
							crosses[lineNumber].push_back(localCoord[i]);
							crossLocs[lineNumber].push_back(step);
						}
						step++;
					}
					break;
				case 'D':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.y * -1; drawLineNumber++) {
						world newWorld = map[lineNumber][wordNumber];
						newWorld.loc.y -= drawLineNumber;
						std::vector<coordinate>localCoord = crossed(&newWorld, newCheckedWorld);
						bool increaseStep = true;
						for (int i = 0; i < localCoord.size(); i++) {
							crosses[lineNumber].push_back(localCoord[i]);
							crossLocs[lineNumber].push_back(step);
						}
						step++;
					}
					break;
				case 'U':
					for (int drawLineNumber = 0; drawLineNumber < map[lineNumber][wordNumber].difference.y; drawLineNumber++) {
						world newWorld = map[lineNumber][wordNumber];
						newWorld.loc.y += drawLineNumber;
						std::vector<coordinate>localCoord = crossed(&newWorld, newCheckedWorld);
						bool increaseStep = true;
						for (int i = 0; i < localCoord.size(); i++) {
							crosses[lineNumber].push_back(localCoord[i]);
							crossLocs[lineNumber].push_back(step);
						}
						step++;
					}
					break;
				default:/*
					std::cout << "ERROR NO COMPATIBLE CHARACTER" << std::endl;
					system("pause");*/
					break;
				}
			}
		}
		std::cout << step << " steps" << std::endl;
		std::cout << "Done calculating all movements, calculating closest intersection..." << std::endl;
		/*for (int x = 0; x < 2; x++) {
			for (int y = 0; y < crosses.size(); y++) {
				std::cout << crosses[x][y].x << ", " << crosses[x][y].y << std::endl;
			}
		}*/
		std::cout << std::endl;
		//system("pause");
		int distance = 69420;
		int* currentCalcDistance = new int(0);
		std::vector<int> location(2);
		for (int j = 0; j < crosses.size(); j++) {
			std::wcout << "Line number: " << j << std::endl;
			for (int i = 0; i < crosses[j].size(); i++) {
				//std::cout << j << ", " << i << std::endl;
				std::cout << crosses[j][i].x << ", " << crosses[j][i].y << std::endl;
				if (crosses[j][i].x < 0) {
					*currentCalcDistance = crosses[j][i].x * -1 + crosses[j][i].y;
				}
				else if (crosses[j][i].y < 0) {
					*currentCalcDistance = crosses[j][i].x + crosses[j][i].y * -1;
				}
				else if (crosses[j][i].x < 0 && crosses[j][i].y < 0) {
					*currentCalcDistance = crosses[j][i].x * -1 + crosses[j][i].y * -1;
				}
				else {
					*currentCalcDistance = crosses[j][i].x + crosses[j][i].y;
				}

				if (*currentCalcDistance != 0 && *currentCalcDistance < distance) {
					std::cout << *currentCalcDistance << " is less than " << distance << ", adding " << i << " to distance" << std::endl;
					distance = *currentCalcDistance;
					location[j] = i + 1;
				}
			}
		}
		
		std::cout << "Manhattan distance: " << distance << std::endl;
		std::cout << "Done calculating closest intersection, creating linker array..." << std::endl;
		std::vector<coordinate> linker;
		for (int x = 0; x < crosses[0].size(); x++) {
			for (int y = 0; y < crosses[0].size(); y++) {
				if (crosses[0][x].x == crosses[1][y].x && crosses[0][x].y == crosses[1][y].y) {
					linker.push_back({ x, y });
				}
			}
		}

		for (int x = 0; x < linker.size(); x++) {
			std::cout << linker[x].x << ", " << linker[x].y << std::endl;
		}

		std::cout << "started calculating steps..." << std::endl;
		//std::vector<int>calcSteps;
		int* totalStep = new int(69420);
		for (int crossLocation = 0; crossLocation < linker.size(); crossLocation++) {
			coordinate firstArrayCheck = crosses[0][linker[crossLocation].x];
			coordinate secondArrayCheck = crosses[1][linker[crossLocation].y];
			int firstAmount = crossLocs[0][linker[crossLocation].x];
			int secondAmount = crossLocs[1][linker[crossLocation].y];
			for (int mapCheckLoc = 0; mapCheckLoc < 301; mapCheckLoc++) {
				if (firstAmount + secondAmount < *totalStep && firstAmount != 0 && secondAmount != 0) {
					*totalStep = firstAmount + secondAmount;
					std::cout << "Total steps: " << *totalStep << std::endl;
				}
			}
		}
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

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
			/*currentCoord->x = 750;
			currentCoord->y = 750;*/

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

	std::cout << "DONE WITH DAY 3, MOVING ON TO DAY 4" << std::endl;
	// DAY 4
	int currentCheckNumber = 347312;
	int MIN_NUMBER = 347312;
	int MAX_NUMBER = 805915;

	bool notFound = true;
	int totalPasswordValue = 0;
	while (currentCheckNumber < MAX_NUMBER) {
		std::vector<int> checkNumbers = numbersToArray(currentCheckNumber);
		std::vector<coordinate> doubleDigitList;
		bool doubleDigit = false;


		for (int i = 0; i < 6; i++) {
			//if(i < 5 && checkNumbers[i] > checkNumbers[i + 1]) std::cout << "Is lower than expected; raising number..." << std::endl;
			while (i < 5 && checkNumbers[i] > checkNumbers[i + 1]) {
				currentCheckNumber++;
				checkNumbers = numbersToArray(currentCheckNumber);
			}
			//if (i < 5 && checkNumbers[i] == checkNumbers[i + 1]) doubleDigit = true;
			bool addNew = true;
		}
		std::cout << currentCheckNumber << std::endl;
		for (int i = 0; i < doubleDigitList.size(); i++) {
			//std::cout << doubleDigitList[i].x << " is more than once: " << doubleDigitList[i].y << std::endl;
			if (doubleDigitList[i].y > 5) {
				std::cout << "Critical counting error!" << std::endl;
				system("pause");
			}
			if (doubleDigitList[i].y < 2) {
				std::cout << doubleDigitList[i].x << " is double!" << std::endl;
				doubleDigit = true;
			}
		}
		if (doubleDigit && currentCheckNumber < MAX_NUMBER) {
			notFound = false;
			totalPasswordValue++;
			std::cout << currentCheckNumber << std::endl;
		}
		currentCheckNumber++;
	}
	std::cout << "Total password amount: " << totalPasswordValue << std::endl;

	
	system("pause");
	inputFile.close();
	inputOfCodes.close();
	outputFile.close();
	return 0;
}