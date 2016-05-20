#ifndef _PREDITORUMBIT_INL_
#define _PREDITORUMBIT_INL_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "preditorUmBit.hpp"

/*!
*   @brief    A função run()
*   @param    argc    Esse parametro recebe o parametro inteiro argc do main.
*   @param    argv[]  Esse parametro recebe o parametro array de char argv[] do main.
*   @return   Essa função não possui retorno.
*/
void UmBit::run(int &argc, const char *argv[]) {
  if(argc != 2) {
    throw(Erro(Erro::Type::ArquivoNaoFoiAberto)); // falha de arquivo não aberto
    // exit(1);
  }

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

  for(int x = 0; x < 3 || x < tamanhoSaltos();x++) {
    this->saltos[x] = nullptr;
  }

  std::string linha = "";
  int quantos = 0;
  int k = 0;
  for(k=0; !fileIn.eof() && !fileIn.fail() && k < tamanhoSaltos(); k++) {
    std::getline(fileIn, linha);
    quantos = this->extrair_saltos(linha, saltos[k]);
  }

  for(int x = 0; x < tamanhoSaltos(); x++)
    this->resultados[x] = new int[quantos];

  fileIn.close();
}

/*!
*   @brief    Esse função controla a execução do codigo que faz a predição de salto. Para executala é importante que antes o arquivo de entrada ja tenha sido lido.
*   @param    linha   Esse parametro recebe alinha que deverá ser tratada.
*   @param    salto  Esse parametro recebe uma das posições do vector de ponteiros de inteiros Matriz. 
*   @return   Essa função não possui retorno.
*/
int UmBit::extrair_saltos(std::string linha, int *&salto) {
  salto = new int[linha.size()]; // alocando espaço para todas as interações
  salto[0] = 0; // esse elemento representa a correlação do salto
  int x = 1; // variável de controle para o vetor de saltos
  bool lendo_correlacao = true; // esse booleano controla se a correlação está sendo lida nesse momento
   for(int i = 0; linha[i] != '\0'; i++)  { // percorrer todos os caracteres
    if(lendo_correlacao) {//  verificar se o o salto tem correlação
      if(linha[i] == '-') { // caso não aja correlação de salto
        salto[0] = 0; // não tem correlação com ninguem
      }
      else {
       if(linha[i] == ' ')
        lendo_correlacao = false; // terminou de ler correlação e vai começar com as interações
       else {
        if(linha[i] == '/') salto[0] *= 10; // abrindo espaço para por a nova correlação
        else salto[0] += linha[i] - '0'; // convertendo de caractere para inteiro
       }
      }
    }
    else { // caso o caracter atual NÃO seja um numero porem o ultimo caracter lido era um numero
      if(linha[i] == 'T')
        salto[x] = 1;
      else
        salto[x] = 0;
      x++;
    }
  }
  return x;
}

/*!
*   @brief    Esse função controla a execução do codigo que faz a predição de salto. Para executala é importante que antes o arquivo de entrada ja tenha sido lido.
*   @return   Essa função não possui retorno.
*/
void UmBit::predicao() {
  std::cout << "" ;
}


#endif
