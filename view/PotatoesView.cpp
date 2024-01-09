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

 #include "PotatoesView.h"
 
/**
* Display current commands
*/
void PotatoesView::displayCommands()  {
	std::cout << "commands:\"switch\" \"display\" \"exit\" \"clmd\" \"next\" \"previous\" \"select\" \"add\" \"delete\" \"sort\" \"search\"" << std::endl;
	std::cout << ":";
}

/**
* Display table header
*/
void PotatoesView::displayHeader()  {
	//If the table schema ever changes, this would be trouble. Worth the effort in making this sane,
	//but as using the column names is a requirement, I think this is fine; I'll change it anyways :) 
	std::printf("|%-4s|%-7s|%-30s|%-14s|%-30s|%-34s|%-8s|%-6s|%-8s|%-6s|%-11s|%-12s|%-6s|%-6s|%-6s|%-8s|\n", 
				"row", "refdate", "geo", "DGUID", "Area Production Value", "UOM", "UOMID", "Scalar Factor", "ScalarID", "Vector", "Coordinates", "Value", "Status", "symbol", "Terminated", "Decimals"
	);
}

/**
* Display all data
* @param data_list vector of record dtos to display
*/
void PotatoesView::displayData( std::vector<PotatoesDTO*> data_list )  {
	
	int i = 1; //just for a line count
	this->displayHeader();
	for( PotatoesDTO* tater : data_list )  {

		//if(i > 30)  { break; } //useful for header "debugging"
		std::printf( "|%-4d", i );
		std::printf( "|%-7d", tater->getRefDate() );
		std::printf( "|%-30s", tater->getGeo().c_str() );
		std::printf( "|%-14s", tater->getDguid().c_str() );
		std::printf( "|%-30.30s", tater->getAreaProductionValue().c_str() );
		std::printf( "|%-34s", tater->getUom().c_str() );
		std::printf( "|%-8s", tater->getUomId().c_str() );
		std::printf( "|%-13s", tater->getScalarFactor().c_str() );
		std::printf( "|%-8s", tater->getScalarId().c_str() );
		std::printf( "|%-6s", tater->getVector().c_str() );
		std::printf( "|%-11.2f", tater->getCoordinate() );
		std::printf( "|%-12.2f", tater->getValue() );
		std::printf( "|%-6s", tater->getStatus().c_str() );
		std::printf( "|%-6s", tater->getSymbol().c_str() );
		std::printf( "|%-10s", tater->getTerminated().c_str() );
		std::printf( "|%-8d|", tater->getDecimals() );
		std::cout << std::endl;
		
		i++;
		
	}
	
}

/**
* Display a single record
*/
void PotatoesView::select(PotatoesDTO* tater, int index)  {
	 
	this->displayHeader();
	std::printf( "|%-4d", index );
	std::printf( "|%-7d", tater->getRefDate() );
	std::printf( "|%-30s", tater->getGeo().c_str() );
	std::printf( "|%-14s", tater->getDguid().c_str() );
	std::printf( "|%-30.30s", tater->getAreaProductionValue().c_str() );
	std::printf( "|%-34s", tater->getUom().c_str() );
	std::printf( "|%-8s", tater->getUomId().c_str() );
	std::printf( "|%-13s", tater->getScalarFactor().c_str() );
	std::printf( "|%-8s", tater->getScalarId().c_str() );
	std::printf( "|%-6s", tater->getVector().c_str() );
	std::printf( "|%-11.2f", tater->getCoordinate() );
	std::printf( "|%-12.2f", tater->getValue() );
	std::printf( "|%-6s", tater->getStatus().c_str() );
	std::printf( "|%-6s", tater->getSymbol().c_str() );
	std::printf( "|%-10s", tater->getTerminated().c_str() );
	std::printf( "|%-8d|", tater->getDecimals() );
	std::cout << std::endl;
}
