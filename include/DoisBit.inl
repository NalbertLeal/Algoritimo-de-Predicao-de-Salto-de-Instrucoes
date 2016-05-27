#ifndef _UMBIT_INL_
#define _UMBIT_INL_

#include <vector>
#include <string>
#include <fstream>

#include "DoisBit.hpp"
#include "Erro.hpp"

/*
*	@brief 		
*	@param 		
*	@return 	
*/
void DoisBit::run(int &argc, char const *argv[]) {
	if(argc != 3) {
		throw(Erro(Erro::Type::ArquivoNaoFoiAberto));
	}

	std::string nomeArquivo = argv[1];

  	this->lerArquivo(nomeArquivo);
  	this->preditor();

  	// imprime na tela do usuario oque foi lido
	for(int u = 0; u < matrizSaltos.size(); u++) {
		std::vector<std::string> s = matrizSaltos[u];
		for(int y = 0; y < s.size(); y++) {
			std::cout << s[y] << std::endl;
		}
	}

	std::cout << "\n\n>>> resultados : \n";

	// imprime na tela do usuario oque foi lido
	for(int u = 0; u < matrizSaltos.size(); u++) {
		std::vector<std::string> s = resultadosPredicoes[u];
		std::cout << " [ " ;
		for(int y = 0; y < s.size(); y++) {
			std::cout << s[y];
		}
		std::cout << " ] \n\n";
	}
}

/*
*	@brief 		
*	@param 		
*	@return 	
*/
void DoisBit::lerArquivo(std::string nomeArquivo) {

	std::ifstream fileIn;
	fileIn.open(nomeArquivo);

	if(!fileIn.good() && fileIn.is_open()) {
		throw(Erro(Erro::Type::ArquivoNaoPedeSerLido));
	}

	int quantos = 0;
	std::string linha;
	for( int k = 0; !fileIn.eof() && !fileIn.fail() && k < matrizSaltos.size(); k++) {
		std::getline(fileIn, linha);
		this->extrairSalto(linha, matrizSaltos[k]);
	}

}

/*
*	@brief 		
*	@param 		
*	@return 	
*/
void DoisBit::extrairSalto(std::string linha, std::vector<std::string> & salto) {
	long int x = 1;
	salto = std::vector<std::string>(linha.size());
	salto[0] = "0";
	bool lendo_correlacao = true;
	for(int i = 0; i < linha.size(); i++) {
		if(lendo_correlacao) {
			if(linha[i] == ' ')
        		lendo_correlacao = false; // terminou de ler correlação e vai começar com as interações
       		else {
       			if(linha[i] == '-') {
       				continue;
       			}
       			else if(salto[0][0] == '0') {
       				salto[0] = linha[i];
       			}
       			else {
       				salto[0] += linha[i]; // convertendo de caractere para inteiro
       			}
       		}
		}
		else {
        	salto[x] = linha[i];
      		x++;
		}
	}
}

void DoisBit::preditor() {
	std::string toma = this->tomado;
	bool bitMuda = true;
	int counter1 = 0, counter2 = 1;

	for(int u = 0; u < this->matrizSaltos.size(); u++) {
		int sizeVectorU = this->matrizSaltos[u].size();
		// this->resultadosPredicoes[counter1] armazena a previsão doque o algoritimo acha que vai acontecer no salto
		// o size de resultadosPredicoes[counter1] é igual a sizeVectorU-1 pois o primeiro elemento de matrizSaltos[u] é referente a correlação
		this->resultadosPredicoes[counter1] = std::vector<std::string>(sizeVectorU-1);
		// this->resultadosPredicoes[counter2] armazena a o resultado se oque está em this->resultadosPredicoes[counter1] é igual ou não a this->matrizSaltos[u]
		// o size de resultadosPredicoes[counter1] é igual a sizeVectorU-1 pois o primeiro elemento de matrizSaltos[u] é referente a correlação
		this->resultadosPredicoes[counter2] = std::vector<std::string>(sizeVectorU-1); 
		counter1++;
		counter2++;
		// se entrar nesse if esse salto não possui correlação
		if(matrizSaltos[u][0] == "0") {
			// esse for analiza cada uma das strings
			for(int k = 1; k < sizeVectorU; k++) {
				// se entrar nesse if matrizSaltos[u][k] armazena o valor "T"
				if(matrizSaltos[u][k] == "T") {
					// se entrar nesse if a previsão esta correta armazena o valor "T"
					if(toma == "T") {
						bitMuda == true;
					}
					// se não entrou no if a previsão estava errada, então entra no else
					else {
						// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
						if(bitMuda == true) {
							bitMuda = false;
						}
						// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
						else{
							bitMuda = false;
							toma = "F";
						}
					}
				}
				// se não entrou no if vai entrar no else pois matrizSaltos[u][k] armazena o valor "F"
				else{
					// se entrar nesse if a previsão esta correta armazena o valor "T"
					if(toma == "F") {
						bitMuda == true;
					}
					// se não entrou no if a previsão estava errada, então entra no else
					else {
						// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
						if(bitMuda == true) {
							bitMuda = false;
						}
						// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
						else{
							bitMuda = false;
							toma = "T";
						}
					}
				}
			}
		}
		else {
			// esse for analiza cada uma das strings
			for(int k = 1; k < sizeVectorU; k++) {
				std::string correlacao = matrizSaltos[u][0];
				std::vector<std::string> vectorCorrelacao(correlacao.size());
				int counter3 = 0;
				for(int r = 0; r < correlacao.size(); r++) {
					if(counter3 == 0) {
						vectorCorrelacao[counter3] = "";
					}
					if(correlacao[r] == '/') {
						counter3 = 0;
					}
					else {
						vectorCorrelacao[counter3] = vectorCorrelacao[counter3] + correlacao[r];
						counter3++;
					}
				}
				if(1 < correlacao.size()) {}
			}
		}
	}
}

void DoisBit::clear() {
	matrizSaltos.clear();
}

#endif