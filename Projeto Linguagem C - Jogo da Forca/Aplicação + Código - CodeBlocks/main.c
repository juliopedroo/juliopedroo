#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Variável para sempre armazenar o arquivo aberto, para não precisar ficar criando toda vez
FILE *file;

//Corrigir acentuação (metodo encontrado no liguagemc.com.br)
void ortografia() {
    setlocale(LC_ALL, "Portuguese");
}

// Armazenando informações do ranking em Struct, como solicitado na documentação
struct ranking{

    char nome[30];

    int pontuacao;

} r;

//Menu com opções do game (cabeçalho)
void apresentacao(){

    //Sem operações lógicas, apenas print do cabeçalho
    printf("---------------------------------------------\n");
	printf(">>>>>>>>>>>>>>> JOGO DA FORCA <<<<<<<<<<<<<<< \n");
	printf("---------------------------------------------\n");
	printf("_________________ OPÇÕES: __________________\n\n");

	printf("|1| JOGAR\n");
	printf("|2| CADASTRAR PALAVRA\n");
	printf("|3| RANKING\n");
	printf("|4| CRÉDITOS\n");
	printf("|0| ENCERRAR\n");

	printf("\n---------------------------------------------\n");
}

//Créditos aos alunos desenvolvedores
void creditos(){
    //Sem operações lógicas, apenas print das informações dos alunos
    printf("---------------------------------------------\n");

    printf(">>>>>>>>>>>>>>> ALUNOS DEVS <<<<<<<<<<<<<<<<<\n");

    printf("---------------------------------------------\n");

    printf("\n|1|Júlio Monteiro \n");

	printf("\n|2|Audvânio Marinho \n");

	printf("\n---------------------------------------------\n");
}

