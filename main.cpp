#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <locale.h>
#include <limits>
#include <math.h>

#define MAX_HEAP 100

using namespace std;

//imprime o menu podendo ou não imprimir as opções
void imprimeMenu(bool tudo=true)
{
    system("cls");
    cout << "     _____ _                 __        __  __                        " << endl;
    cout << "    / ___/(_)___ ___  ____  / /__     / / / /__  ____ _____          " << endl;
    cout << "    \\__ \\/ / __ `__ \\/ __ \\/ / _ \\   / /_/ / _ \\/ __ `/ __ \\  " << endl;
    cout << "   ___/ / / / / / / / /_/ / /  __/  / __  /  __/ /_/ / /_/ /         " << endl;
    cout << "  /____/_/_/ /_/ /_/ .___/_/\\___/  /_/ /_/\\___/\\__,_/ .___/       " << endl;
    cout << "                  /_/                              /_/               " << endl;
    cout << "==============================================================" << endl;
    if(tudo)
    {
        cout << " Selecione uma opcao:" << endl;
        cout << "   1. Insercao de elementos em matriz unidimensional" << endl;
        cout << "   2. Criar uma heap" << endl;
        cout << "   3. Insercao de elementos na heap" << endl;
        cout << "   4. Busca de elementos" << endl;
        cout << "   5. Remocao de elementos" << endl;
        cout << "   6. Apresentacao da arvore" << endl;
        cout << "   0. Sair" << endl;
        cout << "==============================================================" << endl;
        cout << ">>";
    }
}

int lerEntrada(const char* print)
{
    int input = -1;
    bool valid= false;
    do
    {
        cout << print;
        cin >> input;
        if (cin.good())
        {
            valid = true;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << " Entrada inválida!" << endl;
        }
    }
    while (!valid);
    return (input);
}

class Heap
{
    char* dados;
    int n_dados;
    int max_dados;
public:
    Heap(int tam_heap)
    {
        dados = new char[tam_heap];
        n_dados = 0;
        max_dados = tam_heap;
    }
    ~Heap()
    {
        delete [] dados;
    }
    //deleta por dado
    int deleteHeap(char elem)
    {
        return deleteHeap(busca(elem));
    }
    //delata o ultimo dado
    void deleteHeap()
    {
        deleteHeap(n_dados-1);
    }
    int deleteHeap(int indice)
    {
        //heap vaiza
        if(n_dados==0)
        {
            cout << "Heap vazia" << endl;
            return 0;
        }
        if((indice<0)||(indice >= n_dados))
        {
            cout << "Dado nao encontrado" << endl;
            return 0;
        }
        //coloco a raiz no lugar
        dados[indice] = dados[0];
        n_dados--;
        //copio o ultimo para a raiz e organizo descendo
        dados[0] = dados[n_dados];
        descer(0);
        return 1;
    }
    //======dava para melhor essa função, ela busca em todos
    //busca a posição em dados do elem, se não existir retorna -1
    int busca(char elem)
    {
        for(int i=0; i<n_dados; i++)
        {
            if(dados[i]==elem)
                return i;
        }
        //dado não encontrada
        return -1;
    }
    int addHeap(const char dado)
    {
        //heap cheia
        if(n_dados>max_dados)
            return 0;
        //coloco no final e subo se precisar
        dados[n_dados] = dado;
        subir(n_dados);
        n_dados++;
        return 1;
    }

    //subir valor na posição indice em dados, se for um valor maior
    void subir(int indice)
    {
        //raiz
        if(indice == 0)
            return;
        int pai = (indice+1)/2 - 1;
        //filho maior que pai
        if(dados[pai]<dados[indice])
        {
            //troca
            char tmp = dados[pai];
            dados[pai] = dados[indice];
            dados[indice] = tmp;
            //contiua a subir
            subir(pai);
        }
        return;
    }

