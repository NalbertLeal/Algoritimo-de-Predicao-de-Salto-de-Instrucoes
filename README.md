# Predição de salto

### tópicos abordados:  
  
- **Introdução**;
- **O projeto**;
- **A implementação**;
- **Como compilar e executar**
- **Testes realizados**;
- **Bugs**;
- **Observações**;
- **Sobre o grupo**;

##### status do projeto: **Em desenvolvimento**  
    
#### Introdução  
  Este projeto implementa um simulador de predição de salto(Branch Prediction), a predição de salto é uma técnica
usada pelos processadores atuais que visa aumentar a performance do mesmo, uma vez que o processador encontra uma instrução de jump, em seu pipeline, ele deve decidir se deve ou não toma aquele salto, se ele tomar a decisão errada, irá encher o pipeline com instruções inúteis e precisará se desfazer delas
para, só então, executar as instruções na ordem correa, é por esse motivo que surgiram as predições. Com o auxilio dessas técnicas o processador poderá evitar esse tipo de problema e tornar a execução de
algoritmos mais eficiente.

### O projeto
Esse projeto está sendo desenvolvido como uma atividade complementar ao semestre 2016.1 da turma de IOAC da professora Monica Magalhães, uma predição de salto baseada em correlação que usa um e dois bits como forma de previsão dinâmica será implementada.
   
#### A implementação:  
  
  Os seguintes arquivos são pertencentes a implementação da predição até o momento:
  
  1) **src/main.cpp** : Contém o codigo da função main  
  2) **include/DoisBin.hpp** :  Contém a classe DoisBin.  
  3) **include/DoisBin.inl** : Contém a implentação dos métodos da classe DoisBin.  
  4) **Doxygen** :  Arquivo de configuração para gerar a documentação do codigo com o doxygen.  
  
### Como compilar e executar
  Para compilar o código é indicado o compilador g++ pois esse foi o programa utilizado na compilação do codigo. Assumindo que os requerimentos/conselhos estejam sendo seguidos para compilar o codigo do vector usando o g++ é necessario utilizar o seguinte comando no terminar dentro da pasta Vector:
  
    g++ -std=c++11 -I include src/main.cpp -o bin/predicaoDeSalto
  
  Também pode se utilizar o makefile, basta digitar o comando a seguir que o código será compilado:
  
    make
  
  O arquivo gerado se encontra dentro da pasta bin do diretorio do projeto.
### Testes realizados:
  
  Os testes realizados foram feitos com base na entrada modelo demonstrada no email enviado pela professora Monica. Esses testes podem não refletir algum eventual bug que testes profundos no codigo revelariam.
    
### Bugs:
  
  Os testes realizados não revelaram algum erro. Entretanto isso não significa que o programa está livre de erros.

### Observações:

  O codigo será postado no GitHub para posiveis avaliações futuras. O projeto é muito interessante e pode ter suas ideias fundamentais sendo utilizadas base para diversos projetos futuros.

  Esse projeto se encontra no Git Hub no link:  
   [link do projeto](https://github.com/nalbertg/HashTbl)


### Sobre o grupo:
    
- **Aluno**: Nalbert Gabriel Melo Leal;  
- **GitHub**: github.com/nalbertg ;  
- **email pessoal**: nalbertrn@yahoo.com.br;  
- **email acadêmico/profissional**: nalbertg@outlook.com;  


- **Aluno**: Matheus Alves;
- **GitHub**: github.com/MatheusAlvesA;
  
