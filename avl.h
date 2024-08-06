//Bibliotecas
#include <stdio.h>
#include <stdlib.h>

//Criando a estrutura nó
struct node{
    int key;                    //Chave
    int height;                 //Altura
    struct node *left;          //Subárvore à esquerda
    struct node *right;         //Subárvore à direita
} node;

//criando o tipo árvore, que é basicamente um ponteiro para nó (node *)
typedef struct node *tree;

//Protótipos
int height(tree);               //Função auxiliar
int max(int , int);             //Função auxiliar
tree new_node(int);             //Função auxiliar
tree min_value(tree);        //Função auxiliar
int fator_balanco(tree);
tree buscar_chave(tree, int);
tree sucessor(tree, int);
tree rotacao_dir(tree);
tree rotacao_esq(tree);
tree rotacao_esq_dir(tree);
tree rotacao_dir_esq(tree);
tree inserir_chave(tree, int);
tree remover_chave(tree, int);
void inorder(tree);

/*
Nome: height
Objetivo: Obter a altura de um nó
Parâmetros: 
    tree tree - Nó que se deseja verificar a altura
Valor de retorno:
    int - Altura do nó passado por referência
*/
int height(tree tree){
    if(tree == NULL){           //Se não possui nó
        return 0;               //Retorna 0
    }
    else{                       //Se possui nó
        return tree->height;    //Retorna a altura desse nó
    }
}

/*
Nome: max
Objetivo: Verificar o maior número entre dois inteiros
Parâmetros: 
    int a - Primeiro inteiro da comparação
    int b - Segundo inteiro da comparação
Valor de retorno:
    int - Maior inteiro entre os dois passados como parâmetros
*/
int max(int a, int b){
    return (a > b) ? a : b;
}

/*
Nome: new_node
Objetivo: Criar um nó com o valor da sua chave sendo um inteiro passado como parâmetro
Parâmetros: 
    int key - Inteiro a ser incorporado como chave do novo nó
Valor de retorno:
    tree - Endereço do novo nó criado
*/
tree new_node(int key){
    //Declarações locais
    tree node;

    //Criando o novo nó
    node = (tree) malloc(sizeof(struct node));          //Aloca memória para o novo nó
    node->key = key;                                    //O campo "chave" do novo nó recebe o valor passado como parâmetro
    node->height = 0;                                   //O novo nó é adicionado como folha
    node->left = NULL;                                  //Subárvore à esquerda nula
    node->right = NULL;                                 //Subárvore à direita nula

    //Retorna o endereço do nó alocado
    return(node);
}

/*
Nome: min_value
Objetivo: Encontrar o menor valor dentro de um árvore
Parâmetros: 
    tree root - Raiz da árvore a ser investigada
Valor de retorno:
    tree - Endereço do nó que possui a menor chave
*/
tree min_value(tree root){
    //Declarações locais
    tree aux;

    //Encontrando a menor chave, ou seja, folha mais à esquerda
    aux = root;
    while (aux->left != NULL){
        aux = aux->left;
    }

    //Retornando o endereço do nó com a menor chave
    return aux;
}

/*
Nome: fator_balanco
Objetivo: Calcular o fator de balanço do nó de uma árvore
Parâmetros: 
    tree root - Raiz da árvore a ter seu fator de balanço calculado
Valor de retorno:
    int - Fator de balanço do nó
*/
int fator_balanco(tree root){
    if(root == NULL){
        return 0;
    }
    else{
        return height(root->left) - height(root->right);
    }
}

/*
Nome: buscar_chave
Objetivo: Encontrar o endereço de um nó a partir de sua chave
Parâmetros: 
    tree root - Raiz da árvore a ser percorrida em busca da chave
    int key - Chave utilizada na busca
Valor de retorno:
    tree - Endereço do nó correspondente à chave passada como parâmetro
*/
tree buscar_chave(tree root, int key){
    //Se a árvore não possui nó ou possui nó e a chave buscada está nesse nó
    if(root == NULL || root->key == key){ 
        return root;                            //Retorna a própria raiz dessa árvore
    }

    //Se a chave buscada é maior que a chave da raiz da árvore
    if(root->key < key){
        return buscar_chave(root->right, key);  //Busca na subárvore à direita
    }

    //Se a chave buscada é menor que a chave da raiz da árvore
    return buscar_chave(root->left, key);       //Busca na subárvore à esquerda
}

