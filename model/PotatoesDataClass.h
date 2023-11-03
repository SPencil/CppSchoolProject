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

#ifndef POTATOES_DATA_CLASS_HEAD
#define POTATOES_DATA_CLASS_HEAD

#include "PotatoesDTO.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <map>

#define LISTMAX 100
#define LINEMAX 256


/**
 * Abstract class which can be implemented by the model
 *///std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
class PotatoesDataClass  {
	
	public:
		virtual ~PotatoesDataClass() {}
	
		virtual std::vector<PotatoesDTO*> getCurrentData() = 0;
		virtual PotatoesDTO* getRecord(int index) = 0;
		virtual void addRecord(PotatoesDTO* tater) = 0;
		virtual void deleteRecord(int index) = 0;
		virtual void nextSet() = 0;
		virtual void previousSet() = 0;
		virtual void addDTO(PotatoesDTO* tater) = 0;
		virtual int datasetCount() = 0;
		virtual void clearModified() = 0;
		virtual void changeSorting(std::string order) = 0;
		virtual void search(std::map<std::string, std::string> column_search) = 0;
		
		
		PotatoesDTO* createDTO( char line[LINEMAX] )  {
			//the string looks like "","","","" 
	
			PotatoesDTO* tater = new PotatoesDTO();
			
			std::string columns[15];
			int current_column = 0;
			bool extract_char = false;
			
			//Parsing the line data into an array of data that can be passed into the dto
			//Unfortunately, the original dataset has all values in quotes and the API doesn't save
			//values with surrounding quotes unless they have a space or a comma, so both need to be handled.
			
			//all values in quotes, all lines start with a " //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
			if(line[0] == '"')  {
				for(int i = 0; i <= (int)strlen(line); i++)  {
					if(line[i] == '\0')  { break; }
					
					//flip between extracting characters or moving along
					if(line[i] == '"')  {
						if(extract_char == false)  {
							extract_char = true;
							continue;
						}
						else  {
							extract_char = false;
							current_column++;
							continue;
						}
					}
					//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
					//while between quotes, push the character into it's respective string.
					if(extract_char == true)  {
						columns[current_column].push_back(line[i]);
						continue;
					}
					
				} //for
			}
			//not all values in quotes.
			else  {
				bool inner_quote = false; //reading between quotes?
				for(int i = 0; i <= (int)strlen(line); i++)  {
					if(line[i] == '\0')  { break; }
					
					//are we reading a inside a quoted value
					if(line[i] == '"' && inner_quote == false)  { 
						inner_quote = true;
						continue;
					}
					if(line[i] == '"' && inner_quote == true)  { 
						inner_quote = false;
						continue; //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
					}
					
					//is this comma inside a quoted value
					if(line[i] == ',' && inner_quote == false)  {
						//std::cout << columns[current_column] << std::endl;
						current_column++;
						continue;
					}
					
					columns[current_column].push_back(line[i]);
					continue;
					
					 //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
				}
			}
			
			//set the values in the dto
			tater->setRefDate( std::stoi(columns[0]) );
			tater->setGeo( columns[1] );
			tater->setDguid( columns[2] );
			tater->setAreaProductionValue( columns[3] );
			tater->setUom( columns[4] );
			tater->setUomId( columns[5] );
			tater->setScalarFactor( columns[6] );
			tater->setScalarId( columns[7] );
			tater->setVector( columns[8] );
			tater->setCoordinate( std::stod(columns[9]) );//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
			//Value is the only converted field that can be empty, which stod does not like.
			try  {
				tater->setValue( std::stod(columns[10]) );
			}
			catch(const std::invalid_argument& oops)  {
				tater->setValue( 0.0 );
			} //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
			tater->setStatus( columns[11] );
			tater->setSymbol( columns[12] );
			tater->setTerminated( columns[13] );
			tater->setDecimals( std::stoi(columns[14]) );
			
			return tater;
		}	
		
};

#endif
