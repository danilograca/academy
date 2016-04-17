/* 
 * File:   operational.c
 * Author: @DaniloGraca
 *
 * Created on 15 de Abril de 2016, 18:59
 */

/*
 * 
 */
unsigned int b_Panel = 1U;

/*
 * 
 */
unsigned short us_Mode = 1U;

/*
 * 
 */
signed short ss_Position = 0U;

/*
 * 
 */
void operational(unsigned int b_FAIL) {

    if (us_Mode == 2U) 
    {
        extend(b_FAIL);
    } 
    else if (us_Mode == 4U) 
    {
        retract(b_FAIL);
    } 
    else if (us_Mode == 1U) 
    {
        panelClose();
    } 
    else if (us_Mode == 3U)
    {
        panelOpen();
    } 
}

/*
 * 
 */
void extend(unsigned int b_FAIL) {

    if (b_FAIL == 1) 
    {
        // Mode EXTEND on REDUCED STATE
        ss_Position += 1U;
    } 
    else 
    {
        ss_Position += 2U;
    }

    if (ss_Position > 20U) 
    {
        // Change to mode PANEL OPEN
        us_Mode = 3U;
    }
}

/*
 * 
 */
void retract(unsigned int b_FAIL) {
    
    if (b_FAIL == 1) 
    {
        // Mode RETRACT 
        ss_Position -= 1U;
    } 
    else 
    {
        // Mode RETRACT 
        ss_Position -= 2U;
    }

    if (ss_Position < 0) 
    {
        //*Change to mode PANEL CLOSE
        us_Mode = 1U;
    }
}

/*
 * 
 */
void panelClose() {
    
    //* Mode PANEL CLOSE 
    if (b_Panel == 1U) 
    {
        //* Change to mode EXTEND 
        us_Mode = 2U;
    }
}

/*
 * 
 */
void panelOpen() {
    
    //*Mode PANEL OPEN
    if (b_Panel == 0) 
    {
        //*Change to mode RETRACT
        us_Mode = 4U;
    }
}

/*
 * 
 */
void shutdown(unsigned int b_FAIL){

    while(ss_Position != 0)
    {
        if (b_FAIL == 1) 
        {
            // Mode EXTEND on REDUCED STATE
            ss_Position -= 1U;
        } 
        else 
        {
            ss_Position -= 2U;
        }
    }
}