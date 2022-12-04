#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Vari�vel para sempre armazenar o arquivo aberto, para n�o precisar ficar criando toda vez
FILE *file;

//Corrigir acentua��o (metodo encontrado no liguagemc.com.br)
void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

// Armazenando informa��es do ranking em Struct, como solicitado na documenta��o
struct ranking{

    char nome[30];

    int pontuacao;

} r;

//Menu com op��es do game (cabe�alho)
void apresentacao(){

    //Sem opera��es l�gicas, apenas print do cabe�alho
    printf("---------------------------------------------\n");
	printf(">>>>>>>>>>>>>>> JOGO DA FORCA <<<<<<<<<<<<<<< \n");
	printf("---------------------------------------------\n");
	printf("_________________ OP��ES: __________________\n\n");

	printf("|1| JOGAR\n");
	printf("|2| CADASTRAR PALAVRA\n");
	printf("|3| RANKING\n");
	printf("|4| CR�DITOS\n");
	printf("|0| ENCERRAR\n");

	printf("\n---------------------------------------------\n");
}

//Cr�ditos aos alunos desenvolvedores
void creditos(){
    //Sem opera��es l�gicas, apenas print das informa��es dos alunos
    printf("---------------------------------------------\n");

    printf(">>>>>>>>>>>>>>> ALUNOS DEVS <<<<<<<<<<<<<<<<<\n");

    printf("---------------------------------------------\n");

    printf("\n|1|J�lio Monteiro \n");

	printf("\n|2|Audv�nio Marinho \n");

	printf("\n---------------------------------------------\n");
}

//Forca a ser desenhada com as condi��es
void forca(int status){

    int qtdeErros = status;

    //Desenho de forca
    printf("\n ---------------");

    printf("\n |       %c", (qtdeErros >= 1 ? '|' : ' ')); // Operador Condicional Tern�rio: Condi��o ? Consequ�ncia : Alternativa (para exibir a parte do "corpo" apenas com o numero de erros especifico para tal parte)

    printf("\n |       %c", (qtdeErros >= 1 ? 'o' : ' '));

    printf("\n |      %c%c%c", (qtdeErros >= 2 ? '-' : ' '), (qtdeErros >= 3 ? '|' : ' '), (qtdeErros >= 4 ? '-' : ' '));

    printf("\n |      %c %c", (qtdeErros >= 5 ? '/' : ' '), (qtdeErros >= 6 ? '\\' : ' '));

    printf("\n |");

    printf("\n |________");

    if (qtdeErros >= 6){ //Mensagem de derrota, exibida apenas ao atingir o limite de erros!

        printf("\n\n---------------------------------------------\n");
        printf(">>>>>>>>>>>>>>>> VOC� PERDEU! <<<<<<<<<<<<<<< \n");
        printf("| Que pena, voc� n�o acertou a palavra secreta!|\n");
        printf("---------------------------------------------\n");
    }
}

//Sortear e escolher uma palavra aleatoria no arquivo de palavras
char *sorteiaPalavra(char nomeArquivo[], char escolha[]) {

    char linha[100] [50];
    int contador = 0, i;

    // Abre o arquivo
    abrir_arqPalavras_ler();
    do {
        //L� linha do arquivo
        fgets(escolha, 30, file);

        //Retira as quebras extras de linhas
        for (i = 0; i < strlen(escolha); i++)
            if (escolha[i] == '\n')
                escolha[i] = '\0';

        //Testa se a string n�o est� vazia e armazena no vetor
            if (strcmp(escolha, "")) {
                strcpy(linha[contador], escolha);
                contador++;
            }
    } while (!feof(file));


    // Sorteia uma palavra pelo indice
    srand(time(NULL));
    i = rand() % contador + 1;

    strcpy(escolha, linha[i]);

    //Retorna uma palavra sorteada
    return escolha;

}

//Cadastro de Palavras
void cadastrar_palavra(){

    char palavra[100];

    printf("---------------------------------------------\n");
	printf(">>>>>>>>>>> CADASTRO DE PALAVRAS <<<<<<<<<<<< \n");
	printf("---------------------------------------------\n");
	printf(">OBS: Para cadastrar mais de uma palavra ao <\n");
	printf(">    mesmo tempo, as separe por espa�os!    < \n");
	printf("---------------------------------------------\n");

    //Solicita e coleta a palavra que o usu�rio deseja cadastrar
	printf("Digite a palavra que voc� deseja cadastrar: ");
	scanf("%s", &palavra);

    //Garantindo que todas as letras da palavra sejam cadastradas minusculas
	for(int i = 0; i < strlen(palavra); i++){
        palavra[i] = tolower(palavra[i]);
	}


    //Salvar palavra no arquivo
	abrir_arqPalavras_escrever(); //Abre o arquivo
	fprintf(file, palavra); //Pega a variavel palavra e adiciona no arquivo
    fprintf(file, "\n"); //Pula a linha no arquivo para quando for cadastrada uma nova palavra
    fflush(file); // Limpando o buffer
    fclose(file); // Fecha o arquivo.

    //Limpa a tela
    system("cls");

    printf("Dados gravados, retornando ao menu principal...");

    //Aguarda 2 segundos at� abrir o menu novamente
    sleep(2);


	printf("\n---------------------------------------------\n");



}

