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

   
#ifndef POTATOES_DB_HEAD
#define POTATOES_DB_HEAD

#include <iostream>
#include <vector>
#include <pqxx/pqxx>

#include "../libraries/rapidcsv/src/rapidcsv.h"
#include "./PotatoesDataClass.h"


/**
 * Dataclass for using a database to access and manipulate the dataset.
 * function documentation is in the corresponding cpp file.
 */
class PotatoesDB : public PotatoesDataClass{
	
	private:
	
		rapidcsv::Document datadoc;
		pqxx::connection dbConnection;
		std::vector<PotatoesDTO*> dtoList;
		
		int recordCount;
		int recordCursor;
		
		void initDb();
		void initData();
		
		std::string sorting;
		std::string searchTerm;
	
	public:
	
		PotatoesDB(std::string file_location);
		
		std::vector<PotatoesDTO*> getCurrentData() override;
		PotatoesDTO* getRecord(int index) override;
		void addRecord(PotatoesDTO* tater) override;
		void deleteRecord(int index) override;
		void nextSet() override;
		void previousSet() override;
		void addDTO(PotatoesDTO* tater) override;
		int datasetCount() override;
		void clearModified() override;
		void changeSorting(std::string order) override;
		void search(std::map<std::string, std::string> column_search) override;
};

#endif
