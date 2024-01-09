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
 
#include "DTOList.h"
 
////////////////
//DTO operations

/**
* Constructor
* @param file_location path to dataset file
*/
DTOList::DTOList(std::string file_location)  {
	
	//this->dtoList.resize(LISTMAX);
	this->fileLocation = file_location;
	this->recordCount = 0;
	this->recordCursor = 0;
	
	try  {
		this->datadoc = rapidcsv::Document( file_location, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(',', false, false, false, true, '"'), rapidcsv::ConverterParams(), rapidcsv::LineReaderParams() );
	}
	catch(const std::ios_base::failure& oops)  {
		throw(oops);
	}
	
	std::string modified_location = file_location;
	bool exists = true;
	modified_location.append(".mod");
	try  {
		this->modifiedDatadoc = rapidcsv::Document(modified_location, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(',', false, false, false, true, '"'), rapidcsv::ConverterParams(), rapidcsv::LineReaderParams() );
		this->fileLocationMod = modified_location;
	}
	catch(const std::ios_base::failure& oops)  {
		exists = false;
	}

	if(!exists)  {
		std::cout << "no modified set detected, creating one." << std::endl;
		this->start_modified = false;
		this->datadoc.Save(modified_location);
		try  {
			this->modifiedDatadoc = rapidcsv::Document(modified_location, rapidcsv::LabelParams(), rapidcsv::SeparatorParams(',', false, false, false, true, '"'), rapidcsv::ConverterParams(), rapidcsv::LineReaderParams());
		}
		catch(const std::ios_base::failure& oops)  {
			throw(oops);
		}
		this->datadoc = this->modifiedDatadoc;		
	}
	else  {
		std::cout << "using modified set." << std::endl;
		this->start_modified = true;
		this->datadoc = this->modifiedDatadoc;
	}
	
	//this->data
	
	initDataset();
	
}


 
/**
* Get all data from the list
* @return a vector containing references to record DTOs
*/
std::vector<PotatoesDTO*> DTOList::getCurrentData()  {
	return this->dtoList;
}

/**
* Get a single record from the table
* @param index index / row of record
* @return record dto reference
*/
PotatoesDTO* DTOList::getRecord(int index)  {
	return this->dtoList[index - 1];
}

/**
* Completely reset the modified file with the original
*/
void DTOList::clearModified()  {
	try  {
		this->datadoc = rapidcsv::Document(this->fileLocation);
	}
	catch(const std::ios_base::failure& oops)  {
		throw(oops);
	}
	
	std::string mod = this->fileLocation;
	mod.append(".mod");
	std::remove(mod.c_str());
	this->datadoc.Save(mod);
	try  {
		this->modifiedDatadoc = rapidcsv::Document(mod);
	}
	catch(const std::ios_base::failure& oops)  {
		throw(oops);
	}
	this->datadoc = this->modifiedDatadoc;
	
	this->initDataset();
	
}

/**
* Add a record to the dataset
* @param tater a reference to a record dto
*/
void DTOList::addRecord(PotatoesDTO* tater)  {
	
	std::vector<std::string> csv_row;
	csv_row.push_back( std::to_string(tater->getRefDate()) );
	csv_row.push_back( tater->getGeo() );
	csv_row.push_back( tater->getDguid() );
	csv_row.push_back( tater->getAreaProductionValue() );
	csv_row.push_back( tater->getUom() );
	csv_row.push_back( tater->getUomId() );
	csv_row.push_back( tater->getScalarFactor() );
	csv_row.push_back( tater->getScalarId() );
	csv_row.push_back( tater->getVector() );
	csv_row.push_back( std::to_string(tater->getCoordinate()) );
	csv_row.push_back( std::to_string(tater->getValue()) );
	csv_row.push_back( tater->getStatus() );
	csv_row.push_back( tater->getSymbol() );
	csv_row.push_back( tater->getTerminated() );
	csv_row.push_back( std::to_string(tater->getDecimals()) );
	
	this->modifiedDatadoc.InsertRow(0, csv_row);
	this->modifiedDatadoc.Save();
	this->initDataset();
	
}

/**
* Remove a record from the dataset given an index relative to the current list
* @param index index / row of record to remove
*/
void DTOList::deleteRecord(int index)  {
	
	//The display table is shifted by +1 to start at 1 instead of 0
	index--;
	
	std::cout << "deleting " << this->dtoList[index]->getGeo() << " " << this->dtoList[index]->getValue() << std::endl;
	
	this->modifiedDatadoc.RemoveRow( (index) + (this->recordCursor - 100) );
	this->modifiedDatadoc.Save();
	this->initDataset();
	
}

/**
* Add a record dto to the table
* @param tater record to add to the table
*/
void DTOList::addDTO(PotatoesDTO* tater)  {
	this->dtoList.push_back(tater);
}


