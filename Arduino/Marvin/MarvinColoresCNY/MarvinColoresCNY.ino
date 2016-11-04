//CNY
int Pin1 = A0; // CNY izq de marvin
int Pin2 = A5; // CNY dcha de marvin

//Ultrasonidos
const int trigger=8;//amarillo
const int echo=9;//naranja
float distance;
float distance1;

void setup() {

Serial.begin(9600);
pinMode(Pin1, INPUT);
pinMode(Pin2, INPUT);
pinMode(trigger,OUTPUT);
pinMode(echo,INPUT);
  

}
void loop() {

  //CNY
if (analogRead(Pin1) > 900)
  Serial.println("Negro");

if ((analogRead(Pin1) > 250) && (analogRead(Pin1) < 300))
  Serial.println("Verde");

if ((analogRead(Pin1) > 200) && (analogRead(Pin1) < 250))
  Serial.println("Blanco");

if (analogRead(Pin2) > 800)
  Serial.println("Negro");

if ((analogRead(Pin2) > 35) && (analogRead(Pin2) < 40))
  Serial.println("Verde");

if ((analogRead(Pin2) > 30) && (analogRead(Pin2) < 35))
  Serial.println("Blanco");


//Ultrasonidos
digitalWrite(trigger,LOW);
delayMicroseconds(5);
digitalWrite(trigger,HIGH);
delayMicroseconds(10);
digitalWrite(trigger,LOW);
distance=pulseIn(echo,HIGH); // Medimos el ancho del pulso
                                // (Cuando la lectura del pin sea HIGH medira
                                // el tiempo que transcurre hasta que sea LOW
distance1=(distance/2)/29.1;//Parece mas exacto----------------------------------
Serial.print(distance1);
Serial.println(" cm");



delay (500);

}
