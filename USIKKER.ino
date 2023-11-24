#define SensorPin0 A0 //pHsensor 1 som analog pin 0
#define SensorPin1 A1 //pHsensor 2 som analog pin 1
#define SensorPin2 A2 //turbiditetsensor 1 som analog pin 2
#define SensorPin3 A3 //turbiditetsensor 2 som analog pin 3
#define Offset  -19.1025 //verdi brukt for kalibrering av phsensor 1
#define offset -19.1025 //verdi brukt for kalibrering av phsensor 1
#define LED 1
#define samplingInterval 20 
#define printInterval 2000 //hvor raskt verdiene printes
#define ArrayLenth  40


int pHArray0[ArrayLenth]; //lagre verdiene for pHsensor 1 i en liste
int pHArray1[ArrayLenth]; //lagre verdiene for pHsensor i en liste


int pHArray0Index=0;
int pHArray1Index=0;

int turbidityValue0 = analogRead(SensorPin2);
int turbidityValue1 = analogRead(SensorPin3);


void setup(void)
{
  pinMode(LED,OUTPUT);
  Serial.begin(9600);
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue0,voltage0;
  static float pHValue1,volatge1;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray0[pHArray0Index++]=analogRead(SensorPin0); //lagrer nævernede pH verdi i listen
      pHArray1[pHArray1Index++]=analogRead(SensorPin1); //lagrer nævernede pH verdi i listen


      if(pHArray0Index==ArrayLenth)pHArray0Index=0;
      voltage0 = avergearray(pHArray0, ArrayLenth)*5.0/263.53;
      pHValue0 = 3.5*voltage0+Offset;
      samplingTime=millis();
  
      if(pHArray1Index==ArrayLenth)pHArray1Index=0;
      voltage0 = avergearray(pHArray1, ArrayLenth)*5.0/263.53;
      pHValue1 = 3.5*voltage0+offset;
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {

    int turbidityValue0 = analogRead(SensorPin2); //leser av verdien på turbiditets sensor 1 
    int turbidityValue1 = analogRead(SensorPin3); //leser av verdien på turbiditets sensor 2

    Serial.println(pHValue0); //printe verdiene fra pH sensor 1
    Serial.println(pHValue1); //printe verdiene fra pH sensor 2
    Serial.println(turbidityValue0); //printe verdiene fra turbiditets sensor 1
    Serial.println(turbidityValue1); //printe verdiene fra turbiditets sensor 2
    digitalWrite(LED,digitalRead(LED)^1);
    printTime=millis();
  }
}
double avergearray(int* arr, int number){ //denne delen av koden funker som en fes
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;

}

