#include <Time.h>

//Varios
  int etapa = 1;
  int tiempo = 0;
  
//CNY
int I = A0; // CNY izq de marvin blanco
int D = A1; // CNY dcha de marvin amarillo
int C = A2; // CNY central de marvin amarillo

//CNY Encoder
int E = A3; // CNY Encoder
int cambia = 0; //Transiciones entre negro y blanco
int colorAnterior = 0; //1 negro, 0 blanco

//Ultrasonidos
const int trigger=8;//naranja
const int echo=7;//amarillo
float distance;
float distance1 = 30;

//Rueda derecha
const int ruedaDerecha = 10;
const int adelanteLentoD = 137;
const int adelanteRapidoD = -180;
const int atrasLentoD = 158;
const int atrasRapidoD = 180;
//Rueda izquierda
const int ruedaIzquierda = 9;
const int adelanteLentoI = 165; 
const int adelanteRapidoI = 180;
const int atrasLentoI = 140;
const int atrasRapidoI = -180;




//----------------------------------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(I, INPUT);
  pinMode(D, INPUT);
  pinMode(C, INPUT);
  pinMode(E, INPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  delay(10000);
  
  //etapa = 10;
}

//----------------------------------------------------------------------------------------------------

void loop() {
  
  ojos();
  
  switch (etapa){
    case 1:
      poneFrescos();
      break;
    case 2:
      vuelve();
      break;
    case 3:
      lanzaPelotas();
      break;
    case 4:
      espera();
      break;
    case 5:
      lanzaRed();
      break;
    case 6:
      termina();
      
    case 10: //Pruebas
      //sigueLineaAtras();
      break;
  }  
  //delay (500);
}

//------------------------------------------------------------------------------------------------------

void poneFrescos(){
  Serial.println("etapa 1");
  //Codigo del encoder
  if (digitalRead(E) != colorAnterior){
      colorAnterior = digitalRead(E);
      cambia++;
    }
    
  //Gestion del movimiento
    
  if ((distance1 < 15)&&(cambia < 60)){
    retrocedeRapido("derecha");
    retrocedeRapido("izquierda");
    delay(50);
    quieto();
  }  
  while ((distance1 < 15)&&(cambia < 60)){//60 es la estimacion minima de pasos hasta llegar al fresco
    quieto();
    ojos();
    delay(2000);
  }
  if (distance1 > 7)
    sigueLinea();
  else{
    //if (cambia < pasosNecesariosParaLlegarALaPared) delay(1000);
    //else (paraMotores y pasa a la siguiente etapa)
    //Vuelve a comprobar la distancia por si ha sido un error
          /*para("derecha");
          para("izquierda");
          delay(5000);
          ojos();
          if (distance1 < 12){            
            avanza("izquierda");
            avanza("derecha");
            delay(1500);
            para("derecha");
            para("izquierda");
            etapa ++;
          }*/
          quieto();
          /*Serial.print("Ha cambiado: ");
          Serial.print(cambia);
          Serial.println(" veces");
          delay(10000);
  */
          etapa ++;
      }
}


void vuelve(){
   Serial.println("etapa 2");
   /*ojos();
   Serial.print("_");
   Serial.println(distance1);
   while (distance1 < 10){
     sigueLineaAtras();
     ojos();
   }
   Serial.println("Para y da la vuelta");
   para("izquierda");
   para("derecha");
   */
   retrocedeRapido("derecha");
   retrocedeRapido("izquierda");
   delay(300);
   quieto();
   G180();
   tiempo = now() + 9;//10 segundos andando hasta ponerse delante del mamut. Es mentira, CAMBIAR.
   while(tiempo > now()){//            <------------ Lo suyo seria usar odometria para no perder tiempo parado
     ojos();
     if (distance1 < 4){
       quieto();
     }
     else
       sigueLinea();
  }
  quieto();  
  etapa ++;  
}

void G180(){
  while(!leeNegro("izquierda")){
    avanzaRapido("derecha");
    retrocedeRapido("izquierda");
  }
  while(leeNegro("izquierda")){
    avanzaRapido("derecha");
    retrocedeRapido("izquierda");
  }
  quieto();  
}