////////////////////
//Dataset operations

/**
* initialize / reset the record list
*/
void DTOList::initDataset()  {

	//reset everything
	this->recordCount = this->datasetCount();
	this->recordCursor = 0;
	this->dtoList.clear();
	
	//starting with the original or modified dataset? Start the input stream.
	try  {
		(this->start_modified) ? this->fileStream.open( this->fileLocationMod ) : this->fileStream.open( this->fileLocation );
	}
	catch(const std::ios_base::failure& oops)  {
		throw(oops);
	} 
	
	//iterate through the stream line by line and create their dtos, but
	//only 100 times.
	int count = 0;
	for(; count <= LISTMAX; ++count)  {
		if( this->fileStream.eof() )  { break; }
		
		//First line is the header.
		if(count == 0)  {
			char header[LINEMAX];
			this->fileStream.getline(header, LINEMAX);
			continue;
		}
		
		char line[LINEMAX];
		this->fileStream.getline(line, LINEMAX);
		
		//ignore garbage lines.
		if( line[0] == '\n' || line[0] == '\0')  {
			break;
		}
		
		//create and add to the list.
		PotatoesDTO* tater = this->createDTO(line);
		this->addDTO(tater);
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
	}
	
	//The loop will run a total of 101 times because of the header, but only 100 records are read.
	count--;
	this->recordCursor = count;
	std::cout << "read complete with " << count << " records" << std::endl;
	std::cout << this->recordCount << " records total detected" << std::endl;
		
	this->fileStream.close();
}

/**
* Get the total number of records
* @return record total
*/
int DTOList::datasetCount()  {
	
	//starting with the original or modified dataset? Start the input stream.
	try  {
		(this->start_modified) ? this->fileStream.open( this->fileLocationMod ) : this->fileStream.open( this->fileLocation );
	}
	catch(const std::ios_base::failure& oops)  {
		throw(oops);
	}

	//rip through the input stream, counting the lines. 
	int count = 0;
	char dump[LINEMAX];
	this->fileStream.getline(dump, LINEMAX); //ignore the header

	while( !this->fileStream.eof() )  {
		this->fileStream.getline(dump, LINEMAX);
		//ignore garbage.
		if( dump[0] == '\n' || dump[0] == '\0' )  {
			break;
		}
		count++;
	}
	this->fileStream.close();
	return count;
}

/**
* Advances the table through the dataset
*/
void DTOList::nextSet() {

	try {
		this->fileStream.open(this->fileLocationMod);
	}
	catch (const std::ios_base::failure& oops) {
		throw(oops);
	}

	//discard the header
	char dump[LINEMAX];
	this->fileStream.getline(dump, LINEMAX);

	int cursor = 0;
	while (cursor < this->recordCursor) {
		//discard lines until the first record in the next 100 is reached
		this->fileStream.getline(dump, LINEMAX);
		cursor++;
	}

	this->dtoList.clear();

	//read the next 100 records into the list.
	for (int i = 0; i < LISTMAX; i++) {
		this->fileStream.getline(dump, LINEMAX);
		if (dump[0] == '\n' || dump[0] == '\0') {
			break;
		}
		PotatoesDTO* tater = this->createDTO(dump);
		this->addDTO(tater);
		cursor++;
	}
	this->recordCursor = cursor;

	this->fileStream.close();
}

/**
* Scrolls backwards through the dataset
*/
void DTOList::previousSet() {
	std::cout << this->recordCursor << std::endl;
	//Check if we're at the beginning of the dataset
	if (this->recordCursor <= LISTMAX) {
		std::cout << "no previous entries" << std::endl;
		return;
	}
	
	//set the input file stream
	try {
		this->fileStream.open(this->fileLocationMod);
	}
	catch (const std::ios_base::failure& oops) {
		throw(oops);
	}

	//discard the header
	char dump[LINEMAX];
	this->fileStream.getline(dump, LINEMAX);

	int cursor = 0;
	while ( cursor < this->recordCursor - (LISTMAX * 2) ) {
		//discard lines until the first record of the previous 100 is reached
		this->fileStream.getline(dump, LINEMAX);
		cursor++;
	}

	this->dtoList.clear();
	
	//read the next 100 records into the list
	for (int i = 0; i < LISTMAX; i++) {
		this->fileStream.getline(dump, LINEMAX);
		if (dump[0] == '\n' || dump[0] == '\0') {
			break;
		}
		PotatoesDTO* tater = this->createDTO(dump);
		this->addDTO(tater);
		cursor++;
	}
	this->recordCursor = cursor;

	this->fileStream.close();
}

void DTOList::changeSorting(std::string order)  {
	
}

void DTOList::search(std::map<std::string, std::string> column_search)  {
	
}
