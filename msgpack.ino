#include <msgpck.h>
#include "pack.h"
#include "protocol.h"
#include "context.h"
#include "server.h"

server ser;
// msgpack::packer packer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  ser.listen();
  // packer.pack_str(5);

  // char str[5] = "hello";

  // packer.pack_str_body(&str[0], 5);

  // delay(500);
}
