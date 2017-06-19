/*
*   Exercicio 1.
*
*   Determine se um Sudoku é válido. A placa de Sudoku pode ser preenchida parcialmente,
*   onde as células vazias são preenchidas com o caractere '.'.
*
*   Nivel de Dificultad     Orden
*   Facil                   0 a 35
*   Medio                   36 a 50
*   Dificil                 51 a 63
*   Muy Dificil             64
*
*/

/////////////////////////////INCLUDES
#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <ctime>
#include <sstream>
#include <dirent.h>
#include "Sudoku.h"
/////////////////////////////INCLUDES

/////////////////////////////DEFINES
//Definiçao do string do menu
#define menu "\n1--Determinar se um Sudoku é valido (Manual)\n\n2--Determinar se um Sudoku é valido (Arquivo)\n\n3--Gerar Sudokus\n\n4--Jogar Sudoku\n\n0--Sair\n\n"//Definiçao do tamaño do nome dos arquivos a salver e do formato deles
#define FORMATO_NOME "Sudoku_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME 27
#define FORMATO_NOME_PRINT "Sudokus_pr_%Y%m%d_%H%M%S.txt"
#define TAMANHO_NOME_PRINT 31
#define CHAR_VACIO '_'
/////////////////////////////DEFINES

using namespace std;

//Funçao que mostra o menu de opçoes inicial
int mostrarMenu(){

    int opcao=-1;

    //Enquanto o usuario nao escreva uma opçao valida o menu vai se mostrar uma e outra vez.
    while(opcao<0 || opcao>7){
        system("cls");
        //Usamos a variavel definida 'menu'
        cout << menu << endl;
        cin >> opcao;
        if(opcao<0 || opcao>7){
            cout << "Inserir uma opcao valida (0-7)" << endl;
            Sleep(2000);
        }
    }
    return opcao;
}

//funçao para perguntar ao usuario se ele quer finalizar o apicativo o mostrar o menu inicial outra vez
bool finalizar(){

    char fim = CHAR_VACIO;

    //Se pergunta ao usuario se que sair e devolve um valor booleano para a funçao main
    while(fim!='S' && fim!='s' && fim!='N' && fim!='n'){
        cout << "\n\n\nDeseja finalizar o programa? (S/N)" << endl;
        cin >> fim;
    }

    if(fim=='S' || fim == 's'){
        return true;
    }else{
        return false;
    }

}

//A funçao percorre todas as posiçoes da matriz "matriz" ou da matriz "resultado" do objeto Sudoku dependendo do parametro matRes
void mostrarSudoku(Sudoku &sudo, int matRes){


    cout << " ____ ____ ____   ____ ____ ____   ____ ____ ____" << endl;
    for(int i=0;i<9;i++){
        cout << "|    |    |    | |    |    |    | |    |    |    |" << endl;
        cout << "|";
        for(int j=0;j<9;j++){
            if(sudo.ler(i,j,matRes) == 0){
                cout << "  . |";
            }else{
                if(sudo.lerErro(i,j)!=-1){
                    cout << " (" << sudo.ler(i,j,matRes) <<")|";
                }else{
                    cout << "  " << sudo.ler(i,j,matRes) <<" |";
                }
            }
            if((j+1)%3 == 0 && j != 8) cout << " |";
        }
        cout << endl;
        cout << "|____|____|____| |____|____|____| |____|____|____|" << endl;
        if((i+1)%3 == 0 && i != 8){
            cout << endl;
            cout << " ____ ____ ____   ____ ____ ____   ____ ____ ____" << endl;
        }
    }
    cout << "\n\n";
}

//A funçao percorre a matriz do sudoku e insire um valor em cada posiçao. Se o usuario digitar "F" termina o que resta do vetor com 0
void obterDeTeclado(Sudoku &sudo){

    system("cls");
    char entrada = CHAR_VACIO;

    cout << endl << "Escreva os numeros do Sudoku em ordem de arriba esquerda à abaixo direita." << endl << "Só serao aceitos numeros inteiros positivos de 1 à 9." << endl << "Escreva um ponto (.) para os espaços vazios." << endl << "Digite F se quer finalizar a entrada de dados e que o resto de espaços fiquem vazios." << endl << "No caso escreva mais de um numero/caracter, eles vao ser inseridos em ordem no sudoku.\n" << endl;

    system("pause");

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){

            system("cls");
            //Mostramos sudoku
            mostrarSudoku(sudo, 0);

            while((entrada < 46 || entrada > 57 || entrada == 47 || entrada == 48) && entrada != 'F' && entrada != 'f'){
                cout << "Numero da posiçao Fila: " << i+1 << " Coluna: " << j+1 << ":  ";
                cin >> entrada;
                cout << "\n\n";
            }
            if(entrada == 'F' || entrada == 'f'){
                j=9;
                i=9;
            }else{
                if(entrada == '.'){
                    sudo.insertar(i,j,0);
                }else{
                    sudo.insertar(i,j,entrada - '0');
                }
                entrada = CHAR_VACIO;
            }
        }
    }
}

