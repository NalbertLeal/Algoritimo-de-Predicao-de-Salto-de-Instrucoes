#include <string>
#include <vector>
#include <iostream>

#include "Erro.hpp"
#include "DoisBit.hpp"

int main(int argc, char const *argv[])
{
	try{
		DoisBit dois("T");
		dois.run(argc, argv);
	}
	catch(Erro erro) {
		erro.what();
	}
	return 0;
}