/*
Nome: sucessor
Objetivo: Encontrar o sucessor de um nó
Parâmetros: 
    tree root - Raiz da árvore a ser percorrida em busca do sucessor
    int key - Chave do nó a ter seu sucessor encontrado
Valor de retorno:
    tree - Endereço do nó que possui a chave sucessora à do nó passado como parâmetro
*/
tree sucessor(tree root, int key){
    //Declarações locais
    tree aux, successor, ancestor;

    //Buscando o nó passado por referência
    aux = buscar_chave(root, key);
    if(aux == NULL){   //Se não há nó com a chave referência
        return NULL;    //Retorna nulo
    }

    //Encontrando o sucessor
    if(aux->right != NULL){                    //Se o nó possui subárvore à direta
        return min_value(aux->right);        //Encontra e retorna a menor chave dessa subárvore à direita
    }
    else{                                       //Se o nó não possui subárvore à direta
        successor = NULL;                       //Inicializa o sucessor como NULL
        ancestor = root;                        //Atribui a raiz à variável que representa o ancestral
        while(ancestor != aux){               //Enquanto o ancestral for diferente do nó passado por referência
            if(aux->key < ancestor->key){     //Se a chave do nó passado por referência é menor que a do ancestral
                successor = ancestor;           //O sucessor passa a ser o ancestral
                ancestor = ancestor->left;      //O ancestral se torna a raiz da sua subárvore à esquerda
            }
            else{                               //Se a chave do nó passado por referência é maior que a do ancestral
                ancestor = ancestor->right;     //O ancestral se torna a raiz da sua subárvore à direita
            }
        }
        //Retornando o endereço do nó sucessor ao nó passado por referência
        return successor;
    }
}

