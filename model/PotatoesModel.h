
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

#ifndef POTATOES_MODEL_HEAD
#define POTATOES_MODEL_HEAD
 
#include <vector>
#include <map>

#include "PotatoesDataClass.h"

#include "DTOList.h"
#include "PotatoesDB.h"

#define LINEMAX 256
 
/**
 * PotatoesModel is responsible for holding and manipulating any data associated with 
 * the program. One and only one reference should live in the controller.
 * 
 * As the model currently only consists of the table itself, everything so far is a
 * pass-through between the controller and the list object. 
 */ 
class PotatoesModel  {
	 
	private:
		PotatoesDataClass* dataset;
		
		bool usingDbb;
		
		//DTOList* dtoList; //Reference to the object responsible for the record list
	 
	public:

		/**
		 * Constructor
		 * @param dataset_location The path to the dataset file
		 */
		PotatoesModel(std::string dataset_location, bool use_database);
		
		/**
		 * Is the model currently using the db or csv?
		 */
		bool usingDb();

		/**
		 * Gets all the data in the table
		 * @return vector containing all rows in the table
		 */
		std::vector<PotatoesDTO*> getCurrentData();
		
		/**
		 * Gets a single record from the table
		 * @param index index / row number of the record
		 * @return record dto
		 */
		PotatoesDTO* getRecord(int index);
		
		
		/**
		 * Add a record to the dataset
		 * @param tater record dto
		 */
		void addRecord(PotatoesDTO* tater);

		/**
		 * Remove a record from the dataset
		 * @param index index / row number of the record
		 */
		void deleteRecord(int index);
		
		/**
		 * Completely reset the modified dataset with the original
		 */
		void clearModified();
		
		/**
		 * Advances the current table buffer through the dataset
		 */
		void nextSet();

		/**
		 * Loads previous data from the dataset into the table buffer
		 */
		void previousSet();
		
		 
		/**
		 * Creates a record DTO from a line with the full record data.
		 * The line is expected to be a line from a CSV file.
		 * @param line the full record data, comma separated.
		 */
		PotatoesDTO* createDTO(char line[LINEMAX]);
		
		
		void changeSorting(std::string order);
		
		void search(std::map<std::string, std::string> column_search);
};
 
#endif
