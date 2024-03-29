
/* Things to do:
    1. Change over to ttf for all fonts
    2. Change LOCK_TO_DTZ to only be effective on Joe-Philippines.
    3. Add one to the key number for displaying while X Rate fetch.

   String apikey = "k5MJFkvlen6ebpAvKRpUlbbBd7uPAzAC";  // Mikey's key

   This one was burned for the month of June, 2022.
   String apikey = "gs2IkNdDcZMjmlCsfFn3PFPkBBquhu82"; // for joebauer49@gmail.com

   This is the one switched to after I ate up all of the gs2...u82 one with the overfetching.
   String apikey = "23TJj8EbyRWec1MPBECv5kLI7zAZNh3C"; // for joe@kapwa.net
  h
*/

//For the ILI9486 with Touch, select Setup6A_ESP_SPI_ILI9486

#include "Defines_and_Docs.h"  // Lots of setups that take up a lot of space!
/***************************************************************************/
void setup()
/****setup******************************************************************/
{
  //  void* SpStart = NULL;
  //  StackPtrAtStart = (void *)&SpStart;
  //  watermarkStart =  uxTaskGetStackHighWaterMark(NULL);
  //  StackPtrEnd3.1 = StackPtrAtStart - watermarkStart;
  int ofrFontHeight;

  Serial.begin(115200); delay(1000);
  //  trySSHColor();
  //  while (1);c
  tft.begin(); // Initialize the screen.
  //  Serial.printf("TFT_BL %i\r\n", TFT_BL);
  tft.setSwapBytes(true);
  tft.invertDisplay(false);
#if defined TFT_BL
  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(TFT_BL, pwmLedChannelTFT); // TFT_BL, 0 - 15
  ledcWrite(pwmLedChannelTFT, 100);
#endif
  tft.setRotation(requestedOrientation);
  touch_calibrate();

  ofr.setDrawer(tft); // Link renderer to base display for init messages..

  //------------------

  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF. Init 1");
    while (1);
  }
  Serial.print("Freetype version: "); ofr.showFreeTypeVersion(); // print FreeType version
  ofr.setFontSize(50);
  tft.fillScreen(SkyBlue);
  ofr.setFontColor(TFT_BLACK, SkyBlue);  // Foreground color, Background color
  myBuildString = "ABCabcjyWM";  // Include caps and descenders to get the full height
  ofrFontHeight = ofr.getTextHeight(myBuildString.c_str());
  ofrFontHeight = ofr.getTextHeight(sizingChars);
  ofrFontHeight += 8;

  yPos = 50;
  myBuildString = "Little Clock v" + String(Vers);
  ofr.setCursor(dispWidth / 2, yPos); ofr.cprintf(myBuildString.c_str());
  ofr.setCursor(dispWidth / 2, yPos + 80); ofr.cprintf("Initializing");
  pinMode (LED_BUILIN, OUTPUT);
  digitalWrite(LED_BUILIN, false); // Turn it off (on some boards).
  Serial.println("\r\n\r\nThis is \"Big Little Clock\" with ezTime using WiFiMulti,");
  Serial.println("using Bedroom, LallaveWifi, MikeysHS, RaPhaEl and N_Port.");
  Serial.printf("This is version %.2f.\r\n", Vers);
  //  String moduleFname = String(__FILE__);
  //  moduleFname = moduleFname.substring(moduleFname.lastIndexOf("\\") + 1,
  //                                      moduleFname.length());
  //  Serial.printf("Running from: %s\r\n", moduleFname);
  Serial.printf("Running from: %s\r\n", __FILE__);
  Serial.printf("Compiled on %s\r\n", __TIMESTAMP__);
  Serial.printf("Working with a %ix%i pixel screen (WxH as rotated)\r\n",
                tft.width(), tft.height());
  //  Serial.print("\r\nStack: ");
  //  Serial.println(uxTaskGetStackHighWaterMark(NULL) );
  //-----------------------------------------------------------------
  myBuildString = "Sprite61";
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf("Sprite61");

  //  Serial.print("\r\nStack before sprite61 allocation: ");
  //  Serial.println(uxTaskGetStackHighWaterMark(NULL));
  int *a;  // Sprite61 (the small one)
  a = (int*)sprite61.createSprite(spriteW, spriteH);
  if (a == 0) {
    Serial.println("sprite61 creation failed.  Cannot continue.");
    while (1);
  }
  Serial.printf("createSprite61 dispWidth x dispHeight returned: %p\r\n", a);

  int psramPresent = ESP.getPsramSize();
  if (psramPresent > 0)
    spriteHHOK = (int*)spriteHH.createSprite(sprite_W_HH, sprite_H_HH);  //SpriteHH, the Half Height one.
  if (spriteHHOK == 0 || psramPresent == 0) {
    Serial.println("spriteHH creation failed. Using tft drawing for 3-line display.");
  } else {
    Serial.println("spriteHH creation successful. Using spriteHH drawing for 3-line display.");
    Serial.printf("createSpriteHH dispWidth x dispHeight returned: %p\r\n", spriteHHOK);
    ofr.setDrawer(spriteHH);
    if (ofr.loadFont(LiquidCrystalTTF, sizeof(LiquidCrystalTTF))) {
      Serial.println("Render loadFont error for LiquidCrystalTTF. Setup 1");
      while (1);
    }
    ofr.setFontColor(TFT_YELLOW, DarkerRed);
    ofr.setFontSize(190);
    ofr.setDrawer(tft);
  }
  //-----------------------------------------------------------------

  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf("Preferences");

  // The begin() method opens a “storage space” with a defined namespace.
  // The false argument means that we’ll use it in read/write mode.
  // Use true to open or create the namespace in read-only mode.
  // Name the "folder" we will use and set for read/write.

  preferences.begin("LittleClock", false);
  whichToShow = preferences.getInt("defaultShow", analogHandsShow);
