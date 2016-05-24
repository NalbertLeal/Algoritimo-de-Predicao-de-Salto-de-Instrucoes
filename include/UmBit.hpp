#ifndef _UMBIT_HPP_
#define _UMBIT_HPP_

#include "Erro.hpp"

/*
*	@brief 		
*	@param 		
*	@return 	
*/
class UmBit {
	public:
		UmBit(bool valorInicial) :
		tomado(valorInicial)
		{/* Empty */}

		~UmBit()
		{
			this->clear();
		}

		void run(int &argc, const char *argv[]);
	private:
		bool predicao();
		void lerArquivo(std::string);
		int UmBit::extrairSalto(std::string);

		void preditor();

		// variaveis

		// valor inicial da predição
		bool tomado;
		// matriz de vector que armqzena os resultados das predições
		std::vector<std::vector<char>> matrizSaltos(4);
};

#include "UmBit.inl"

#endif