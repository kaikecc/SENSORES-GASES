#include <SPI.h>
#include <SD.h>

// ======================================================================================================
// --- Mapeamento de Hardware ---

#define MQ135 A0
#define MQ7 A1
#define MQ8 A2
#define MQ3 A3

const int chipSelect = 10;

// ======================================================================================================
// --- Constantes ---
const uint16_t T1_init = 0;
const uint16_t T1_comp = 6250;

// constante para configuração do prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);


// ======================================================================================================
// --- Interrupção ---
ISR(TIMER1_COMPA_vect)
{

  TCNT1 = T1_init;      //reinicializa TIMER1

  File dataFile = SD.open("D.txt", FILE_WRITE);

  if (dataFile) {
    dataFile.print(analogRead(MQ135));
    dataFile.print(",");
    dataFile.print(analogRead(MQ7));
    dataFile.print(",");
    dataFile.print(analogRead(MQ8));
    dataFile.print(",");
    dataFile.println(analogRead(MQ3));

    dataFile.close();
  }

  Serial.print(analogRead(MQ135));
  Serial.print(",");
  Serial.print(analogRead(MQ7));
  Serial.print(",");
  Serial.print(analogRead(MQ8));
  Serial.print(",");
  Serial.println(analogRead(MQ3));
} //end ISR


// ======================================================================================================
// --- Configurações Iniciais ---
void setup()
{
  Serial.begin(9600);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("FALHA NO CARD");
    // don't do anything more:
    while (1);
  }
  Serial.println("CARD INICIALIZADO");

  analogReference(EXTERNAL);

  pinMode(MQ135, INPUT);
  pinMode(MQ7, INPUT);
  pinMode(MQ8, INPUT);
  pinMode(MQ3, INPUT);

  //Modo de Comparação
  TCCR1A = 0;

  //Prescaler 1:256
  TCCR1B |=  (1 << CS12);
  TCCR1B &= ~(1 << CS11);
  TCCR1B &= ~(1 << CS10);

  //Inicializa Registradores
  TCNT1 = T1_init;
  OCR1A = T1_comp;

  //Habilita Interrupção do Timer1
  TIMSK1 = (1 << OCIE1A);

  // configura o preescaler do ADC
  ADCSRA &= ~PS_128;  //limpa configuração da biblioteca do arduino

  // valores possiveis de prescaler só deixar a linha com prescaler desejado

  // PS_16, PS_32, PS_64 or PS_128
  //ADCSRA |= PS_128; // 64 prescaler
  //   ADCSRA |= PS_64; // 64 prescaler
  //  ADCSRA |= PS_32; // 32 prescaler
  ADCSRA |= PS_16; // 16 prescaler
} //end setup


// ======================================================================================================
// --- Loop Infinito ---
void loop()
{} //end loop
