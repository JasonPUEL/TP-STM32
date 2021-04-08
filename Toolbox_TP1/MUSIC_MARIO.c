/******************************************************************************/
/*                                                                            */
/*                      MAIN BASIQUE STM32L152RE                              */
/*                                                                            */
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
    RCC->AHBENR |= (1<<2);//activation de l'horloge périphérique au port digital GPIOB pour allumer les LEDS par le bus AHB
    
    /*PIN*/
    //GPIOC->OSPEEDR&=~((1<<2)&(1<<7));   //définir la vitesse d'actualisation du port (p 13) sert a rien
    
    GPIOC->OTYPER&=~(1<<7);              //OT7 Output push-pull (reset state)
    GPIOC->PUPDR &=~(3<<14);             //no pull-up, no pull-down
    
    GPIOC->AFR[0]|=(1<<29);             //lien buzzer timer 
    GPIOC->MODER |=(2<<14);             //bit 1 0 pour Pc7 page 12
}

/*---------------------------------------------*/

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

/*void tone(uint64_t F, uint64_t T){
  
  RCC->APB1ENR |=(1<<1);//Buzzer 1 est sur la pin  PC7/TIM3_CH2 du STM32 PC
  //TIMER et INTERRUPT
    //Initialiser le TIM3
    
    TIM3->ARR =F;       //100         // configuration de l'ARR
    TIM3->PSC =16000000/(100*F);      //configuration du prescalaire
    
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
    
    
    TIM3->CCR2 =(TIM3->ARR)*0.5;  // rapport cyclique
    TIM3->CCER |=(1<<4);           //activer sortie PWM

}*/

void tone(uint64_t F, uint64_t T){
  
  RCC->APB1ENR |=(1<<1);//Buzzer 1 est sur la pin  PC7/TIM3_CH2 du STM32 PC
  //TIMER et INTERRUPT
    //Initialiser le TIM3
    
    TIM3->ARR =100;       //100         // configuration de l'ARR
    TIM3->PSC =16000000/(100*F);       //250         //configuration du prescalaire
    
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
    
    
    TIM3->CCR2 =(TIM3->ARR)*0.5;  // rapport cyclique
    TIM3->CCER |=(1<<4);           //activer sortie PWM
    
    delay(T);

}

/*--------------Programme-Principal------------*/

void main(){
  
  Init_GPIO();

  while(1)
  {
  tone(660,100);
  delay(150);
  tone(660,100);
  delay(300);
  tone(66000,100);
  delay(300);
  tone(510,100);
  delay(100);
  tone(660,100);
  delay(300);
  tone(770,100);
  delay(550);
  tone(380,100);
  delay(575);
  
  tone(510,100);
  delay(450);
  tone(380,100);
  delay(400);
  tone(320,100);
  delay(500);
  tone(440,100);
  delay(300);
  tone(480,80);
  delay(330);
  tone(450,100);
  delay(150);
  tone(430,100);
  delay(300);
  tone(380,100);
  delay(200);
  tone(660,80);
  delay(200);
  tone(760,50);
  delay(150);
  tone(860,100);
  delay(300);
  tone(700,80);
  delay(150);
  tone(760,50);
  delay(350);
  tone(660,80);
  delay(300);
  tone(520,80);
  delay(150);
  tone(580,80);
  delay(150);
  tone(480,80);
  delay(500);
  
  tone(510,100);
  delay(450);
  tone(380,100);
  delay(400);
  tone(320,100);
  delay(500);
  tone(440,100);
  delay(300);
  tone(480,80);
  delay(330);
  tone(450,100);
  delay(150);
  tone(430,100);
  delay(300);
  tone(380,100);
  delay(200);
  tone(660,80);
  delay(200);
  tone(760,50);
  delay(150);
  tone(860,100);
  delay(300);
  tone(700,80);
  delay(150);
  tone(760,50);
  delay(350);
  tone(660,80);
  delay(300);
  tone(520,80);
  delay(150);
  tone(580,80);
  delay(150);
  tone(480,80);
  delay(500);
  
  tone(500,100);
  delay(300);
  
  tone(760,100);
  delay(100);
  tone(720,100);
  delay(150);
  tone(680,100);
  delay(150);
  tone(620,150);
  delay(300);
  
  tone(650,150);
  delay(300);
  tone(380,100);
  delay(150);
  tone(430,100);
  delay(150);

  }
  
}
