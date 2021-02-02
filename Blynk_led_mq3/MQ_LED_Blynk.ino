#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // thêm thư viện Blynk

#define BLYNK_PRINT Serial

BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "hTpsB5aGa3bHtCOPS3bm-DR4tchCM0tk"; // Lấy Token từ app Blynk trên điện thoại.

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1723"; // kết nối wifi.
char pass[] = "13031990";

#define MQ2 34 // khai báo Chân đọc ADC A0 GPIO34
#define BLUE 2 // khai báo led on board GPIO 2

int sensorValue = 0;
boolean state = false;

void setup()
{
  // Debug console
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass); // kết nối đến app.
  pinMode(MQ2, INPUT);
  pinMode(BLUE, OUTPUT);
  timer.setInterval(1000L, sendUptime);
}

void sendUptime()
{
  
  sensorValue = analogRead(MQ2); // đọc ADC.
  Blynk.virtualWrite(V1, sensorValue); // V1 cài đặt ở trên App.
  Serial.println(sensorValue); // xuất ra màn hình giá trị.

  if (sensorValue > 600) // Nếu Gas quá ngưỡng bật LED và gửi cảnh báo từ app.
  {
    Blynk.notify("Gas Detected!");
    digitalWrite(BLUE, HIGH);
  }

  else
  {
    digitalWrite(BLUE, LOW); // nếu không tắt LED.
  }
}

void loop()
{
  Blynk.run(); // run chương trình.
  timer.run();
}
