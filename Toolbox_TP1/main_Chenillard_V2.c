/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                          Chenillard V2                                     */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*                         Jason PUEL                                         */
/*                       Septembre 2018                                       */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/



#include "stm32l1xx_nucleo.h"

uint64_t T=40000;

/*---------------------------------------------*/

void INIT_LED(){
GPIOB->MODER |=(1<<2);    //LED 0 sur la pin PB1 (p12)
GPIOB->MODER |=(1<<4);    //LED 1 sur la pin PB2
GPIOB->MODER |=(1<<20);   //LED 2 sur la pin PB10  
GPIOB->MODER |=(1<<22);   //LED 3 sur la pin PB11
GPIOB->MODER |=(1<<24);   //LED 4 sur la pin PB12
GPIOB->MODER |=(1<<26);   //LED 5 sur la pin PB13
GPIOB->MODER |=(1<<28);   //LED 6 sur la pin PB14
GPIOB->MODER |=(1<<30);   //LED 7 sur la pin PB15
}

/*--------------Programme-Principal------------*/

void main()
{
RCC ->AHBENR |=(1<<1);   //Allumer l'horloge GPIOx (p4)

INIT_LED();

  while(1)
  {
    
    for(uint64_t k=1; k<=2; k++){
        GPIOB->ODR |=(1<<k); //Allumer les LEDs
        for(uint64_t i=0; i<=T; i++){} //Delay
        GPIOB->ODR &=~(1<<k); 
    }
    
    for(uint64_t j=10; j<=15; j++){
        GPIOB->ODR |=(1<<j);
        for(uint64_t i=0; i<=T; i++){} //Delay
        GPIOB->ODR &=~(1<<j);}
    
  }
  
}

