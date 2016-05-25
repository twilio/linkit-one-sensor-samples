# Using Twilio Wireless Commands API with the Hackpack (LinkIt ONE)
If you received a hackpack at Twilio SIGNAL or you have created one yourself using a LinkIt ONE you can use it with the [Twilio Wireless Commands API](https://www.twilio.com/docs/api/wireless/rest-api/command). You'll need a [Twilio SIM card](https://twilio.com/wireless) set up in your Twilio account with a valid device.

Make sure you install the `Libraries` from the root of this repo into your `Arduino/libraries` folder since you'll need it for the `DisplayManager` to output text to your screen.

Run the `twiliocommands.ino` sketch file and once you see "SMS ready." on your Serial Monitor you can send a command to your device.

Find your Device ID using the `/Devices` API and send the following `POST` request (substitute in your device ID):

```
curl -X POST https://preview.twilio.com/wireless/Commands \
  -d 'Device=DE************' \
  -d 'Command=hello' \
  -u '{{ account_sid }}:{{ auth_token }}'
```

You should see the word "hello" appear on your OLED display.
