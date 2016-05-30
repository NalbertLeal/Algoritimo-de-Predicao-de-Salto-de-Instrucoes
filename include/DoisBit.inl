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

  	std::cout << "\n\n>>> size matrizSaltos : " << matrizSaltos.size() << std::endl;

  	// imprime na tela do usuario oque foi lido
	for(int u = 0; u < matrizSaltos.size(); u++) {
		std::cout << " [ ";
		std::vector<std::string> s = matrizSaltos[u];
		for(int y = 0; y < s.size(); y++) {
			std::cout << s[y] << " ";
		}
		std::cout << " ]\n";
	}

	std::cout << "\n\n>>> size resultadosPredicoes : " << resultadosPredicoes.size() << std::endl;
	std::cout << "\n\n>>> resultados : \n";

	// imprime na tela do usuario oque foi lido
	for(int u = 0; u < resultadosPredicoes.size(); u++) {
		std::vector<std::string> s = resultadosPredicoes[u];
		std::cout << " [ " ;
		for(int y = 0; y < s.size(); y++) {
			std::cout << s[y] << " ";
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
		std::cout << sizeVectorU << "\n"; // sizeVectorU = 0; DESCOBRIR O PQ !!!!
		// this->resultadosPredicoes[counter1] armazena a previsão doque o algoritimo acha que vai acontecer no salto
		// o size de resultadosPredicoes[counter1] é igual a sizeVectorU-(matrizSaltos[u][0].size()) pois o primeiro elemento de matrizSaltos[u] é referente a correlação, e a quantidade de elementos da correlação deve ser subtraida do size da linha.
		this->resultadosPredicoes[counter1] = std::vector<std::string>(sizeVectorU-(matrizSaltos[u][0].size()));
		// this->resultadosPredicoes[counter2] armazena a o resultado se oque está em this->resultadosPredicoes[counter1] é igual ou não a this->matrizSaltos[u]
		// o size de resultadosPredicoes[counter2] é igual a sizeVectorU-(matrizSaltos[u][0].size()) pois o primeiro elemento de matrizSaltos[u] é referente a correlação, e a quantidade de elementos da correlação deve ser subtraida do size da linha.
		this->resultadosPredicoes[counter2] = std::vector<std::string>(sizeVectorU-(matrizSaltos[u][0].size()));
		// se entrar nesse if esse salto não possui correlação
		std::cout << ">>> size resultatdos[counter1] = " << resultadosPredicoes[counter1].size() << std::endl;
		std::cout << ">>> size resultatdos[counter2] = " << resultadosPredicoes[counter2].size() << std::endl;
		toma = this->tomado;
		if(matrizSaltos[u][0] == "0") {
			// esse for analiza cada uma das strings
			for(int k = 1; k < sizeVectorU && matrizSaltos[u][k] != ""; k++) {
				// adiciona oque se espara nesse salto a previsão
				resultadosPredicoes[counter1][k-1] = toma;
				// se entrar nesse if matrizSaltos[u][k] armazena o valor "T".
				if(matrizSaltos[u][k] == "T") {
					// se entrar nesse if a previsão esta correta armazena o valor "T".
					if(toma == "T") {
						//	adiciona um "A" para indicar que a previsão esta correta.
						resultadosPredicoes[counter2][k-1] = "A";
						bitMuda = true;
					}
					// se não entrou no if a previsão estava errada, então entra no else
					else {
						// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
						if(bitMuda == true) {
							//	adiciona um "A" para indicar que a previsão esta errada.
							resultadosPredicoes[counter2][k-1] = "E";
							bitMuda = false;
						}
						// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
						else{
							//	adiciona um "A" para indicar que a previsão esta errada.
							resultadosPredicoes[counter2][k-1] = "E";
							bitMuda = true;
							toma = "T";
						}
					}
				}
				// se não entrou no if vai entrar no else pois matrizSaltos[u][k] armazena o valor "N", ou seja "não tomado"
				else{
					// se entrar nesse if a previsão esta correta armazena o valor "T"
					if(toma == "N") {
						//	adiciona um "A" para indicar que a previsão esta correta.
						resultadosPredicoes[counter2][k-1] = "A";
						bitMuda = true;
					}
					// se não entrou no if a previsão estava errada, então entra no else
					else {
						// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
						if(bitMuda == true) {
							//	adiciona um "A" para indicar que a previsão esta errada.
							resultadosPredicoes[counter2][k-1] = "E";
							bitMuda = false;
						}
						// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
						else{
							//	adiciona um "A" para indicar que a previsão esta errada.
							resultadosPredicoes[counter2][k-1] = "E";
							bitMuda = true;
							toma = "N";
						}
					}
				}
			}
		}
		// se não entrou no if significa que possui correlação, então entrará no else
		else {
			for(size_t p = 0; p < matrizSaltos[u][0].size(); p++) {
				if(matrizSaltos[u][0][p] == '/') {
					continue;
				}
				std::string saltoDaCorrelacao = "";
				for(size_t l = 0; l < matrizSaltos[u][0].size() && matrizSaltos[u][0][l] != '/'; l++) {
					saltoDaCorrelacao = saltoDaCorrelacao + matrizSaltos[u][0][l];
					p++;
				}

				size_t intSaltoDaCorrelacao = std::stoi(saltoDaCorrelacao);

				std::cout << ">>> saltoDaCorrelacao: " << saltoDaCorrelacao << "\n";

				// esse for analiza cada uma das strings
				for(int k = 1; k < sizeVectorU && matrizSaltos[u][k] != ""; k++) {
					
					// deixa nulo a celula pois não ah pq fazer o teste por conta da correlação.
					if(saltoDaCorrelacao != "0") {
						//if((resultadosPredicoes[intSaltoDaCorrelacao-1][k-1] == "T") && (resultadosPredicoes[intSaltoDaCorrelacao][k-1] == "A")) {
						if((matrizSaltos[intSaltoDaCorrelacao-1][k-1] == "T")) {
							resultadosPredicoes[counter1][k-1] = "-";
							resultadosPredicoes[counter2][k-1] = "-";
							continue;
						}
						else if((resultadosPredicoes[intSaltoDaCorrelacao-1][k-1] == "--") && (resultadosPredicoes[intSaltoDaCorrelacao][k-1] == "--")) {
							resultadosPredicoes[counter1][k-1] = "-";
							resultadosPredicoes[counter2][k-1] = "-";
							continue;
						}
					}
					
					// adiciona oque se espara nesse salto a previsão
					resultadosPredicoes[counter1][k-1] = toma;
					// se entrar nesse if matrizSaltos[u][k] armazena o valor "T".
					if(matrizSaltos[u][k] == "T") {
						// se entrar nesse if a previsão esta correta armazena o valor "T".
						if(toma == "T") {
							//	adiciona um "A" para indicar que a previsão esta correta.
							resultadosPredicoes[counter2][k-1] = "A";
							bitMuda = true;
						}
						// se não entrou no if a previsão estava errada, então entra no else
						else {
							// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
							if(bitMuda == true) {
								//	adiciona um "A" para indicar que a previsão esta errada.
								resultadosPredicoes[counter2][k-1] = "E";
								bitMuda = false;
							}
							// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
							else{
								//	adiciona um "A" para indicar que a previsão esta errada.
								resultadosPredicoes[counter2][k-1] = "E";
								bitMuda = true;
								toma = "T";
							}
						}
					}
					// se não entrou no if vai entrar no else pois matrizSaltos[u][k] armazena o valor "N", ou seja "não tomado"
					else{
						// se entrar nesse if a previsão esta correta armazena o valor "T"
						if(toma == "N") {
							//	adiciona um "A" para indicar que a previsão esta correta.
							resultadosPredicoes[counter2][k-1] = "A";
							bitMuda = true;
						}
						// se não entrou no if a previsão estava errada, então entra no else
						else {
							// se entrar nesse if é porque este é o primeiro erro e bitMuda recebe false.
							if(bitMuda == true) {
								//	adiciona um "A" para indicar que a previsão esta errada.
								resultadosPredicoes[counter2][k-1] = "E";
								bitMuda = false;
							}
							// se não entrou no if é porque este é o segundo erro e bitMuda recebe true e a proxima previsão será para o contrario.
							else{
								//	adiciona um "A" para indicar que a previsão esta errada.
								resultadosPredicoes[counter2][k-1] = "E";
								bitMuda = true;
								toma = "N";
							}
						}
					}
				}

			}
		}
		for(size_t op = 0; op < resultadosPredicoes[counter1].size(); op++)
			std::cout << resultadosPredicoes[counter1][op] << " ";
		std::cout << "\n";
		for(size_t op = 0; op < resultadosPredicoes[counter1].size(); op++)
			std::cout << resultadosPredicoes[counter2][op] << " ";
		std::cout << "\n";

		counter1 += 2;
		counter2 += 2;
	}
}

void DoisBit::clear() {
	matrizSaltos.clear();
}

#endif
