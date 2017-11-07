# Primos
### A busca incansável por novos primos de Mersenne

Trabalho de conclusão de curso. Davi Augusto Aragão. IFSP.

#### Usando o programa

1. Clone o projeto:

`git clone https://github.com/DaviAragao/primos.git`

2. Instale as dependências do projeto:

  1.  Instale a biblioteca [GMP](https://gmplib.org/):
  
    **Linux:** `sudo apt-get install libgmp3-dev`
    
    **Windows:** [Link](http://cs.nyu.edu/~exact/core/gmp/index.html)
    
  2.  Instale a biblioteca [MPICH2](http://www.mpich.org/):
  
    **Linux:** [Link](http://mpitutorial.com/tutorials/installing-mpich2/)
    
    **Windows:** [Link](http://swash.sourceforge.net/online_doc/swashimp/node9.html)
    
3. Compile o programa:

`gcc main.c -o main -lgmp`

4. Execute o programa:

`./main`
