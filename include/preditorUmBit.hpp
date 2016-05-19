#ifndef _PREDITORUMBIT_HPP_
#define _PREDITORUMBIT_HPP_

#include <iostream>
#include <fstream>
#include <string>

#include "erro.hpp"

/*!
*   @brief		A classe UmBit cria objetos para fazer a predição de salto
*/
class UmBit {
  public:
    UmBit(bool valorInicial = false) : valorInicial(valorInicial)  {}
    ~UmBit() {}

    //	A função run() é responsavel por controlar a ordem de execução das funções da classe UmBit.
    void run(int &argc, const char *argv[]);

  private:
  	//  A variavel arquivo é do tipo string que armazena tudo que foi lido do arquivo.
    std::string arquivo;  
    //  A tomado  booleano que controla o preditor
    bool tomado;
    //  A variavel valorInicial armazena o valor inicial da previsão quando o objeto dessa classe é criado.
    bool valorInicial;
    // **matriz
    int **matriz;

    // As funções abaixo são privadas e somente podem ser lidas dentro dessa classe.

    //	A função predicao() controla a execução da predição de salto.
    void predicao();
    //	A função lerArquivo() controla a execução da abetura e leitura do arquivo de leitura que foi passado por parametro.
    void lerArquivo(std::string);
    // A função tokenizar() faz a tokenização dos dados do arquivo
    int tokenizar(int **&matriz);
    // A função extrairSaltos() extria s saltos
    int extrair_saltos(std::string bruto, int *&saltos);
};

#include "preditorUmBit.inl"

#endif
