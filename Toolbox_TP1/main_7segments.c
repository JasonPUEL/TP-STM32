/******************************************************************************/
/*                                                                            */
/*                      Configuration de l'I2C                                */
/*                                                                            */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*                          AUTRAN ANTHONY                                    */
/*                         DELAHAYE GEOFFREY                                  */
/*                         CHASSIGNOL MAUD                                    */
/*                                                                            */
/*                          JANVIER  2016                                     */
/*                                                                            */
/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

#include "stm32l1xx_nucleo.h"
#define eteint 0x0000
#define tiret 0x0001
#define un 0x0030
#define deux 0x006D
#define trois 0x0079
#define quatre 0x0033
#define cinq 0x005B
#define six 0x005F
#define sept 0x0070
#define huit 0x007F
#define neuf 0x007B
#define zero 0x007E

#define digit1 0x0100
#define digit2 0x0200
#define digit3 0x0300
#define digit4 0x0400

uint16_t BP1 = 0;
uint16_t BP2 = 0;

void delay(void)
{
  int n=0;

  for(n=0;n<100000;n++)
  {
          
  }	
}

void GPIO_INIT()
{
  RCC->AHBENR |= RCC_AHBENR_GPIOAEN; // Horloge du GPIOA activée
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // Horloge du SPI1 activée
  
  GPIOA->MODER |= GPIO_MODER_MODER5_1; // PA5 en alternative mode
  GPIOA->MODER &=~ GPIO_MODER_MODER5_0;
  
  GPIOA->MODER |= GPIO_MODER_MODER7_1; // PA7 en alternative mode
  GPIOA->MODER &=~ GPIO_MODER_MODER7_0;
  
  GPIOA->MODER |= GPIO_MODER_MODER8_0; // PA8 en mode Output
  GPIOA->MODER &=~ GPIO_MODER_MODER8_1;
  
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT_5; // Outpout push-pull
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT_7; // De-même
  GPIOA->OTYPER &=~ GPIO_OTYPER_OT_8; // De-même
  
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR5; // PA5 en High Speed
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR7; // PA7 aussi
  GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8; // PA8 aussi
  
  GPIOA->AFR[0] |= (1<<20); // AF5: 0101 -> SPI1 | alternate function mod on PA5 and PA7
  GPIOA->AFR[0] |= (1<<22);
  GPIOA->AFR[0] |= (1<<28);
  GPIOA->AFR[0] |= (1<<30);
  GPIOA->AFR[0] &=~ (1<<21);
  GPIOA->AFR[0] &=~ (1<<23);
  GPIOA->AFR[0] &=~ (1<<29);
  GPIOA->AFR[0] &=~ (1<<31);
}

void SPI_CONFIG(void)
{
  SPI1->CR1 |= SPI_CR1_MSTR;       // Configuration en mode Master
  SPI1->CR1 |= SPI_CR1_BIDIMODE;   // Bidirectionnal data wire
  SPI1->CR1 |= SPI_CR1_BIDIOE;     // Data line in Output (Transmit only)
  SPI1->CR2 |= SPI_CR2_SSOE;       // Mode Master
  SPI1->CR2 &=~ SPI_CR2_FRF;       // Mode Motorola 
  SPI1->CR1 |= SPI_CR1_BR;         // BaudRate = f/256. On divise la fréquence d'horloge par 256
  SPI1->CR1 |= SPI_CR1_DFF;        // Les trames de datas sont sur 16 Bits pour les transmission et les réceptions
  SPI1->CR1 |= SPI_CR1_SPE;        // On active le périphérique du SPI (le démarre) à la fin de la configuration des registres
}

//SPI1_CS sur PA8
void SET_CS(void)
{
  delay();
  GPIOA->ODR |= GPIO_ODR_ODR_8; // PA8 = 1	
}

void RESET_CS(void)
{
  delay();
  GPIOA->ODR &=~ GPIO_ODR_ODR_8; // PA8 = 0
}