void G90(String color){
  if (color.equals("amarillo")){
  
  
  }
  else{//rojo
    retrocedeRapido("derecha");
    avanzaRapido("izquierda");
    delay(500);
    quieto();
    /*
    while(!leeNegro("derecha") || !leeNegro("izquierda")){ 
     retrocede("derecha");
     retrocede("izquierda");
    }
    para("izquierda");
    para("derecha");
    if (leeNegro("derecha")){
      while(!leeNegro("izquierda"))
        retrocede("izquierda");
        //analogWrite(ruedaIzquierda,139);
      para("izquierda");
      delay(100);
    }
    else{
      while(!leeNegro("derecha"))
        retrocede("derecha");
        //analogWrite(ruedaDerecha,160);
      para("derecha");  
    }
    */
  }
    
}

void lanzaPelotas(){
  Serial.println("etapa 3");
  //Gira para posicionarse delante del mamut
  G90("rojo");
  /*Lanza las pelotas
  --------------
  -------------
  
  
  -------------
  -------------
  */  
  etapa ++;
}

void espera(){
  Serial.println("etapa 4");
  etapa ++;
}

void lanzaRed(){
  Serial.println("etapa 5");
  etapa ++;
}

void termina(){
  Serial.println("etapa 6");
  quieto();
  delay(30000);
}

void sigueLinea(){
  if (leeNegro("centro")){
    //Quieto si lee negro en ambos lados (Cambiar, solo utilizado durante la codificacion)
    if (leeNegro("izquierda") && leeNegro("derecha")){
      quieto();
    }
    else
    if (leeNegro("izquierda")){
      avanzaLento("izquierda");
      delay(100);
      avanzaRapido("izquierda");  
    }
    else
    if (leeNegro("derecha")){
      avanzaLento("derecha");
      delay(100);
      avanzaRapido("derecha");
    }
    else{
        avanzaRapido("izquierda");
        avanzaRapido("derecha");
    }
  }
  else{ //Si no leeNegro(centro)
    if (leeNegro("izquierda")){
      retrocedeRapido("izquierda");
      delay(100);
      avanzaRapido("izquierda");  
    }
    else
    if (leeNegro("derecha")){
      retrocedeRapido("derecha");
      delay(100);
      avanzaRapido("derecha");
    }
  }
}
/*
void sigueLineaAtras(){
  //Quieto si lee negro en ambos lados (Cambiar, solo utilizado durante la codificacion)
  if (leeNegro("izquierda") && leeNegro("derecha")){
    para("derecha");
    para("izquierda");
  }
  else
  if (leeNegro("izquierda")){
    avanza("izquierda");
    para("derecha");
    delay(40);
    retrocede("izquierda");
    retrocede("derecha");
  }
  else
  if (leeNegro("derecha")){
    avanza("derecha");
    para("izquierda");
    delay(40);
    retrocede("derecha");
    retrocede("izquierda");
  }
  else{
      retrocede("izquierda");
      retrocede("derecha");
  }
}
*/

boolean leeNegro(String lado){
  if (lado.equals("izquierda"))
    return(analogRead(I) > 900);
  else 
  if (lado.equals("derecha"))
    return(analogRead(D) > 900);
  else 
  if (lado.equals("centro"))
    return(analogRead(C) > 900);
  else 
  if (lado.equals("encoder"))
    return(analogRead(E) > 900);
}

void avanzaRapido(String rueda){
  if (rueda.equals("izquierda"))
    analogWrite(ruedaIzquierda,adelanteRapidoI);
  else
    analogWrite(ruedaDerecha,adelanteRapidoD);
}

void retrocedeRapido(String rueda){
  if (rueda.equals("izquierda"))
    analogWrite(ruedaIzquierda,atrasRapidoI);
  else
    analogWrite(ruedaDerecha,atrasRapidoD);
}

void avanzaLento(String rueda){
  if (rueda.equals("izquierda"))
    analogWrite(ruedaIzquierda,adelanteLentoI);
  else
    analogWrite(ruedaDerecha,adelanteLentoD);
}

void retrocedeLento(String rueda){
  if (rueda.equals("izquierda"))
    analogWrite(ruedaIzquierda,atrasLentoI);
  else
    analogWrite(ruedaDerecha,atrasLentoD);
}

void para(String rueda){
  if (rueda.equals("izquierda"))
    analogWrite(ruedaIzquierda,0);
  else
    analogWrite(ruedaDerecha,0);
}

void quieto(){
  para("izquierda");
  para("derecha");
}

void ojos(){
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  distance=pulseIn(echo,HIGH); // Medimos el ancho del pulso
                                // (Cuando la lectura del pin sea HIGH medira
                                // el tiempo que transcurre hasta que sea LOW

  if (((distance/2)/29.1) < 300)
    distance1=(distance/2)/29.1;//Parece mas exacto----------------------------------
  Serial.print(distance1);
  Serial.println(" cm");
}
