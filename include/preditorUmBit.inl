#ifndef _PREDITORUMBIT_INL_
#define _PREDITORUMBIT_INL_

#include <iostream>
#include <fstream>
#include <string>

#include "preditorUmBit.hpp"

/*!
*   @brief    A função run()
*   @param    argc    Esse parametro recebe o parametro inteiro argc do main.
*   @param    argv[]  Esse parametro recebe o parametro array de char argv[] do main.
*   @return   
*/
void UmBit::run(int &argc, const char *argv[]) {
  if(argc != 2) {
    throw(Erro(Erro::Type::ArquivoNaoFoiAberto)); // falha de arquivo não aberto
    // exit(1);
  }

  this->matriz = new int*[4]; // São 3 correlações mais o primeiro salto que não possui correlação.
                              // descobrir um modo de pegar o numero de correlações que serão feitas.

   for(int x = 0; x < 3;x++)
    matriz[x] = nullptr;

   int quantas = this->tokenizar( nome); // faz a leitura e a extração dos dados para o arquivo
    Preditor preditor(matriz, quantas+1, 2);
    preditor.processar();

   for(int x = 0; x < 4; x++);
    //delete [] matriz[x]; // liberando memória

  std::string nomeArquivo = argv[1];

  this->lerArquivo(nomeArquivo);
  this->predicao();
}

/*!
*   @brief    A função lerArquivo() recebe por parametro o nome do arquivo de entrada, abre esse arquivo e coloca todo o contudo desse arquivo dentro de uma variavel string que esta dentro da classe UmBit.
*   @param    nomeArquivo   Esse parametro recebe o valor do nome do arquivo que deverá ser aberto.
*   @return   Essa função não possui retorno.
*/
void UmBit::lerArquivo(std::string nomeArquivo) {
  std::ifstream fileIn;
  fileIn.open(nomeArquivo);

  if(!fileIn.is_open() || !fileIn.good()) {
    throw(Erro(Erro::Type::ArquivoNaoAouC)); // falha de arquivo não aberto ou corrompido
    // exit(1);
  }

  std::string line = "";
  int x = 0;
  for(x=0; !fileIn.eof(); e++) {
    std::getline(fileIn, line);
    this->tokenizar(matriz);
    this->extrair_saltos(linha, matriz[x]);
  }

  fileIn.close();
}

int tokenizar(int **&matriz) {

  int x = 0; // essa vriavel coloca os saltos em suas posições na matriz
  int quantos; // guarda quantas interaçãoes esses saltos vão ter
  while(!arquivo.fail() && x < 4) { // esse loop vai percorrer linha a linha do arquivo lendo até 4 saltos
    std::getline(arquivo, linha); // lendo a linha e guardando na string linha
    quantos = extrair_saltos(linha, matriz[x]); // extraindo todos os numeros encontratos na linha e armazenando na matriz
    x++;
  }
}

  this->arquivo = line;
}

/*!
*   @brief    Esse função controla a execução do codigo que faz a predição de salto. Para executala é importante que antes o arquivo de entrada ja tenha sido lido.
*   @return   Essa função não possui retorno.
*/
void UmBit::predicao() {
  std::cout << "" ;
}


#endif
