#define DOUT 7
#define LATCHOUT 6
#define CLKOUT 5
#define print(x) Serial.println(x)

int displayBuffer[8][8] = {
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0}
};

int rain_1[4]={0,0,0,1};
int rain_2[4]={0,0,0,1};
int rain_3[4]={0,0,0,1};
int rain_4[4]={0,0,0,1};
int rain_5[4]={0,0,0,1};
int rain_6[4]={0,0,0,1};
int rain_7[4]={0,0,0,1};
int rain_8[4]={0,0,0,1};

void setup() {
  pinMode(DOUT,OUTPUT);
  pinMode(LATCHOUT,OUTPUT);
  pinMode(CLKOUT,OUTPUT);
  Serial.begin(115200);
  print("READY");
}


long timer = millis();
int x,y,z;

#define INPUT_SIZE 50
char rx_string[INPUT_SIZE];
int rx_index = 0;

long rxtimer = 0;

void loop() {
//  if(Serial.available() > 0){
//    char rxin = Serial.read();
//    if(rxin != '\n'){
//      rx_string[rx_index] = rxin;
//      rx_index++;
//    } else {
//      rx_index = 0;
//      char* command = strtok(rx_string, " \n");
//      char* param = strtok (NULL, " \n");
//      if(strcmp(command,"SET") == 0){
//        char*xchar = strtok(param, ",");
//        char*ychar = strtok(NULL, ",");
//        char*zchar = strtok(NULL, ",");
//        int xtemp = atoi(xchar);
//        int ytemp = atoi(ychar);
//        int ztemp = atoi(zchar);
//        setPixel(xtemp,ytemp,ztemp);
////        print("OK");
//      } else if(strcmp(command,"CLR") == 0){
//        char*xchar = strtok(param, ",");
//        char*ychar = strtok(NULL, ",");
//        char*zchar = strtok(NULL, ",");
//        int xtemp = atoi(xchar);
//        int ytemp = atoi(ychar);
//        int ztemp = atoi(zchar);
//        clearPixel(xtemp,ytemp,ztemp);
////        print("OK");
//      } else if(strcmp(command,"CLR") == 0){
//        char*xchar = strtok(param, ",");
//        char*ychar = strtok(NULL, ",");
//        char*zchar = strtok(NULL, ",");
//        int xtemp = atoi(xchar);
//        int ytemp = atoi(ychar);
//        int ztemp = atoi(zchar);
//        clearPixel(xtemp,ytemp,ztemp);
////        print("OK");
//      } else if(strcmp(command,"CLRALL") == 0){
//        clearDisplay();
////        print("OK");
//      } 
//      for(int i = 0; i < INPUT_SIZE; i++){
//        rx_string[i] = NULL;
//      }
//    }
//  }
//  sweepPlane();
//  box();
  rain();
//  love();
  updateDisplay();
}

void sweepPlane (){
  if((millis()-timer)> 60){
    z--;
    clearDisplay();
    for(int y =0; y < 8;y++){
      displayBuffer[z][y] = B11111111;
    }
    if(z == -1){
      z = 7;
    }
    timer = millis();
  }
}

void love(){
  setPixel(1,3,6);
  setPixel(2,3,6);
  setPixel(5,3,6);
  setPixel(6,3,6);
  for(int i = 0; i <8; i++) setPixel(i,3,5);
  for(int i = 0; i <8; i++) setPixel(i,3,4);
  for(int i = 0; i <8; i++) setPixel(i,3,3);
  for(int i = 1; i <7; i++) setPixel(i,3,2);
  for(int i = 2; i <6; i++) setPixel(i,3,1);
  for(int i = 3; i <5; i++) setPixel(i,3,0);

  setPixel(1,2,5);
  setPixel(2,2,5);
  setPixel(5,2,5);
  setPixel(6,2,5);
  for(int i = 1; i <7; i++) setPixel(i,2,4);
  for(int i = 1; i <7; i++) setPixel(i,2,3);
  for(int i = 2; i <6; i++) setPixel(i,2,2);
  for(int i = 3; i <5; i++) setPixel(i,2,1);

  
  setPixel(1,4,5);
  setPixel(2,4,5);
  setPixel(5,4,5);
  setPixel(6,4,5);
  for(int i = 1; i <7; i++) setPixel(i,4,4);
  for(int i = 1; i <7; i++) setPixel(i,4,3);
  for(int i = 2; i <6; i++) setPixel(i,4,2);
  for(int i = 3; i <5; i++) setPixel(i,4,1);
}

void scrollLight(){
  if((millis()-timer)> 10){
    clearDisplay();
    setPixel(x,y,z);
    x++;
    if(x == 8){
      x = 0;
      y++;
      if(y == 8){
        y = 0;
        z++;
        if(z == 8){
          z = 0;
        }
      }
    }
    timer = millis();
  }
}

void updateDisplay() {
  for(int i = 0; i < 8; i++){
    int layerSelect = 0;
    bitSet(layerSelect, i);
    digitalWrite(LATCHOUT,LOW);
    shiftOut(DOUT, CLKOUT, LSBFIRST, layerSelect);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][0]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][1]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][2]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][3]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][4]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][5]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][6]);
    shiftOut(DOUT, CLKOUT, LSBFIRST, displayBuffer[i][7]);
    digitalWrite(LATCHOUT,HIGH);
//    delay(100);
  }
}
long time12;
int stage =1;
int laststage = 0;
bool directions = 0;

