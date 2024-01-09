



ProjectMain : ./ProjectMain.cpp ./model/PotatoesDTO.cpp ./model/PotatoesModel.cpp ./model/DTOList.cpp ./view/PotatoesView.cpp ./controller/PotatoesController.cpp
	g++ ./ProjectMain.cpp ./model/PotatoesDTO.cpp ./model/PotatoesModel.cpp ./model/DTOList.cpp ./model/PotatoesDB.cpp ./view/PotatoesView.cpp ./controller/PotatoesController.cpp -L/usr/local/lib -lpqxx -lpq -o ProjectMain -Wall -g 

