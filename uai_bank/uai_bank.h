#ifndef UAI_BANK_H
#define UAI_BANK_H

#include "../user/user.h"
#include "../vector/vector.h"

#include <stdio.h>

static Vector bd = {NULL, 0, sizeof(User)};

void carregar_banco();

void salvar_banco();

bool cadastrar_usuario(User* user);

void deletar_usuario();

void buscar_usuario();

void transferencia();

void deposito();

void saque();

double ler_valor(char* title);

uint64 ler_id();

uint64 selecionar_usuario(char* title);

bool existe_usuario(uint64);

User* getUserFromVector(Vector* , uint16 index);

#endif //UAI_BANK_H
