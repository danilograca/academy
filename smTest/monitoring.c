/* 
 * File:   monitoring.c
 * Author: @DaniloGraca
 *
 * Created on 17 de Abril de 2016, 02:40
 */

/*
 * Storage Power from panel
 */
unsigned short us_Power = 100U;

/*
 * Manage power
 */
int getPower(){
    
    /* Return power */
    return us_Power;
}

/*
 * Monitoring the power from panel
 */
int monitoringPower(int state){
    
    /* Testing power */
    if (getPower() < 200)
    {
        /* Return to EMERGENCY state */
        return 9U;
    }
    
    return state;
}
 