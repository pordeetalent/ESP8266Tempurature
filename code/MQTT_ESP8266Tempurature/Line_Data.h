#include "TridentTD_LineNotify.h"

#include "global.h"
#define LINE_TOKEN  "xxxxx"

void Linesetup(){
  Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  Serial.printf("WiFi connecting to %s\n", WLAN_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
}

void Line_msg(String Text){
  LINE.notify(Text);
  /*// ตัวอย่างส่งข้อความ
  LINE.notify("อุณหภูมิ เกินกำหนด");
  LINE.notify("myarduino.net");
  // ตัวอย่างส่งข้อมูล ตัวเลข
  LINE.notify(2342);          // จำนวนเต็ม
  LINE.notify(212.43434, 5);  // จำนวนจริง แสดง 5 หลัก

  // เลือก Line Sticker ได้จาก https://devdocs.line.me/files/sticker_list.pdf
  LINE.notifySticker(3, 240);       // ส่ง Line Sticker ด้วย PackageID 3 , StickerID 240
  LINE.notifySticker("Hello", 1, 2); // ส่ง Line Sticker ด้วย PackageID 1 , StickerID 2  พร้อมข้อความ

  // ตัวอย่างส่ง รูปภาพ ด้วย url
  LINE.notifyPicture("https://preview.ibb.co/j6G51n/capture25610417181915334.png");
  LINE.notifyPicture("จตุธาตุ", "https://www.fotoaparat.cz/storage/pm/09/10/23/670915_a5351.jpg");*/
}
