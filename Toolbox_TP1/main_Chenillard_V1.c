/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                            Chenillard                                      */
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

uint64_t test = 100000;

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
    GPIOB->ODR |=(1<<1); //Allumer les LEDs
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<1); //Eteindre les LEDs
    GPIOB->ODR |=(1<<2);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<2);
    GPIOB->ODR |=(1<<10);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<10);
    GPIOB->ODR |=(1<<11);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<11);
    GPIOB->ODR |=(1<<12);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<12); 
    GPIOB->ODR |=(1<<13);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<13);
    GPIOB->ODR |=(1<<14);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<14);
    GPIOB->ODR |=(1<<15);
    
    for(uint64_t i=0; i<=test;i++){} //Delay
    
    GPIOB->ODR &=~(1<<15);
  }
  
}

