#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <string>

using namespace std;

class Sudoku {
    private:

        int matriz[9][9];
        int resultado[9][9];
        int erros[9][9];
        bool val;

    public:

        Sudoku();
        void carregar(string dir);
        void insertar(int i, int j, int numero);
        void insertarResult(int i, int j, int numero);
        int ler(int i, int j, int matRes);
        void insertarErro(int i, int j);
        void apagarErro(int i, int j);
        int lerErro(int i, int j);
        void validar(bool valid);
        bool isVal();

};
#endif // SUDOKU_H
