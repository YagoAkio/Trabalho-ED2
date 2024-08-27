#define tamanho_string 50

struct token{
    char info[tamanho_string];
    struct token *prox;
};
typedef struct token Token;

struct linha{
    Token *token;
    struct linha *prox, *ant;
};
typedef struct linha Linha;

int prioridade(char token[20]){
    if(strcmp(token,"or")==1||strcmp(token,"and")==1||strcmp(token,"==")==1)
        return 1;
    else if(strcmp(token,"if")==1||strcmp(token,"else")==1||strcmp(token,"elif")==1)
        return 2;
    else if(strcmp(token,"while")==1||strcmp(token,"for")==1)
        return 3;
    else
        return 0;

}

FILE *abrir_programa(char nome_arquivo[20]){
    return fopen(nome_arquivo, "rb");
}

void exibir_arquivo_get(FILE *arquivo){
    char caracter;
    while((caracter = fgetc(arquivo))!=EOF){
        printf("%c",caracter);
    }
}

void exibir_arquivo_fscanf(FILE *arquivo){
    char informacao_linha_arquivo[tamanho_string];
    while (fscanf(arquivo, "%[^\n]\n",&informacao_linha_arquivo)!=EOF){
        printf("%s\n",informacao_linha_arquivo);
    }
}

Token *criar_token_vazio(){
    Token *token;
    token = (Token *) malloc(sizeof(Token *));
    token -> prox = NULL;
    return token;
}

Linha *criar_linha_vazia(){
    Linha *linha;
    linha = (Linha *) malloc(sizeof(Linha *));
    linha->token = criar_token_vazio();
    return linha;
}

/*
linha->prox = criar_linha_vazia();
linha_auxiliar = linha;
linha = linha->prox;
linha->ant = linha_auxiliar;
*/

//Linha *ler_programa (FILE *arquivo){
//    char caracter;
//    int contador_auxiliar=0;
//    Token *token;
//    Linha *linha, *linha_auxiliar;
//    linha = criar_linha_vazia();
//    token = linha->token;
//    while((caracter = fgetc(arquivo))!=EOF){
//        if(caracter == ' ' || caracter == '\n'){
//            token->info[++contador_auxiliar] = '\0';
//            contador_auxiliar = 0;
//            token -> prox = criar_token_vazio();
//            token = token -> prox;
//            if(caracter == '\n'){
//                linha->prox = criar_linha_vazia();
//                linha_auxiliar = linha;
//                linha = linha->prox;
//                linha->ant = linha_auxiliar;
//                token = linha->token;
//            }
//        }else{
//            token->info[contador_auxiliar++] = caracter;
//        }
//    }
//    return linha;
//}

Token *quebrar_linha(char informacao[tamanho_string]){
    Token *token;
    token = criar_token_vazio();
    strcpy(token->info,informacao);
    return token;
}

Linha *ler_programa(FILE *arquivo){
    Linha *linha_retorno, *linha, *linha_auxiliar;
    char informacao_linha_arquivo[tamanho_string];

    linha = criar_linha_vazia();
    linha_retorno = linha;

    while(fscanf(arquivo, "%[^\n]\n",&informacao_linha_arquivo)!=EOF){
        linha->token->prox = quebrar_linha(informacao_linha_arquivo);
        linha_auxiliar = criar_linha_vazia();
        linha->prox = linha_auxiliar;
        linha_auxiliar->ant = linha;
        linha = linha->prox;
    }

    return linha_retorno;
}

void exibir_programa_TAD (Linha *programa){
    Token *aux;
    while(programa->prox != NULL){
        aux = programa->token;
        while(aux->prox != NULL){
            printf("%s",aux->info);
            aux = aux->prox;
        }
        programa = programa->prox;
    }
}

//void adicionar_linha(){
//    char arquivo[]="arquivo.py";
//    printf("%s",ler_linha(abrir_programa(arquivo)).token);
//}