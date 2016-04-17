/* 
 * File:   stateMachine.c
 * Author: @DaniloGraca
 *
 * Created on 15 de Abril de 2016, 18:59
 */

#include <stdio.h>
#include <stdint.h>
#include "stateMachine.h"
#include "bit.h"
#include "maintenance.h"
#include "operational.h"
#include "monitoring.h"

/*
 * 
 */
unsigned int b_On;

/*
 * 
 */
unsigned int b_Fail;

/*
 *
 */
unsigned int b_Shutdown;

/*
 * 
 */
unsigned int b_Maintenance;

/*
 * 
 */
unsigned int b_Emergency;

/*
 * 
 */
unsigned int b_Operational;

/*
 * 
 */
unsigned short us_State;

/*
 *  Variables Initialization
 */
void sm_init() {

    us_State = 1U;
    b_On = 1U;
    b_Fail = 0U;
    b_Shutdown = 0U;
    b_Operational = 1U;
    b_Maintenance = 0U;
}

/*
 * State Machine Declaration
 */
void sm_run() {

    if (us_State == 1U) 
    {
        if (b_On == 1U) 
        {
            /* Change State to IBIT */
            us_State = 2U;
        }

        if (b_Emergency == 1U) 
        {
            printf(" --EMERGENCY ACTIVATED-- ");
        }
    }
    else 
    {
        if (us_State == 7U) 
        {
            if (b_On == 1U) 
            {
                /* Call OPERATIONAL state */
                operational(b_Fail); 
            }
            else 
            {
                /* Call to Close Panel */
                shutdown(b_Fail);

               if(b_Fail == 1)
               {
                   /* Return to Fail state */
                   us_State = 3U;
               }
               else
               {
                   /* Return to READY state */
                   us_State = 4U;
               }
            }
            
            us_State = monitoringPower(us_State);
        } 
        else if (us_State == 2U) 
        {
            us_State = bit();
            
            us_State = monitoringPower(us_State);
        }
        else if (us_State == 3U) 
        {
            /* Alert system to FAIL */
            b_Fail = 1U;
            
            if (b_Operational == 1U) 
            {
                /* Change State to OPERATIONAL REDUCED */
                us_State = 7U;    
            }
            
            us_State = monitoringPower(us_State);
        }
        else if (us_State == 4U) 
        {
            if (b_Maintenance == 1U) 
            {
                /*Change State to MAINTENANCE*/
                us_State = 6U;
            }

            if (b_Operational == 1U) 
            {
                /*Change State to Operational*/
                us_State = 7U;
            }
            
            us_State = monitoringPower(us_State);
        }
        else if (us_State == 6U) 
        {
            if (b_Maintenance == 0U) 
            {
                /* Call to Close Panel */
                shutdown(b_Fail);

                /* Change State to READY */
                us_State = 4U;
            }
            else 
            {
                /* State MAINTENANCE */
                maintenance();
            }
            
            us_State = monitoringPower(us_State);
        }
        else 
        {
            if (us_State == 9U) 
            {
                /* Emergency Ative */
                b_Emergency = 1U;

                /* Shutdown System Safely */
                shutdown(b_Fail);

                /* System on STANDBY */
                us_State = 1U;

                /* Turn OFF */
                b_On = 0;
            }
        }
    }
}
