#include<16f877a.h>

#FUSES NOWDT                    
#FUSES HS                       
#FUSES PUT                      
#FUSES NOPROTECT                
#FUSES BROWNOUT                 
#FUSES NOLVP                    
#FUSES NOCPD                    
 
#use delay(clock=20000000)      
#use rs232(baud=9600, xmit = pin_b1, rcv = pin_b2, parity = N) //Configura a serial para comunicação com o módulo Wi-Fi

#define trisa 0b00000100
#define trisb 0b00000010
#define trisc 0b00000000
#define trisd 0b00000000

long litro = 0;

#define lcd_enable pin_d6            // pino enable do LCD
#define lcd_rs     pin_d4            // pino rs (register select)do LCD
                                     // (0) para comandos    (1) para dados
 
#define lcd_db4    pin_d0            // pino de dados d4 do LCD
#define lcd_db5    pin_d1            // pino de dados d5 do LCD
#define lcd_db6    pin_d2            // pino de dados d6 do LCD
#define lcd_db7    pin_d3            // pino de dados d7 do LCD

#include <lcd.h>                     //declaração da biblioteca do LCD

void main(){
	inicializa_lcd();               //Inicializa o LCD
	limpa_lcd();                    //Limpa o display do LCD
    caracter_inicio(1,1);
    printf(escreve_lcd,"Hidrometro");
	delay_ms(5000);
	delay_ms(5000);
	set_tris_b(0x00);
	output_low(pin_a2);
	printf("AT+CWMODE=1\r\n\0");     //Configura o módulo para trabalhar em modo estação
	delay_ms(5000);
	printf("AT+CIPMUX=1\r\n\0");     //Configura o módulo para trabalhar com múltiplas conexôes
	delay_ms(500);
	while(TRUE){
		if(!input(pin_a3)){          //Aguarda o fechamento da chave do hidrômetro
			delay_ms(200);           //Delay de debouncing para evitar interferências
			if(!input(pin_a3)){      
				litro = litro + 100;    //Adiciona 100 a contagem de litros
				limpa_lcd();            //Limpa o display do LCD
    			caracter_inicio(1,1);
    			printf(escreve_lcd,"Hidrometro");
				caracter_inicio(2,1);
    			printf(escreve_lcd,"Litros:%lu", litro); //Exibe no LCD o valor dos litros
				printf("AT+CIPSTART=4,\"TCP\",\"184.106.153.149\",80\r\n\0");       //Prepara o módulo para enviar a contagem de litros para o ThingSpeak
				delay_ms(5000);
				printf("AT+CIPSEND=4,49\r\n\0");                                    //Avisa a quantidade de caracteres que serão enviados para o módulo
				delay_ms(1000);
				printf("GET /update?key=PONNX2DA6QXP297T&field1=%lu\r\n\0", litro); //Envia o dado para o canal através da chave API
				delay_ms(1000);
				printf("AT\r\n\0");
			}

		}


	}
}
