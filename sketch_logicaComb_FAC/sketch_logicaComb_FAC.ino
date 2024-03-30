#define pinTrigger A1
#define echoPin A2

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
  pinMode(17, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);

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
  distancia = (travel_time/2)*(0.0344); // 0.0344 velocidad del sonido a 20 C°

  // condiciones según el valor del potenciómetro para la tabla de gray
  if(distancia <= 58) {
    OutGray[2] = 0; OutGray[1] = 0; OutGray[0] = 0; } // 0

  if(distancia > 58 && distancia <= 114) {
    OutGray[2] = 0; OutGray[1] = 0; OutGray[0] = 1; } // 1

  if(distancia > 114 && distancia <= 170) {
    OutGray[2] = 0; OutGray[1] = 1; OutGray[0] = 1; } // 2

  if(distancia > 170 && distancia <= 226) {
    OutGray[2] = 0; OutGray[1] = 1; OutGray[0] = 0; } // 3

  if(distancia > 226 && distancia <= 282) {
    OutGray[2] = 1; OutGray[1] = 1; OutGray[0] = 0; } // 4

  if(distancia > 282 && distancia <= 338) {
    OutGray[2] = 1; OutGray[1] = 1; OutGray[0] = 1; } // 5

  if(distancia > 338 && distancia <= 394) {
    OutGray[2] = 1; OutGray[1] = 0; OutGray[0] = 1; } // 6

  if(distancia > 394) {
    OutGray[2] = 1; OutGray[1] = 0; OutGray[0] = 0; } // 7

  setOut_pinGray();
  set_displaySeg();
  Serial.print("La distancia es: ");
  Serial.println(distancia);
  delay(200); // 200 ms
}

// Se colocan en alto los bits que posean un 1
void setOut_pinGray(){
  int index_gray = 0;
  for (int i = 9; i < 12; i++){

    if (OutGray[index_gray] == 0){digitalWrite(i, LOW);}
    else {digitalWrite(i, HIGH);}
    index_gray++;
  }
}

void set_displaySeg(){
  bitWrite(InBinario, 0, digitalRead(BitBin0));
  bitWrite(InBinario, 1, digitalRead(BitBin1));
  bitWrite(InBinario, 2, digitalRead(BitBin2));

  switch(InBinario){

    case 0b000:
        segments_display = 0b0111111; // 0
        
      break;
    case 0b001:
        segments_display = 0b0000110; // 1
      
      break;
    case 0b010:
        segments_display = 0b1011011;  // 2
      
      break;
    case 0b011:
        segments_display = 0b1001111;  // 3
      
      break;
    case 0b100:
      segments_display = 0b1100110;  // 4
      
      break;
    case 0b101:
      segments_display = 0b1101101;  // 5

      break;
    case 0b110:
      segments_display = 0b1111101;  // 6
      
      break;
    case 0b111:
      segments_display = 0b0000111; // 7

      break;
    default:
      segments_display = 0b0111111;

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

