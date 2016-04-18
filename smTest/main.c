/* 
 * File:   main.c
 * Author: @DaniloGraca
 *
 * Created on 21 de Março de 2016, 21:37
 */
#include "stateMachine.h"

/*
 * Main Procedure
 */
int main(int argc, char** argv) {

    /*
     * Initialize all variables used on stateMachine
     */
    sm_init();

    /*
     * Looping forever
     */
    //while (1) {
        
        /*
         * Call state machine
         */
        sm_run();
    //}

    return (0);
}