//Funçao para criar e salvar um arquivo com o sudoku criado.
void salvarArquivo(Sudoku &sudo){

    char salvar=CHAR_VACIO;
    stringstream ss;
    string out;

    //Perguntamos ao usuario se deseja salvar o sudoku num arquivo.
    while(salvar!='S' && salvar!='s' && salvar!='N' && salvar!='n'){
        cout << "\n\nVoce quer salvar o Sudoku? (S/N)" << endl;
        cin >> salvar;
        if(salvar=='S' || salvar=='s'){

            ofstream arquivoSalvar;

            //Formatamos o nome do arquivo com a data e hora do momento da criaçao do arquivo segundo o formato definido acima.
            char nome[TAMANHO_NOME];
            time_t timestamp = time(0);
            strftime(nome, sizeof(nome), FORMATO_NOME, localtime(&timestamp));

            arquivoSalvar.open (nome);
            //Escrevemos uma linha com todos os valores do sudoku.
            for(int i=0;i<9;i++){
                for(int j=0;j<9;j++){
                    ss << sudo.ler(i,j,0);
                }
            }
            ss >> out;
            arquivoSalvar << out;
            arquivoSalvar.close();
        }
    }
}

//Funçao que salva num arquivo o sudoku de modo "visual"
void savePrint(Sudoku sudos[], int numSudos){

    char salvar=CHAR_VACIO;

    //Perguntamos ao usuario se deseja salvar o sudoku num arquivo.
    while(salvar!='S' && salvar!='s' && salvar!='N' && salvar!='n'){
        cout << "\n\nVoce quer salvar os Sudokus? (S/N)" << endl;
        cin >> salvar;
        if(salvar=='S' || salvar=='s'){

            ofstream arquivoSalvar;

            //Formatamos o nome do arquivo com a data e hora do momento da criaçao do arquivo segundo o formato definido acima.
            char nome[TAMANHO_NOME_PRINT];
            time_t timestamp = time(0);
            strftime(nome, sizeof(nome), FORMATO_NOME_PRINT, localtime(&timestamp));

            arquivoSalvar.open (nome);

            for(int n=0; n<numSudos; n++){
                 arquivoSalvar << " ____ ____ ____   ____ ____ ____   ____ ____ ____" << endl;
                for(int i=0;i<9;i++){
                    arquivoSalvar << "|    |    |    | |    |    |    | |    |    |    |" << endl;
                    arquivoSalvar << "|";
                    for(int j=0;j<9;j++){
                        if(sudos[n].ler(i,j,0) == 0){
                            arquivoSalvar << "  . |";
                        }else{
                            if(sudos[n].lerErro(i,j)!=-1){
                                arquivoSalvar << " (" << sudos[n].ler(i,j,0) <<")|";
                            }else{
                                arquivoSalvar << "  " << sudos[n].ler(i,j,0) <<" |";
                            }
                        }
                        if((j+1)%3 == 0 && j != 8) arquivoSalvar << " |";
                    }
                    arquivoSalvar << endl;
                    arquivoSalvar << "|____|____|____| |____|____|____| |____|____|____|" << endl;
                    if((i+1)%3 == 0 && i != 8){
                        arquivoSalvar << endl;
                        arquivoSalvar << " ____ ____ ____   ____ ____ ____   ____ ____ ____" << endl;
                    }
                }
                arquivoSalvar << "\n\n\n\n";
            }

            //MOSTRAR LOS RESULTADOS
            for(int n=0; n<numSudos; n++){
                for(int i=0;i<9;i++){
                    for(int j=0;j<9;j++){
                        arquivoSalvar << sudos[n].ler(i,j,1) << " ";
                    }
                    arquivoSalvar << "\n";
                }
                arquivoSalvar << "\n\n\n\n";
            }

            arquivoSalvar.close();
        }
    }
}

