#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "usuarios.txt"
#define MAX 100

typedef struct {
    char nome[MAX];
    char senha[MAX];
} Usuario;

void criptografar(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] += 3; 
    }
}

void descriptografar(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] -= 3; 
    }
}

void adicionarUsuario() {
    Usuario u;
    FILE *file = fopen(FILENAME, "a");

    printf("Nome do usuario: ");
    scanf("%s", u.nome);
    printf("Senha do usuario: ");
    scanf("%s", u.senha);

    criptografar(u.senha);

    fprintf(file, "%s %s\n", u.nome, u.senha);
    fclose(file);
}

void listarUsuarios() {
    Usuario u;
    FILE *file = fopen(FILENAME, "r");

    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fscanf(file, "%s %s", u.nome, u.senha) != EOF) {
        descriptografar(u.senha);
        printf("Nome: %s, Senha: %s\n", u.nome, u.senha);
    }

    fclose(file);
}

void alterarUsuario() {
    Usuario u;
    char nome[MAX], novaSenha[MAX];
    int encontrado = 0;

    printf("Nome do usuario para alterar: ");
    scanf("%s", nome);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(file, "%s %s", u.nome, u.senha) != EOF) {
        if (strcmp(u.nome, nome) == 0) {
            printf("Nova senha: ");
            scanf("%s", novaSenha);
            criptografar(novaSenha);
            fprintf(temp, "%s %s\n", u.nome, novaSenha);
            encontrado = 1;
        } else {
            fprintf(temp, "%s %s\n", u.nome, u.senha);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (encontrado) {
        printf("Senha alterada com sucesso!\n");
    } else {
        printf("Usuario nao encontrado.\n");
    }
}

void excluirUsuario() {
    Usuario u;
    char nome[MAX];
    int encontrado = 0;

    printf("Nome do usuario para excluir: ");
    scanf("%s", nome);

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(file, "%s %s", u.nome, u.senha) != EOF) {
        if (strcmp(u.nome, nome) != 0) {
            fprintf(temp, "%s %s\n", u.nome, u.senha);
        } else {
            encontrado = 1;
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (encontrado) {
        printf("Usuario excluido com sucesso!\n");
    } else {
        printf("Usuario nao encontrado.\n");
    }
}

int main() {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Adicionar usuario\n");
        printf("2. Listar usuarios\n");
        printf("3. Alterar usuario\n");
        printf("4. Excluir usuario\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarUsuario();
                break;
            case 2:
                listarUsuarios();
                break;
            case 3:
                alterarUsuario();
                break;
            case 4:
                excluirUsuario();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 5);

    return 0;
}
