#ifndef _UMBIT_HPP_
#define _UMBIT_HPP_

#include <vector>
#include <string>

#include "Erro.hpp"

/*
*	@brief 		
*	@param 		
*	@return 	
*/
class DoisBit {
	public:
		DoisBit(bool valorInicial) :
		tomado(valorInicial)
		{
			matrizSaltos.resize(4);
		}

		~DoisBit()
		{
			this->clear();
		}

		void run(int &argc, const char *argv[]);
	private:
		bool predicao();
		void lerArquivo(std::string);
		int extrairSalto(std::string);

		void preditor();

		void clear();

		// variaveis

		// valor inicial da predição
		bool tomado;
		// matriz de vector que armqzena os resultados das predições
		std::vector<std::vector<std::string>> matrizSaltos;
};

#include "DoisBit.inl"

#endif