//Funçao que percorre a matriz "erros" e pede ao usuario inserir um novo valor nas posiçoes com valor != -1
void modificar(Sudoku &sudo){

    system("cls");
    mostrarSudoku(sudo, 0);
    char novo_num = CHAR_VACIO;

    cout << endl << "Escreva novos valores para as posicoes en conflito (escreva um ponto se deseja apagar o valor).\n" << endl;

    for(int i=0 ; i<9 ; i++){
        for(int j=0 ; j<9 ; j++){
            if(sudo.lerErro(i,j) != -1){
                while(novo_num < 46 || novo_num > 57 || novo_num == 47 || novo_num == 48){
                    cout << "Numero da posiçao Fila: " << i+1 << " Coluna: " << j+1 << ":  ";
                    cin >> novo_num;
                    cout << "\n\n";
                }
                if(novo_num == '.'){
                    sudo.insertar(i,j,0);
                    sudo.apagarErro(i,j);
                }else{
                    sudo.insertar(i,j,novo_num - '0');
                    sudo.apagarErro(i,j);
                }
                novo_num = CHAR_VACIO;

                system("cls");
                mostrarSudoku(sudo, 0);
            }
        }
    }
}

//Funçao que tem tres partes: primeiro comprova os valores de cada fila e insire um erro se achar dois iguais (no caso o parametro adErros seja certo), depois faz o mesmo com as colunas e por ultimo com os subquadros.
bool posicaoValida(int num, Sudoku &sudo, int i, int j, bool adErros){

    bool val = true;
    int nextNum = 0;

    //comprobar fila
    for(int k=0;k<9;k++){
        if(adErros){nextNum = sudo.ler(i,k,0);}else{nextNum = sudo.ler(i,k,1);}
        if(num == nextNum && j!=k){
            if(adErros){
                sudo.insertarErro(i,j);
                sudo.insertarErro(i,k);
            }
            val = false;
        }
    }

    //comprobar columna
    for(int k=0;k<9;k++){
        if(adErros){nextNum = sudo.ler(k,j,0);}else{nextNum = sudo.ler(k,j,1);}
        if(num == nextNum && i!=k){
            if(adErros){
                sudo.insertarErro(i,j);
                sudo.insertarErro(k,j);
            }
            val = false;
        }
    }

    //comprobar cuadrado
    for(int k=(i/3)*3 ; k<((i/3)*3)+3 ; k++){
        for(int l=(j/3)*3 ; l<((j/3)*3)+3 ; l++){
            if(adErros){nextNum = sudo.ler(k,l,0);}else{nextNum = sudo.ler(k,l,1);}
            if(num == nextNum && i!=k && j!=l){
                if(adErros){
                    sudo.insertarErro(i,j);
                    sudo.insertarErro(k,l);
                }
                val = false;
            }
        }

    }
    return val;

}

//A funçao tenta inserir os numeros vaalidos em ordem crescente (1->10) de esquerda pra direita e de cima para baixo. Quando chegar a um ponto que nao poder inserir nenhum valor de 1 a 10 volta ao começo e tenta com
//o seguinte numero o mesmo sistema. até chegar a linha 10 (que nao existe) que entao devolve todo um ate a chamada original.
int resolver(Sudoku &sudo, int i, int j){

    int num = 1;
    if(i == 9){
        return 1;
    }

    //Se o valor da posiçao (i,j) é distinto de zero chama a funçao para o seguinte quadro.
    if (sudo.ler(i,j,0) != 0) {
        if (j == 8) {
            if (resolver(sudo, i+1, 0)) return 1;
        } else {
            if (resolver(sudo, i, j+1)) return 1;
        }
        return 0;
    }

    for (num = 1; num<10; num++) {
        if(posicaoValida(num, sudo, i, j, false)) {
            sudo.insertarResult(i,j,num);
            if (j == 8) {
                if (resolver(sudo, i+1, 0)) return 1;
            } else {
                if (resolver(sudo, i, j+1)) return 1;
            }
            // Se nao achar um valor posivel insire "0"
            sudo.insertarResult(i,j,0);
        }
    }


}

