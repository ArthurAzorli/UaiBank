#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "uai_bank/uai_bank.h"
#include "util/io_util.h"

/**
 * @by: Arthur Gagliardi Azorli
 * @numero_usp: 16855452
 */


void print_menu() {

    printf("\n");
    printf("|=================================================|\n");
    printf("|                                                 |\n");
    printf("|              Bem Vindo ao Uai Bank              |\n");
    printf("|                                                 |\n");
    printf("|=================================================|\n\n");
    printf("|---------------------OPTIONS---------------------|\n\n");
    printf("| [1] Cadastrar novo Usuario                      |\n");
    printf("| [2] Cadastrar multiplos Usuarios                |\n");
    printf("| [3] Deletar Usuario por ID                      |\n");
    printf("| [4] Buscar Usuario por ID                       |\n");
    printf("| [5] Realizar Transferencia                      |\n");
    printf("| [6] Realizar Deposito                           |\n");
    printf("| [7] Realizar Saque                              |\n");
    printf("| [8] Limpar Tela                                 |\n");
    printf("| [9] Finalizar Programa                          |\n");
    printf("|-------------------------------------------------|\n\n");
    printf("| Digite a opcao desejada: ");
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 07");

    carregar_banco();

    int option;
    do {
        print_menu();
        option = getchar();

        if (clearBuffer()) {
            error_message("Entrada excede limite de caracteres!\n");
            press_enter();
            continue;
        }

        printf("\n");

        switch (option) {
            case '1': {
                cadastrar_usuario();
                break;
            }
            case '2': {
                cadastrar_multiplos_usuarios();
                break;
            }
            case '3': {
                deletar_usuario();
                break;
            }
            case '4': {
                buscar_usuario();
                break;
            }
            case '5': {
                transferencia();;
                break;
            }
            case '6': {
                deposito();
                break;
            }
            case '7': {
                saque();
                break;
            }
            case '8': {
                system("cls");
                break;
            }
            case '9': {
                printf("Finalizando Sistema...\n");
                salvar_banco();
                successful_message("Finalizacao Concluida!\n");
                break;
            }
            default: {
                error_message("Entrada invalida!\n");
                break;
            }
        }
        press_enter();
    }
    while (option != '9');
    return 0;
}