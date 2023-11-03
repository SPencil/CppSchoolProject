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
 #ifndef DTO_LIST_HEAD
 #define DTO_LIST_HEAD
 
 #include <iostream>
 #include <fstream>
 #include <vector>
 #include "PotatoesDTO.h"
 #include <string.h>
 
#include "../libraries/rapidcsv/src/rapidcsv.h"
#include "./PotatoesDataClass.h"
 
 class DTOList : public PotatoesDataClass {
	
	private:
		rapidcsv::Document datadoc; //Dataset file
		rapidcsv::Document modifiedDatadoc; //Modified dataset file
		std::vector<PotatoesDTO*> dtoList; //List of records
		std::string fileLocation; //path to dataset file
		std::string fileLocationMod; //path to modified dataset file 
		std::fstream fileStream; //used as input stream for dataset files.
		int recordCount; //total count of all records
		int recordCursor; //current position in the dataset.
		std::string dtoHeader; //dataset header
		bool start_modified; //whether to initialize with the original or modified dataset
		 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
		 
		/**
		 * initialize / reset the record list
		 */
		void initDataset();
	 
	 public:
	 
		/**
		 * Constructor
		 * @param file_location path to dataset file
		 */
		DTOList(std::string file_location);
		
		/**
		 * Get the total number of records
		 * @return record total
		 */
		int datasetCount() override;
		
		/**
		 * Get all data from the list
		 * @return a vector containing references to record DTOs
		 */
		std::vector<PotatoesDTO*> getCurrentData() override;
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		/**
		 * Get a single record from the table
		 * @param index index / row of record
		 * @return record dto reference
		 */
		PotatoesDTO* getRecord(int index) override;
		
		/**
		 * Completely reset the modified file with the original
		 */
		void clearModified();
		
		/**
		 * Add a record to the dataset
		 * @param tater a reference to a record dto
		 */
		void addRecord(PotatoesDTO* tater) override;
		//std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
		/**
		 * Remove a record from the dataset given an index relative to the current list
		 * @param index index / row of record to remove
		 */
		void deleteRecord(int index) override;
		
		/**
		 * Advances the table through the dataset
		 */
		void nextSet() override;
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		/**
		 * Scrolls backwards through the dataset
		 */
		void previousSet() override;
		
		/**
		 * Add a record dto to the table
		 * @param tater record to add to the table
		 */
		void addDTO(PotatoesDTO* tater) override;
		
		/**
		 * Creates a record dto given a line of data
		 * @param line data to turn into a record dto
		 * @return reference to a record dto
		 */
		//PotatoesDTO* createDTO( char line[LINEMAX] );
		 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
		 
		void changeSorting(std::string order) override;
		
		void search(std::map<std::string, std::string> column_search) override;
 };
 
 
 #endif
