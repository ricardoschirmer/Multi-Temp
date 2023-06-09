// BIBLIOTECA

#include "max6675.h" // include MAX6675
#include <LiquidCrystal.h> // LiquidCrystal

// PINOS DIGITAL 

#define TK01_SLK 2      // pin SCK Sensor 1
#define TK01_CS 3       // pin CS  Sensor 1
#define TK01_SO 4       // pin SO  Sensor 1
#define TK02_SLK 5      // pin SCK Sensor 2
#define TK02_CS 6       // pin CS  Sensor 2
#define TK02_SO 7       // pin SO  Sensor 2
#define TK03_SLK 8      // pin SCK Sensor 3
#define TK03_CS 9       // pin CS  Sensor 3
#define TK03_SO 10      // pin SO  Sensor 3
#define TK04_SLK 11     // pin SCK Sensor 4
#define TK04_CS 12      // pin CS  Sensor 4
#define TK04_SO 13      // pin SO  Sensor 4
#define TK05_SLK 30     // pin SCK Sensor 5
#define TK05_CS 32      // pin CS  Sensor 5
#define TK05_SO 34      // pin SO  Sensor 5

#define YELLOW_LED 22   // pin LED AMARELO
#define BLUE_LED 24     // pin LED AZUL
#define RED_LED 26      // pin LED VERMELHO
#define PUSHBUTTON 35   // pin (Push Button)BOTÃO QUE INICIA O EXPERIMENTO
#define RELAY_1 38      // pin RESISTENCIA (Relay 1) AQUECER A BARRA
#define RELAY_2 39      // pin RESISTENCIA (Relay 2) AQUECER A BARRA

// VARIABLES 
int T = 40;                   // Controle de temperatura do amarelo
int danger = 150;              // Valor de temperatura que o sistema desliga sozinho
unsigned long lastTime = 0;
const int interval = 10000;   // Tempo em milissegundos (10 segundos)
int state_button = 2;
float celsius_new = 0.0;
float celsius_old = 0.0;
LiquidCrystal lcd(43, 44, 47, 48, 51, 52); // Display

// INSTANCES

MAX6675 ktc01(TK01_SLK, TK01_CS, TK01_SO); // Instance Sensor 1 SENSOR BARRA
MAX6675 ktc02(TK02_SLK, TK02_CS, TK02_SO); // Instance Sensor 2 SENSOR BARRA
MAX6675 ktc03(TK03_SLK, TK03_CS, TK03_SO); // Instance Sensor 3 SENSOR BARRA
MAX6675 ktc04(TK04_SLK, TK04_CS, TK04_SO); // Instance Sensor 4 SENSOR BARRA
MAX6675 ktc05(TK05_SLK, TK05_CS, TK05_SO); // Instance Sensor 5 RESISTENCIA

void setup(){
    Serial.begin(9600); //INICIALIZA A SERIAL
   
    lcd.begin(16, 2);                  // Define o número de colunas e linhas do LCD
    lcd.clear();                       // Limpa a tela
    lcd.setCursor(0, 0);
    lcd.print("Iniciando Modulo");
    lcd.setCursor(3, 1);
    lcd.print("Aguarde... ");
    
    pinMode(PUSHBUTTON, INPUT_PULLUP); // Define o pino do botao como entrada
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(RELAY_1, OUTPUT);
    pinMode(RELAY_2, OUTPUT);   
    
    // PARAMETRO INICIAL DE VERIFICAÇÃO
    digitalWrite(YELLOW_LED, HIGH);  
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, LOW);
    delay(3000); // INTERVALO DE 1000 MILISSEGUNDOS
    digitalWrite(YELLOW_LED, LOW);  
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, HIGH);
}