//Jogar
void jogar(){

    char palavra_secreta[30], palavra_tela[30], escolha[30];
    int erros = 0, correta = 0, pontuacao_final = 0, pontuacao_inicial = 100;
    char letra;

    //Buscando a palavra aleatoria no banco utilizando a fun��o "palavra_secreta"
    strcpy(palavra_secreta, sorteiaPalavra("palavras.txt", escolha));


    //Solicitando nome do jogador
    printf("JOGADOR:\n");
    printf("Qual o seu nome? \n");
    // Limpando o buffer com fflush
    fflush(stdin);
    //Coletando o nome do jogador com fgets
    fgets(r.nome, 30, stdin);
    //Limpando a tela
    system("cls");

    //Dica de quantas letr
    printf("A palavra tem %lu letras/caracteres", strlen(palavra_secreta));

    //Copia a palavra secreta para a vari�vel que vai aparecer na tela
    strcpy(palavra_tela, palavra_secreta);

    //Substitui a as letras da palavra por underline
    for (int i = 0; i < strlen(palavra_tela); i++){
        palavra_tela[i] = '_';
    }

    while (1){ // imprime a forca sem erros (0 atribuido � varialvel erros na declara��o de variaveis) e ja inicia os chutes das letras

        forca(erros);

        printf("\n A palavra secreta �: ");

        //Printando os underlines, ou seja, os espa�os das letras
        for (int i = 0; i < strlen(palavra_tela); i++){
            printf("%c ", palavra_tela[i]);
        }

        //Solicitando e recebendo a letra digitada
        printf("\n \n Digite a letra desejada: ");
        scanf(" %c", &letra);

        //Limpando a tela
        system("cls");

        int errou = 1; // Esta vari�vel "errou" ser� 1 quando o jogador ERRAR e 0 quando ACERTAR.

        //La�o FOR para comparar a letra digitada em todos os indices da palavra secreta.
        for (int i = 0; i < strlen(palavra_tela); i++){

            // Entra no if se o jogador acertou a letra.
            if (letra == tolower(palavra_secreta[i])){ //tolower para garantir que a letrar digitada estar� min�scula para compara��o
                palavra_tela[i] = letra;
                errou = 0; //Atribuindo 0 � v�riavel errou, que como dito, ser� 0 em caso de acerto
                printf("Pontua��o: %d", r.pontuacao);
            }
        }

        // Caso n�o entre no IF, a letra ser� errada, ent�o o errou seguir� como 1, ent�o, letra errada
        if (errou == 1){
            erros++;
            pontuacao_final = pontuacao_inicial - (erros * 10);
            r.pontuacao = pontuacao_final;
            printf("Pontua��o: %d", r.pontuacao);
        }

        // Caso o jogador use todas 6 chances e n�o complete a palavra, n�o pontua, ent�o, pontua��o = 0
        if (erros == 6){
            r.pontuacao = 0;
        }

        // Caso o jogador n�o cometa nenhum erro, sua pontua��o permanecer� igual a inicial (100 pontos)
        if (erros == 0){
            r.pontuacao = pontuacao_inicial;
        }

        // Compara as palavras (palavra secreta x palavra tela),se forem iguais printa o acerto.
        if (strcmp(palavra_tela, palavra_secreta) == 0){

            printf("\n\n---------------------------------------------\n");
            printf(">>>>>>>>>>>>>>>> VOC� GANHOU! <<<<<<<<<<<<<<< \n");
            printf(" Parab�ns %s , voc� acertou a palavra secreta!|\n", r.nome);
            printf("---------------------------------------------\n");

            //Printando a palavra na tela
            for (int i = 0; i < strlen(palavra_tela); i++){
                printf("%c ", palavra_tela[i]);
            }
            printf("\n---------------------------------------------\n\n\n");

            break;
        }

        //Caso atinja o limite de erros, usa a fun��o "forca" para printar que perdeu o jogo
        if (erros == 6){
            forca(erros);
            break;
        }

    } // Registra os dados do participante no arquivo de ranking
        abrir_arqRanking_escrever(); //Abre o arquivo com a fun��o criada
        fprintf(file, "Nome: %s", r.nome); //Registra nome
        fprintf(file, "Pontua��o: %d\n", r.pontuacao); //Registra Pontua��o
        fclose(file); // Fecha o arquivo.
}

