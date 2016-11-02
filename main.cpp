#include <iostream>
#define MAX_HEAP 100
using namespace std;

class Heap{
    char* dados;
    int n_dados;
    int max_dados;
public:
    Heap(int tam_heap){
        dados = new char[tam_heap];
        n_dados = 0;
        max_dados = tam_heap;
    }
    ~Heap(){
        delete [] dados;
    }
    void addHeap(const char dado){
        //heap cheia
        if(n_dados>max_dados)
            return;
        //coloco no final e subo se precisar
        dados[n_dados] = dado;
        subir(n_dados);
        n_dados++;
    }
    //subir valor na posição indice em dados, se for um valor maior
    void subir(int indice){
        //raiz
        if(indice == 0)
            return;
        int pai = (indice+1)/2 - 1;
        //filho maior que pai
        if(dados[pai]<dados[indice]){
            //troca
            int tmp = dados[pai];
            dados[pai] = dados[indice];
            dados[indice] = tmp;
            //contiua a subir
            subir(pai);
        }
        return;
    }

    void imprimir(){
        //heap vaiza
        if(n_dados == 0){
            cout << "Heap esta vazia!" << endl;
            return;
        }
        cout << "Raiz: " << dados[0] << "\tFD: " << filho(0,1) << "\tFE: " << filho(0,0) << endl;
        for(int i=1;i<n_dados;i++){
            cout << "No: " << dados[i] << "\tFD: " << filho(i,1) << "\tFE: " << filho(i,0) << endl;
        }
        return;
    }
    void imprimirInt(){
        //heap vaiza
        if(n_dados == 0){
            cout << "Heap esta vazia!" << endl;
            return;
        }
        cout << "Raiz: " << (int)dados[0]-'a' << "\tFD: " << (int)filho(0,1)-'a' << "\tFE: " << (int)filho(0,0)-'a' << endl;
        for(int i=1;i<n_dados;i++){
            cout << "No: " << (int)dados[i]-'a' << "\tFD: " << (int)filho(i,1)-'a' << "\tFE: " << (int)filho(i,0)-'a' << endl;
        }
        return;
    }
    //retorna o valor do filho de indice, lado=0(esquerda), lado=1(direita)
    char filho(int indice, bool lado){
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

};
int main()
{
    Heap *heap = new Heap(MAX_HEAP);

    heap->addHeap('c');
    heap->addHeap('o');
    heap->addHeap('r');
    heap->addHeap('d');
    heap->addHeap('e');
    heap->addHeap('i');
    heap->addHeap('r');
    heap->addHeap('o');

    //heap->imprimirInt();
    heap->imprimir();
    delete heap;

    return 0;
}