//A funçao comprova que todas as posiçoes que tem valor distinto de 0 cumplem as normas do jogo.
//Se alguma posiçao esta errada da a opçao ao usuario de modificar os valores das posiçoes em conflito
//Finalmente chama a funçao resolver para verificar que o sudoku é resoluvel.
bool validar(Sudoku &sudo){

    char modif = CHAR_VACIO;
    sudo.validar(true);

    cout << "\n\n" << "Validando...\n\n";

    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            if(sudo.ler(i,j,0)!=0){

                sudo.validar(posicaoValida(sudo.ler(i,j,0),sudo, i, j, true));

            }
        }
    }

    system("cls");
    mostrarSudoku(sudo,0);

    if(sudo.isVal()){
        if(resolver(sudo, 0, 0) == 1){
            return true;
        }else{
            return false;
        }
    }else{

        while(modif!='S' && modif!='s' && modif!='N' && modif!='n'){
            cout << "Sudoku malformado. Deseja modificar os erros?" << endl;
            cin >> modif;
        }
        if(modif=='S' || modif=='s'){
            modificar(sudo);
            return (validar(sudo));
        }else{
            return false;
        }

    }
}

//Funçao para listar os elementos de um diretorio.
void list_dir(string dir){

    DIR *directorio;
    struct dirent *elemento;
    string elem;

    if(directorio = opendir(dir.c_str())){
        while(elemento = readdir(directorio)){
            elem = elemento -> d_name;
            if(elem.length() > 4){
                if(elem.substr(elem.length()-3,elem.length()-1) == "txt"){
                    cout << elem << endl;
                }
            }
        }
    }
    closedir(directorio);
}

//troca duas linhas aleatoriamente.
void barajarLinhas(Sudoku &sudo, int vezes){

    int aux=0;
    int lin1=0,lin2=0;

    for(int k=0; k<vezes; k++){
        lin1 = rand() % 9;
        lin1 = lin1/3;
        lin1 = lin1*3;
        lin2 = rand() % 3 + lin1;
        for(int i=0; i<9; i++){
            aux = sudo.ler(lin1,i,0);
            sudo.insertar(lin1,i,sudo.ler(lin2,i,0));
            sudo.insertar(lin2,i,aux);
        }
    }


}

//troca duas colunas aleatoriamente.
void barajarColunas(Sudoku &sudo, int vezes){

    int aux=0;
    int col1=0,col2=0;

    for(int k=0; k<vezes; k++){
        col1 = rand() % 9;
        col1 = col1/3;
        col1 = col1*3;
        col2 = rand() % 3 + col1;
        for(int i=0; i<9; i++){
            aux = sudo.ler(i,col1,0);
            sudo.insertar(i,col1,sudo.ler(i,col2,0));
            sudo.insertar(i,col2,aux);
        }
    }


}

//troca duas colunas de subquadros aleatoriamente
void barajarBlocosV(Sudoku &sudo, int vezes){

    int aux=0;
    int col1=0,col2=0;

    for(int k=0; k<vezes; k++){
        while(col1==col2){
        col1 = rand() % 9;
        col1 = col1/3;
        col1 = col1*3;
        col2 = rand() % 9;
        col2 = col2/3;
        col2 = col2*3;
        }
        for(int j=0;j<3;j++){
            for(int i=0; i<9; i++){
                aux = sudo.ler(i,col1+j,0);
                sudo.insertar(i,col1+j,sudo.ler(i,col2+j,0));
                sudo.insertar(i,col2+j,aux);
            }
        }
        col1=col2;
    }
}

//troca duas filas de subquadros aleatoriamente.
void barajarBlocosH(Sudoku &sudo, int vezes){


    int aux=0;
    int lin1=0,lin2=0;

    for(int k=0; k<vezes; k++){
        while(lin1==lin2){
        lin1 = rand() % 9;
        lin1 = lin1/3;
        lin1 = lin1*3;
        lin2 = rand() % 9;
        lin2 = lin2/3;
        lin2 = lin2*3;
        }
        for(int j=0;j<3;j++){
            for(int i=0; i<9; i++){
                aux = sudo.ler(lin1+j,i,0);
                sudo.insertar(lin1+j,i,sudo.ler(lin2+j,i,0));
                sudo.insertar(lin2+j,i,aux);
            }
        }
        lin1=lin2;
    }

}

//transforma a matriz do sudoku em sua trasposta
void trasponer(Sudoku &sudo){

    int aux[9][9];

    if(rand() % 2){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                aux[i][j] = sudo.ler(i,j,0);
            }
        }
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                sudo.insertar(i,j,aux[j][i]);
            }
        }
    }
}

