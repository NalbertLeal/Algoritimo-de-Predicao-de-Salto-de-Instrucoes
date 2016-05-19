#ifndef _PREDITORUMBIT_INL_
#define _PREDITORUMBIT_INL_

#include <iostream>
#include <fstream>

#include "preditorUmBit.hpp"

/*!
*   @brief
*   @param
*   @return
*/
void UmBit::run(int &argc, const char *argv[]) {
  if(argc != 2) {
    throw(Erro(Erro::Type::ArquivoNaoFoiAberto)); // falha de arquivo não aberto
    exit(1);
  }

  std::string nomeArquivo = argv[1];

  this->lerArquivo(nomeArquivo);

}

/*!
*   @brief
*   @param
*   @return
*/
void UmBit::lerArquivo(std::string nomeArquivo) {
  std::ifstream fileIn;
  fileIn.open(nomeArquivo);

  if(!fileIn.is_open() || !fileIn.good()) {
    throw(Erro(Erro::Type::ArquivoNaoAouC)); // falha de arquivo não aberto ou corrompido
    exit(1);
  }

  std::string line = "";
  while(!fileIn.eof()) {
    std::getline(fileIn, line);
    this->arquivo = line;
  }

  fileIn.close();
}

/*!
*   @brief
*   @return
*/
void UmBit::predicao() {

}


#endif
