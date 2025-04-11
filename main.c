#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

#include "uai_bank/uai_bank.h"
#include "util/file_util.h"
#include "util/io_util.h"

void print_menu() {

    printf("\n|=================================================|\n");
    printf("|                                                 |\n");
    printf("|              Bem Vindo ao Uai Bank              |\n");
    printf("|                                                 |\n");
    printf("|=================================================|\n\n");
    printf("|---------------------OPTIONS---------------------|\n\n");
    printf("| [1] Cadastrar novo Usuario                      |\n");
    printf("| [2] Cadastrar grupo de Usuarios                 |\n");
    printf("| [3] Deletar Usuario por ID                      |\n");
    printf("| [4] Buscar Usuario por ID                       |\n");
    printf("| [5] Realizar Transferencia                      |\n");
    printf("| [6] Realizar Deposito                           |\n");
    printf("| [7] Realizar Saque                              |\n");
    printf("| [8] Limpar Tela                                 |\n");
    printf("| [9] Sair                                        |\n");
    printf("|-------------------------------------------------|\n\n");
    printf("| Digite a opcao desejada: ");

}

int main() {
    setlocale(LC_ALL, "Portuguese");
    system("color 07");

    load_file_data(&bd);

    uint8 option;
    do {

        print_menu();
        option = (uint8) getchar();

        if (clearBuffer()) {
            error_message("Entrada excede limite de caracteres!\n");
            press_enter();
            continue;
        }

        switch (option) {
            case '1': {
                User newUser;
                if (cadastrar_usuario(&newUser)) {
                    save_user_data(&newUser);
                }
                break;
            }
            case '2': {

                break;
            }
            case '3': {
                deletar_usuario();
                create_file_data(&bd);
                break;
            }
            case '4': {
                buscar_usuario();
                break;
            }
            case '5': {
                transferencia();
                create_file_data(&bd);
                break;
            }
            case '6': {
                deposito();
                create_file_data(&bd);
                break;
            }
            case '7': {
                saque();
                create_file_data(&bd);
                break;
            }
            case '8': {
                system("cls");
                break;
            }
            case '9': {
                printf("Finalizando Sistema...\n");
                create_file_data(&bd);
                successful_message("Finalizacao Concluida!\n");
                break;
            }
            default: {
                error_message("Erro: Entrada invalida!\n");
                break;
            }
        }
        press_enter();
    }
    while (option != '9');
    return 0;
}