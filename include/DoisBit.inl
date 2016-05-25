#ifndef _UMBIT_HPP_
#define _UMBIT_HPP_

#include "Erro.hpp"

/*
*	@brief 		
*	@param 		
*	@return 	
*/
void DoisBit::run(int &argc, const char *argv[]) {
	if(argc != 3) {
		throw(Erro(Erro::Type::ArquivoNaoFoiAberto));
	}

	std::string nomeArquivo = argv[1];

  	this->lerArquivo(nomeArquivo);
  	this->predicao();
}

/*
*	@brief 		
*	@param 		
*	@return 	
*/
bool DoisBit::predicao(std::string nomeArquivo) {
	
	std::ifstream fileIn;
	fileIn.open(nomeArquivo);

	if(!fileIn.good() && fileIn.is_open()) {
		throw(Erro(Erro::Type::ArquivoNaoPedeSerLido));
	}

	int quantos = 0
	std::string linha;
	for( int k = 0; !fileIn.eof() && !fileIn.fail() && k < tamanhoSaltos(); k++) {
		std::getline(fileIn, linha);
		this->extrairSalto(linha, matrizSaltos[k]);
	}
}

/*
*	@brief 		
*	@param 		
*	@return 	
*/
void DoisBit::extrairSalto(std::string linha, int &k, vector<int> & salto) {
	long int x = 1;
	salto = std::vector<std::string>(linha.size());
	salto[0] = 0;
	bool lendoCorrelacao = true;
	for(int i = 0; i < linha.size(); i++) {
		if(lendoCorrelacao) {
			if(linha[i] == ' ')
        		lendo_correlacao = false; // terminou de ler correlação e vai começar com as interações
       		else {
        		salto[0] += linha[i]; // convertendo de caractere para inteiro
       		}
		}
		else {

        	salto[x] = linha[i];
      		x++;
		}
	}
}

void DoisBit::preditor() {}

void DoisBit::clear() {
	for(int i = 0; i < matrizSaltos.size(); i++) {
		matrizSaltos.~vector();
	}
}

#endif