
#define CATCH_CONFIG_MAIN
#include </usr/local/include/catch2/catch.hpp>

#include <iostream>
#include <vector>

#include "../model/DTOList.h"
#include "../model/PotatoesDTO.h"



TEST_CASE("Check that a DTO is added (Cameron Wass)", "[dto]")  {
	
	//initialize, clear any changes, pull the data out, compare the first record.
	DTOList* list = new DTOList("../32100358.csv");
	list->clearModified();
	std::vector<PotatoesDTO*> listarr = list->getCurrentData();
	PotatoesDTO* first_dto = listarr[0];
	
	int first_value = first_dto->getValue();
	REQUIRE( first_value == 503600 );
	
	PotatoesDTO* tater = new PotatoesDTO();

	tater->setRefDate( 9999 );
	tater->setGeo( "SOMEWHERE" );
	tater->setDguid( "UHH" );
	tater->setAreaProductionValue( "TATERS" );
	tater->setUom( "TATERS" );
	tater->setUomId( "cool" );
	tater->setScalarFactor( "TATERS" );
	tater->setScalarId( "some" );
	tater->setVector( "vec" );
	tater->setCoordinate( 2.2 );//Cameron Wass, 040-626-741, wass0010@algonquinlive.com
	tater->setValue( 500 );
	tater->setStatus( "" );
	tater->setSymbol( "" );
	tater->setTerminated( "" );
	tater->setDecimals( 0 );
	
	list->addRecord(tater);
	listarr = list->getCurrentData();
	PotatoesDTO* second_dto = listarr[0];
	
	int second_value = second_dto->getValue();
	
	REQUIRE( second_value == 500 );
	
	list->clearModified();
}
