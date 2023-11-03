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

#include "PotatoesModel.h"

 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
 
/**
* Constructor
* @param dataset_location The path to the dataset file
*/
PotatoesModel::PotatoesModel(std::string dataset_location, bool use_database)  {	
	
	if(use_database)  {
		try  {
			this->dataset = new PotatoesDB(dataset_location);
			this->usingDbb = use_database;
		}
		catch (const std::exception &e)  {
			std::cout << "Failed to connect to database: " << e.what() << std::endl;
			std::cout << "defaulting to csv file" << std::endl;
			dataset = new DTOList(dataset_location);
			this->usingDbb = false;
		}
	}
	else  {
		dataset = new DTOList(dataset_location);
		this->usingDbb = use_database;
	}
	
}

/**
 * 
 */
bool PotatoesModel::usingDb()  {
	return this->usingDbb;
}

/**
* Gets all the data in the table
* @return vector containing all rows in the table
*/
std::vector<PotatoesDTO*> PotatoesModel::getCurrentData()  {
	return this->dataset->getCurrentData();
}

/**
* Gets a single record from the table
* @param index index / row number of the record
* @return record dto
*/
PotatoesDTO* PotatoesModel::getRecord(int index)  {
	return this->dataset->getRecord(index);
}
//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
/**
* Add a record to the dataset
* @param tater record dto
*/
void PotatoesModel::addRecord(PotatoesDTO* tater)  {
	this->dataset->addRecord(tater);
}
//std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
/**
* Remove a record from the dataset
* @param index index / row number of the record
*/
void PotatoesModel::deleteRecord(int index)  {
	this->dataset->deleteRecord(index);
}
//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
/**
* Completely reset the modified dataset with the original
*/
void PotatoesModel::clearModified()  {
	this->dataset->clearModified();
}
 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;

/**
* Advances the current table buffer through the dataset
*/
void PotatoesModel::nextSet() {
	this->dataset->nextSet();
}
//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
/**
* Loads previous data from the dataset into the table buffer
*/
void PotatoesModel::previousSet() {
	this->dataset->previousSet();
}

/**
* Creates a record DTO from a line with the full record data.
* The line is expected to be a line from a CSV file.
* @param line the full record data, comma separated.
*/
PotatoesDTO* PotatoesModel::createDTO(char line[LINEMAX])  {
	return this->dataset->createDTO(line);
}
//std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;

void PotatoesModel::changeSorting(std::string order)  {
	this->dataset->changeSorting(order);
}

void PotatoesModel::search(std::map<std::string, std::string> column_search)  {
	this->dataset->search(column_search);
}
