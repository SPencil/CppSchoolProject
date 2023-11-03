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
  //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
 #ifndef POTATOES_CONTROLLER_HEAD
 #define POTATOES_CONTROLLER_HEAD
 
 #include <string>
 #include <map>
 
 #include "../view/PotatoesView.h"
 #include "../model/PotatoesModel.h"
 #include "../model/PotatoesDTO.h"
 
 #define LINEMAX 256
 
class PotatoesController  {
	 
	private:
		PotatoesView* view; //reference to the view object
		PotatoesModel* model; //reference to the model
		
		bool keepAlive = true; //solve the halting problem.
		std::string dataFile;
	 
	public:
		/**
		 * Constructor
		 * @param data_file path to dataset
		 */
		PotatoesController(std::string data_file, bool use_database);

		/**
		 * Check if we should halt
		 */
		bool isAlive();
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		/**
		 * Select which function to run based on user input
		 * @param user input
		 */
		void parseInput(std::string input);
		
		void switchDataset();
		
		/**
		 * Displays all data in the list
		 */
		void displayCurrentData();
		
		/**
		 * Display one record from the list
		 */
		void displayRecord();
		
		 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
		 
		/**
		 * Add a record to the dataset
		 */
		void addRecord();
		
		/**
		 * Delete a record from the dataset
		 */
		void deleteRecord();
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		/**
		 * Clear all changes to the dataset
		 */
		void clearModified();
	 
		/**
		 * Advance the table through the dataset
		 */
		void nextSet();
		
		/**
		 * scroll backwards through the dataset
		 */
		void previousSet();
	 //Cameron Wass, 040-626-741, wass0010@algonquinlive.com
	 
		void changeSorting();
		
		void search();
 };
 
 #endif
