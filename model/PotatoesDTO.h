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
 
 #ifndef POTATOES_DTO_HEAD
 #define POTATOES_DTO_HEAD
 
 #include <string>
 
 /**
 * This class represents a row within the 'area, production and farm value of potatoes' dataset.
 * Author: Cameron Wass, 040-626-741, wass0010@algonquinlive.com
 */
 class PotatoesDTO  {
	
	private:
		/*
		 * All the columns of the potatoes data table
		*/
		int refDate; //Year of the data point
		std::string geo; //province or country
		std::string dguid; //seems to be a province or country code?
		std::string areaProductionValue; //description of the data point
		std::string Uom; //"unit of measure"
		std::string UomId; //unique id for each differen UOM
		std::string scalarFactor; //what to scale the amount by
		std::string scalarId; //unique id for the different scalars
		std::string vector; //groups data based on the full year range for a specific location and what's measured.
		double coordinate; //data coordinate
		double value; //the value of this data point.
		std::string status; //unsure, unused
		std::string symbol; //unsure, (mostly) unused
		std::string terminated; //unsure, unused
		int decimals; //how many decimal places should value use?
		
	public:
	
		/**
		 * See source for function documentation; it's nothing but setters and getters, so really there's not much to see.
		 */
	
		int getRefDate();
		void setRefDate(int ref_date);
		
		std::string getGeo();
		void setGeo(std::string geo);
		
		std::string getDguid();
		void setDguid(std::string dguid);
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		std::string getAreaProductionValue();
		void setAreaProductionValue(std::string area_production_value);
		
		std::string getUom();
		void setUom(std::string uom);
		
		std::string getUomId() ;
		void setUomId(std::string uomid);
		
		std::string getScalarFactor();
		void setScalarFactor(std::string scalar_factor);
		
		std::string getScalarId();
		void setScalarId(std::string scalar_id);
		
		std::string getVector();
		void setVector(std::string vector);
		
		double getCoordinate();
		void setCoordinate(double coordinate);
		
		double getValue();
		void setValue(double value);
		
		std::string getStatus();
		void setStatus(std::string status);
		
		std::string getSymbol();
		void setSymbol(std::string symbol);
		
		std::string getTerminated();
		void setTerminated(std::string terminated);
		//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		int getDecimals();
		void setDecimals(int decimals);
 };
 
 #endif
