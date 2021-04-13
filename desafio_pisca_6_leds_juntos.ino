/*
* Prog: Pisca 6 juntos
* Criado por: Daniel H. N. Dantas
* Criado em: 12 abr 21
* 
* Prg proposto para o 1º Desafio do curso Mst do Arduino.
* Ligar e desligar 6 LED "simultaneo". 0,5s ON e 0,5s OFF.
*/

// Funcao de config. inicial
void setup()
{
  // Def. os pinos de 2 ao 7 como saida
  for(byte i=2; i<8;i++){
    pinMode(i,OUTPUT);
  }
}

void loop()
{    
  // Laco que inverte o estado da porta baseando o estado anterior
  for(byte i=2; i<8;i++){
    digitalWrite(i,!digitalRead(i));
  }delay(500); // 'Congela' 0,5s e reinicia o loop
}

/*
* O ATMega328 (microprocessador do arduino) tem um clock de 16MHz
* 16 x 10^6 (16 milhoes) de pulsos (chaveamentos) em 1s
* 0.0000000625 segundos para mudar de ligado para desligado (vice-versa)
* por isso, mesmo sendo sequencial, parece ser "simultaneo"
*/