void abrir_arqPalavras_escrever(){ // Essa fun��o abre o arquivo "palavras.txt" para a grava��o de novas palavras

    file = fopen("palavras.txt", "a"); // O "a" significa append, usado para adicionar dados a um arquivo j� existente ou, se ele n�o existir, criar e incluir o texto.

    if (file == NULL)
    {

        printf("Erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqPalavras_ler(){ //Essa fun��o abre o arquivo "palavras.txt" para leitura
   file = fopen("palavras.txt", "rt"); // O "rt" significa abertura para leitura do arquivo de texto
    if (file == NULL)
    {

        printf("erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqRanking_escrever(){ // Essa fun��o abre o arquivo "ranking.txt" para a grava��o dos usuarios e suas pontua��es

    file = fopen("ranking.txt", "a"); // O "a" significa append, usado para adicionar dados a um arquivo j� existente ou, se ele n�o existir, criar e incluir o texto.

    if (file == NULL)
    {

        printf("erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqRanking_ler(){ //Essa fun��o abre o arquivo "ranking.txt" para leitura
   file = fopen("ranking.txt", "rt");
    if (file == NULL)
    {

        printf("erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void exibirRanking(){
    char linha_nome[100], linha_pontos[100];
    char *nome;
    char *pontuacao;
    int i;

    printf("---------------------------------------------\n");
	printf(">>>>>>>>>>>>> RANKING DA FORCA <<<<<<<<<<<<<< \n");
	printf("---------------------------------------------\n");

	abrir_arqRanking_ler(); //Usando a fun��o criada para abrir o arquivo de ranking para leitura

	i = 1; //Vari�vel criada para ser utilizada com �ndice

	while (!feof(file)){ //Verificando todo o arquivo. "Enquanto n�o chegar ao fim"
        nome = fgets(linha_nome, 100, file); //Primeira linha nome
        pontuacao = fgets(linha_pontos, 100, file); //Segunda linha nome
        //No pr�ximo giro, busca as linhas sequintes no meu arquivo que segue a mesma ordem: nome -> pontos

        if (nome){ //Se foi poss�vel ler
            printf("|%d| %s - %s", i, nome, pontuacao);
        }
        i++; //aumentando o indice para o proximo la�o/posi��o
	}



	printf("\n---------------------------------------------\n");
}

int main(){

    ortografia(); //Fun��o para corrigir acentua��o

    int numeroMenuEscolhido = -1; //Iniciando a vari�vel de escolha de op��o (n�o foi iniciada com 0 pois essa op��o est� no menu

    do{

        int escolha; //vari�vel que aparece nas p�ginas de ranking e cr�ditos, dando op��o de retornar ao menu

        apresentacao(); //Fun��o com o cabe�alho do jogo

        printf("Escolha uma das op��es acima para seguir: \n");

        scanf("%d", &numeroMenuEscolhido);

        switch (numeroMenuEscolhido){

            case 1: //jogar

                system("cls");

                jogar();

                break;

            case 2: //cadastrar palavra

                system("cls");

                cadastrar_palavra();

                break;


            case 3: //ranking

                system("cls");

                exibirRanking();

                //Op��o de voltar ao menu ou encerrar o programa
                printf("\n Deseja voltar ao menu principal?\n Digite '1' para sim e '2' para n�o\n");
                fflush(stdin);
                scanf("%d", &escolha);

                if (escolha == 1){
                    apresentacao();
                    system("cls");
                }else{
                    exit(0);
                }

                break;;

            case 4: //creditos

                system("cls");

                creditos();

                //Op��o de voltar ao menu ou encerrar o programa
                printf("\n Deseja voltar ao menu principal?\n Digite '1' para sim e '2' para n�o\n");
                fflush(stdin);
                scanf("%d", &escolha);

                if (escolha == 1){
                    apresentacao();
                    system("cls");
                }else{
                    exit(0);
                }

                break;


            case 0: //encerrar

                system("cls");

                printf("Fim do Programa. \n");

                break;

            default:

                system("cls");

                printf("Op��o Inv�lida. \n");

                printf("Por favor escolha algum n�mero informado no Menu. \n\n\n");

                break;
            }

    }while (numeroMenuEscolhido != 0);

    return 0;
}
