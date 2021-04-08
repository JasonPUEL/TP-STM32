/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                              MOTOR                                         */
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
   

void Init_GPIO(){
    /*PERIPHERIQUE*/
    RCC->AHBENR |= (1<<1);//activation de l'horloge périphérique au port digital GPIOB pour allumer les LEDS par le bus AHB   
    /*PIN*/
    GPIOB->OSPEEDR&=~((1<<2)&(1<<7));   //définir la vitesse d'actualisation du port (p 13) sert a rien
    
    GPIOB->OTYPER&=~(1<<4);             //OT4 Output push-pull (reset state)
    GPIOB->PUPDR &=~(3<<8);             //pull-down
    
    GPIOB->AFR[0]|=(1<<17);//0010 pour afrl4 page16   AFRRL et AFRH n'existe pas
    GPIOB->MODER |=(2<<14);            //bit 1 0 pour Pb7 page 12
}

/*---------------------------------------------*/

void TIMER3_CH1(){
    RCC->APB1ENR |=(1<<1);//Buzzer 1 est sur la pin  PC7/TIM3_CH2 du STM32 PC
  /*TIMER et INTERRUPT*/
    //Initialiser le TIM3
    TIM3->PSC = 15999;                //configuration du prescalaire
    TIM3->ARR =1000;                // configuration de l'ARR pour 750ms
    
    //Registre controle TIM3 p36
    TIM3->CR1 |=(1<<7);                    
    TIM3->CR1 &=~(1<<6);
    TIM3->CR1 &=~(1<<5);
    TIM3->CR1 |=(1<<4);
    
    TIM3->CR1 |=(1<<0);     // CEN Counter Enable
    
    //configurer la période du PWM p41
    TIM3->CCMR1 |=(1<<5);     
    TIM3->CCMR1 |=(1<<6);

    
    TIM3->CCR1 = 500;                 // rapport cyclique                 Mettre en choix 1: 110 
    TIM3->CCER |=(1<<0);               //activer sortie PWM
}

/*--------------Programme-Principal------------*/
void main()
{
  
  Init_GPIO();
  TIMER3_CH1();
  
  
    while(1){
    }
  
    
}