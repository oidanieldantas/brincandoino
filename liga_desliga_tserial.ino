/*
* Prog: Liga/Desliga via console-serial
* Criado por: Daniel H. N. Dantas
* Criado em: 13 abr 21
* Usando: Visual Studio Code + PlatformIO
* Dispositivo: ESP32 WiFi_Kit32
* Baseado no cod: http://arahna.de/arduino-command-line/ 
*/

/***** Includes (bibs externas) *************/
#include <Arduino.h> //necessaria inserir pq foi feito no PlatformIO
/********************************************/

/***** Defines (rotulos de pinos/nomes) *****/
#define ledPin 2 //Pino com o LED acionado
/********************************************/

/***** Variaveis Globais ********************/
String inData; //String que guarda os chars do console formando uma string
bool estado_led = false; //guarda estado para alternar
/********************************************/

/***** Funcoes complementares do prg ********/
void comunic_serial();      //funcao que monit a serial
void acao();                //avalia entrada, realiza acao
void seta_led(byte estado); //liga ou desliga o led
/********************************************/

/***** Configuracoes iniciais ***************/
void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);                                                      //necessario para iniciar o terminal serial
  Serial.println("Serial conection started, waiting for instructions..."); //avida que esta pronto para receber
}
/********************************************/

/***** Fincacao principal *******************/
void loop()
{
  comunic_serial();
}
/********************************************/

/***** Funcao de comunicacao Serial *********/
void comunic_serial()
{                                //funcao para comunicacao serial
  while (Serial.available() > 0) //Em qnt houver pulso na serial
  {
    char recieved = Serial.read(); //ler entrada armazena caracter
    inData += recieved;            //junta caracter para formar uma String

    // Process message when new line character is recieved
    if (recieved == '\n') //checa se o último char recebido foi Enter (retorno do echo)
      acao();             //qnd o echo enviar '\n' chama a acao do led
  }
}
/********************************************/

/***** Funcao de imprimir e chamar acao *****/
void acao() //imprime a msg e pega a acao do led
{
  Serial.print("Received: "); //qnd terminar o echo no terminal surge a string
  Serial.print(inData);

  if (inData == "ON\n" || inData == "on\n")
  {
    seta_led(1); //lega o led
    Serial.println("LIGADO!");
  }

  // You can put some if and else here to process the message juste like that:

  else if (inData == "OFF\n" || inData == "off\n")
  {
    seta_led(2); //desliga o led
    Serial.println("DESLIGADO!");
  }

  else if (inData == "BLINK\n" || inData == "blink\n") //toda strind termina com o '\n'
  {
    seta_led(3); //pisca o led
    Serial.print("PISCOU E...");
    if(!estado_led)
      Serial.println("desligou!");
    else
      Serial.println("ligou!");
  }
  
  else
    seta_led(0);

  inData = ""; // Clear recieved buffer - limpa a stringa para novo texto
}
/********************************************/

/***** Funcao de acionar led ****************/
void seta_led(byte estado)
{
  switch (estado)
  {
  case 1:
    digitalWrite(ledPin, HIGH);
    estado_led = true;
    break;
  case 2:
    digitalWrite(ledPin, LOW);
    estado_led = false;
    break;
  case 3:
    for (byte i = 0; i < 13; i++)
    {
      digitalWrite(ledPin, !digitalRead(ledPin));
      delay(150);
    }
    if (estado_led)
    {
      digitalWrite(ledPin, LOW);
      estado_led = false;
    }
    else
    {
      digitalWrite(ledPin, HIGH);
      estado_led = true;
    }
    break;
  default:
    Serial.println("ON    OFF    BLINK");
    break;
  }
}
/********************************************/