//a funçao converte em 0 um numero aleatorio de posiçoes da matriz dependendo da dificuldade
//o metodo consiste em tirar eses valores de forma aleatoria e comprovar se a matriz continua sendo resoluvel
//se nao for, tira outros valores aleatoriamente ate que seja
//É um metodo bem simples mas como a velocidade de procesamento é boa, nao precisa de nada mais complexo
void tirarNums(Sudoku &sudo, int dificuldade){
    int n=0,i,j;
    Sudoku aux;

    switch(dificuldade){
        case 1:
            //DEBUG FACIL:
            //n = rand() % 6;
            n = rand() % 26 + 10;
        break;
        case 2:
            n = rand() % 15 + 36;
        break;
        case 3:
            n = rand() % 13 + 51;
        break;
        case 4:
            n = 64;
        break;
        default:
        break;
    }

    do{
        aux = sudo;
        for(int k=0; k<n; k++){
            i=rand() % 9;
            j=rand() % 9;
            while(aux.ler(i,j,0)==0){
                i=rand() % 9;
                j=rand() % 9;
            }
            aux.insertar(i,j,0);
        }
    }while(!validar(aux));
    sudo = aux;
}

//Funçao para gerar sudokus.
//Inicialmente gera um sudoku semente com os numeros em ordem mas cumplindo as normas do jogo.
//Aleatoriamente chama as funçoes de trasposiçao n vezes entre 0 e 100 de modo que a probabilidade de ter dois sudokus iguais é muito pequena.
void gerar(int dificuldade, int numSudokus){

    Sudoku sudos[numSudokus];
    Sudoku sudo;
    int k=1,n=1;
    srand (time(NULL));

    for(int p=0;p<numSudokus;p++){

        k=1;
        n=1;

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                sudo.insertar(i,j,0);
            }
        }

        for(int i=0;i<9;i++){
            k=n;
            for(int j=0;j<9;j++){
                if(k<=9){
                    sudo.insertar(i,j,k);
                    k++;
                }else{
                    k=1;
                    sudo.insertar(i,j,k);
                    k++;
                }
            }
            n=k+3;
            if(k==10)
            n=4;
            if(n>9)
            n=(n%9)+1;
        }
        barajarLinhas(sudo,rand() % 100+1);
        barajarColunas(sudo,rand() % 100+1);
        barajarBlocosV(sudo,rand() % 100+1);
        barajarBlocosH(sudo,rand() % 100+1);
        trasponer(sudo);

        tirarNums(sudo,dificuldade);

        sudos[p] = sudo;
    }

    system("cls");

    for(int i=0;i<numSudokus;i++){
        mostrarSudoku(sudos[i],0);
    }

   system("pause");
    savePrint(sudos,numSudokus);


}

//A funçao gera um sudoku e armazena a soluçao na matriz "resultado"
//O programa vai pedindo ao usuario valores  e até que sua matriz nao seja igual a matriz "resultado" nao da o sudoku por valido e o usuario como ganhador.
void jogar(int dificuldade){

    Sudoku sudo, aux;
    int k=1,n=1,x=0,y=0,num=0;
    bool correto = false;

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sudo.insertar(i,j,0);
        }
    }

    for(int i=0;i<9;i++){
        k=n;
        for(int j=0;j<9;j++){
            if(k<=9){
                sudo.insertar(i,j,k);
                k++;
            }else{
                k=1;
                sudo.insertar(i,j,k);
                k++;
            }
        }
        n=k+3;
        if(k==10)
        n=4;
        if(n>9)
        n=(n%9)+1;
    }
    barajarLinhas(sudo,rand() % 100+1);
    barajarColunas(sudo,rand() % 100+1);
    barajarBlocosV(sudo,rand() % 100+1);
    barajarBlocosH(sudo,rand() % 100+1);
    trasponer(sudo);

    tirarNums(sudo,dificuldade);

    aux = sudo;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            sudo.insertarResult(i,j,sudo.ler(i,j,0));
        }
    }
    while(!correto){
        x=0;
        y=0;
        correto = true;

        system("cls");
        cout << "Tablero inicial:" << endl;
        mostrarSudoku(sudo, 0);
        cout << "Resposta:" << endl;
        mostrarSudoku(sudo, 1);

        cout << "Fila: ";
        cin >> x;
        cout << "Coluna: ";
        cin >> y;
        cout << "Valor: ";
        cin >> num;

        if(sudo.ler(x-1,y-1,0) == 0){
            sudo.insertarResult(x-1,y-1,num);
        }else{
            cout << "posicao invalida!" << endl;
            Sleep(1000);
        }

        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(aux.ler(i,j,1) != sudo.ler(i,j,1)){
                    correto = false;
                }
            }
        }
    }
    system("cls");
    mostrarSudoku(sudo, 1);
    cout << "\n\nGANHOU! :D" << endl;
    system("pause");

}

