#ifndef _PREDITORUMBIT_HPP_
#define _PREDITORUMBIT_HPP_

#include <iostream>
#include <fstream>
#include <string>

class UmBit {
  public:
    Umbit(bool valorInicial) : valorInicial(valorInicial) {}

    bool predicao();
    void lerArquivo(std::string nomeArquivo);
    void run(int &argc, const char *argv[]);

  private:
    std::string arquivo;  //  string que armazena tudo que foi lido do arquivo
    bool toma;            //  booleano que controla o preditor
    bool valorInicial;    //  valor inicial da previsão
};

#include "preditorUmBit.inl"

#endif