void SENDDATA_SPI(uint16_t data)
{
  data = data | 0x80;//le max7219 est config sur MSb first
  while((SPI1->SR) & (1<<1) != 1) // Tant que le bit TXE est égal à 1 (=> buffer pas vide donc on peut pas écrire dedans)
  {
  }
  SPI1->DR = data; // Si le buffer est vide, on écrit les datas dans le registre de données
}
       
void SPI_WRITE(uint16_t addr, uint16_t data)
{
  RESET_CS(); //0

  data = addr | data; // Concatenation de l'adresse et des datas que l'on remet ensuite dans data

  SENDDATA_SPI(data); // On écrit la nouvelle valeur de data dans le registre des données
	
  while(((SPI1->SR) & (1<<7) != 0) && ((SPI1->SR) & (1<<1) != 1)) // Check du bit BUSY et du bit TXE
  {
  }
  SET_CS(); //1
}

void INIT_AFFICHEUR(void)
{
  SPI_WRITE(0x0C00, 0x0001); // Normal Operation
  SPI_WRITE(0x0A00, 0x00AF); // Intensity max
  SPI_WRITE(0x0900, 0x0000); // No decode (on a tout rentré en dur)
  SPI_WRITE(0x0B00, 0x0004); // Scan-limit Format : Display digit 0 -> 4
  SPI_WRITE(0x0F00, 0x0000); // Display test mode
	
	
  // On eteint les digits
  SPI_WRITE(digit4,eteint);
  SPI_WRITE(digit3,eteint);
  SPI_WRITE(digit2,eteint);
  SPI_WRITE(digit1,eteint);
}

void DEFILEMENT (void)
{
  SPI_WRITE(digit4,un);
  SPI_WRITE(digit3,0x0000);
  SPI_WRITE(digit2,0x0000);
  SPI_WRITE(digit1,0x0000);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,deux);
  SPI_WRITE(digit3,un);
  SPI_WRITE(digit2,0x0000);
  SPI_WRITE(digit1,0x0000);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,trois);
  SPI_WRITE(digit3,deux);
  SPI_WRITE(digit2,un);
  SPI_WRITE(digit1,0x0000);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,quatre);
  SPI_WRITE(digit3,trois);
  SPI_WRITE(digit2,deux);
  SPI_WRITE(digit1,un);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,cinq);
  SPI_WRITE(digit3,quatre);
  SPI_WRITE(digit2,trois);
  SPI_WRITE(digit1,deux);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,six);
  SPI_WRITE(digit3,cinq);
  SPI_WRITE(digit2,quatre);
  SPI_WRITE(digit1,trois);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,sept);
  SPI_WRITE(digit3,six);
  SPI_WRITE(digit2,cinq);
  SPI_WRITE(digit1,quatre);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,huit);
  SPI_WRITE(digit3,sept);
  SPI_WRITE(digit2,six);
  SPI_WRITE(digit1,cinq);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,neuf);
  SPI_WRITE(digit3,huit);
  SPI_WRITE(digit2,sept);
  SPI_WRITE(digit1,six);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,0x0000);
  SPI_WRITE(digit3,neuf);
  SPI_WRITE(digit2,huit);
  SPI_WRITE(digit1,sept);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,0x0000);
  SPI_WRITE(digit3,0x0000);
  SPI_WRITE(digit2,neuf);
  SPI_WRITE(digit1,huit);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,0x0000);
  SPI_WRITE(digit3,0x0000);
  SPI_WRITE(digit2,0x0000);
  SPI_WRITE(digit1,neuf);
  delay();
  delay();
  delay();
  delay();
  SPI_WRITE(digit4,0x0000);
  SPI_WRITE(digit3,0x0000);
  SPI_WRITE(digit2,0x0000);
  SPI_WRITE(digit1,0x0000);
  delay();
  delay();
  delay();
  delay();
}
           
int main(void)
{
  GPIO_INIT();
  SPI_CONFIG();
  INIT_AFFICHEUR();
   while(1)
  {
    DEFILEMENT();
  }
}

