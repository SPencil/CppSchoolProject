
#define CATCH_CONFIG_MAIN
#include </usr/local/include/catch2/catch.hpp>

#include <iostream>
#include <vector>

#include "../model/PotatoesDB.h"
#include "../model/PotatoesDTO.h"
#include <pqxx/pqxx>


TEST_CASE("Check that a DTO is added to the database (Cameron Wass)", "[dto]")  {
	
	pqxx::connection dbConnection("postgresql://urist@localhost/potatoesDB");
	
	PotatoesDB* list = new PotatoesDB("../32100358.csv");
	PotatoesDTO* tater = new PotatoesDTO();
	//craft the test DTO
	tater->setRefDate( 9999 );
	tater->setGeo( "SOMEWHERE" );
	tater->setDguid( "UHH" );
	tater->setAreaProductionValue( "TATERS" );
	tater->setUom( "TATERS" );
	tater->setUomId( "42" );
	tater->setScalarFactor( "TATERS" );
	tater->setScalarId( "420" );
	tater->setVector( "vec" );
	tater->setCoordinate( 2.2 );//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
	tater->setValue( 500 );
	tater->setStatus( "" );
	tater->setSymbol( "" );
	tater->setTerminated( "" );
	tater->setDecimals( 0 );
	//Add the DTO to the DB
	list->addRecord(tater);
	//SQL to retrieve the test record
	std::string sql = "SELECT * FROM tatertable WHERE Geo LIKE 'SOMEWHERE';";
	//execute sql, store results in an object
	pqxx::nontransaction sel(dbConnection); 
	pqxx::result current_data( sel.exec(sql.c_str()) );
	
	PotatoesDTO *tater2 = new PotatoesDTO();
	//should only be one result, but I'm just ripping this from how I did it in the PotatoesDB.cpp file
	for (pqxx::result::const_iterator row = current_data.begin(); row != current_data.end(); row++)  {
		tater2->setRefDate( row[1].as<int>() );
		tater2->setGeo( row[2].as<std::string>() );
		tater2->setDguid( row[3].as<std::string>() );
		tater2->setAreaProductionValue( row[4].as<std::string>() );
		tater2->setUom( row[5].as<std::string>() );
		tater2->setUomId( row[6].as<std::string>() );
		tater2->setScalarFactor( row[7].as<std::string>() );
		tater2->setScalarId( row[8].as<std::string>() );
		tater2->setVector( row[9].as<std::string>() );
		tater2->setCoordinate( row[10].as<double>() );//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
		//Value is the only converted field that can be empty, which stod does not like.
		try  {
			tater2->setValue( row[11].as<double>() );
		}
		catch(const std::invalid_argument& oops)  {
			tater2->setValue( 0.0 );
		} //std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
		tater2->setStatus( row[12].as<std::string>() );
		tater2->setSymbol( row[13].as<std::string>() );
		tater2->setTerminated( row[14].as<std::string>() );
		tater2->setDecimals( row[15].as<double>() );
		
		//std::cout << "Cameron Wass, 040-626-741, wass0010@algonquinlive.com" << std::endl;
	}
	
	REQUIRE( tater2->getValue() == 500 );
}
