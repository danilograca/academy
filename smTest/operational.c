/* 
 * File:   operational.c
 * Author: @DaniloGraca
 *
 * Created on 15 de Abril de 2016, 18:59
 */

/*
 * 
 */
unsigned int b_Panel;

/*
 * 
 */
unsigned short us_Mode;

/*
 * 
 */
signed short ss_Position;

/*
 * Initialize variables
 */
void operational_init(){
    
    b_Panel = 0U;
    us_Mode = 1U;
    ss_Position = 0U;
}

/*
 * 
 */
void operational(unsigned int b_FAIL) {

    if (us_Mode == 1U) 
    {
        panelClosed();
    } 
    else if (us_Mode == 2U) 
    {
        extend(b_FAIL);
    } 
    else if (us_Mode == 3U)
    {
        panelOpened();
    } 
    else if(us_Mode == 4U) 
    {
        retract(b_FAIL);
    } 
    
    printf("\nPanel - %d", b_Panel );
    printf("\nMode - %d", us_Mode );
    printf("\nPosition - %d", ss_Position );
    
}

/*
 * Mode to open the panel
 */
void extend(unsigned int b_FAIL) {

    if (b_FAIL == 1) 
    {
        /* Mode EXTEND on REDUCED STATE */
        ss_Position += 1U;
    } 
    else 
    {
        /* Mode EXTEND on OPERATIONAL STATE */
        ss_Position += 2U;
    }

    if (ss_Position > 20U) 
    {
        /* Change to mode PANEL OPEN */
        us_Mode = 3U;
    }
}

/*
 * Mode to close the panel
 */
void retract(unsigned int b_FAIL) {
    
    if (b_FAIL == 1) 
    {
        /* Mode RETRACT on REDUCED state */
        ss_Position -= 1U;
    } 
    else 
    {
        /* Mode RETRACT on OPERATIONAL state */
        ss_Position -= 2U;
    }

    if (ss_Position < 0) 
    {
        /* Change to mode PANEL CLOSED */
        us_Mode = 1U;
    }
}

/*
 * Waiting with PANEL CLOSED
 */
void panelClosed() {
    
    /* IF set panel to OPEN */
    if (b_Panel == 1U) 
    {
        /* Change to mode EXTEND */
        us_Mode = 2U;
    }
}

/*
 * Mode WAITING with PANEL OPENED
 */
void panelOpened() {
    
    /* Mode PANEL OPEN */
    if (b_Panel == 0) 
    {
        /* Change to mode RETRACT */
        us_Mode = 4U;
    }
}

/*
 * Shutdown system safely
 */
void shutdown(unsigned int b_FAIL){

    /* Close the Panel before SHUTDOWN */
    while(ss_Position > 0)
    {
        if (b_FAIL == 1) 
        {
            /* Close panel on REDUCED STATE */
            ss_Position -= 1U;
        } 
        else 
        {
            /* Close panel on OPERATIONAL STATE */
            ss_Position -= 2U;
        }
    }
    
    /* Set panel to CLOSED */
    b_Panel = 0;
    
    /* Set Mode to WAITING with PANEL CLOSED */
    us_Mode = 1;
    
    printf("\nPanel - %d", b_Panel );
    printf("\nMode - %d", us_Mode );
    printf("\nPosition - %d", ss_Position );
}