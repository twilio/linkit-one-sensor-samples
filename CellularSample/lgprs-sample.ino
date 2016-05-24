#include <LGPRS.h>
#include <LGPRSClient.h>

#define SITE_URL "putsreq.com"

LGPRSClient client;

void setup() {
  Serial.begin(9600);
  
  // Connect to cellular network using Twilio Wireless
  while(!LGPRS.attachGPRS("wireless.twilio.com", NULL, NULL)) {
    Serial.println("Waiting for GPRS signal...");
    delay(1000);
  }

  Serial.println("GPRS attached.");

  // Connect client to the test site
  Serial.print("Connecting to: " SITE_URL "...");
  if(!client.connect(SITE_URL, 80))
  {
   Serial.println("Could not connect to: " SITE_URL);
   return;
  } else {
    Serial.println("Connection successful.");
  }

  Serial.println("Sending test GET request...");

  // Make GET request to test site. Returns "Hello world!"
  // We'll display the response in loop()
  client.println("GET /m3JKNFhGxaeu0KsXcdLl HTTP/1.1");
  client.println("Host: " SITE_URL);
  client.println();

  Serial.println("Waiting for response from test site...");
}

void loop() {
  if (client.available()) 
  { 
    char c = client.read(); 
    Serial.print(c); 
  }
}