    void descer(int indice)
    {
        int filhoD, filhoE;
        filhoD = (indice+1)*2;
        filhoE = (indice+1)*2-1;
        //filho existe
        if(filhoD<n_dados)
        {
            //filho maior que pai
            if(dados[filhoD]>dados[indice])
            {
                //troca
                char tmp = dados[filhoD];
                dados[filhoD] = dados[indice];
                dados[indice] = tmp;
                //continua a descer
                descer(filhoD);
                return;
            }
        }
        else if(filhoE<n_dados)
        {
            //filho maior que pai
            if(dados[filhoE]>dados[indice])
            {
                //troca
                char tmp = dados[filhoE];
                dados[filhoE] = dados[indice];
                dados[indice] = tmp;
                //continua a descer
                descer(filhoE);
                return;
            }
        }
        return;
    }
    void imprimir()
    {
        //heap vaiza
        if(n_dados == 0)
        {
            cout << "Heap esta vazia!" << endl;
            return;
        }
        cout << "Raiz: " << dados[0] << "\tFD: " << filho(0,1) << "\tFE: " << filho(0,0) << endl;
        for(int i=1; i<n_dados; i++)
        {
            cout << "No: " << dados[i] << "\tFD: " << filho(i,1) << "\tFE: " << filho(i,0) << endl;
        }
        return;
    }
    //igual função imprimir, porem imprime numeros
    void imprimirInt()
    {
        //heap vaiza
        if(n_dados == 0)
        {
            cout << "Heap esta vazia!" << endl;
            return;
        }
        cout << "Raiz: " << (int)dados[0]-'a' << "\tFD: " << (int)filho(0,1)-'a' << "\tFE: " << (int)filho(0,0)-'a' << endl;
        for(int i=1; i<n_dados; i++)
        {
            cout << "No: " << (int)dados[i]-'a' << "\tFD: " << (int)filho(i,1)-'a' << "\tFE: " << (int)filho(i,0)-'a' << endl;
        }
        return;
    }
    //retorna o valor do filho de indice, lado=0(esquerda), lado=1(direita)
    char filho(int indice, bool lado)
    {
        int filho;
        if(!lado)//esquerda
            filho = (indice+1)*2-1;
        else //direita
            filho = (indice+1)*2;
        //filho nem existe
        if(filho>=n_dados)
            return ' ';
        return dados[filho];
    }
    //retorna o tamanho atual da heap(quantidade de elementos)
    int getSize()
    {
        return n_dados;
    }
};


int main()
{
    Heap *heap = new Heap(MAX_HEAP);

    char ent;
    char matriz[MAX_HEAP];
    int tam = 0;
    string entrada;

    while(1)
    {
        system("cls");
        imprimeMenu();

        getline(cin, entrada);
        ent = entrada[0];
        switch(ent)
        {
        case '0':
            return 0;
            break;
        /// Insercao de elementos em matriz unidimensional
        case '1':
            while(1)
            {
                imprimeMenu(false);
                cout << " 1. Insercao de elementos em matriz unidimensional" << endl;
                cout << "   Matriz atual: ";
                if(tam == 0)
                {
                    cout << "Vazia!" << endl;
                }
                if(tam == 1)
                {
                    cout << matriz[0] << endl;
                }
                else if(tam>1)
                {
                    cout << matriz[0];
                    for(int i=1; i<tam; i++)
                        cout << ", " << matriz[i];
                    cout << endl;
                }
                cout << "   Inserir elemento (pressione somente Enter para sair): ";

                getline(cin, entrada);
                if(entrada == "")
                    break;
                matriz[tam++] = entrada[0];
                system("cls");
            }

            break;
        /// Criar uma heap
        case '2':
            imprimeMenu(false);
            cout << " 2. Criar uma heap" << endl;
            if(tam == 0)
            {
                cout << "   Heap nao foi criada! Matriz unidimensional vazia!" << endl;
            }
            else
            {
                for(int i=0; i<tam; i++)
                    heap->addHeap(matriz[i]);
                cout << "   Heap criada!" << endl;
            }
            system("pause");
            break;
        /// Insercao de elementos na heap
        case '3':
            imprimeMenu(false);
            cout << " 3. Insercao de elementos na heap" << endl;
            cout << "   Inserir elemento (pressione somente Enter para sair): ";
            getline(cin, entrada);
            if(entrada == "")
                break;
            if(heap->addHeap(entrada[0]))
                cout << "   Elemento adicionado" << endl;
            else
                cout << "   Elemento nao adicionado! Heap cheia" << endl;
            system("pause");
            system("cls");
            break;
        /// Busca de elementos
        case '4':
            imprimeMenu(false);
            cout << " 4. Busca de elementos" << endl;
            cout << "   Buscar elemento: ";
            getline(cin, entrada);
            if(entrada == "")
                break;
            if(heap->busca(entrada[0]))
                cout << "   O elemento esta na Heap!" << endl;
            else
                cout << "   O   elemento nao está na Heap!" << endl;
            system("pause");
            break;
        /// Remoção de elementos
        case '5':
            imprimeMenu(false);
            cout << " 5. Remover elemento" << endl;
            cout << "   Remover elemento: ";
            getline(cin, entrada);
            if(entrada == "")
                break;

            if(heap->deleteHeap(entrada[0]))
            cout << "   O elemento foi removido!" << endl;
            else
            cout << "   O elemento nao esta na heap e portanto nao foi removido!" << endl;

            system("pause");
            break;
        /// Apresentação da arvore
        case '6':
            cout << " 6. Apresentacao da arvore" << endl;
            heap->imprimir();
            system("pause");
            break;
        /// Entrada inválida
        default:
            break;
        }
    }

    delete heap;
    return 0;
}
