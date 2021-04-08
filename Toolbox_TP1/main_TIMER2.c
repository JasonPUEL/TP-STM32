/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                            Timer                                           */
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

void delay(uint64_t T){        //utilisation du TIMER au lieu des boucles for
  RCC->APB1ENR |=(1<<0);//activation de l'horloge du périphérique TIM2 sur le groupe RCC par le bus APB1
  /*TIMER  suivre cheminement page 35*/
  TIM2->PSC =(15999);//prescaler; donne la fréquence du clock
  TIM2->ARR =(T); // changement de la valeur autoreload prise au prochain événement
  
  //Registre controle TIM2
  TIM2->CR1 |=(1<<7);// recharger automatiquement le préchargeur -> ARPE=1
  TIM2->CR1 &=~((1<<6)|(1<<5)|(1<<4));//CMS en mode compte ou décompte selon le bit de direction qui est en mode DIR=décompte
    
  TIM2->CR1 |=(1<<0); //activer le compteur avec CEN
  while((TIM2->SR &(1<<0))==0);//tant qu' on compte; soit que le premier bit (UIF) est à 0
  TIM2->SR &=~(1<<0); //on fini de compter; c-a-d on désactive l'interruption
  TIM2->CR1 &=~(1<<0); //on désactive le compteur avec CEN
}

/*---------------------------------------------*/

void INIT_LED(){
  RCC->AHBENR |= (1<<1);//activation de l'horloge périphérique au port digital GPIOB pour allumer les LEDS par le bus AHB
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
 INIT_LED();
 
  while(1)
  {
  GPIOB->ODR |=(1<<1);  
  delay(500);
  GPIOB->ODR &=~(1<<1);
  delay(500);
  }
  
}


