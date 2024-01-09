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

#include "PotatoesController.h"
 
/**
* Constructor
* @param data_file path to dataset
*/
PotatoesController::PotatoesController(std::string data_file, bool use_database)  {
	this->view = new PotatoesView();
	this->model = new PotatoesModel(data_file, use_database);
	this->dataFile = data_file;

	this->view->displayCommands();
}

/**
* Check if we should halt
*/
bool PotatoesController::isAlive()  {
	return this->keepAlive;
}
 
/**
* Select which function to run based on user input
* @param user input
*/
void PotatoesController::parseInput(std::string input)  {
	 
	if(input == "display")  {
		this->displayCurrentData();
		return;
	}
	if (input == "exit") {
		this->keepAlive = false;
		return;
	}
	if (input == "next") {
		this->nextSet();
		return;
	}
	if (input == "previous") {
		this->previousSet();
		return;
	}
	if(input == "select")  {
		this->displayRecord();
		return;
	}
	if(input == "clmd")  {
		this->clearModified();
		return;
	}
	if(input == "add")  {
		this->addRecord();
		return;
	}
	if(input == "delete")  {
		this->deleteRecord();
		return;
	} 
	if(input == "switch")  {
		this->switchDataset();
		return;
	}
	if(input == "sort")  {
		this->changeSorting();
		return;
	}
	if(input == "search")  {
		this->search();
		return;
	}

	std::cout << "invalid command: " << input << std::endl;
	this->view->displayCommands();

}

/**
 * Switches between reading and modifying the dataset using the database or the csv file
 */
void PotatoesController::switchDataset()  {
	
	this->model->usingDb() ? std::cout << "switching to csv" << std::endl : std::cout << "switching to database" << std::endl;
	this->model = new PotatoesModel( this->dataFile, !this->model->usingDb() );
	this->view->displayCommands();
}

/**
* Displays all data in the list
*/
void PotatoesController::displayCurrentData()  {
	 this->view->displayData( this->model->getCurrentData() );
	 this->view->displayCommands();
 }

/**
* Display one record from the list
*/
void PotatoesController::displayRecord()  {
	 
	 std::cout << "which record number: ";
	 int index;
	 std::cin >> index;
	 if( !std::cin.good() || index < 1 || index > 100)  {
		 std::cout << "invalid number: " << index << std::endl;
		 this->view->displayCommands();
		 return;
	 }
	 
	 this->view->select( this->model->getRecord(index), index );
	 this->view->displayCommands();
 }
 
/**
* Add a record to the dataset
*/
void PotatoesController::addRecord()  {
	 
	PotatoesDTO* tater = new PotatoesDTO();

	//TODO: This is gross. Needs to be refactored
	
	std::cout << "RefDate: ";
	int ref_date;
	std::cin >> ref_date;
	tater->setRefDate(ref_date);
	
	std::cout << "Geo: ";
	std::string geo;
	std::cin >> geo;
	tater->setGeo(geo);
	
	std::cout << "Dguid: ";
	std::string dg;
	std::cin >> dg;
	tater->setDguid(dg);
	
	std::cout << "Area Production Value: ";
	std::string apv;
	std::cin >> apv;
	tater->setAreaProductionValue(apv);
	
	std::cout << "Uom: ";
	std::string uom;
	std::cin >> uom;
	tater->setUom(uom);
	
	std::cout << "UomId: ";
	std::string uomid;
	std::cin >> uomid;
	tater->setUomId(uomid);

	std::cout << "ScalarFactor: ";
	std::string sf;
	std::cin >> sf;
	tater->setScalarFactor(sf);
	
	std::cout << "ScalarId: ";
	std::string sid;
	std::cin >> sid;
	tater->setScalarId(sid);
	
	std::cout << "Vector: ";
	std::string vec;
	std::cin >> vec;
	tater->setVector(vec);
	
	std::cout << "Coordinate: ";
	double coord;
	std::cin >> coord;
	tater->setCoordinate(coord);
	
	std::cout << "value: ";
	double val;
	std::cin >> val;
	tater->setValue(val);
	
	std::cout << "Status: ";
	std::string stat;
	std::cin >> stat;
	tater->setStatus(stat);

	std::cout << "Symbol: ";
	std::string sym;
	std::cin >> sym;
	tater->setSymbol(sym);
	
	std::cout << "Terminated: ";
	std::string term;
	std::cin >> term;
	tater->setTerminated(term);
	
	std::cout << "Decimals: ";
	int dec;
	std::cin >> dec;
	tater->setDecimals(dec);
	
	this->model->addRecord(tater);
	//this->view->displayHeader();
	this->view->select(tater, 1);
	this->view->displayCommands();
	 
}

/**
* Delete a record from the dataset
*/
void PotatoesController::deleteRecord()  {
	std::cout << "which record number: ";
	int index;
	std::cin >> index;
	if( !std::cin.good() || index < 1 || index > 100)  {
		std::cout << "invalid number: " << index << std::endl;
		this->view->displayCommands();
		return;
	}

	this->model->deleteRecord(index);
	std::cout << "record deleted" << std::endl;
	this->view->displayCommands();
}
 
/**
* Clear all changes to the dataset
*/
void PotatoesController::clearModified()  {
	 this->model->clearModified();
	 std::cout << "all changes reverted." << std::endl;
	 this->view->displayCommands();
 }

  
/**
* Advance the table through the dataset
*/
void PotatoesController::nextSet()  {
	 this->model->nextSet();
	 this->view->displayData( this->model->getCurrentData() );
	 this->view->displayCommands();
 }

/**
* scroll backwards through the dataset
*/
void PotatoesController::previousSet()  {
	this->model->previousSet();
	this->view->displayData(this->model->getCurrentData());
	this->view->displayCommands();
}

/**
 * Create the order by string.
 */
void PotatoesController::changeSorting()  {
	
	std::cout << "Enter new columns to sort by, enter 'done' when done." << std::endl << ":";
	
	//TODO: fragile, refactor

	std::string order = "";
	std::string input = "";
	std::cin >> input;
	while(input != "done")  {
		order.append( input + ", " );
		std::cout << std::endl << ":";
		std::cin >> input;
	}
	order.erase( order.size()-2 ); //get rid of the comma-space
	
	
	this->model->changeSorting(order);
	this->view->displayData( this->model->getCurrentData() );
	this->view->displayCommands();
}

/**
 * Create the hashmap full of columns and search terms to hand to the model
 */
void PotatoesController::search()  {

	//TODO: This isn't really clear, and I feel like I need something to wrap the cin and cout calls
	
	std::string column;
	std::string search;
	std::map<std::string, std::string> column_search;
	
	std::cout << "enter column to search (enter 'done' to stop)" << std::endl << "(entering 'done' here will remove all search terms)" << std::endl << ":";
	std::cin >> column;
	
	//Keep adding to the hashmap until ""done""
	while(column != "done")  {
		std::cout << "enter search term: ";
		std::cin >> search;
		
		column_search[column] = search;
		std::cout << "will search for " << search << " in column " << column << std::endl;
		std::cout << "enter column to search (enter 'done' to stop): ";
		std::cin >> column;
	}
	

	this->model->search(column_search);
	this->view->displayData( this->model->getCurrentData() );
	this->view->displayCommands();
	
}
