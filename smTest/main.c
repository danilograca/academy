/* 
 * File:   main.c
 * Author: Homine
 *
 * Created on 21 de Março de 2016, 21:37
 */
#include "stateMachine.h"

/*
 * 
 */
int main(int argc, char** argv) {

    sm_init();

    while (1) {
        
        sm_run();
    }

    return (0);
}

