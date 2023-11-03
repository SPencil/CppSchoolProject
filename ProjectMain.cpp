/* 
 * 	This file is part of Cameron Wass' programming research project
 * 	Copyright (c) 2023 Cameron Wass.
 * 
 * 	This project is free software: you can redistribute it and/or modify  
 * 	it under the terms of the GNU General Public License as published by  
 * 	the Free Software Foundation, version 3.
 *	
 * 	This program is distributed in the hope that it will be useful, but 
 * 	WITHOUT ANY WARRANTY; without even the implied warranty of 
 * 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * 	General Public License for more details.
 *	
 *	You should have received a copy of the GNU General Public License 
 * 	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

/*	Contains information licensed under the Open Government Licence – Canada.
 *  https://open.canada.ca/en/open-government-licence-canada
 * 
 * 	https://open.canada.ca/data/en/dataset/d32a60af-68bc-4a40-9b9e-1b82db338308
 */
 
/*********************************************************************
 * A quick note on naming convention:
 * 	ClassesAreCamelCase
 * 	classFunctions and classVariables are camelCase
 * 	parameters_and_function_variables_are_snake_case
 * 	CONSTANTS ARE STILL LOUD
 * 
 * 	Some APIs may differ from this.
 */

#include "ProjectMain.h"


/*3rd party libraries are external to the project as to not get accidentally 
 * swept up in the submission file.
 * To run this code, dependencies must be in a libraries folder one level up from
 * the project main.
 */

//https://github.com/d99kris/rapidcsv licensed under BSD-3
//#include "../libraries/rapidcsv/src/rapidcsv.h"


/** Cameron Wass, 040-626-741, wass0010@algonquinlive.com
 * Project main function
 */
int main (int argc, char* argv[])  {
	
	//All the main is used for is creating the controller, and  passing input.
	//A halting flag is set when it's ready to die. 
	
	std::cout << "Use database? (y/n)" << std::endl;
	std::string db;
	std::cin >> db;
	
	
	PotatoesController* controller; 
	if(db == "y")  {
		controller = new PotatoesController("./data/32100358.csv", true);
	}
	else if(db == "n")  {
		controller = new PotatoesController("./data/32100358.csv", false);
	}
	else {
		std::cout << "defaulting to csv" << std::endl;
		controller = new PotatoesController("./data/32100358.csv", false);
	}
	
	while(controller->isAlive() == true) {
		
		//TODO: refactor to use std::get_line, so that parameters can be passed.
		//instead of one "word" commands
		std::string input;
		std::cin >> input;
		controller->parseInput(input);
		input = "";

	}
	//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
	return 0;
}
