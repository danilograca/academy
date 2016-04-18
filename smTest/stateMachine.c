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
    b_Operational = 0U;
    b_Maintenance = 0U;
}

/*
 * State Machine
 */
void sm_run() {

    /* STANDBY STATE */
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
        /* OPERATIONAL STATE */
        if (us_State == 7U) 
        {
            if (b_Operational == 1U) 
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
            
            /* Call Health Monitoring
             * return: state if changed */
            us_State = monitoringPower(us_State);
        } 
        
        /* BIT STATE */
        else if (us_State == 2U) 
        {
            /* Call Built-in Test */
            us_State = bit();
            
            /* Call Health Monitoring
             * return: state if changed */
            us_State = monitoringPower(us_State);
        }
        
        /* FAIL STATE */
        else if (us_State == 3U) 
        {
            /* Alert system to FAIL */
            b_Fail = 1U;
            
             if (b_On == 0U) 
            {
                /*Change State to STANDBY*/
                us_State = 1U;
            }
            
            if (b_Operational == 1U) 
            {
                /* Change State to OPERATIONAL REDUCED */
                us_State = 7U;
                
                /* Initialize operational variables */
                operational_init();
            }
            
            /* Call Health Monitoring
             * return: state if changed */
            us_State = monitoringPower(us_State);
        }
        
        /* READY STATE */
        else if (us_State == 4U) 
        {
            if (b_On == 0U) 
            {
                /*Change State to STANDBY*/
                us_State = 1U;
            }
            
            if (b_Maintenance == 1U) 
            {
                /*Change State to MAINTENANCE*/
                us_State = 6U;
            }

            if (b_Operational == 1U) 
            {
                /*Change State to Operational*/
                us_State = 7U;
                
                /* Initialize operational variables */
                operational_init();
            }
            
            /* Call Health Monitoring
             * return: state if changed */
            us_State = monitoringPower(us_State);
        }
        
        /* MAINTENANCE STATE */
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
            
            /* Call Health Monitoring
             * return: state if changed */
            us_State = monitoringPower(us_State);
        }
        else 
        {
            /* EMERGENCY STATE */
            if (us_State == 9U) 
            {
                /* System Turn OFF */
                b_On = 0;
                
                /* Set FAIL Alert to OFF */
                b_Fail = 0;

                /* Change state to STANDBY */
                us_State = 1U;

                /* Emergency Active */
                b_Emergency = 1U;
                
                /* Operational OFF */
                b_Operational = 0U;
                
                /* Shutdown System Safely */
                shutdown(b_Fail);
            }
        }
    }
    
    printf("\nState - %d \n", us_State );
    printf("On - %d \n", b_On );
    printf("Fail - %d \n", b_Fail );
    printf("Shutdown - %d \n", b_Shutdown );
    printf("Emergency - %d \n", b_Emergency );
    printf("Operational - %d \n", b_Operational );
    printf("Maintenance - %d", b_Maintenance );
}
