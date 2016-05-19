#ifndef _PREDITORUMBIT_HPP_
#define _PREDITORUMBIT_HPP_

#include <iostream>
#include <fstream>
#include <string>

/*!
*   @brief		A classe UmBit cria objetos para fazer a predição de salto
*/
class DoisBit {
  public:
    DoisBit(bool valorInicial = false) : valorInicial(valorInicial)  {}
    ~DoisBit() {}
    //	A função predicao() controla a execução da predição de salto.
    void predicao();
    //	A função lerArquivo() controla a execução da abetura e leitura do arquivo de leitura que foi passado por parametro.
    void lerArquivo(std::string nomeArquivo);
    //	A função run() é responsavel por controlar a ordem de execução das funções da classe UmBit.
    void run(int &argc, const char *argv[]);

  private:
  	//  A variavel arquivo é do tipo string que armazena tudo que foi lido do arquivo.
    std::string arquivo;  
    //  A tomado  booleano que controla o preditor
    bool tomado;            
    bool valorInicial;    //  valor inicial da previsão
};

#include "preditorUmBit.inl"

#endif
