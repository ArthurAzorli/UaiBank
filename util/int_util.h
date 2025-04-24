#ifndef INT_UTIL_H
#define INT_UTIL_H

typedef unsigned long long int uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef signed long long int int64;
typedef signed int int32;
typedef signed short int16;
typedef signed char int8;

typedef int bool;
#define true	1
#define false	0

/**
 * @brief
 * @param text : valor em texto
 * @return : valor booleano que indica se o valor em texto se tratar de um número natural
 */
bool isNumber(const char* text);

/**
 * @brief
 * @param text : valor em texto
 * @return : valor booleano que indica se o valor em texto se tratar de um número real
 */
bool isDouble(const char* text);
#endif //INT_UTIL_H
