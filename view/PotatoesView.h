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

#ifndef POTATOES_VIEW_HEAD
#define POTATOES_VIEW HEAD
 
#include <iostream>
#include <string>
#include <vector>
#include "../model/PotatoesDTO.h"
 
class PotatoesView  {
	
	private:
	
	public:
	
		/**
		 * Display current commands
		 */
		void displayCommands();
		
		/**
		 * Display table header
		 */
		void displayHeader();
		
		/**
		 * Display all data
		 * @param data_list vector of record dtos to display
		 */
		void displayData( std::vector<PotatoesDTO*> data_list );
		
		/**
		 * Display a single record
		 */
		void select(PotatoesDTO* tater, int index);

};
 
 #endif