//Funçoes que gerenciam as funcionalidades do programa
bool opcao1(){

    system("cls");

    Sudoku sudo;

    obterDeTeclado(sudo);

    if(validar(sudo)){
        cout << "\n\nO sudoku e valido! :D" << endl;
        salvarArquivo(sudo);
    }else{
        cout << "\n\nO sudoku NAO e valido! :(\n" << endl;
    }

    //devolvemos o valor que vamos obter da funçao finalizar()
    return finalizar();
}

bool opcao2(){

    string dir;
    string nome;
    Sudoku sudo;

    system("cls");

    //C:\Users\thenasker\Desktop\LP\AV2\Exercicio1\Exercicio1
    cout << "Escreva a rota onde buscar o arquivo (Ex: C\\)\n" << endl;
    cin >> dir;
    list_dir(dir);
    cout << "Escreva o nome do arquivo (Ex: sudoku_facil.txt)\n" << endl;
    cin >> nome;

    dir.append("\\");
    dir.append(nome);

    //pasamos o arquivo
    sudo.carregar(dir);


    if(validar(sudo)){
        cout << "\n\nO sudoku e valido! :D" << endl;
        salvarArquivo(sudo);
    }else{
        cout << "\n\nO sudoku NAO e valido! :(\n" << endl;
    }
    //devolvemos o valor que vamos obter da funçao finalizar()
    return finalizar();
}

bool opcao3(){

    int dificuldade = 0;
    int numSudokus = 0;
    Sudoku sudo;

    system("cls");

    while(dificuldade != 1 && dificuldade != 3 && dificuldade != 2 && dificuldade != 4){

        system("cls");
        cout << "Escolha um nivel de dificuldade:\n" << endl;
        cout << "1.- Facil (55 a 80 numeros)\n2.- Medio (31 a 55 numeros)\n3.- Dificil (18 a 30 numeros)\n4.- Muy dificil (17 numeros)\n" << endl;
        cin >> dificuldade;

    }

    while(numSudokus < 1 || numSudokus > 20){

        system("cls");
        cout << "Escolha a quantidade de sudokus a gerar (1-20):\n" << endl;
        cin >> numSudokus;

    }

    gerar(dificuldade,numSudokus);

    return finalizar();
}

bool opcao4(){

    int dificuldade = 0;
    int novo = 1;
    Sudoku sudo;
    srand (time(NULL));

    system("cls");

    while(novo == 1){
        while(dificuldade != 1 && dificuldade != 3 && dificuldade != 2 && dificuldade != 4){

            system("cls");
            cout << "Escolha um nivel de dificuldade:\n" << endl;
            cout << "1.- Facil (55 a 80 numeros)\n2.- Medio (31 a 55 numeros)\n3.- Dificil (18 a 30 numeros)\n4.- Muy dificil (17 numeros)\n" << endl;
            cin >> dificuldade;

        }

        jogar(dificuldade);

        novo = -1;

        while(novo<0 || novo>1){
            cout << "Deseja jogar de novo? (1-SIM 0-NAO)" << endl;
            cin >> novo;
        }
    }

return finalizar();
}

//Funçao main
int main(){

    bool finalizar = false;

    //Mostramos a introduçao
    cout << "Linguagem de programacao" << endl;
    cout << "AV2. Questao 1. Sudoku." << endl;
    cout << "Pablo Rufat Munoz" << endl;
    cout << "Marcos Marques" << endl;
    cout << "2017/1\n\n" << endl;
    system("pause");

    //Mientras a funçao finalizar() nao devolva true, vamos chamar a funçao que mostra o menu.
    while(!finalizar){
        switch(mostrarMenu()){
            case(0):
                finalizar = true;
                break;
            case(1):
                finalizar = opcao1();
                break;
            case(2):
                finalizar = opcao2();
                break;
            case(3):
                finalizar = opcao3();
                break;
            case(4):
                finalizar = opcao4();
                break;
            default:
                finalizar = true;
                break;
        };
    }
    return 0;
}
