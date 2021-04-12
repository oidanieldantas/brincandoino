/*
* Prog: Leitor de LDR on-off (ler o valor medio das leituras qnt tem luz e nao)
* Criado em: 12 abr 21
* Criado por: Daniel H. N. Dantas
*/

#define portaLED 13 	//Porta a ser utilizada para ligar o led
#define portaLDR A0		//Porta analógica utilizada pelo LDR

String	estado="";		      //gaveta para colocar o nome Lig ou Deslig
unsigned long	media_LDR=0;	//media das leituras do ldr
unsigned long	contador=0;		//contad auxi de leituras
unsigned long	pega_tempo=0;	//pega tempo para não usar o delay

void setup()
{
  pinMode(portaLED, OUTPUT);	//Define a porta do Led como saída
  pinMode(portaLDR, INPUT_PULLUP);		//Define a porta do LDR como entrada para não deixar flutuando coloquei pull_up
  Serial.begin(9600); 			//Inicia a serial
}

void loop()
{ 
  //Ler o estado do LED e guarda na string para imprimir Lig ou Deslig
  estado = digitalRead(portaLED)?"Ligado":"Desliado";

  //leitura media do ldr
  media_LDR=0;	//zera para recebe novos valores
  contador=0;	//zera para reinicar a contagem
  pega_tempo=millis();	//iniciar a marcacao do tempo
  while(millis()-pega_tempo<500){
    media_LDR+=analogRead(portaLDR);
    contador++;
  }
  media_LDR/=contador;
  
  //Imprime o estado do LED e o valor lido no LDR
  Serial.println(estado+" - "+media_LDR);
  
  //Escreve o novo estado no LED invertendo a condicao lida no inicio
  digitalWrite(portaLED,!digitalRead(portaLED));
}


/*
Este programa pode ser usado para distinguir cores também
*/
