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
  
#include "PotatoesDB.h"

/**
 * Constructor, opens database connection and sets up a fresh table.
 * @param file_location dataset location
 */
PotatoesDB::PotatoesDB(std::string file_location)  {
	
	this->datadoc = rapidcsv::Document(file_location);
	this->recordCount = this->datadoc.GetRowCount();
	this->recordCursor = 0;
	this->sorting = "tatertable.refdate, tatertable.coordinate, tatertable.vector";
	this->searchTerm = "";
	
	//Create reference to the database
	try {
		this->dbConnection = pqxx::connection("postgresql://urist@localhost/potatoesDB");
		if (this->dbConnection.is_open())  {
			std::cout << "Opened database successfully: " << dbConnection.dbname() << std::endl;
		} 
	}
	catch (const std::exception &e)  {
		std::cout << "Failed to open, trying to recreate db" << std::endl;
	}
	
	//Since this is for learning and demonstration, for now I will recreate the database every time. 
	//Not prod friendly.
	this->initDb();
	this->initData();
}

/**
 * (re)creates dataset table
 */
void PotatoesDB::initDb()  {
	
	std::cout << "initializing database" << std::endl;
	pqxx::work table_transac(dbConnection);
	
	//tater table sequence
	try  {
		std::string tater_seq = 	"DROP SEQUENCE IF EXISTS public.tatertable_id_seq CASCADE; CREATE SEQUENCE public.tatertable_id_seq "
										"INCREMENT BY 1 "
										"MINVALUE 1 "
										"MAXVALUE 2147483647 "
										"START WITH 1 "
										"CACHE 1 "
										"NO CYCLE "
										"OWNED BY NONE;";
		table_transac.exec( tater_seq.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//set sequence owner
	try  {
		std::string alter_seq = "ALTER SEQUENCE public.tatertable_id_seq OWNER TO urist;";
		table_transac.exec( alter_seq.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//create tater table
	try  {
		std::string tater_table = 	"DROP TABLE IF EXISTS public.tatertable CASCADE; CREATE TABLE public.tatertable ( "
										"uomid integer NOT NULL, "
										"scalarid integer NOT NULL, "
										"dguid text NOT NULL, "
										"wasmodified integer NOT NULL, "
										"refdate integer NOT NULL, "
										"vector text NOT NULL, "
										"coordinate real NOT NULL, "
										"areaproductionvalue text NOT NULL, "
										"value numeric, "
										"status text, "
										"symbol text, "
										"terminated text, "
										"decimals integer NOT NULL, "
										"CONSTRAINT tatertable_pk PRIMARY KEY (refdate,vector,coordinate)"
									");";
		table_transac.exec( tater_table.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//table owner
	try  {
		std::string tater_owner = "ALTER TABLE public.tatertable OWNER TO urist;";
		table_transac.exec( tater_owner.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//uom table
	try  {
		std::string uom_table = "DROP TABLE IF EXISTS public.uom_table CASCADE; CREATE TABLE public.uom_table ( "
									"uom text NOT NULL, "
									"uomid integer NOT NULL, "
									"CONSTRAINT uom_pkey PRIMARY KEY (uomid)"
								");";
		table_transac.exec( uom_table.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//uom table owner
	try  {
		std::string uom_owner = "ALTER TABLE public.uom_table OWNER TO urist;";
		table_transac.exec( uom_owner.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//scalar table
	try  {
		std::string scalar_table = "DROP TABLE IF EXISTS public.scalar_table CASCADE; CREATE TABLE public.scalar_table ("
										"scalarfactor text NOT NULL, "
										"scalarid integer NOT NULL, "
										"CONSTRAINT scalar_pk PRIMARY KEY (scalarid)"
									");";
		table_transac.exec( scalar_table.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//scalar table owner
	try  {
		std::string scalar_owner = "ALTER TABLE public.scalar_table OWNER TO urist;";
		table_transac.exec( scalar_owner.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//geo table
	try  {
		std::string geo_table = "DROP TABLE IF EXISTS public.geo_table CASCADE; CREATE TABLE public.geo_table ("
									"geo text NOT NULL, "
									"dguid text NOT NULL, "
									"CONSTRAINT geo_pk PRIMARY KEY (dguid)"
								");";
		table_transac.exec( geo_table.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//geo table owner
	try  {
		std::string geo_owner = "ALTER TABLE public.geo_table OWNER TO urist;";
		table_transac.exec( geo_owner.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//modified table
	try  {
		std::string modified_table = 	"DROP TABLE IF EXISTS public.wasmodified_table CASCADE; CREATE TABLE public.wasmodified_table ("
											"wasmodified bool NOT NULL, "
											"modifiedid integer NOT NULL, "
											"CONSTRAINT modified_pk PRIMARY KEY (modifiedid) "
										");";
		table_transac.exec( modified_table.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//modified owner
	try  {
		std::string modified_owner = "ALTER TABLE public.wasmodified_table OWNER TO urist;";
		table_transac.exec( modified_owner.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//uom fk
	try  {
		std::string uom_fk = 	"ALTER TABLE public.tatertable ADD CONSTRAINT uom_fk FOREIGN KEY (uomid) "
									"REFERENCES public.uom_table (uomid) MATCH SIMPLE "
									"ON DELETE NO ACTION ON UPDATE NO ACTION;";
		table_transac.exec( uom_fk.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//scalar_fk
	try  {
		std::string scalar_fk = "ALTER TABLE public.tatertable ADD CONSTRAINT scalar_fk FOREIGN KEY (scalarid) "
									"REFERENCES public.scalar_table (scalarid) MATCH SIMPLE "
									"ON DELETE NO ACTION ON UPDATE NO ACTION;";
		table_transac.exec( scalar_fk.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//geo fk
	try  {
		std::string geo_fk = "ALTER TABLE public.tatertable ADD CONSTRAINT geo_fk FOREIGN KEY (dguid) "
								"REFERENCES public.geo_table (dguid) MATCH SIMPLE "
								"ON DELETE NO ACTION ON UPDATE NO ACTION;";
		table_transac.exec( geo_fk.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	//modified fk
	try  {
		std::string modified_fk = 	"ALTER TABLE public.tatertable ADD CONSTRAINT modified_fk FOREIGN KEY (wasmodified) "
										"REFERENCES public.wasmodified_table (modifiedid) MATCH SIMPLE "
										"ON DELETE NO ACTION ON UPDATE NO ACTION;";
		table_transac.exec( modified_fk.c_str() );
	}
	catch (const std::exception &e)  {
		std::cout << e.what() << std::endl;
		throw(e);
	}
	
	table_transac.commit();
}

void PotatoesDB::initData()  {
	
	std::cout << "initializing table data" << std::endl;
	
	//Create the modified table
	pqxx::work uom_work(dbConnection);
	std::string modified_insert = "INSERT INTO wasmodified_table (wasmodified, modifiedid) VALUES (false, 0) ON CONFLICT DO NOTHING;";
	uom_work.exec( modified_insert.c_str() );
	modified_insert = "INSERT INTO wasmodified_table (wasmodified, modifiedid) VALUES (true, 1) ON CONFLICT DO NOTHING;";
	uom_work.exec( modified_insert.c_str() );
	
	//rip through the dataset, creating the SQL for each line and running it.
	for(int i = 0; i < this->recordCount; ++i)  {
		std::vector<std::string> row = this->datadoc.GetRow<std::string>(i);
		
		//While this value /can/ be null, C++ doesn't like null doubles.
		std::string value = ( row[10].empty() ? "0.0" : row[10] );

		std::string uom_insert = std::string("INSERT INTO uom_table (uom, uomid) VALUES (") + "'" + row[4].c_str() + "', " + row[5].c_str() + ") ON CONFLICT DO NOTHING;";
		std::string geo_insert = std::string("INSERT INTO geo_table (geo, dguid) VALUES (") + "'" + row[1].c_str() + "', '" + row[2].c_str() + "') ON CONFLICT DO NOTHING;";
		std::string scalar_insert = std::string("INSERT INTO scalar_table (scalarfactor, scalarid) VALUES (") + "'" + row[6].c_str() + "', " + row[7].c_str() + ") ON CONFLICT DO NOTHING;";
		std::string tater_insert = 	std::string("INSERT INTO tatertable (uomid, scalarid, dguid, wasmodified, refdate, vector, coordinate, areaproductionvalue, value, status, symbol, terminated, decimals) VALUES (") +
										row[5].c_str() + ", " + row[7].c_str() + ", '" + row[2].c_str() + "', " + "0" + ", " + row[0].c_str() + ", '" + row[8].c_str() + "', " + 
										row[9].c_str() + ", '" + row[3].c_str() + "', " + value + ", '" + row[11].c_str() + "', '" + row[12].c_str() + "', '" + row[13].c_str() + "', " + row[14].c_str() +
									") ON CONFLICT DO NOTHING;";
		
		uom_work.exec( uom_insert.c_str() );
		uom_work.exec( geo_insert.c_str() );
		uom_work.exec( scalar_insert.c_str() );
		uom_work.exec( tater_insert.c_str() );
		
		//just to make it nice to look at while it inserts all the data.
		if( i % 100 == 0 )  { std::cout << std::endl; }
		(i % 10 == 0) ? std::cout << i : std::cout << ".";
		
	}
	
	uom_work.commit();
	
	//Get and print out the counts of each table.
	pqxx::nontransaction counting(dbConnection);
	pqxx::result uom_count( counting.exec( "SELECT COUNT(*) FROM uom_table;" ) );
	pqxx::result geo_count( counting.exec( "SELECT COUNT(*) FROM geo_table;" ) );
	pqxx::result sca_count( counting.exec( "SELECT COUNT(*) FROM scalar_table;" ) );
	pqxx::result rec_count( counting.exec( "SELECT COUNT(*) FROM tatertable;" ) );
	int uom = uom_count[0][0].as<int>();
	int geo = geo_count[0][0].as<int>();
	int scalar = sca_count[0][0].as<int>();
	int record = rec_count[0][0].as<int>();
	
	std::cout << std::endl;
	std::cout << "uom: " << uom << std::endl;
	std::cout << "geo: " << geo << std::endl;
	std::cout << "scalar: " << scalar << std::endl;
	std::cout << "records: " << record << std::endl;
	
}

/**
 * Displays a list of 100 records, depending on cursor location.
 * @return a vector of DTOs
 */
std::vector<PotatoesDTO*> PotatoesDB::getCurrentData()  {
	
	this->dtoList.clear();
			
	std::string select = std::string(	"select 	tatertable.refdate, geo_table.geo, tatertable.dguid, tatertable.areaproductionvalue, "
											"uom_table.uom, tatertable.uomid, scalar_table.scalarfactor, tatertable.scalarid, "
											"tatertable.vector, tatertable.coordinate, tatertable.value, tatertable.status, "
											"tatertable.symbol, tatertable.terminated, tatertable.decimals "
										"from tatertable "
										"inner join geo_table "
											"on tatertable.dguid = geo_table.dguid "
										"inner join uom_table "
											"on tatertable.uomid = uom_table.uomid "
										"inner join scalar_table "
											"on tatertable.scalarid = scalar_table.scalarid ") +
										this->searchTerm + std::string(" ") +
										std::string("order by ") + this->sorting +
										std::string(" limit 100 offset ") + std::to_string(this->recordCursor) + ";";
	
	//execute sql, store results in an object
	pqxx::nontransaction sel(dbConnection); 
	pqxx::result current_data( sel.exec(select.c_str()) );
	
	
	std::cout << "records from db: " << current_data.size() << std::endl;
	
	//rip through the results object, creating DTOs and adding them to the list.
	for (pqxx::result::const_iterator row = current_data.begin(); row != current_data.end(); row++)  {
		
		PotatoesDTO *tater = new PotatoesDTO();
		
		tater->setRefDate( row[0].as<int>() );
		tater->setGeo( row[1].as<std::string>() );
		tater->setDguid( row[2].as<std::string>() );
		tater->setAreaProductionValue( row[3].as<std::string>() );
		tater->setUom( row[4].as<std::string>() );
		tater->setUomId( row[5].as<std::string>() );
		tater->setScalarFactor( row[6].as<std::string>() );
		tater->setScalarId( row[7].as<std::string>() );
		tater->setVector( row[8].as<std::string>() );
		tater->setCoordinate( row[9].as<double>() );
		//Value is the only converted field that can be empty, which stod does not like.
		try  {
			tater->setValue( row[10].as<double>() );
		}
		catch(const std::invalid_argument& oops)  {
			tater->setValue( 0.0 );
		}
		tater->setStatus( row[11].as<std::string>() );
		tater->setSymbol( row[12].as<std::string>() );
		tater->setTerminated( row[13].as<std::string>() );
		tater->setDecimals( row[14].as<double>() );
		
		
		this->addDTO(tater);
	}
	
	return this->dtoList;
}

/**
 * Get a single record from the list
 * @return record DTO
 */
PotatoesDTO* PotatoesDB::getRecord(int index)  {
	return this->dtoList[index - 1];
}

/**
 * Add a record to the table
 * @param tater record DTO to add
 */
void PotatoesDB::addRecord(PotatoesDTO* tater)  {
	
	//this is so much better than it was. 
	
	pqxx::work data(dbConnection);
	
	//I could save on LOC by just using them in the big string concatenation below, 
	//but for the extra clarity I feel it's worth it.
	std::string uomid = tater->getUomId();
	std::string scaid = tater->getScalarId();
	std::string dguid = tater->getDguid();
	std::string wasmd = "1";
	int			refdt = tater->getRefDate();
	std::string vectr = tater->getVector();
	std::string	coord = std::to_string( tater->getCoordinate() );
	std::string arprv = tater->getAreaProductionValue();
	double 		value = tater->getValue();
	std::string sttus = tater->getStatus();
	std::string symbl = tater->getSymbol();
	std::string arnld = tater->getTerminated();
	int		 	decml = tater->getDecimals();
	
	//one great long concat.
	std::string tater_insert = 	std::string("INSERT INTO tatertable (uomid, scalarid, dguid, wasmodified, refdate, vector, coordinate, areaproductionvalue, value, status, symbol, terminated, decimals) VALUES (") +
										uomid.c_str() + ", " + scaid.c_str() + ", '" + dguid.c_str() + "', " + wasmd + ", " + std::to_string(refdt) + ", '" + vectr.c_str() + "', '" + 
										coord + "', '" + arprv.c_str() + "', " + std::to_string(value) + ", '" + sttus.c_str() + "', '" + symbl.c_str() + "', '" + arnld.c_str() + "', " + std::to_string(decml) +
									");";
	
	data.exec( tater_insert );
	data.commit();
	
	std::cout << "record added" << std::endl;
	
}

/**
 * Remove a record from the table
 * @param index of the record in the LIST to delete from the TABLE
 */
void PotatoesDB::deleteRecord(int index)  {
	
	//get the values for the compound key
	PotatoesDTO *tater = this->getRecord(index);
	std::string refdate = std::to_string( tater->getRefDate() );
	std::string vector = std::string("'") + tater->getVector() + std::string("'");
	std::string coord = std::to_string( tater->getCoordinate() );
	
	std::string sql =	std::string("DELETE FROM tatertable WHERE ") +
							std::string("refdate = ") + refdate +
							std::string(" AND vector = ") + vector +
							std::string(" AND coordinate = ") + coord +
						std::string(";");
	
	pqxx::work data(dbConnection);
	pqxx::result result( data.exec(sql.c_str()) );
	
	std::cout << "Rows affected: " << result.affected_rows() << std::endl;
	std::cout << sql << std::endl;
	
	data.commit();
	
}

/**
 * Advance through the dataset by 100 records.
 */
void PotatoesDB::nextSet()  {
	if(this->recordCursor + 100 > this->recordCount)  {
		this->recordCursor += this->recordCount - this->recordCursor;
	}
	else  {
		this->recordCursor += 100;
	}
}

/** 
 * backtrack through the dataset by 100 records.
 */
void PotatoesDB::previousSet()  {
	if(this->recordCursor - 100 < 1)  {
		this->recordCursor = 1;
	}
	else  {
		this->recordCursor -= 100;
	}
	
}

/**
 * Add a DTO to the list
 * @param potatoe DTO to add
 */ 
void PotatoesDB::addDTO(PotatoesDTO* tater)  {
	this->dtoList.push_back(tater);
}

/**
 * Get the record count.
 * @return record count
 */
int PotatoesDB::datasetCount()  {
	
	pqxx::nontransaction data(dbConnection);
	pqxx::result result( data.exec("SELECT COUNT(*) FROM tatertable;") );
	return result[0][0].as<int>();
}

/**
 * Undo all changes.
 */
void PotatoesDB::clearModified()  {
	
	//Delete all rows that were added to the set
	int pre_count = this->datasetCount();
	pqxx::work pre(dbConnection);
	pqxx::result result( pre.exec("DELETE FROM tatertable WHERE wasmodified = 1;") );
	pre.commit();
	
	//restore deleted rows
	this->initData();
	int post_count = abs( this->datasetCount() - pre_count );
	
	std::cout << "Added rows deleted: " << result.affected_rows() << std::endl;
	std::cout << "removed rows recovered: " << post_count << std::endl;
	
}


/**
 * Change the order records are displayed
 * @param string of comma separated columns to sort by
 */
void PotatoesDB::changeSorting(std::string order)  {
	
	this->sorting = order;
	std::cout << "sorting by: " << order << std::endl;
	
}


/**
 * Set the search term
 * @param hashmap with columns and the terms to search them for
 */
void PotatoesDB::search(std::map<std::string, std::string> column_search)  {
	
	//stop sorting?
	if( column_search.empty() )  {
		this->searchTerm = "";
		return;
	}
	
	//guess we sortin'
	//Craft a WHERE clause, casting everything to TEXT for simplicity
	std::string term = "WHERE ";
	std::map<std::string, std::string>::iterator i = column_search.begin();
	while( i != column_search.end() )  {
		term.append( i->first ); term.append("::TEXT ILIKE " );
		term.append("'"); term.append( i->second ); term.append("'::TEXT AND ");
		i++;
	}
	term.erase( term.size()-4 ); //remove trailing AND
	this->searchTerm = term;
	
}
