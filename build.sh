#!/bin/bash

g++ ./ProjectMain.cpp ./model/PotatoesDTO.cpp ./model/PotatoesModel.cpp ./model/DTOList.cpp ./model/PotatoesDB.cpp ./view/PotatoesView.cpp ./controller/PotatoesController.cpp -L/usr/local/lib -lpqxx -lpq -o ProjectMain -Wall -g 
	echo "project built"
#g++ ./model/PotatoesDTO.cpp ./model/PotatoesModel.cpp ./model/DTOList.cpp ./model/PotatoesDB.cpp ./view/PotatoesView.cpp ./controller/PotatoesController.cpp ./tests/PotatoesTest_AddDTO_db.cpp -L/usr/local/lib -lpqxx -lpq -o ProjectTest -Wall -g
#	echo "test built"
