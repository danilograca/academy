#include <stdio.h>
#include <stdint.h>
#include "stateMachine.h"
#include "ibit.h"
#include "maintenance.h"
#include "operational.h"

unsigned int b_On;
unsigned int b_Fail;
unsigned int b_Shutdown;
unsigned int b_Maintenance;
unsigned int b_Operational;

unsigned short us_State;

/*
 *  Variables Initialization of State Machine
 */
void sm_init() {
  
    us_State = 1U;
    b_On = 01U;
    b_Fail = 0U;
    b_Shutdown = 0U;
    b_Operational = 1U;
    b_Maintenance = 0U;  
}

/*
 * State Machine Declaration
 */
void sm_run() {

    if (us_State == 9U) 
    {       
        if (b_On == 0U) {
            
            /*System on STANDBY*/
            us_State = 1U;
        }
    } 
    else if (us_State == 7U) 
    {
        if (b_On == 0U) 
        {
            shutdown(b_Fail);
            
            us_State = 4U;    
        } 
        else 
        {
            operational(b_Fail);
        }
    }
    else if (us_State == 1U) 
    {
        if (b_On == 1)
        {
            /*Change State to IBIT*/
            us_State = 2U;
        }
    } 
    else if (us_State == 2U) 
    {
        us_State = ibit();
    } 
    else if (us_State == 3U) 
    {
        /*Change State to OPERATIONAL REDUCED*/
        us_State = 7U;
        
         /*Alert system to FAIL*/
        b_Fail = 1;
    } 
    else if (us_State == 4U) 
    {
        if (b_Maintenance == 1) 
        {
            /*Change State to MAINTENANCE*/
            us_State = 6U;
        } 
        
        if (b_Operational == 1) 
        {
            /*Change State to Operational*/
            us_State = 7U;
        }
    } 
    else 
    {
        if (us_State == 6U) 
        {
             if (b_Maintenance == 0U) 
            {
                shutdown();
            
                us_State = 4U;    
            } 
            else 
            {
                /*State MAINTENANCE*/
                maintenance();
            }
        }
    }
    
    printf("STATE %d ",us_State);

}
