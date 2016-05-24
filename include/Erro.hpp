#ifndef _ERRO_HPP_
#define _ERRO_HPP_

/*!
*   @brief    A classe Erro cria o objeto que faz o menejamento do erro gerado em UmBit
*/
class Erro {
	public:
	/*!
	*   @brief		Erro(int err) é o construtor da classe Erro que constroi o objeto
	*   @param 		err 	Esse parametro é um inteiro que representa o erro que ocorreu
	*   @return		O construtor não possui retorno
	*/
	Erro(int err) : err(err) {}

	//	Essa função é responsavel por retornar uma string informando o erro que ocorreu.
	std::string what() {
		switch(err) {
			case 1:
				return ">>> O arquivo não pode ser aberto. Por favor use a seguinte notação: \n        ./predicao nomeDoArquivoDeEntrada.suaExtenção \n";
				break;
			case 2:
				return ">>> O arquivo não pode ser aberto pois não esta no diretorio indicado ou esta corrompido.\nPor favor verifique a entrada do nome do arquivo e se o está em boas condições.\n";
				break;
		}
	}

	// O enum Type armazena os nomes dos erros que podem ocorrer e atribui algum valor inteiro para cada erro.
	enum Type {
		ArquivoNaoFoiAberto = 1,
		ArquivoNaoPedeSerLido = 2
	};
	private:
		// variável err é do tipo inteiro e armazena o numero que representa o erro que ocorreu.
		int err;
};

#endif