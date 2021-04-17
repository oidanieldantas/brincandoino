/************************************************************
* Prog.: RecebeEnviaBT
* Criado por: Daniel H. N. Dantas
* Criado em: 17 abr 21
*
* OBS.: Com ajustes esse cod pode se tornar uma funcao para enviar palavras/textos para o clienteBT
* Referencia:
* How to Use Classic Serial Bluetooth in ESP32
* https://circuitdigest.com/microcontroller-projects/using-classic-bluetooth-in-esp32-and-toogle-an-led
* Acesso: 17 abr 21
*************************************************************/

#include <Arduino.h>

/**** Requisitos para uma comunicacao BT_Serial (Old BT) ****/
#include <BluetoothSerial.h> //bib necessaria que ja vem disponivel na ide
BluetoothSerial ESP_BT; //instacia de obj Bluetooth
/************************************************************/

//var globais nao sao inicializadas pois seriam vistas como const
char c_recebido;  //var para receber os caracters do clienteBT
String palavra;   //palavra formada pela juncao do c_recebido

void setup() {
  // put your setup code here, to run once:
  ESP_BT.begin("ESP32"); //nome do dispositivo exibido para parear e acessar
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ESP_BT.available())  //verifica se algo foi recebido pelo BT
  { 
    c_recebido=ESP_BT.read(); //o retorno do .read() é um inteiro, ao atribuir para uma char faço um 'casting'
    // ESP_BT.print("Voce enviou: ");  //envia para o clienteBT a msg
    // ESP_BT.println(recebido);  //ler o char enviado pelo clienteBT e envi a msg com os cod ASCII
    // //ESP_BT.println((char)ESP_BT.read());  //faz o 'casting' converte para caracter o ASCII recebido
    //para receber uma palvra temos que juntar os caracteres recebidos em uma var String global
    if(c_recebido!=13 && c_recebido!=10)  //verifica se o char é difirente de Enter ou CR (msg do terminal)
    {                                 //se nao tiver o !=10 na String aparecera um ^M   
      palavra+=c_recebido;  //se o char recebido for diferente de Eneter e ^M ele junta com o anterior
      ESP_BT.print("Voce enviou: ");  //envia para o clienteBT a msg
      ESP_BT.println(c_recebido); //envia para o clienteBT o caracter recebido
    }
    if(c_recebido==13)  //verifica se o char é Enter, se for imprime a String e limpa para receber
    {
      ESP_BT.print("Tudo junto é: ");
      ESP_BT.println(palavra);
      palavra=""; //limpa a string para receber nova sequencia
    }

  }
}
