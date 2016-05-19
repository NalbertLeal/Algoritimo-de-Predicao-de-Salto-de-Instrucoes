#include <iostream>
#include <stdlib.h>

#include "preditorUmBit.hpp"

/*!
*   @brief		Essa é a função main, é nela que o codigo vai rodar.
*   @param 		argc 	Esse parametro é um inteiro que armazena a quantidade de valores passados por parametro para o programa.
*   @param 		argv[] 	Esse parametro é um array que possui os valores passados por referência para o programa.
*   @return		O retorno é EXIT_SUCCESS se o codigo tiver rodado sem problemas e EXIT_FAILURE se ocorreu algum erro durante a execução.
*/
main(int argc, char const *argv[])
{
	try{
		UmBit bit(true);
		bit.run(argc, argv);
	}
	catch(Erro err) {
		std::cout << err.what();
		return EXIT_FAILURE; 
	}
	
	return EXIT_SUCCESS;
}