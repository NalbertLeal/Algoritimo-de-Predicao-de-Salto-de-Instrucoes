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

	std::cout << "\n\n>>> size resultadosPredicoes : " << resultadosPredicoes.size() << std::endl;
	std::cout << "\n\n>>> resultados : \n";

	size_t o = 0;
	// imprime na tela do usuario oque foi lido
	for(int u = 0; u < matrizSaltos.size(); u++) {
		std::vector<std::string> s = resultadosPredicoes[u];
		std::cout << " [ " ;
		for(int y = 0; y < s.size(); y++) {
			std::cout << s[o][y];
		}
		std::cout << " ] \n\n";
		o++;
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
		// o size de resultadosPredicoes[counter1] é igual a sizeVectorU-1 pois o primeiro elemento de matrizSaltos[u] é referente a correlação
		this->resultadosPredicoes[counter1] = std::vector<std::string>(sizeVectorU-1);
		// this->resultadosPredicoes[counter2] armazena a o resultado se oque está em this->resultadosPredicoes[counter1] é igual ou não a this->matrizSaltos[u]
		// o size de resultadosPredicoes[counter1] é igual a sizeVectorU-1 pois o primeiro elemento de matrizSaltos[u] é referente a correlação
		this->resultadosPredicoes[counter2] = std::vector<std::string>(sizeVectorU-1);
		// se entrar nesse if esse salto não possui correlação
		std::cout << ">>> size resultatdos[counter1] = " << resultadosPredicoes[counter1].size() << std::endl;
		std::cout << ">>> size resultatdos[counter2] = " << resultadosPredicoes[counter2].size() << std::endl;
		if(matrizSaltos[u][0] == "0") {
			// esse for analiza cada uma das strings
			for(int k = 1; k < sizeVectorU && matrizSaltos[u][k] != ""; k++) {
				// adiciona oque se espara nesse salto a previsão
				std::cout << ">>> toma: " << toma << "\n";
				std::cout << ">>> bitMuda: " << bitMuda << "\n";
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
						bitMuda == true;
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
			// 	string que armazana temporariamente a correlação pega no arquivo.
			std::string correlacao = matrizSaltos[u][0];
			//	vectorCorrelacao armazena cada a correlacão que esse salto tem.
			std::vector<std::string> vectorCorrelacao(correlacao.size());
			// esse counter3 será utilizado para adicionar cada char do numero da correlação na posição correta do vectorCorrelacao.
			int counter3 = 0;
			// esse FOR analiza a correlação do salto
			for(size_t r = 0; r < correlacao.size(); r++) {
				std::string temp = "";
				// esse FOR pega cada um dos char de um salto da correlação e os coloca na string temp
				for(size_t y = r; correlacao[y] != '/' && y < correlacao.size(); y++) {
					temp = temp + correlacao[y];
					r++;
				}
				r--;
				vectorCorrelacao[counter3] = temp;
				counter3++;
			}

			// resize de vectorCorrelacao para ter o tamanho exato do vector com a quantidade exata de correlações.
			//vectorCorrelacao.resize(counter3);

			// agora o salto com correlação sera analizado. OBS.: sem a correlação.
			for(int k = 1; k < sizeVectorU && matrizSaltos[u][k] != ""; k++) {
				// adiciona oque se espara nesse salto a previsão
				resultadosPredicoes[counter1][k-1] = toma;
				// se entrar nesse if matrizSaltos[u][k] armazena o valor "T".
				if(matrizSaltos[u][k] == "T") {
					// se entrar nesse if a previsão esta correta armazena o valor "T".
					if(toma == "T") {
						//	adiciona um "A" para indicar que a previsão esta correta.
						resultadosPredicoes[counter2][k-1] = "A";
						bitMuda == true;
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
				// se não entrou no if vai entrar no else pois matrizSaltos[u][k] armazena o valor "F"
				else{
					// se entrar nesse if a previsão esta correta armazena o valor "T"
					if(toma == "N") {
						//	adiciona um "A" para indicar que a previsão esta correta.
						resultadosPredicoes[counter2][k-1] = "A";
						bitMuda == true;
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

			std::string aux = vectorCorrelacao[0];
			// se aux == "0" então não existe correlação
			if(aux != "0") {
				// agora as correlações serão adicionadas
				for(size_t i = 0; i < sizeVectorU && vectorCorrelacao[i] != ""; i++) {
					aux = vectorCorrelacao[i];
					size_t auxInt = std::stoi(aux);
					if((resultadosPredicoes[auxInt-1][i] == "T" && resultadosPredicoes[auxInt][i] == "A") || (resultadosPredicoes[auxInt][i] == "--" && resultadosPredicoes[auxInt-1][i] == "--")) {
						resultadosPredicoes[counter1][i] = "--";
						resultadosPredicoes[counter2][i] = "--";
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
	std::cout << "\n\n>>> size resultadosPredicoes : " << resultadosPredicoes.size() << std::endl;
}

void DoisBit::clear() {
	matrizSaltos.clear();
}

#endif
