#include <DisplayManager.h>
#include <Icons.h>
#include <Lumi.h>
#include <Lumi_default_font.h>
#include <LumiBig.h>
#include <system.h>

#include <LGSM.h>

char buff[50];
int len = 0;
char *command;
char *device;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize the OLED display library
  DisplayManager::init();

  // Start up the SMS listener
  while(!LSMS.ready()) {
    delay(1000);
  }

  // If there's a leftover message, flush it.
  if(LSMS.available())
  {
    Serial.println("Flushing in setup...");
    LSMS.flush();
  }

  // SMS is ready to go.
  Serial.println("SMS ready.");
}

void loop() {
  // If we have SMS data available, we received a command!
  if(LSMS.available())
  { 
    // We received a command!
    // Read in the command response into buff
    while(true)
    {
      int v = LSMS.read();
      if(v < 0)
      break;

      buff[len++] = (char)v;
    }

    // Store the device ID
    device = strtok(buff, " ");

    // Store the command
    command = strtok(NULL, " ");

    // Write the command text to the OLED display.
    DisplayManager::writeText(command);

    // Reset variables for next message.
    LSMS.flush();
    memset(&buff[0], 0, sizeof(buff));
    len = 0;
  }
}
