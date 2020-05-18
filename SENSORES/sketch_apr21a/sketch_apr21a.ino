#include <SPI.h>
#include <SD.h>

// ======================================================================================================
// --- Mapeamento de Hardware ---

#define MQ135 A0
#define MQ7 A1
#define MQ8 A2
#define MQ3 A3

const int chipSelect = 10;


#define SAMPLES 128 // Números de amostras 
#define SAMPLING_FREQUENCY 500 //Hz, must be less than 10000 due to ADC Frequencia de amostragem

unsigned  sampling_period_us; unsigned long microseconds;// variaveis de tempo

unsigned  long tempo[SAMPLES];// vetor que armazena os tempos de execucao em microsegundos do for
unsigned dados[SAMPLES];// vetor que armazena os tempos relativo a distancia em microsegundos do for

// constante para configuração do prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void setup()
{
  Serial.begin(115200);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("FALHA NO CARD");
    // don't do anything more:
    while (1);
  }
  Serial.println("CARD INICIALIZADO");

 // analogReference(EXTERNAL);

  pinMode(MQ135, INPUT);
  pinMode(MQ7, INPUT);
  pinMode(MQ8, INPUT);
  pinMode(MQ3, INPUT);
  
  DDRD |= (1 << PD7);

  sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQUENCY));// periodo de amostragem em microsegundos nesse caso 2000us ou 0.002s

  // configura o preescaler do ADC
  ADCSRA &= ~PS_128;//limpa configuração da biblioteca do arduino

  // valores possiveis de prescaler só deixar a linha com prescaler desejado
  // PS_16, PS_32, PS_64 or PS_128
  //ADCSRA |= PS_128;//64 prescaler
  // ADCSRA |= PS_64;//64 prescaler
  // ADCSRA |= PS_32;//32 prescaler
  ADCSRA |= PS_16;//16 prescaler
}

void loop()
{
  microseconds = micros();//Overflows after around 70 minutes! CUIDADO

  File dataFile = SD.open("TESTE.txt", FILE_WRITE);

  if (dataFile) {
    PORTD |= (1 << PD7);
    dataFile.print(microseconds);
    dataFile.print(",");
    dataFile.print(analogRead(MQ135));
    dataFile.print(",");
    dataFile.print(analogRead(MQ7));
    dataFile.print(",");
    dataFile.print(analogRead(MQ8));
    dataFile.print(",");
    dataFile.println(analogRead(MQ3));

    dataFile.close();

  }
  PORTD &= ~(1 << PD7);

  while (micros() < (microseconds + sampling_period_us)) {
  }

}
