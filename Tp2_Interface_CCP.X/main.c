/*
 * Programme fait par : Jeff Truong
 * Date : 04 Fev 2025
 * Description : un programme qui controle un servo moteur.
 * 
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application
 */

unsigned int trouver_CPPR (double duty);

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    //load la valeur PWM de base pour le mode neutre
    PWM2_LoadDutyValue(trouver_CPPR (7.5));
    //Menu etat neutre.
    printf("\r\n Appuyer sur l pour Lock ou u pour Unlock");
    
    while (1)
    {
        switch(EUSART1_Read())
        {
            //Cas Lock.
            case 'l':
                //load la valeur PWM a 11.5%
                PWM2_LoadDutyValue(trouver_CPPR (11.5));
                printf("\r\n Lock"); 
            break;
            //Cas Unlock.
            case 'u':
                //load la valeur PWM a 3.5%
                PWM2_LoadDutyValue(trouver_CPPR (3.5));
                printf("\r\n Unlock");
            break;
        }
    }
}

unsigned int trouver_CPPR (double duty)
{
    //si valeur duty cycle est entre 3.5 et 11.5 fait le calcul.
    if(duty >= 3.5 && duty <= 11.5)
    {
        return (duty/100)*0.019968/0.032768*1023;
    }
    //sinon retourne valeur minimum.
    else if (duty < 3.5)
    {
        return (21);
    }
    //sinon retourne valeur maximum.
    else
    {
        return (71);
    }
}
/**
 End of File
*/