void box(){
  if((millis()-time12)>1000){
    if(directions == 0)stage++;
    if(directions == 1)stage--;
  }
  if(stage !=laststage)time12 = millis();
  Serial.println(millis() - time12);
  if(stage == 4 && directions == 0){
    directions = 1;
  }
  if(stage == 1 && directions == 1){
    directions = 0;
  }
  clearDisplay();
  switch(stage){
    case 1:
      for(int i = 0; i < 8; i++){
      setPixel(i,7,7);
      setPixel(i,0,7);
      setPixel(i,7,0);
      setPixel(i,0,0);
      setPixel(0,i,0);
      setPixel(7,i,7);
      setPixel(7,i,0);
      setPixel(0,i,7);
      setPixel(0,0,i);
      setPixel(7,0,i);
      setPixel(0,7,i);
      setPixel(7,7,i);
      }
    break;
    case 2:
      for(int i = 1; i < 7; i++){
      setPixel(i,1,6);
      setPixel(i,6,6);
      setPixel(i,6,1);
      setPixel(i,1,1);
      setPixel(1,i,1);
      setPixel(6,i,6);
      setPixel(6,i,1);
      setPixel(1,i,6);
      setPixel(1,1,i);
      setPixel(6,1,i);
      setPixel(1,6,i);
      setPixel(6,6,i);
      }
    break;
    case 3:
      for(int i = 2; i < 6; i++){
      setPixel(i,2,5);
      setPixel(i,5,5);
      setPixel(i,5,2);
      setPixel(i,2,2);
      setPixel(2,i,2);
      setPixel(5,i,5);
      setPixel(5,i,2);
      setPixel(2,i,5);
      setPixel(2,2,i);
      setPixel(5,2,i);
      setPixel(2,5,i);
      setPixel(5,5,i);
      }
    break;
    case 4:
      setPixel(3,3,3);
      setPixel(4,4,4);
      setPixel(3,4,4);
      setPixel(4,3,4);
      setPixel(3,3,4);
      setPixel(4,4,3);
      setPixel(3,4,3);
      setPixel(4,3,3);
    break;
  }
  laststage = stage;
}

void rain(){
  clearDisplay();
  switch(random(12)){
    case 0:if(rain_1[4] == 1){
    rain_1[1]= random(8);
    rain_1[2]= random(8);
    rain_1[3] = 7;
    rain_1[4] = 0;
    }
      break;
    case 1:if(rain_2[4] == 1){
    rain_2[1]= random(8);
    rain_2[2]= random(8);
    rain_2[3] = 7;
    rain_2[4] = 0;
    }
      break;
    case 2:if(rain_3[4] == 1){
    rain_3[1]= random(8);
    rain_3[2]= random(8);
    rain_3[3] = 7;
    rain_3[4] = 0;
    }
      break;
    case 3:if(rain_4[4] == 1){
    rain_4[1]= random(8);
    rain_4[2]= random(8);
    rain_4[3] = 7;
    rain_4[4] = 0;
    }
      break;
    case 4:if(rain_5[4] == 1){
    rain_5[1]= random(8);
    rain_5[2]= random(8);
    rain_5[3] = 7;
    rain_5[4] = 0;
    }
      break;
    case 5:if(rain_6[4] == 1){
    rain_6[1]= random(8);
    rain_6[2]= random(8);
    rain_6[3] = 7;
    rain_6[4] = 0;
    }
      break;
    case 6:if(rain_7[4] == 1){
    rain_7[1]= random(8);
    rain_7[2]= random(8);
    rain_7[3] = 7;
    rain_7[4] = 0;
    }
      break;
    case 7:if(rain_8[4] == 1){
    rain_8[1]= random(8);
    rain_8[2]= random(8);
    rain_8[3] = 7;
    rain_8[4] = 0;
    }
      break;
      default:
      break;
  }
  
  if((millis()-time12)>30){
      stage++;
      if(rain_1[4] == 0){
      setPixel(rain_1[1],rain_1[2],rain_1[3]);
      rain_1[3]--;
      if(rain_1[3] == -1)rain_1[4] = 1;
    }
    if(rain_2[4] == 0){
      setPixel(rain_2[1],rain_2[2],rain_2[3]);
      rain_2[3]--;
      if(rain_2[3] == -1)rain_2[4] = 1;
    }
    if(rain_3[4] == 0){
      setPixel(rain_3[1],rain_3[2],rain_3[3]);
      rain_3[3]--;
      if(rain_3[3] == -1)rain_3[4] = 1;
    }
    if(rain_4[4] == 0){
      setPixel(rain_4[1],rain_4[2],rain_4[3]);
      rain_4[3]--;
      if(rain_4[3] == -1)rain_4[4] = 1;
    }
    if(rain_5[4] == 0){
      setPixel(rain_5[1],rain_5[2],rain_5[3]);
      rain_5[3]--;
      if(rain_5[3] == -1)rain_5[4] = 1;
    }
    if(rain_6[4] == 0){
      setPixel(rain_6[1],rain_6[2],rain_6[3]);
      rain_6[3]--;
      if(rain_6[3] == -1)rain_6[4] = 1;
    }
    if(rain_7[4] == 0){
      setPixel(rain_7[1],rain_7[2],rain_7[3]);
      rain_7[3]--;
      if(rain_7[3] == -1)rain_7[4] = 1;
    }
    if(rain_8[4] == 0){
      setPixel(rain_8[1],rain_8[2],rain_8[3]);
      rain_8[3]--;
      if(rain_8[3] == -1)rain_8[4] = 1;
    }
  }
  if(stage !=laststage)time12 = millis();
  laststage = stage;
}

void setPixel(int x, int y, int z){
  bitSet(displayBuffer[z][y],x);
}

void clearPixel(int x, int y, int z){
  bitClear(displayBuffer[z][y],x);
}

void clearDisplay(){
  for(int x = 0; x < 8; x++){
    for(int y = 0; y < 8; y++){
      for(int z = 0; z < 8; z++){
        displayBuffer[z][y] = 0;
      }
    }
  }
}
