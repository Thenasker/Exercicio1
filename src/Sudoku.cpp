#include "Sudoku.h"
#include <iostream>
#include <string>
#include <fstream>

Sudoku::Sudoku()
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            matriz[i][j] = 0;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            resultado[i][j] = 0;
        }
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            erros[i][j] = -1;
        }
    }
    val = true;
}

void Sudoku::carregar(string dir){

    int cont = 0;
    string aux;
    ifstream arquivo(dir.c_str());
    std::getline(arquivo, aux);

    for(int i=0 ; i<9 ; i++){
        for(int j=0 ; j<9 ; j++){

            matriz[i][j] = (aux.at(cont) - 48);
            resultado[i][j] = (aux.at(cont) - 48);
            cont++;

        }
    }
}
void Sudoku::insertar(int i, int j, int numero){

    matriz[i][j] = numero;
    resultado[i][j] = numero;

}
void Sudoku::insertarResult(int i, int j, int numero){

    resultado[i][j] = numero;

}
int Sudoku::ler(int i, int j, int matRes){

    if(matRes == 0){
        return matriz[i][j];
    }else{
        return resultado[i][j];
    }

}
void Sudoku::insertarErro(int i, int j){

    erros[i][j] = matriz[i][j];

}
void Sudoku::apagarErro(int i, int j){

    erros[i][j] = -1;

}
int Sudoku::lerErro(int i, int j){

    return erros[i][j];

}
void Sudoku::validar(bool valid){
    val = valid;
}
bool Sudoku::isVal(){
    return val;
}
