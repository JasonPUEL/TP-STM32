/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                              BUZZER                                        */
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


void TIMER3_CH2(uint64_t F){
  
  RCC->APB1ENR |=(1<<1);//Buzzer 1 est sur la pin  PC7/TIM3_CH2 du STM32 PC
  /*TIMER et INTERRUPT*/
    //Initialiser le TIM3
    TIM3->PSC =16000000/(100*F);                //configuration du prescalaire
    TIM3->ARR =100;                // configuration de l'ARR pour 750ms
    
    //Registre controle TIM3 p36
    TIM3->CR1 |=(1<<7);                    
    TIM3->CR1 &=~(1<<4);
    TIM3->CR1 &=~(1<<5);
    TIM3->CR1 &=~(1<<6);
    
    TIM3->CR1 |=(1<<0);           // CEN Counter Enable
    
    //configurer la période du PWM p41
    TIM3->CCMR1 |=(1<<13);     
    TIM3->CCMR1 |=(1<<14);
    TIM3->CCMR1 &=~(1<<12);
    
    
    TIM3->CCR2 =( TIM3->ARR)*0.5;  // rapport cyclique
    TIM3->CCER |=(1<<4);           //activer sortie PWM

}

/*---------------------------------------------*/

void Init_GPIO(){
  
  /*PERIPHERIQUE*/
    RCC->AHBENR |= (1<<2);//activation de l'horloge périphérique au port digital GPIOB pour allumer les LEDS par le bus AHB
    
    /*PIN*/
    //GPIOC->OSPEEDR&=~((1<<2)&(1<<7));   //définir la vitesse d'actualisation du port (p 13) sert a rien
    
    GPIOC->OTYPER&=~(1<<7);              //OT7 Output push-pull (reset state)
    GPIOC->PUPDR &=~(3<<14);             //no pull-up, no pull-down
    
    GPIOC->AFR[0]|=(1<<29);             //lien buzzer timer 
    GPIOC->MODER |=(2<<14);             //bit 1 0 pour Pc7 page 12
}

/*--------------Programme-Principal------------*/

void main()
{  
  
Init_GPIO();
TIMER3_CH2(440);
    
    

    while(1){
    }
  
    
}