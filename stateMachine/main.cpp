/* 
 * File:   main.cpp
 * Author: DaniloGraca
 *
 * Created on 20 de Março de 2016, 01:49
 */

#include <cstdlib>
#include <iostream>

using namespace std;

namespace variables {
    
    bool b_On;
    bool b_Fail;
    bool b_Panel;
    bool b_Shutdown;
    bool b_Maintenance;
    signed short sshort_Position;
    unsigned short ushort_Mode;
    unsigned short ushort_Power;
    unsigned short ushort_State;
    unsigned short ushort_timeCount; 
}

void stateMachine();

int main() {
    
    unsigned short in1 = 0U;

    variables::b_Fail = false;
    variables::ushort_Mode = 0U;
    variables::b_Panel = false;
    variables::sshort_Position = 0U;
    variables::ushort_State = 1U;
    variables::ushort_Power = 0U;
    variables::b_On = false;
    variables::b_Maintenance = false;
    variables::ushort_timeCount = 0U;
    variables::b_Shutdown = false;

    do {
        std::cout << "\n"
                "\n | Please, Choose Variable.  |"
                "\n | ========================= |"
                "\n | 1 - On                    |"
                "\n | 2 - Power                 |"
                "\n | 3 - Maintenance           |"
                "\n | 4 - SHUTDOWN              |"
                "\n | 5 - Run Again             |"
                "\n | 0 - EXIT                  |"
                "\n | ========================= |"
                "\n   -->> ";
        std::cin >> in1;

        if (in1 != 0U) {
            switch (in1) {
                case 1U:
                    std::cout << " | ========================= |\n | Please, Enter Value:      |\n   -->> ";
                    std::cin >> variables::b_On;
                    break;

                case 2U:
                    std::cout << " | ========================= |\n | Please, Enter Value:      |\n   -->> ";
                    std::cin >> variables::ushort_Power;
                    break;

                case 3U:
                    std::cout << " | ========================= |\n | Please, Enter Value:      |\n   -->> ";
                    std::cin >> variables::b_Maintenance;
                    break;

                case 4U:
                    std::cout << " | ========================= |\n | Please, Enter Value:      |\n   -->> ";
                    std::cin >> variables::b_Shutdown;
                    break;

                case 5U:
                    std::cout << " | ========================= |\n | ===== Running Again ===== |";
                    stateMachine();  
                    break;

                default:
                    std::cout << " | ========================= |\n | ===== Running Again ===== |";
                    break;
            }
        }
    } while (in1 != 0U);
    return 0;
}

void stateMachine() {
   
    if (variables::ushort_State == 9U) 
    {
        /*EMERGENCY STATE*/
        variables::ushort_State = 1U;
        /*System on STANDBY*/
        variables::b_On = false;
    }
    else if (variables::ushort_State == 7U) 
    {
        if (variables::ushort_Mode == 2U) 
        {
            if (variables::b_Fail) 
            {
                // Mode EXTEND on REDUCED STATE
                variables::sshort_Position += 1U;
            } 
            else 
            {
                variables::sshort_Position += 2U;
            }

            if (variables::sshort_Position >= 20U) 
            {
                // Change to mode PANEL OPEN
                variables::ushort_Mode = 3U;
            }
        } 
        else if (variables::ushort_Mode == 4U) 
        {
            if (variables::b_Fail) 
            {
                // Mode RETRACT 
                variables::sshort_Position -= 1U;
            } 
            else 
            {// Mode RETRACT 
                variables::sshort_Position -= 2U;
            }
            if (variables::sshort_Position <= 0U) 
            {
                //*Change to mode PANEL CLOSE
                variables::ushort_Mode = 1U;
                cout << "PANEL CLOSE";
            }
        } 
        else if (variables::ushort_Mode == 1U) 
        {
            //* Mode PANEL CLOSE 
            if (variables::b_Panel == true) 
            {
                //* Change to mode EXTEND 
                variables::ushort_Mode = 2U;
            }
        } 
        else if (variables::ushort_Mode == 3U) 
        {
            //*Mode PANEL OPEN
            if (variables::b_Panel == false) 
            {
                //*Change to mode RETRACT
                variables::ushort_Mode = 4U;
                cout << "PANEL OPEN";
            }
        } 
        else 
        {
            // Mode SAFE SHUTDOWN
            variables::sshort_Position = 0U;
        }
    }
    else if (variables::ushort_State == 1U) 
    {
        if (variables::b_On == true) 
        {
            /*Change State to IBIT*/
            variables::ushort_State = 2U;
            variables::ushort_timeCount = 0U;
        }

        if (variables::b_Shutdown == true) 
        {
            std::cout << "|SHUTDOWN|";
        }
    }
    else if (variables::ushort_State == 2U) 
    {
        if (variables::ushort_Power <= 200U) 
        {
            /*Change State to EMERGENCY*/
            variables::ushort_State = 9U;
        }
        else if (variables::ushort_Power <= 500U) 
        {
            /*Change State to FAIL*/
            variables::ushort_State = 3U;
        }
        else 
        {
            variables::ushort_timeCount++;

            if (variables::ushort_timeCount >= 5U) 
            {
                /*Change State to READY*/
                variables::ushort_State = 4U;
            }
        }
    }
    else if (variables::ushort_State == 3U) 
    {
        /*Change State to OPERATIONAL REDUCED*/
        variables::ushort_State = 7U;
        variables::ushort_Mode = 1U;
        variables::b_Fail = true;
        cout << "REDUCED MODE";
    }
    else if (variables::ushort_State == 4U) 
    {
        if (variables::b_Maintenance == true) 
        {
            /*Change State to MAINTENANCE*/
            variables::ushort_State = 6U;
        }
        else 
        {
            /*Change State to Operational*/
            variables::ushort_State = 7U;
        }
    }
    else 
    {
        if (variables::ushort_State == 6U) 
        {
            /*State MAINTENANCE*/
            
        }
    }
}