#if defined LOCK_TO_DTZ
  whichToShow = dtz_Show;
#endif

  //  whichToShow = three_LineShow;  // Testing

  prevWhichToShow = whichToShow;
  Serial.printf("Which to show preference: %i (%s)\r\n",
                whichToShow, displayName[whichToShow]);
  preferences.end();  // Close LittleClock

  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf("WiFiManager");
  startWiFiManager();

  IPAddress ip = WiFi.localIP();
  sprintf(workDate, "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);

  tft.fillScreen(SkyBlue);
  tft.setTextColor(TFT_BLACK, SkyBlue);  // Foreground color, Background color
  ofr.setCursor(dispWidth / 2,  50); ofr.cprintf("WiFi");
  ofr.setCursor(dispWidth / 2, 108); ofr.cprintf("connected to");
  ofr.setCursor(dispWidth / 2, 172); ofr.cprintf(workDate);
  ofr.setCursor(dispWidth / 2, 238); ofr.cprintf(WiFi.SSID().c_str());
  for (loopWait = 0; loopWait < 3000; loopWait++) delay(1);  // Wait 3 seconds.

  tft.fillScreen(SkyBlue);
  yPos = 50;
  myBuildString = "Little Clock v" + String(Vers);
  ofr.setCursor(dispWidth / 2, yPos); ofr.cprintf(myBuildString.c_str());
  ofr.setCursor(dispWidth / 2, yPos + 80); ofr.cprintf("Initializing");

  myBuildString = "Calender";
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf("Calender");
  InitCalendarHighlights();  // Load and sort the array

  Serial.println("Getting time epoch");
  //  tft.drawString("Time", xCenter, yPos + 160); delay(250);
  tft.fillRect(0, yPos + 160, dispWidth, ofrFontHeight, SkyBlue);
  ofr.setCursor(dispWidth / 2, yPos + 160); ofr.cprintf("Time");

  // If this is changed, also go to Defines_and_Docs,
  //  around line 64 and coordinate.
  // Search for "String topCity =" to find the code.
#if defined CONFIG_FOR_JOE
  //  Serial.println("Setting cities for Joe.");
  String homeTimeLocStr = "America/Los Angeles";
  String dtzTopCityLocStr = "America/Los Angeles";
  String dtzBottomCityLocStr = "Asia/Manila";
  homeTime.setLocation(homeTimeLocStr);
  dtzTopCity.setLocation(dtzTopCityLocStr);
  dtzBottomCity.setLocation(dtzBottomCityLocStr);
#else  // Config for Mike
  //  Serial.println("Setting cities for Mike.");`
  String homeTimeLocStr = "Asia/Manila";
  String dtzTopCityLocStr = "Asia/Manila";
  String dtzBottomCityLocStr = "America/Los Angeles";
  homeTime.setLocation(homeTimeLocStr);
  dtzTopCity.setLocation(dtzTopCityLocStr);
  dtzBottomCity.setLocation(dtzBottomCityLocStr);
#endif
  setInterval(NTP_Update);
  if (!waitForSync(60)) ESP.restart();  // Wait 60 seconds, reboot and try again.
  Serial.println("UTC:             " + UTC.dateTime());
  Serial.println("Hometime:        " + homeTime.dateTime());
  Serial.println("DTZ Top City:    " + dtzTopCity.dateTime());
  Serial.println("DTZ Bottom City: " + dtzBottomCity.dateTime());
  //  if (UTC.now()        == homeTime.now()   || UTC.now()      == dtzTopCity.now()    || UTC.now() == dtzBottomCity.now() ||
  //      homeTime.now()   == dtzTopCity.now() || homeTime.now() == dtzBottomCity.now() ||
  //      dtzTopCity.now() == dtzBottomCity.now()) {
  //    Serial.println("The time fetch was defective.  Rebooting in 2 seconds to try again.");
  //    delay(2000); ESP.restart();
  //  }
  // Use homeTime for this one.

  tft.fillScreen(SkyBlue);
  //  tft.drawString("Initialization", xCenter, yCenter - 60);
  //  tft.drawString("Complete", xCenter, yCenter + 30);
  ofr.setCursor(dispWidth / 2, yCenter - 90); ofr.cprintf("Initialization");
  ofr.setCursor(dispWidth / 2, yCenter + 30); ofr.cprintf("Complete");

  for (loopWait = 0; loopWait < 1500; loopWait++) delay(1);  // Wait 1.5 seconds.
  tft.setTextPadding(0);  // Blanking area function disabled.

#if defined TFT_BL
  Serial.printf("Setting display brightness for %02i:00 to %02i.\r\n",
                homeTime.hour(), hourlyBrilliance[homeTime.hour()]);
  ledcWrite(pwmLedChannelTFT, hourlyBrilliance[homeTime.hour()]);
#endif
  Serial.println("Initialization Completed. To work, we go...");

  prevHour = homeTime.hour();  // No flash on startup, please.
  Serial.print("Starting on "); Serial.println(homeTime.dateTime());
  // For BCDShow
  segWidth = tft.width() / 6;
  segHeight = (tft.height() - 50) / 4;

  //  serverPath = "https://api.apilayer.com/exchangerates_data/latest?"
  //               "symbols=PHP&base=USD&apikey=";
  //  serverPath = serverPath + apiArray[0];

  showSelectedClock(true);  // "true" will initialize the screen.
}
/***************************************************************************/
void loop()
/****loop*******************************************************************/
{
  //This must run every entry into loop.  Put nothing before it!
  touchType = myGetTouch(&myiX, &myiY, &myeX, &myeY, &mydX, &mydY);

  if (touchType != NO_TOUCH) {  // If there was a touch
    //    Serial.printf("Loop entry seeing touch value %i\r\n", touchType);
    if (touchType == SHORT_TOUCH) whichToShow++;
    else if (touchType == DOUBLE_TOUCH)
      ShowCalendar(homeTime.month(), homeTime.year());
    else if (touchType == TRIPLE_TOUCH) PayDaySearch();
    else if (touchType == LONG_TOUCH)   showOptionsScreen();
    if (touchType < SWIPE_OFFSET)
      showSelectedClock(true);  // "true" will initialize the screen.
    else {
      PayDaySearch();
      showSelectedClock(true);  // "true" will initialize the screen.
    }
  }

  if (Serial.available()) handleUserReq();

  //  calcFullDate();
  if (last_sec == homeTime.second()) {
    delay(1); return;  // Same second?  No action needed.
  }
  last_sec = homeTime.second();  // Out of the way, coming through!
  // Next second has arrived.  I can do my job, now.
  digitalWrite(LED_BUILIN, true); // Turn it off on some boards, on on others.

  loopStartMS = millis();

  // Only save "Show" preferences at the top of the minute, only if changed,
  //  to save flash memory life.

  if (homeTime.second() == 0) {
    //    Serial.println(homeTime.dateTime());); // A debug.print, really...
    if (prevWhichToShow != whichToShow) {  // If it has been changed, save it now
      prevWhichToShow = whichToShow;  // Remember the new setting so no resaving.
      preferences.begin("LittleClock", false);         // Open LittleClock in r/w.
      preferences.putInt("defaultShow", whichToShow);  // Save the data.
      preferences.end();                               // Close LittleClock
      Serial.printf("Which to show preference: %i (%s)\r\n",
                    whichToShow, displayName[whichToShow]);
    }
  }
  // Waiting until the new hour first second is shown, then do the show.
  // On hour change, do a few things:
  //  1. Boot at 5am on Sundays
  //  2. Do the "hour dance".  In this case, some inverts.
  //  3. Change the screen brightness if needed.
  if (prevHour != homeTime.hour()) {
    prevHour = homeTime.hour();  // Reset hour.
    // Refresh (false) each call except on a new hour, then init (true).
    showSelectedClock(true);  // Show selected clock face after screen init.
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false); delay(200);
    tft.invertDisplay(true);  delay(200); tft.invertDisplay(false);
    if ((homeTime.hour() == 5) && (homeTime.weekday() == 2))  // Tuesday 5am
      ESP.restart();  // Weekly reboot
  } else {  // Same hour, don't init clock.  NO FLICKERING!
    showSelectedClock(false);      // Show without screen init, just update it.
  }
  // Screen brightness adjustment on the hour.
  // Don't need the DispOff command.  The PWM on the LED channel is enough.
  // Set up hourly brightness values in UserSettings.h
  if (ledcRead(pwmLedChannelTFT) != hourlyBrilliance[homeTime.hour()]) {
    Serial.printf("Setting display brightness for %i:00 to %i.\r\n",
                  homeTime.hour(), hourlyBrilliance[homeTime.hour()]);
    ledcWrite(pwmLedChannelTFT, hourlyBrilliance[homeTime.hour()]);
    delay(200);
  }
  lastLoopTime = millis() - loopStartMS;
  digitalWrite(LED_BUILIN, false); // Turn it off (on some boards).
}
//***************************************************************************/
void startWiFiMulti()
//***startWiFiMulti***************************************************************/
{
  //  wifiMulti.addAP("MikeysHS",    "signal2noise");
  //  wifiMulti.addAP("LallaveWifi", "Lallave@Family7");
  //  wifiMulti.addAP("Bedroom",     "Ilti3168");
  //  //  wifiMulti.addAP("DownUnder",   "signal2noise");  // Was causing problems.
  //  wifiMulti.addAP("RaPhaEl",     "thinkpositive-0829");
  //  wifiMulti.addAP("N_Port",      "helita1943");
  //
  //  int waitingWiFi = 1;
  //  Serial.print("Connecting Wifi...");
  //  for (int i = 0; i < 40; i++) {
  //    tft.drawString("WiFi (try #" + String(i + 1) + ")", xCenter, yPos + 160);
  //    Serial.printf(" %i", waitingWiFi++);
  //    if (wifiMulti.run() == WL_CONNECTED) {
  //      Serial.print("\r\nWiFi connected to: ");
  //      Serial.println(WiFi.SSID());
  //      Serial.print("IP address: ");
  //      Serial.println(WiFi.localIP());
  //      break;
  //    }
  //    delay(5000);
  //  }
  //  /*
  //     typedef enum {
  //    WIFI_POWER_19_5dBm = 78,// 19.5dBm
  //    WIFI_POWER_19dBm = 76,// 19dBm
  //    WIFI_POWER_18_5dBm = 74,// 18.5dBm
  //    WIFI_POWER_17dBm = 68,// 17dBm
  //    WIFI_POWER_15dBm = 60,// 15dBm
  //    WIFI_POWER_13dBm = 52,// 13dBm
  //    WIFI_POWER_11dBm = 44,// 11dBm
  //    WIFI_POWER_8_5dBm = 34,// 8.5dBm
  //    WIFI_POWER_7dBm = 28,// 7dBm
  //    WIFI_POWER_5dBm = 20,// 5dBm
  //    WIFI_POWER_2dBm = 8,// 2dBm
  //    WIFI_POWER_MINUS_1dBm = -4// -1dBm
  //    } wifi_power_t;
  //  */
  //  Serial.printf("WiFi default transmit power: %i\n", WiFi.getTxPower());
  //  //  WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);
  //  if (wifiMulti.run() != WL_CONNECTED) ESP.restart();
}
//***************************************************************************/
void startWiFiManager()
//***startWiFiManager********************************************************/
{

  //  wifiManager.resetSettings(); // wipe settings -- emergency use only.

  wifiManager.setTimeout(60);  // 30 second connect timeout then reboot.
  wifiManager.disconnect();
  //  wifiManager.mode(WIFI_STA); // switch off AP
  if (!wifiManager.autoConnect(myPortalName, "BigLittleClock")) {
    Serial.println(F("failed to connect and hit timeout"));
    //Reboot and try again.
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
  // Set callback that gets called when connecting to previous WiFi fails,
  //  and enters Access Point mode
  wifiManager.setAPCallback(configModeCallback);

  //Fetches ssid and pass and tries to connect
  //If it does not connect it starts an access point with the specified name
  //here  "ESPWiFiMgr"
  //and goes into a blocking loop awaiting configuration
  wifiManager.setDebugOutput(false);  // Quieter on the Serial Monitor
  if (!wifiManager.autoConnect(myPortalName)) {
    Serial.println(F("Failed to connect and hit timeout."));
    //Reset and try again, or maybe put it to deep sleep
#ifdef ESP32
    ESP.restart();
#else
    ESP.reset();
#endif
  }
  // If you get here you have connected to the WiFi
  Serial.println(F("Now connected. To work, we go..."));
  delay(2000);
}
//***************************************************************************/
//uint16_t getPixelColor(uint16_t x, uint16_t y)
///***************************************************************************/
//{
// Does not seem to work on the ILI9486, sadly...
// Callback function to provide the pixel color at x,y
//  return tft.readPixel(x, y);
//}
///***************************************************************************/
//int trySSHColor()
///***************************************************************************/
//{
//  delay(10000);
//  Serial.printf("\r\n%sRed, %sBright Red, %sNormal.\r\n",
//                sshRED, sshREDL, sshNC);
//  Serial.printf("%sBlack, %sDark Gray, %sNormal.\r\n",
//                sshBlack, sshGrayD, sshNC);
//  Serial.printf("%sGreen, %sBright Green, %sNormal.\r\n",
//                sshGreen, sshGreenL, sshNC);
//  Serial.printf("%sBrown/Orange, %sBright Yellow, %sNormal.\r\n",
//                sshBrownOrange, sshYellow, sshNC);
//  Serial.printf("%sBlue, %sBrighunloadt Blue3.21, %sNormal.\r\n",
//                sshBlue, sshBlueL, sshNC);
//  Serial.printf("%sPurple, %sBright Purple, %sNormal.\r\n",
//                sshPurple, sshPurpleL, sshNC);
//  Serial.printf("%sCyan, %sBright Cyan, %sNormal.\r\n",
//                sshCyan, sshCyanL, sshNC);
//  Serial.printf("%sLight Gray, %sWhite, %sNormal.\r\n",
//                sshGrayL, sshWhite, sshNC);
//}
/***************************************************************************/
void configModeCallback (WiFiManager * myWiFiManager)
/***************************************************************************/
{
  Serial.println(F("Entered config mode..."));
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  yPos = 10;
  tft.fillScreen(Red);
  tft.setTextColor(White, Red);  // Foreground color, Background color
  tft.drawString("Need SSID", xCenter, yPos);
  tft.drawString("Connect to", xCenter, yPos + 43);
  tft.drawString(myPortalName, xCenter, yPos + 85);
}