void loop(){
      
    unsigned long currentTime = millis(); // Obtém o tempo atual em milissegundos
    
    // Verifica se já se passaram 10 segundos desde a última leitura
    if (currentTime - lastTime >= interval) {
        lastTime = currentTime; // Atualiza o tempo da última leitura
        
        // LÊ AS TEMPERATURAS DOS SENSORES E AS ENVIA PARA O PYTHON
        Serial.print(millis() / 1000.0); // Envia o tempo em segundos
        Serial.print(", ");
        Serial.print(ktc01.readCelsius());
        Serial.print(", ");
        Serial.print(ktc02.readCelsius());
        Serial.print(", ");
        Serial.print(ktc03.readCelsius());
        Serial.print(", ");
        Serial.print(ktc04.readCelsius());
        Serial.print(", ");
        Serial.print(ktc05.readCelsius());
        Serial.println();
    }

    // SE O BOTÃO FOR PRESSIONADO 
    /*
    Quando o botão é precionado ele vai acrecentar um número saindo de um estado par(0) par impar(1)
    Quando estiver sobre a rotina IMPAR o LED VERMELHO vai LIGAR junto com as RESISTÊNCIAS,
    Inicialmento o Display estará fazendo a verificação das temperadtura dos 4 termopares
    Quando o botão for precionado o display sai da leitura dos 4 sensores e inicia a verificação do 5° termopar (resistencia)   
    */
    if (digitalRead(PUSHBUTTON) == LOW){
        state_button = state_button + 1;
    }  
    
    // LEDS
    digitalWrite(BLUE_LED, HIGH);       // SISTEMA (LIGADO)
    
    if (ktc05.readCelsius() >= T){      // CONTROLE DE TEMPERATURA (LED AMARELO)
      digitalWrite(YELLOW_LED, HIGH);   // RESISTÊNCIA >= T 40ºC 
    } else {
      digitalWrite(YELLOW_LED, LOW);    // RESISTÊNCIA > T 40ºC
    }
    
    if (state_button % 2 == 0){         // SE PAR
      
        digitalWrite(RED_LED, LOW);     // RESISTÊNCIA DESLIGADA 
        // RELAYs
        digitalWrite(RELAY_1, HIGH);    // RESISTÊNCIA DESLIGADA (DEVIDO AOS RELAY SEREM UM CONJUNTO DE 4 UNIDADES USADOS EM MOTORES)
        digitalWrite(RELAY_2, HIGH);    // RESISTÊNCIA DESLIGADA (DEVIDO AOS RELAY SEREM UM CONJUNTO DE 4 UNIDADES USADOS EM MOTORES)

         /*
          LIMPA A TELA DO DISPLAY, POSTERIORMENTE INICIA A LEITURA DA TEMPERATURA DO TERMISTOR 1 AO 4
          */
        // LCD DISPLAY 
        lcd.clear();                     // Limpa a tela
        lcd.setCursor(0, 0);
        lcd.print("1:");
        lcd.setCursor(2, 0);
        lcd.print(ktc01.readCelsius());
        lcd.setCursor(7, 0);
        lcd.print("  ");  
        lcd.setCursor(9, 0);
        lcd.print("2:");
        lcd.setCursor(11, 0);
        lcd.print(ktc02.readCelsius());
        lcd.setCursor(0, 1);
        lcd.print("3:");
        lcd.setCursor(2, 1);
        lcd.print(ktc03.readCelsius());
        lcd.setCursor(7, 1);
        lcd.print("  "); 
        lcd.setCursor(9, 1);
        lcd.print("4:");
        lcd.setCursor(11, 1);
        lcd.print(ktc04.readCelsius());

    } // FINAL SE PAR
    /*
     QUANDO A VARIÁVEL STATE_BUTTON ESTA IMPAR, LIGA O LED VERMELHO, LIGA OS 2 RELAYs ACIONANDO AS 2 RESISTÊNCIAS E INICIA O AQUECIMENTO DA BARRA.
     */
    else { // SE IMPAR 

        digitalWrite(RED_LED, HIGH);        // LED LIGADO
        // RELAYs
        digitalWrite(RELAY_1, LOW);         // RESISTÊNCIA LIGADO
        digitalWrite(RELAY_2, LOW);         // RESISTÊNCIA LIGADO

        /*
         SISTEMA DE SEGURANÇA IMPEDE QUE A BARRA ULTRAPASE OS 300°C.
         */
        if (ktc05.readCelsius() >= danger){ // 300ºC LIMITE DE PROTEÇÃO DO SISTEMA.
          state_button = state_button + 1;
          digitalWrite(RED_LED, LOW);       // DESLIGADO
          digitalWrite(RELAY_1, HIGH);
          digitalWrite(RELAY_2, HIGH);
        } 

        // LCD DISPLAY
        lcd.clear();
        lcd.setCursor(1, 0);
        lcd.print("SISTEMA LIGADO");
        celsius_new = ktc05.readCelsius() - celsius_old;
        lcd.setCursor(0, 1);
        lcd.print("T:");
        lcd.setCursor(2, 1);
        lcd.print(ktc05.readCelsius());
        lcd.setCursor(7, 1);
        lcd.print("C +");
        lcd.setCursor(10, 1);
        lcd.print(abs(celsius_new));
        celsius_old = ktc05.readCelsius();
        lcd.setCursor(14, 1);
        lcd.print("C");
               
    } // FINAL IMPAR
    
    delay(1000); //INTERVALO DE 500 MILISSEGUNDOS   
} // end void
