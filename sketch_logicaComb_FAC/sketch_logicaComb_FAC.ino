#define pinTrigger A0
#define echoPin A1

#define BitBin0 A3
#define BitBin1 A4
#define BitBin2 A5

boolean OutGray [3] = {0,0,0};
byte InBinario = 0b000;
byte segments_display;

int travel_time, distancia;

int BitGray0 = 9;
int BitGray1 = 10;
int BitGray2 = 11;

int Display_a = 2;
int Display_b = 3;
int Display_c = 4;
int Display_d = 5;
int Display_e = 6;
int Display_f = 7;
int Display_g = 8;


void setup() {
  // Pines del sensor
  pinMode(pinTrigger, OUTPUT);
  pinMode(echoPin, INPUT);

  // Pines para el código Gray
  pinMode(BitGray0, OUTPUT);
  pinMode(BitGray1, OUTPUT);
  pinMode(BitGray2, OUTPUT);

  // Pines para el código binario de entrada
  pinMode(BitBin0, INPUT);
  pinMode(BitBin1, INPUT);
  pinMode(BitBin2, INPUT);

  //  Pines para el display de siete segmentos
  pinMode(Display_a, OUTPUT);
  pinMode(Display_b, OUTPUT);
  pinMode(Display_c, OUTPUT);
  pinMode(Display_d, OUTPUT);
  pinMode(Display_e, OUTPUT);
  pinMode(Display_f, OUTPUT);
  pinMode(Display_g, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // Se realiza un disparo de la señal del sensor
  digitalWrite(pinTrigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  
  // Se toma el tiempo que duró el disparo
  travel_time = pulseIn(echoPin, HIGH);
  distancia = (travel_time/2)*(0.0344); 

  // condiciones según el valor del potenciómetro para la tabla de gray
  if(distancia <= 12) {
    OutGray[2] = 0; OutGray[1] = 0; OutGray[0] = 0; } // 0

  if(distancia > 12 && distancia <= 24) {
    OutGray[2] = 0; OutGray[1] = 0; OutGray[0] = 1; } // 1

  if(distancia > 24 && distancia <= 36) {
    OutGray[2] = 0; OutGray[1] = 1; OutGray[0] = 1; } // 2

  if(distancia > 36 && distancia <= 48) {
    OutGray[2] = 0; OutGray[1] = 1; OutGray[0] = 0; } // 3

  if(distancia > 48 && distancia <= 60) {
    OutGray[2] = 1; OutGray[1] = 1; OutGray[0] = 0; } // 4

  if(distancia > 60 && distancia <= 72) {
    OutGray[2] = 1; OutGray[1] = 1; OutGray[0] = 1; } // 5

  if(distancia > 72 && distancia <= 84) {
    OutGray[2] = 1; OutGray[1] = 0; OutGray[0] = 1; } // 6

  if(distancia > 84) {
    OutGray[2] = 1; OutGray[1] = 0; OutGray[0] = 0; } // 7

  Serial.print("La distancia es: "+String(distancia)+ " cm | ");
  setOut_pin();
  set_displaySeg();
  delay(200); // 200 ms
}

// Se colocan en alto los bits que posean un 1
void setOut_pin(){
  int index_gray = 2;
  Serial.print("Gray --> ");
  for (int i = 11; i > 8; i--){
    Serial.print(String(OutGray[index_gray]));
    if (OutGray[index_gray] == 0){digitalWrite(i, LOW);}
    else {digitalWrite(i, HIGH);}
    index_gray--;
  }
}

void set_displaySeg(){
  bitWrite(InBinario, 0, digitalRead(BitBin0));
  bitWrite(InBinario, 1, digitalRead(BitBin1));
  bitWrite(InBinario, 2, digitalRead(BitBin2));

  switch(InBinario){

    case 0b000:
        segments_display = 0b0111111; // 0
        Serial.println(" | Decimal --> 0");
        
      break;
    case 0b001:
        segments_display = 0b0000110; // 1
        Serial.println(" | Decimal --> 1");

      break;
    case 0b010:
        segments_display = 0b1011011;  // 2
        Serial.println(" | Decimal --> 2");
      
      break;
    case 0b011:
        segments_display = 0b1001111;  // 3
        Serial.println(" | Decimal --> 3");
      
      break;
    case 0b100:
      segments_display = 0b1100110;  // 4
      Serial.println(" | Decimal --> 4");

      break;
    case 0b101:
      segments_display = 0b1101101;  // 5
      Serial.println(" | Decimal --> 5");

      break;
    case 0b110:
      segments_display = 0b1111101;  // 6
      Serial.println(" | Decimal --> 6");
      
      break;
    case 0b111:
      segments_display = 0b0000111; // 7
      Serial.println(" | Decimal --> 7");

      break;
    default:
      segments_display = 0b0111111;
      Serial.println(" | Decimal --> 0");

      break;
  }

  int count = 0;
  int bit;

  for (int i = 2 ; i < 9 ; i++) {
    bit = bitRead(segments_display, count);
    digitalWrite(i, bit);
    count++;
  }  
}

