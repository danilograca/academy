/* 
 * File:   ibit.c
 * Author: @DaniloGraca
 *
 * Created on 15 de Abril de 2016, 18:59
 */

#include "monitoring.h"

/*
 * Time count 
 */
unsigned long us_timeCount;

/*
 * Perform the Built-in Test
 * return: Next State
 */
int bit() {

    /* Start Counter */
    us_timeCount = 0;
    
    if (getPower() <= 200U) 
    {
        /* Change State to EMERGENCY */
        return 9U;
    }
    else if (getPower() <= 500U) 
    {
        /* Change State to FAIL */
        return 3U;
    }
    else 
    {
        /* Iterate time counter */
        us_timeCount++;

        if (us_timeCount > 5000000U) 
        {
            /* Change State to READY */
            return 4U;
            
            /* ReStart Counter */
            us_timeCount = 0;
        }
    }
}
