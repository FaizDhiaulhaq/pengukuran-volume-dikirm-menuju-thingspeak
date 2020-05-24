#include <ThingSpeak.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3f, 16, 2);
//pin scl : A5
//pin sda : A4

#define echoPin 8       //pin 8 arduino untuk echo pin sensor ultrasonic 
#define trigPin 9       //pin 9 arduino untuk trig pin sensor ultrasonic

#define batasAtas 15    //nilai batas jarak dalam satuan cm
#define batasBawah 12  //nilai batas jarak dalam satuan cm

#define batasAtas1 11   //nilai batas jarak dalam satuan cm
#define batasBawah1 8  //nilai batas jarak dalam satuan cm

#define batasAtas2 7   //nilai batas jarak dalam satuan cm
#define batasBawah2 4   //nilai batas jarak dalam satuan cm

long duration, ultraSensor;
int distance;  //membuat devinisi tipe data yang digunakan
float volumenull, volume, volumeL;
char voll[50];
String vol_str;
using namespace std;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
EthernetClient client;

unsigned long myChannelNumber = 1001985;
const char * myWriteAPIKey = "FZBWA51RR894RKN8";
const int updateThingSpeakInterval = 16 * 1000;

void setup()
{
  lcd.begin();
  Serial.begin (9600);
  startEthernet();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(1, OUTPUT);
  pinMode(1, LOW);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);


  Ethernet.begin(mac);
  ThingSpeak.begin(client);
}

void loop()
{
  if (client.available())
  {
    char c = client.read();
    Serial.print(c);
  }
  sensorUltrasonic(trigPin, echoPin);
  ultraSensor = distance; //memberikan nilai ultrasensor dengan nilai yang ada pada distance
  vol_str = String(volumeL);
  vol_str.toCharArray(voll, vol_str.length() + 1);
  cetakjarak();
  volumenull = 3.14 * distance * 7.5 * 7.5; //rumus menghitung volume ruang kosong tabung yang tidak terisi fluida dengan satuan cm3
  volume = 3002.625 - volumenull; // rumus menghitung nilai volume fluida dengan satuan cm3
  volumeL = volume / 1000; // rumus mengubah volume cm3 menjadi Liter
  cetakVolume();
  delay(300);
 
  if (ultraSensor >= 16 )
  {
    satubar();
  }
  else if (ultraSensor <= batasAtas && ultraSensor >= batasBawah)
  {
    duabar();
  }
  else if (ultraSensor <= batasAtas1 && ultraSensor >= batasBawah1)
  {
    tigabar();
  }
  else if (ultraSensor <= batasAtas2 && ultraSensor >= batasBawah2)
  {
    empatbar();
  }
  else if (ultraSensor <= 3 )
  {
    penuh();
  }


  ThingSpeak.writeField(myChannelNumber, 1, voll, myWriteAPIKey);
  delay(20000); // ThingSpeak will only accept updates every 15 seconds.
}

void sensorUltrasonic(int pinTrigger, int pinEcho)
{
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distance = (duration / 2) / 29.1; //rumus untuk menghitung jarak dengan cara membagi dua pada bagian durasi untuk menghilangkan nilai patul kembali dari gelombang ultrasonic lalu dibagi lagi dengan nilai 29.1 yaitu nilai konversi rambat gelombang menjadi cm
  delay(500);
}
void startEthernet()
{

  client.stop();

  Serial.println("Connecting Arduino to network...");
  Serial.println();

  delay(1000);

  // Connect to network amd obtain an IP address using DHCP
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("DHCP Failed, reset Arduino to try again");
    Serial.println();
  }
  else
  {
    Serial.println("Arduino connected to network using DHCP");
    Serial.println();
  }

  delay(1000);
}
