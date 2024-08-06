/*
Observação: Para utilizar o código com esse arquivo main é necessário
ajustar o caminho que importa o arquivo da implementação da árvore
AVL, ou seja, o "#include <C:\Users\...\...\...\avl.h>"
presente na linha 11.
*/

//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <C:\Users\...\...\...\avl.h>"

//Programa principal
int main(){
    //Declarações locais
    tree avl = NULL;

    //Apenas exibindo a árvore no seu estado inicial
    printf("\nPercorrendo a arvore em ordem:\n");
    inorder(avl);
    printf("\nA exibicao deve ser vazia, pois ainda nao ha chaves inseridas\n");

    //Inserindo as chaves na sequência solicitada
    avl = inserir_chave(avl, 11);
    printf("\nChave 11 inserida\n");
    avl = inserir_chave(avl, 12);
    printf("Chave 12 inserida\n");    
    avl = inserir_chave(avl, 13);
    printf("Chave 13 inserida\n");
    avl = inserir_chave(avl, 14);
    printf("Chave 14 inserida\n");
    avl = inserir_chave(avl, 15);
    printf("Chave 15 inserida\n");
    avl = inserir_chave(avl, 20);
    printf("Chave 20 inserida\n");
    avl = inserir_chave(avl, 19);
    printf("Chave 19 inserida\n");
    avl = inserir_chave(avl, 18);
    printf("Chave 18 inserida\n");
    avl = inserir_chave(avl, 17);
    printf("Chave 17 inserida\n");
    avl = inserir_chave(avl, 16);
    printf("Chave 16 inserida\n");
    avl = inserir_chave(avl, 5);
    printf("Chave 5 inserida\n");
    avl = inserir_chave(avl, 4);
    printf("Chave 4 inserida\n");
    avl = inserir_chave(avl, 3);
    printf("Chave 3 inserida\n");
    avl = inserir_chave(avl, 2);
    printf("Chave 2 inserida\n");
    avl = inserir_chave(avl, 1);
    printf("Chave 1 inserida\n");
    avl = inserir_chave(avl, 6);
    printf("Chave 6 inserida\n");
    avl = inserir_chave(avl, 7);
    printf("Chave 7 inserida\n");
    avl = inserir_chave(avl, 8);
    printf("Chave 8 inserida\n");
    avl = inserir_chave(avl, 9);
    printf("Chave 9 inserida\n");
    avl = inserir_chave(avl, 10);
    printf("Chave 10 inserida\n");

    //Exibindo a árvore após as inserções
    printf("\nPercorrendo a arvore em ordem:\n");
    inorder(avl);
    printf("\n");

    //Removendo as chaves na sequência solicitada
    remover_chave(avl, 5);
    printf("\nChave 5 removida\n");
    remover_chave(avl, 10);
    printf("Chave 10 removida\n");
    remover_chave(avl, 15);
    printf("Chave 15 removida\n");

    //Exibindo a árvore após as remoções
    printf("\nPercorrendo a arvore em ordem:\n");
    inorder(avl);
    printf("\n\n");

    //Finalização do programa
    return 0;
}