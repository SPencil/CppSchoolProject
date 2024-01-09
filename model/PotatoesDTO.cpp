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
 
#include "PotatoesDTO.h"

/**
 * Get the data point date
 */
int PotatoesDTO::getRefDate()  {
	return this->refDate;
}
/**
 * Set the data point date
 */
void PotatoesDTO::setRefDate(int ref_date)  {
	this->refDate = ref_date;
}

/**
 * Get the name of the province/territory/country
 */		
std::string PotatoesDTO::getGeo()  {
	return this->geo;
}
/**
 * Set the name of the province/territory/country
 */
void PotatoesDTO::setGeo(std::string geo)  {
	this->geo = geo;
}


/**
 * Get the DGUID
 */
std::string PotatoesDTO::getDguid()  {
	return this->dguid;
}
/**
 * Set the DGUID
 */
void PotatoesDTO::setDguid(std::string dguid)  {
	this->dguid = dguid;
}

/**
 * Get the area production value; what the value is representing
 */
std::string PotatoesDTO::getAreaProductionValue()  {
	return this->areaProductionValue;
}
/**
 * Set the area production value
 */
void PotatoesDTO::setAreaProductionValue(std::string area_production_value)  {
	this->areaProductionValue = area_production_value;
}

/**
 * Get the Unit Of Measure
 */
std::string PotatoesDTO::getUom()  {
	return this->Uom;
}
/**
 * Set the Unit of Measure
 */
void PotatoesDTO::setUom(std::string uom)  {
	this->Uom = uom;
}

/**
 * Get UOMID
 */
std::string PotatoesDTO::getUomId()  {
	return this->UomId;
}
/**
 * Set UOMID
 */
void PotatoesDTO::setUomId(std::string uomid)  {
	this->UomId = uomid;
}

/**
 * Get the scalar factor
 */
std::string PotatoesDTO::getScalarFactor()  {
	return this->scalarFactor;
}
/**
 * Set the scalar factor
 */
void PotatoesDTO::setScalarFactor(std::string scalar_factor)  {
	this->scalarFactor = scalar_factor;
}

/**
 * Get the scalar id
 */
std::string PotatoesDTO::getScalarId()  {
	return this->scalarId;
}
/**
 * Set the scalar id
 */
void PotatoesDTO::setScalarId(std::string scalar_id)  {
	this->scalarId = scalar_id;
}

/**
 * Get the vector
 */
std::string PotatoesDTO::getVector()  {
	return this->vector;
}
/**
 * Set the vector
 */
void PotatoesDTO::setVector(std::string vector)  {
	this->vector = vector;
}


/**
 * Get coordinates
 */
double PotatoesDTO::getCoordinate()  {
	return this->coordinate;
}
/**
 * Set coordinates
 */
void PotatoesDTO::setCoordinate(double coordinate)  {
	this->coordinate = coordinate;
}

/**
 * Get the value
 */
double PotatoesDTO::getValue()  {
	return this->value;
}
/**
 * Set the value
 */
void PotatoesDTO::setValue(double value)  {
	this->value = value;
}


/**
 * Get status
 */
std::string PotatoesDTO::getStatus()  {
	return this->status;
}
/**
 * Set status
 */
void PotatoesDTO::setStatus(std::string status)  {
	this->status = status;
}

/**
 * Get the symbol
 */
std::string PotatoesDTO::getSymbol()  {
	return this->symbol;
}
/**
 * Set the symbol
 */
void PotatoesDTO::setSymbol(std::string symbol)  {
	this->symbol = symbol;
}

/**
 * I am a cybernetic organism: living tissue, over metal endoskeleton
 */
std::string PotatoesDTO::getTerminated()  {
	return this->terminated;
}
/**
 * Set terminated
 */
void PotatoesDTO::setTerminated(std::string terminated)  {
	this->terminated = terminated;
}

/**
 * Get decimal points
 */
int PotatoesDTO::getDecimals()  {
	return this->decimals;
}
/**
 * Set decimal points
 */
void PotatoesDTO::setDecimals(int decimals)  {
	this->decimals = decimals;
}