//Forca a ser desenhada com as condições
void forca(int status){

    int qtdeErros = status;

    //Desenho de forca
    printf("\n ---------------");

    printf("\n |       %c", (qtdeErros >= 1 ? '|' : ' ')); // Operador Condicional Ternário: Condição ? Consequência : Alternativa (para exibir a parte do "corpo" apenas com o numero de erros especifico para tal parte)

    printf("\n |       %c", (qtdeErros >= 1 ? 'o' : ' '));

    printf("\n |      %c%c%c", (qtdeErros >= 2 ? '-' : ' '), (qtdeErros >= 3 ? '|' : ' '), (qtdeErros >= 4 ? '-' : ' '));

    printf("\n |      %c %c", (qtdeErros >= 5 ? '/' : ' '), (qtdeErros >= 6 ? '\\' : ' '));

    printf("\n |");

    printf("\n |________");

    if (qtdeErros >= 6){ //Mensagem de derrota, exibida apenas ao atingir o limite de erros!

        printf("\n\n---------------------------------------------\n");
        printf(">>>>>>>>>>>>>>>> VOCÊ PERDEU! <<<<<<<<<<<<<<< \n");
        printf("| Que pena, você não acertou a palavra secreta!|\n");
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
        //Lê linha do arquivo
        fgets(escolha, 30, file);

        //Retira as quebras extras de linhas
        for (i = 0; i < strlen(escolha); i++)
            if (escolha[i] == '\n')
                escolha[i] = '\0';

        //Testa se a string não está vazia e armazena no vetor
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
	printf(">    mesmo tempo, as separe por espaços!    < \n");
	printf("---------------------------------------------\n");

    //Solicita e coleta a palavra que o usuário deseja cadastrar
	printf("Digite a palavra que você deseja cadastrar: ");
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

    //Aguarda 2 segundos até abrir o menu novamente
    sleep(2);


	printf("\n---------------------------------------------\n");



}

//Jogar
void jogar(){

    char palavra_secreta[30], palavra_tela[30], escolha[30];
    int erros = 0, correta = 0, pontuacao_final = 0, pontuacao_inicial = 100;
    char letra;

    //Buscando a palavra aleatoria no banco utilizando a função "palavra_secreta"
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

    //Copia a palavra secreta para a variável que vai aparecer na tela
    strcpy(palavra_tela, palavra_secreta);

    //Substitui a as letras da palavra por underline
    for (int i = 0; i < strlen(palavra_tela); i++){
        palavra_tela[i] = '_';
    }

    while (1){ // imprime a forca sem erros (0 atribuido à varialvel erros na declaração de variaveis) e ja inicia os chutes das letras

        forca(erros);

        printf("\n A palavra secreta é: ");

        //Printando os underlines, ou seja, os espaços das letras
        for (int i = 0; i < strlen(palavra_tela); i++){
            printf("%c ", palavra_tela[i]);
        }

        //Solicitando e recebendo a letra digitada
        printf("\n \n Digite a letra desejada: ");
        scanf(" %c", &letra);

        //Limpando a tela
        system("cls");

        int errou = 1; // Esta variável "errou" será 1 quando o jogador ERRAR e 0 quando ACERTAR.

        //Laço FOR para comparar a letra digitada em todos os indices da palavra secreta.
        for (int i = 0; i < strlen(palavra_tela); i++){

            // Entra no if se o jogador acertou a letra.
            if (letra == tolower(palavra_secreta[i])){ //tolower para garantir que a letrar digitada estará minúscula para comparação
                palavra_tela[i] = letra;
                errou = 0; //Atribuindo 0 à váriavel errou, que como dito, será 0 em caso de acerto
                printf("Pontuação: %d", r.pontuacao);
            }
        }

        // Caso não entre no IF, a letra será errada, então o errou seguirá como 1, então, letra errada
        if (errou == 1){
            erros++;
            pontuacao_final = pontuacao_inicial - (erros * 10);
            r.pontuacao = pontuacao_final;
            printf("Pontuação: %d", r.pontuacao);
        }

        // Caso o jogador use todas 6 chances e não complete a palavra, não pontua, então, pontuação = 0
        if (erros == 6){
            r.pontuacao = 0;
        }

        // Caso o jogador não cometa nenhum erro, sua pontuação permanecerá igual a inicial (100 pontos)
        if (erros == 0){
            r.pontuacao = pontuacao_inicial;
        }

        // Compara as palavras (palavra secreta x palavra tela),se forem iguais printa o acerto.
        if (strcmp(palavra_tela, palavra_secreta) == 0){

            printf("\n\n---------------------------------------------\n");
            printf(">>>>>>>>>>>>>>>> VOCÊ GANHOU! <<<<<<<<<<<<<<< \n");
            printf(" Parabéns %s , você acertou a palavra secreta!|\n", r.nome);
            printf("---------------------------------------------\n");

            //Printando a palavra na tela
            for (int i = 0; i < strlen(palavra_tela); i++){
                printf("%c ", palavra_tela[i]);
            }
            printf("\n---------------------------------------------\n\n\n");

            break;
        }

        //Caso atinja o limite de erros, usa a função "forca" para printar que perdeu o jogo
        if (erros == 6){
            forca(erros);
            break;
        }

    } // Registra os dados do participante no arquivo de ranking
        abrir_arqRanking_escrever(); //Abre o arquivo com a função criada
        fprintf(file, "Nome: %s", r.nome); //Registra nome
        fprintf(file, "Pontuação: %d\n", r.pontuacao); //Registra Pontuação
        fclose(file); // Fecha o arquivo.
}

void abrir_arqPalavras_escrever(){ // Essa função abre o arquivo "palavras.txt" para a gravação de novas palavras

    file = fopen("palavras.txt", "a"); // O "a" significa append, usado para adicionar dados a um arquivo já existente ou, se ele não existir, criar e incluir o texto.

    if (file == NULL)
    {

        printf("Erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqPalavras_ler(){ //Essa função abre o arquivo "palavras.txt" para leitura
   file = fopen("palavras.txt", "rt"); // O "rt" significa abertura para leitura do arquivo de texto
    if (file == NULL)
    {

        printf("erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqRanking_escrever(){ // Essa função abre o arquivo "ranking.txt" para a gravação dos usuarios e suas pontuações

    file = fopen("ranking.txt", "a"); // O "a" significa append, usado para adicionar dados a um arquivo já existente ou, se ele não existir, criar e incluir o texto.

    if (file == NULL)
    {

        printf("erro na abertura do Arquivo\n");

        system("pause");

        exit(0);
    }
}

void abrir_arqRanking_ler(){ //Essa função abre o arquivo "ranking.txt" para leitura
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

	abrir_arqRanking_ler(); //Usando a função criada para abrir o arquivo de ranking para leitura

	i = 1; //Variável criada para ser utilizada com índice

	while (!feof(file)){ //Verificando todo o arquivo. "Enquanto não chegar ao fim"
        nome = fgets(linha_nome, 100, file); //Primeira linha nome
        pontuacao = fgets(linha_pontos, 100, file); //Segunda linha nome
        //No próximo giro, busca as linhas sequintes no meu arquivo que segue a mesma ordem: nome -> pontos

        if (nome){ //Se foi possível ler
            printf("|%d| %s - %s", i, nome, pontuacao);
        }
        i++; //aumentando o indice para o proximo laço/posição
	}



	printf("\n---------------------------------------------\n");
}

int main(){

    ortografia(); //Função para corrigir acentuação

    int numeroMenuEscolhido = -1; //Iniciando a variável de escolha de opção (não foi iniciada com 0 pois essa opção está no menu

    do{

        int escolha; //variável que aparece nas páginas de ranking e créditos, dando opção de retornar ao menu

        apresentacao(); //Função com o cabeçalho do jogo

        printf("Escolha uma das opções acima para seguir: \n");

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

                //Opção de voltar ao menu ou encerrar o programa
                printf("\n Deseja voltar ao menu principal?\n Digite '1' para sim e '2' para não\n");
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

                //Opção de voltar ao menu ou encerrar o programa
                printf("\n Deseja voltar ao menu principal?\n Digite '1' para sim e '2' para não\n");
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

                printf("Opção Inválida. \n");

                printf("Por favor escolha algum número informado no Menu. \n\n\n");

                break;
            }

    }while (numeroMenuEscolhido != 0);

    return 0;
}
