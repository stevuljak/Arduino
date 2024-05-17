#include <mcp2515.h>
struct can_frame canMsg;  // založení struktury dat pro CAN BUS
MCP2515 mcp2515(10);

int pot1 = 512;
int pot2 = 512;
int tlac = 0;

void setup() {

  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(4, INPUT);

  Serial.begin(9600);
}

void loop() {

  pot1 = analogRead(A1);
  pot2 = analogRead(A2);
  tlac = digitalRead(4);

  canMsg.can_id = 0x01;
  canMsg.can_dlc = 3;
  canMsg.data[0] = pot2 / 4;
  canMsg.data[1] = pot1 / 4;
  canMsg.data[2] = tlac;
  Serial.println(tlac);

  mcp2515.sendMessage(&canMsg);

  if (tlac == 1){delay(2000);}

  Serial.println("Elevace: ");
  Serial.println(pot1);
  Serial.println("Azimuth: ");
  Serial.println(pot2);
  Serial.println("Tlacitko: ");
  Serial.println(tlac);
  
}