/*
Nome: rotacao_dir
Objetivo: Rotacionar uma árvore à direita
Parâmetros: 
    tree root - Raiz da árvore a ser rotacionada
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree rotacao_dir(tree root){
    //Declarações locais
    tree x, aux;

    //Realizando a rotação e atualizando as alturas
    x = root->left;
    aux = x->right;
    x->right = root;
    root->left = aux;
    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    //Retornando a nova raiz
    return x;
}

/*
Nome: rotacao_esq
Objetivo: Rotacionar uma árvore à esquerda
Parâmetros: 
    tree root - Raiz da árvore a ser rotacionada
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree rotacao_esq(tree root){
    //Declarações locais
    tree x, aux;

    //Realizando a rotação e atualizando as alturas
    x = root->right;
    aux = x->left;
    x->left = root;
    root->right = aux;
    root->height = max(height(root->left), height(root->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retornar nova raiz
    return x;
}

/*
Nome: rotacao_esq_dir
Objetivo: Rotacionar uma árvore duplamente à direita (esquerda-direita)
Parâmetros: 
    tree root - Raiz da árvore a ser rotacionada
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree rotacao_esq_dir(tree node){
    //Realizando a rotação para a esquerda
    node->left = rotacao_esq(node->left);
    //Realizando a rotação para a direita e retornando o endereço do novo nó raiz
    return rotacao_dir(node);
}

/*
Nome: rotacao_dir_esq
Objetivo: Rotacionar uma árvore duplamente à esquerda (direita-esquerda)
Parâmetros: 
    tree root - Raiz da árvore a ser rotacionada
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree rotacao_dir_esq(tree node){
    //Realizando a rotação para a direita
    node->right = rotacao_dir(node->right);
    //Realizando a rotação para a esquerda e retornando o endereço do novo nó raiz
    return rotacao_esq(node);
}

/*
Nome: inserir_chave
Objetivo: Inserir uma chave em uma árvore AVL
Parâmetros: 
    tree node - Raiz da árvore a receber a nova chave
    int key - Chave a ser inserida
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree inserir_chave(tree root, int key){
    //Declarações locais
    int balance;

    //Inserindo normalmente na árvore de acordo com suas propriedades
    if(root == NULL){                   //Se o nó é nulo
        return(new_node(key));          //Retornar um novo nó criado com a chave passada como parâmetro
    }
    else{                               //Se o nó não é nulo
        //Verifica se a inserção deve ocorrer na esquerda
        if(key < root->key){            
            root->left = inserir_chave(root->left, key);
        }
        //Verifica se a inserção deve ocorrer na direita
        else if(key > root->key){
           root->right = inserir_chave(root->right, key); 
        } 
        //Se a chave já existir a inserção não acontece
        else{
            return root;
        }
    }

    //Atualizando a altura e obtendo o novo fator de balanço do nó
    root->height = 1 + max(height(root->left), height(root->right));
    balance = fator_balanco(root);

    //Verificando o balanceamento
    if(balance < -1 || balance > 1){                            //Se a árvore está desbalanceada
        if(balance > 1){                                        //Se o desbalanceamento é na esquerda
            if(fator_balanco(root->left) < 0){                  //Se o fator de balanço da subárvore à esquerda é negativo
                return rotacao_esq_dir(root);                   //Faz uma rotação dupla à direita
            }
            else{                                               //Se o fator de balanço da subárvore à esquerda é zero ou positivo
                return rotacao_dir(root);                       //Faz uma rotação simples à direita
            }
        }
        else{                                                   //Se o desbalanceamento é na direita          
            if(fator_balanco(root->right) > 0){                 //Se o fator de balanço da subárvore à esquerda é negativo
                return rotacao_dir_esq(root);                   //Faz uma rotação dupla à esquerda
            }
            else{                                               //Se o fator de balanço da subárvore à esquerda é zero ou negativo
                return rotacao_esq(root);                       //Faz uma rotação simples à esquerda
            }
        }
    }
    else{                                                     //Se a árvore não está desbalanceada
        //Retorna o nó sem precisar realizar rotações
        return root;
    }
}

/*
Nome: remover_chave
Objetivo: Remover uma chave em uma árvore AVL
Parâmetros: 
    tree root - Raiz da árvore a ter a chave removida
    int key - Chave a ser removida
Valor de retorno:
    tree - Endereço do nó que passou a ser a raiz
*/
tree remover_chave(tree root, int key){
    //Declarações locais
    int balance;
    tree aux;

    //Removendo normalmente na árvore de acordo com suas propriedades
    if(root == NULL){                    //Se o nó é nulo
        return root;                     //Retorna o próprio nó já que ele é nulo
    }                    
    else{                                //Se o nó não é nulo
        //Verifica se a remoção deve ocorrer na esquerda
        if(key < root->key){            
            root->left = remover_chave(root->left, key);
        }
        //Verifica se a remoção deve ocorrer na direita
        else if(key > root->key){
            root->right = remover_chave(root->right, key);
        }
        //Se a chave for exatamente a do nó atual, então ele que deve ser removido
        else{
            if(root->left == NULL && root->right == NULL){      //Se o nó não possui filhos
                aux = root;                                     //Nó auxiliar recebe o nó a ser removido
                root = NULL;                                    //O nó passa a ser nulo
                free(aux);                                      //Nó auxiliar tem sua memória liberada
            }
            //Se o nó possui apenas 1 filho
            else if((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL)){
                //Identificando se o nó filho está na esquerda ou na direita
                if(root->left == NULL){
                    aux = root->right;
                }
                else{
                    aux = root->left;
                }

                *root = *aux;                                   //A raiz herda os dados do nó filho
                free(aux);                                      //Nó auxiliar tem sua memória liberada
            }
            //Se o nó possui dois filhos
            else{
                // Nó com dois filhos: obter o sucessor em ordem (menor na subárvore direita)
                aux = min_value(root->right);

                // Copiar o valor do sucessor em ordem para este nó
                root->key = aux->key;

                // Remover o sucessor em ordem
                root->right = remover_chave(root->right, aux->key);
            }
        }
    }

    //Se a árvore era composta por apenas este nó, então retornar
    if(root == NULL){
        return root;
    }
        
    //Atualizando a altura e obtendo o novo fator de balanço do nó
    root->height = 1 + max(height(root->left), height(root->right));
    balance = fator_balanco(root);

    //Verificando o balanceamento
    if(balance < -1 || balance > 1){                            //Se a árvore está desbalanceada
        if(balance > 1){                                        //Se o desbalanceamento é na esquerda
            if(fator_balanco(root->left) < 0){                  //Se o fator de balanço da subárvore à esquerda é negativo
                return rotacao_esq_dir(root);                   //Faz uma rotação dupla à direita
            }
            else{                                               //Se o fator de balanço da subárvore à esquerda é zero ou positivo
                return rotacao_dir(root);                       //Faz uma rotação simples à direita
            }
        }
        else{                                                   //Se o desbalanceamento é na direita          
            if(fator_balanco(root->right) > 0){                 //Se o fator de balanço da subárvore à esquerda é negativo
                return rotacao_dir_esq(root);                   //Faz uma rotação dupla à esquerda
            }
            else{                                               //Se o fator de balanço da subárvore à esquerda é zero ou negativo
                return rotacao_esq(root);                       //Faz uma rotação simples à esquerda
            }
        }
    }
    else{                                                     //Se a árvore não está desbalanceada
        //Retorna o nó sem precisar realizar rotações
        return root;
    }
}

/*
Nome: inorder
Objetivo: Percorrer e exibir de forma crescente todas as chaves de uma árvore
Parâmetros: 
    tree root - Raiz da árvore a ser exibida
Valor de retorno:
    void - Nenhum
*/
void inorder(tree root){
    //Percorrendo a árvore do menos elemento para o maior
    if(root != NULL){               //Se o nó passado como referência não é nulo
        inorder(root->left);        //Percorre mais à esquerda para encontrar os menores elemento
        printf("%d ", root->key);   //Exibe a chave do nó corrente
        inorder(root->right);       //Percorre mais à esquerda para encontrar os maiores elementos
    }
}