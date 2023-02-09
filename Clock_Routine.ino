void drawBubbles() {
  int loopControl, rndX, rndY;
  for (loopControl = 0; loopControl < 2000; loopControl++) {
    rndX = random(tft.width());
    rndY = random(tft.height());
    tft.fillCircle(rndX, rndY, random(40) + 4, GetRndRGB565());
    myWait(1);  // Just slow it down slightly for each circle.
  }
}
uint32_t GetRndRGB565() {
  R = random(200) + 25;
  G = random(200) + 25;
  B = random(200) + 25;
  return (RGB565(R, G, B));
}
void myWait(unsigned long waitMillis) {
  unsigned long startMillis = millis();
  while (millis() < startMillis + waitMillis) {
    //wait approx. [period] ms
  }
  return;
}
/***************************************************************************/
void draw_Clock_Face()
/****draw_Clock_Face********************************************************/
{
  int indiciaNear = dispHeight * 0.43;  // 0.408333333;  // By ratio
  int indiciaFar = dispHeight * 0.48;   // By ratio
  int nearX, nearY, farX, farY;
  int nearX1, nearY1, farX1, farY1;
  int nearX2, nearY2, farX2, farY2;

  // draw hour pointers around the face of a clock
  for (int i = 0; i < 12; i++) {
    nearX  = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter;
    nearY  = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) + yCenter;
    farX   = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter;
    farY   = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) + yCenter;
    tft.drawLine(nearX, nearY, farX, farY, ILI9341_YELLOW);

    //These 4 will be thicker than the others (0, 3, 6, & 9).
    if (i == 0 || i == 6) {
      nearX1 = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter + 1;
      nearY1 = nearY;
      farX1  = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter + 1;
      farY1  = farY;
      nearX2 = (indiciaNear * sin(PI - (2 * PI) / 12 * i)) + xCenter - 1;
      nearY2 = nearY;
      farX2  = (indiciaFar  * sin(PI - (2 * PI) / 12 * i)) + xCenter - 1;
      farY2  = farY;
    }
    if (i == 3 || i == 9) {
      nearX1 = nearX; nearY1 = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter + 1;
      farX1  = farX;  farY1  = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter + 1;
      nearX2 = nearX; nearY2 = (indiciaNear * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter - 1;
      farX2  = farX;  farY2  = (indiciaFar  * cos(PI - (2 * PI) / 12 * i)) +
                               yCenter - 1;
    }
    if (i % 3 == 0) {
      tft.drawLine(nearX1, nearY1, farX1, farY1, ILI9341_YELLOW);
      tft.drawLine(nearX2, nearY2, farX2, farY2, ILI9341_YELLOW);
    }
  }
}
/***************************************************************************/
void draw_Hands(int hour, int minute, int second)
/****draw_Hands*************************************************************/
{
  float handRadians;

  // Settings for 240

  // Length of the pointer end of the hand.
  //  int hourHandLength = 48;
  // Length the twin tails.
  //  int HourHandBackLength = 15;
  //
  // Length of the pointer end of the hand.
  //  int minuteHandLength = 62;
  // Length the twin tails.
  //  int minuteHandBackLength = 19;

  // By ratio

  // Length of the pointer end of the hand.
  int hourHandLength = dispHeight * 0.2;
  // Length the twin tails.
  int HourHandBackLength =  dispHeight * 0.0625;

  // Length of the pointer end of the hand.
  int minuteHandLength = dispHeight * 0.258333333;
  // Length the twin tails.
  int minuteHandBackLength = dispHeight * 0.079166667;

  hour = hour % 12;  // Only 12 hour indicia on a clock face.
  // First, calculate the hand positions for both.
  // Each hour gives 30° to the hour hand.
  // Every minute gives 1/2° to the hour hand.
  handRadians = ((float(hour) * -30. - float(minute) / 2.) - 180) /
                57.2957795130823;
  // This is the tip of the pointer end.
  myHX  = (hourHandLength * sin(handRadians)) + xCenter;
  myHY  = (hourHandLength * cos(handRadians)) + yCenter;
  //Now calculate the hour hand overhang past the center for hour hand.
  //Do this twice with +/-20 degrees then draw 2 triangles.
  handRadians = ((float(hour) * -30. - float(minute) / 2.) - 20.)
                / 57.2957795130823;
  myHXb1  = (HourHandBackLength * sin(handRadians)) + xCenter;
  myHYb1  = (HourHandBackLength * cos(handRadians)) + yCenter;
  handRadians = ((float(hour) * -30. - float(minute) / 2.) + 20.)
                / 57.2957795130823;
  myHXb2  = (HourHandBackLength * sin(handRadians)) + xCenter;
  myHYb2  = (HourHandBackLength * cos(handRadians)) + yCenter;

  //Now calculate the minute hand.
  //Every minute gives 6° to the minute hand. Every second gives .1°
  // to the minute hand.
  handRadians = ((float(minute) * -6. - float(second) / 10.) - 180.)
                / 57.2957795130823;
  // This is the tip of the pointer end.
  myMX = (minuteHandLength * sin(handRadians)) + xCenter;
  myMY = (minuteHandLength * cos(handRadians)) + yCenter;
  //Now the back (short) side of the minute hand across the center.
  //Do this twice with +/-20 degrees then draw 2 triangles.
  handRadians = ((float(minute) * -6. - float(second) / 10.) - 20.)
                / 57.2957795130823;
  myMXb1 = (minuteHandBackLength * sin(handRadians)) + xCenter;
  myMYb1 = (minuteHandBackLength * cos(handRadians)) + yCenter;
  handRadians = ((float(minute) * -6. - float(second) / 10.) + 20.)
                / 57.2957795130823;
  myMXb2 = (minuteHandBackLength * sin(handRadians)) + xCenter;
  myMYb2 = (minuteHandBackLength * cos(handRadians)) + yCenter;

  eraseColor = DarkerRed;
  //  if (myIsPM) eraseColor = DarkerBlue;
  //If either hand moved, must erase and rewrite both.
  // initHands opens the timed gate early.
  if (homeTime.second() % 10 == 0 || initHands) {
    //First, see if this is a new place to draw.
    if (prevHX != myHX || prevMX != myMX || prevHY != myHY || prevMY != myMY
        || initHands) {  // initHands overrides the hands moved update check.
      initHands = false;
      if (prevHX < 10000) {  // Don't erase if nothing there already!
        //It is a new place to draw so remove the previous triangles
        tft.fillTriangle(xCenter, yCenter,
                         prevHX, prevHY,
                         prevHXb1,  prevHYb1,
                         eraseColor);
        tft.fillTriangle(xCenter, yCenter,
                         prevHX, prevHY,
                         prevHXb2, prevHYb2,
                         eraseColor);
      }
      if (prevMX < 10000) {  // Don't erase if nothing there already!
        //It is a new place to draw so remove the previous triangles
        tft.fillTriangle(xCenter, yCenter,
                         prevMX, prevMY,
                         prevMXb1,  prevMYb1,
                         eraseColor);
        tft.fillTriangle(xCenter, yCenter,
                         prevMX, prevMY,
                         prevMXb2,  prevMYb2,
                         eraseColor);
      }
      //Remember for next time through, for erasing.
      prevHX   = myHX;   prevHY   = myHY;
      prevHXb1 = myHXb1; prevHYb1 = myHYb1;
      prevHXb2 = myHXb2; prevHYb2 = myHYb2;
      prevMX   = myMX;   prevMY   = myMY;
      prevMXb1 = myMXb1; prevMYb1 = myMYb1;
      prevMXb2 = myMXb2; prevMYb2 = myMYb2;
      //Now, finally, put in the new hour and minute triangles.
      tft.fillTriangle(xCenter, yCenter, myHX, myHY,
                       myHXb1, myHYb1, HHDarker);
      tft.fillTriangle(xCenter, yCenter, myHX, myHY,
                       myHXb2, myHYb2, HHDarker);
      tft.fillTriangle(xCenter, yCenter, myMX, myMY,
                       myMXb1, myMYb1, MHDarker);
      tft.fillTriangle(xCenter, yCenter, myMX, myMY,
                       myMXb2, myMYb2, MHDarker);
    }
  }
}
/***************************************************************************/
void update_Seconds(int myMin, int mySec)
/****update_Seconds*********************************************************/
{ // This routine takes about 3 ms.  Way more than I thought it would.
  // I force the dots because an hour dance may take longer than 1 second
  //  and that would leave the display messed up, so totally rebuild,
  //  every second.
  int i;
  if (myMin % 2 == 0) {
    // Even minute, drawing second dots from 1 to now
    for (i = 1; i <= mySec; i++) draw_Seconds_Dot(myMin, i, aModeDraw);
    // Erasing each dot from now + 1 second through 60 seconds.
    for (i = mySec + 1; i <= 60; i++) draw_Seconds_Dot(myMin, i, aModeErase);
  } else {
    // Odd minute, erasing second dots from 1 to now
    for (i = 1; i <= mySec; i++) draw_Seconds_Dot(myMin, i, aModeErase);
    // Drawing each dot from now + 1 second through 60 seconds.
    for (i = mySec + 1; i <= 60; i++) draw_Seconds_Dot(myMin, i, aModeDraw);
  }
}
/***************************************************************************/
void draw_Seconds_Dot(int minute, int second, int mode)
/****draw_Seconds_Dot*******************************************************/
{
  // Not really hand length but the distance from center where the dot goes.
  handLength = dispHeight * 0.4;

  mySX = (handLength * sin(PI - (2 * PI) / 60 * second)) + xCenter;
  mySY = (handLength * cos(PI - (2 * PI) / 60 * second)) + yCenter;

  if (mode == aModeDraw) {
    tft.fillCircle(mySX, mySY, 3, ILI9341_YELLOW);
  } else {
    tft.fillCircle(mySX, mySY, 3, DarkYellow);
  }
}
/***************************************************************************/
void initAnalog(int hour, int minute, int second)
/****initAnalog*************************************************************/
{
  tft.fillScreen(DarkerRed);

  initHands = true;  // Allow past the 10 second update gate.
  draw_Clock_Face();

  draw_Hands(hour, minute, second);
  tft.fillCircle(xCenter, yCenter, 4, ILI9341_DARKGREY);  //draw_CenterDot();
  update_Seconds(minute, second);  // Catch up the seconds to now.

  // Cause a complete rewrite of the 4 corners.
  prev_month = -1; prev_DOM = -1; prev_DOW = -1; prev_myYear = -1;
  showCorners();
}
/***************************************************************************/
void updateAnalogScreen()
/****updateAnalogScreen*****************************************************/
{

  //Draw in the proper place.
  draw_Hands(homeTime.hour(), homeTime.minute(), homeTime.second());
  tft.fillCircle(xCenter, yCenter, 4, ILI9341_DARKGREY);  //draw center dot
  update_Seconds(homeTime.minute(), homeTime.second());
  showCorners();
}
/***************************************************************************/
void showCorners()
/****showCorners************************************************************/
{
  ofr.setDrawer(tft); // Link renderer to base display.
  // Foreground color, Background color
  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF. showCorners 1");
    while (1);
  }
  ofr.setFontSize(60);
  ofr.setFontColor(ILI9341_YELLOW, DarkerRed);  // Foreground color, Background color

  //Month name, abbreviated, in top, left corner.
  if (prev_month != homeTime.month()) {
    if (homeTime.month() == 6 || homeTime.month() == 7)
      myBuildString = monthStr(homeTime.month());
    else
      myBuildString = monthShortStr(homeTime.month());
    ofr.setCursor(8, 0); ofr.printf(myBuildString.c_str());  // Month name
    prev_month = homeTime.month();
  }
  //Number of day of the month (1-~31) in top, right corner.
  if (prev_DOM != homeTime.day()) {
    myBuildString = String(homeTime.day() + th(homeTime.day()));
    ofr.setCursor(dispWidth - 12, 0); ofr.rprintf(myBuildString.c_str());  // Day of month
    prev_DOM = homeTime.day();
  }
  //Day of Week name, abbreviated, (DOW) in bottom, left corner.
  if (prev_DOW != homeTime.day()) {
    myBuildString = dayShortStr(homeTime.weekday());
    myTH = ofr.getTextHeight(myBuildString.c_str());
    ofr.setCursor(8, dispHeight - myTH - 16); ofr.printf(myBuildString.c_str());  // Name of day of week
    prev_DOW = homeTime.day();
  }
  //Year value (4 digits) in right, bottom corner.
  if (prev_myYear != homeTime.year()) {
    myBuildString = String(homeTime.year());
    myTW = ofr.getTextWidth(myBuildString.c_str());
    ofr.setCursor(dispWidth - 12, dispHeight - myTH - 16); ofr.rprintf(myBuildString.c_str()); // Year
    prev_myYear = homeTime.year();
  }
}

/***************************************************************************/
void doDTZ_Show()
/****doDTZ_Show*************************************************************/
{

  // ------------------> TOP CITY

  ofr.setDrawer(sprite61);  // And... we're off and sprite'ing.
  // Foreground color, Background color
  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF. doDTZ_Show 1");
    while (1);
  }
  ofr.setFontSize(72);
  ofr.setFontColor(DarkerRed, ILI9341_YELLOW);  // Foreground color, Background color

  workDate[0] = 0; fullDate[0] = 0;  // Set to zero length string
  sprintf(workDate, "%s ", dayShortStr(dtzTopCity.weekday()));
  strcat(fullDate, workDate);
  if (homeTime.month() == 6 || homeTime.month() == 7)
    sprintf(workDate, "%s", monthStr(dtzTopCity.month()));
  else
    sprintf(workDate, "%s", monthShortStr(dtzTopCity.month()));
  strcat(fullDate, workDate);
  sprintf(workDate, " %i", dtzTopCity.day());
  strcat(fullDate, workDate);
  strcat(fullDate, th(dtzTopCity.day()).c_str());

  workTime[0] = 0; fullTime[0] = 0;  // Set to zero length string
  sprintf(workTime, "%02i",  dtzTopCity.hour());
  strcat(fullTime, workTime);
  sprintf(workTime, ":%02i", dtzTopCity.minute());
  strcat(fullTime, workTime);
  sprintf(workTime, ":%02i", dtzTopCity.second());
  strcat(fullTime, workTime);
  //    if (tzTopCity.isAM())
  //      strcat(fullTime, " AM");
  //    else
  //      strcat(fullTime, " PM");
  if (strcmp(prevTopDate, fullDate) != 0) {  // If they don't compare...
    sprite61.fillSprite(TFT_YELLOW); sprite61.setTextColor(DarkerRed);  // Yellow box
    ofr.setCursor(spriteWC - 1, -6); ofr.cprintf(fullDate);
    sprite61.pushSprite(spriteM, 38);
    strcpy(prevTopDate, fullDate);
  }
  sprite61.fillSprite(TFT_YELLOW); sprite61.setTextColor(DarkerRed);  // Yellow box
  ofr.setCursor(70, -6); ofr.printf(fullTime);  // Variable pitch font, 70 fixes it in place
  sprite61.pushSprite(spriteM, 99);

  // ------------------> BOTTOM CITY

  workDate[0] = 0; fullDate[0] = 0;  // Set to zero length string
  sprintf(workDate, "%s ", dayShortStr(dtzBottomCity.weekday()));
  strcat(fullDate, workDate);
  if (homeTime.month() == 6 || homeTime.month() == 7)
    sprintf(workDate, "%s", monthStr(dtzBottomCity.month()));
  else
    sprintf(workDate, "%s", monthShortStr(dtzBottomCity.month()));
  strcat(fullDate, workDate);
  sprintf(workDate, " %i", dtzBottomCity.day());  strcat(fullDate, workDate);
  //  sprintf(workDate, ", %i",  dtzBottomCity.year()); strcat(fullDate, workDate);
  //  Serial.print("Bangui Date: "); Serial.println(fullDate);
  strcat(fullDate, th(dtzBottomCity.day()).c_str());

  workTime[0] = 0; fullTime[0] = 0;  // Set to zero length string
  sprintf(workTime, "%02i",  dtzBottomCity.hour());
  strcat(fullTime, workTime);
  sprintf(workTime, ":%02i", dtzBottomCity.minute());
  strcat(fullTime, workTime);
  sprintf(workTime, ":%02i", dtzBottomCity.second());
  strcat(fullTime, workTime);
  //    if (tzBottomCity.isAM())
  //      strcat(fullTime, " AM");
  //    else
  //      strcat(fullTime, " PM");

  if (strcmp(prevBottomDate, fullDate) != 0) {  // If they don't compare...
    //    sprite61.fillSprite(DarkerRed); sprite61.setTextColor(TFT_YELLOW);  // "Normal"
    sprite61.fillSprite(TFT_YELLOW); sprite61.setTextColor(DarkerRed);  // Yellow box
    //    sprite61.setTextDatum(TC_DATUM);
    //    sprite61.drawString(fullDate, spriteWC - 1, 1);
    ofr.setCursor(spriteWC - 1, -6); ofr.cprintf(fullDate);
    sprite61.pushSprite(spriteM, yCenter + 38);
    strcpy(prevBottomDate, fullDate);
  }
  //    sprite61.fillSprite(DarkerRed); sprite61.setTextColor(TFT_YELLOW);  // "Normal"
  sprite61.fillSprite(TFT_YELLOW); sprite61.setTextColor(DarkerRed);  // Yellow box
  //  sprite61.setTextDatum(TL_DATUM);
  //  sprite61.drawString(fullTime, 70, 7);
  ofr.setCursor(70, -6); ofr.printf(fullTime);  // Variable pitch font, 70 fixes it in place
  sprite61.pushSprite(spriteM, yCenter + 99);
}
/***************************************************************************/
void doBCDShow()
/****doBCDShow**************************************************************/
{
  // Hour Decade ***********************************

  //This routine squirts out the bits backwards.  0001 is 8.
  n = homeTime.hour() / 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (hourDecade[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(0, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Red_68);
    hourDecade[0] = true;
  }
  if (hourDecade[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(0, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Red_68);
    hourDecade[0] = false;
  }

  if (hourDecade[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(0, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Red_68);
    hourDecade[1] = true;
  }
  if (hourDecade[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(0, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Red_68);
    hourDecade[1] = false;
  }

  // Hour Unit   ***********************************

  //This routine squirts out the bits backwards.  0001 is 8.
  n = homeTime.hour() % 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (hourUnit[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(segWidth * 1, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Red_68);
    hourUnit[0] = true;
  }
  if (hourUnit[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(segWidth * 1, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Red_68);
    hourUnit[0] = false;
  }

  if (hourUnit[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(segWidth * 1, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Red_68);
    hourUnit[1] = true;
  }
  if (hourUnit[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(segWidth * 1, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Red_68);
    hourUnit[1] = false;
  }

  if (hourUnit[2] == false && BCDBreak[2] == 1) {
    tft.pushImage(segWidth * 1, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Bright_Red_68);
    hourUnit[2] = true;
  }
  if (hourUnit[2] == true && BCDBreak[2] == 0) {
    tft.pushImage(segWidth * 1, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Dark_Red_68);
    hourUnit[2] = false;
  }

  if (hourUnit[3] == false && BCDBreak[3] == 1) {
    tft.pushImage(segWidth * 1, 52, LEDWidth, LEDHeight, Bright_Red_68);
    hourUnit[3] = true;
  }
  if (hourUnit[3] == true && BCDBreak[3] == 0) {
    tft.pushImage(segWidth * 1, 52, LEDWidth, LEDHeight, Dark_Red_68);
    hourUnit[3] = false;
  }

  // Minute Decade *********************************

  //This routine squirts out the bits backwards.  0001 is 8.
  n = homeTime.minute() / 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (minuteDecade[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(segWidth * 2, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteDecade[0] = true;
  }
  if (minuteDecade[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(segWidth * 2, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteDecade[0] = false;
  }

  if (minuteDecade[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(segWidth * 2, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteDecade[1] = true;
  }
  if (minuteDecade[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(segWidth * 2, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteDecade[1] = false;
  }

  if (minuteDecade[2] == false && BCDBreak[2] == 1) {
    tft.pushImage(segWidth * 2, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteDecade[2] = true;
  }
  if (minuteDecade[2] == true && BCDBreak[2] == 0) {
    tft.pushImage(segWidth * 2, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteDecade[2] = false;
  }

  // Minute Unit ***********************************

  //This routine squirts out the bits backwards.  0001 is 8.
  n = homeTime.minute() % 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (minuteUnit[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(segWidth * 3, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteUnit[0] = true;
  }
  if (minuteUnit[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(segWidth * 3, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteUnit[0] = false;
  }

  if (minuteUnit[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(segWidth * 3, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteUnit[1] = true;
  }
  if (minuteUnit[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(segWidth * 3, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteUnit[1] = false;
  }

  if (minuteUnit[2] == false && BCDBreak[2] == 1) {
    tft.pushImage(segWidth * 3, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteUnit[2] = true;
  }
  if (minuteUnit[2] == true && BCDBreak[2] == 0) {
    tft.pushImage(segWidth * 3, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteUnit[2] = false;
  }

  if (minuteUnit[3] == false && BCDBreak[3] == 1) {
    tft.pushImage(segWidth * 3, 52, LEDWidth, LEDHeight, Bright_Yellow_68);
    minuteUnit[3] = true;
  }
  if (minuteUnit[3] == true && BCDBreak[3] == 0) {
    tft.pushImage(segWidth * 3, 52, LEDWidth, LEDHeight, Dark_Yellow_68);
    minuteUnit[3] = false;
  }

  // Second Decade *********************************

  //This routine squirts out the bits backwards.  0001 is 8.
  n = homeTime.second() / 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (secondDecade[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(segWidth * 4, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondDecade[0] = true;
  }
  if (secondDecade[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(segWidth * 4, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondDecade[0] = false;
  }

  if (secondDecade[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(segWidth * 4, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondDecade[1] = true;
  }
  if (secondDecade[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(segWidth * 4, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondDecade[1] = false;
  }

  if (secondDecade[2] == false && BCDBreak[2] == 1) {
    tft.pushImage(segWidth * 4, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondDecade[2] = true;
  }
  if (secondDecade[2] == true && BCDBreak[2] == 0) {
    tft.pushImage(segWidth * 4, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondDecade[2] = false;
  }

  // Second Unit ***********************************

  n = homeTime.second() % 10;
  for (i = 0; i < 4; i++) BCDBreak[i] = 0;
  for (i = 0; n > 0; i++)
  {
    BCDBreak[i] = n % 2; n = n / 2;
  }
  if (secondUnit[0] == false && BCDBreak[0] == 1) {
    tft.pushImage(segWidth * 5, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondUnit[0] = true;
  }
  if (secondUnit[0] == true && BCDBreak[0] == 0) {
    tft.pushImage(segWidth * 5, (segHeight * 3) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondUnit[0] = false;
  }

  if (secondUnit[1] == false && BCDBreak[1] == 1) {
    tft.pushImage(segWidth * 5, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondUnit[1] = true;
  }
  if (secondUnit[1] == true && BCDBreak[1] == 0) {
    tft.pushImage(segWidth * 5, (segHeight * 2) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondUnit[1] = false;
  }

  if (secondUnit[2] == false && BCDBreak[2] == 1) {
    tft.pushImage(segWidth * 5, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Bright_Green_68);
    secondUnit[2] = true;
  }
  if (secondUnit[2] == true && BCDBreak[2] == 0) {
    tft.pushImage(segWidth * 5, (segHeight * 1) + 52,
                  LEDWidth, LEDHeight, Dark_Green_68);
    secondUnit[2] = false;
  }

  if (secondUnit[3] == false && BCDBreak[3] == 1) {
    tft.pushImage(segWidth * 5, 52, LEDWidth, LEDHeight, Bright_Green_68);
    secondUnit[3] = true;
  }
  if (secondUnit[3] == true && BCDBreak[3] == 0) {
    tft.pushImage(segWidth * 5, 52, LEDWidth, LEDHeight, Dark_Green_68);
    secondUnit[3] = false;
  }
}
/***************************************************************************/
void do3LineShow()
/****do3LineShow************************************************************/
{
  ofr.setDrawer(tft); // Link renderer to base display.

  if (prevHour != homeTime.hour()) {  // On the hour, it is time to clean
    Serial.println("Clearing screen for new update based on hour change");
    tft.fillScreen(DarkerRed);  // Background good color for cleaning.
    prev_Line1 = ""; prev_Line2 = ""; prev_Line3 = "";  // Force redraw of all 3 lines.
  }

  //asdf5
  myBuildString = "";
  tempHour = homeTime.hour();
  if (showAMPM) {  // 12 hour (AM/PM) formatting
    if (tempHour == 0) tempHour = 12;
    if (tempHour > 12) tempHour -= 12;
  }
  if (tempHour > 9) {
    myBuildString = "1";
    tempHour -= 10;
  }
  myBuildString += String(tempHour) + ":";
  myBuildString += String(homeTime.minute() / 10);
  myBuildString += String(homeTime.minute() % 10);
  if (prev_Line1 != myBuildString) {
    prev_Line1 = myBuildString;
    ofr.unloadFont();
    if (ofr.loadFont(LiquidCrystalTTF, sizeof(LiquidCrystalTTF))) {
      Serial.println("Render loadFont error for LiquidCrystalTTF. 3-Line 1");
      while (1);
    }
    // Right here, we have to make a decision whether to use the SpriteHH (no flashing)
    //  or regular tft updating (flashing).  It depends on whether it was properly allocated
    //  during initialization.

    ofr.setFontColor(TFT_YELLOW, DarkerRed);
    ofr.setFontSize(190);
    if (spriteHHOK == 0) {  // 0 means there was no PSRAM allocation.  Use tft drawer.
      ofr.setDrawer(tft);
//      Serial.println("spriteHH creation failed. Using tft drawing.");
      tft.fillRect(0, 0, dispWidth, dispHeight / 2, DarkerRed);
      ofr.setCursor(dispWidth / 2, 10);
      ofr.cprintf(myBuildString.c_str());
    } else {  // We have PSRAM, use spriteHH that is there so no flickering.
      ofr.setDrawer(spriteHH);  // Use big sprite from PSRAM
//      Serial.println("spriteHH creation succeeded. Using spriteHH drawing.");
      spriteHH.fillSprite(DarkerRed);
      ofr.setCursor(spCenterW_HH, 10);
      ofr.cprintf(myBuildString.c_str());
      spriteHH.pushSprite(0, 0);
      ofr.setDrawer(tft); // Link renderer to base display.
    }

    //asdf6  // Only look at the rest if the minute field has changed.
    myBuildString = dayStr(homeTime.weekday());
    if (prev_Line2 != myBuildString) {
      prev_Line2 = myBuildString;
      ofr.unloadFont();
      if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
        Serial.println("Render loadFont error for BritanicBoldTTF 1. 3-Line 2");
        while (1);
      }
      ofr.setFontColor(TFT_YELLOW, DarkerRed);
      ofr.setFontSize(80);
      ofr.setCursor(dispWidth / 2, 160);
      tft.fillRect(0, 160, dispWidth, ofr.getTextHeight(myBuildString.c_str()), DarkerRed);
      ofr.cprintf(myBuildString.c_str());
    }
    //asdf7



    if (homeTime.month() == 6 || homeTime.month() == 7)
      myBuildString = monthStr(homeTime.month()) + " " +
                      String(homeTime.day()) + th(homeTime.day());
    else
      myBuildString = monthShortStr(homeTime.month()) + " " +
                      String(homeTime.day()) + th(homeTime.day());
    //              homeTime.dateTime("S");  // Can also be done this way.
    if (prev_Line3 != myBuildString) {
      prev_Line3 = myBuildString;
      ofr.unloadFont();
      if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
        Serial.println("Render loadFont error for BritanicBoldTTF  3-Line 3");
        while (1);
      }
      ofr.setFontColor(TFT_YELLOW, DarkerRed);
      ofr.setFontSize(80);
      ofr.setCursor(dispWidth / 2, 240);
      tft.fillRect(0, 240, dispWidth, ofr.getTextHeight(myBuildString.c_str()), DarkerRed);
      ofr.cprintf(myBuildString.c_str());
    }
  }
}
/***************************************************************************/
void do4LineShow()
/****do4LineShow************************************************************/
{
  ofr.setDrawer(tft); // Link renderer to base display.

  if (prevHour != homeTime.hour()) {     // On the hour, it is time to clean
    prevHour == homeTime.hour();
    tft.fillScreen(DarkerRed);  // Background good color for cleaning.
    prev_Line1 = ""; prev_Line2 = ""; prev_Line3 = "";  // Force redraw
  }
  // Line 1, Day of the week  asdf1
  myBuildString = dayStr(homeTime.weekday());
  if (prev_Line1 != myBuildString) {
    prev_Line1 = myBuildString;
    ofr.unloadFont();
    if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
      Serial.println("Render loadFont error for BritanicBoldTTF. 4-Line 1");
      while (1);
    }
    ofr.setFontColor(TFT_YELLOW, DarkerRed);
    ofr.setFontSize(80);
    ofr.setCursor(dispWidth / 2, -5);
    tft.fillRect(0, 0, dispWidth, ofr.getTextHeight(myBuildString.c_str()), DarkerRed);
    ofr.cprintf(myBuildString.c_str());
  }

  // Line 2, Month and day number  asdf2
  if (homeTime.month() == 6 || homeTime.month() == 7)
    myBuildString = monthStr(homeTime.month()) + " " + String(homeTime.day());
  else
    myBuildString = monthShortStr(homeTime.month()) + " " + String(homeTime.day());
  myBuildString += th(SS_Pay_Wed_DOM);
  if (prev_Line2 != myBuildString) {
    prev_Line2 = myBuildString;
    ofr.unloadFont();
    if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
      Serial.println("Render loadFont error for BritanicBoldTTF. 4-Line 2");
      while (1);
    }
    ofr.setFontColor(TFT_YELLOW, DarkerRed);
    ofr.setFontSize(80);
    ofr.setCursor(dispWidth / 2, 75);
    tft.fillRect(0, 75, dispWidth, ofr.getTextHeight(myBuildString.c_str()), DarkerRed);
    ofr.cprintf(myBuildString.c_str());
  }

  // Line 3, Year  asdf3
  myBuildString = String(homeTime.year());
  if (prev_Line3 != myBuildString) {
    prev_Line3 = myBuildString;
    ofr.unloadFont();
    if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
      Serial.println("Render loadFont error for BritanicBoldTTF.  4-Line 3");
      while (1);
    }
    ofr.setFontColor(TFT_YELLOW, DarkerRed);
    ofr.setFontSize(80);
    ofr.setCursor(dispWidth / 2, 155);
    tft.fillRect(0, 155, dispWidth, ofr.getTextHeight(myBuildString.c_str()), DarkerRed);
    ofr.cprintf(myBuildString.c_str());
  }

  // Line 4, Time  asdf4

  ofr.setDrawer(sprite61); // Link renderer to sprite (font will be rendered in sprite sprite61_HH)

  calcFourLineScreenTime();
  sprite61.fillSprite(DarkerRed);
  ofr.unloadFont();
  if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
    Serial.println("Render loadFont error for BritanicBoldTTF.  4-Line 4");
    while (1);
  }
  ofr.setFontColor(TFT_YELLOW, DarkerRed);
  ofr.setFontSize(75);
  ofr.setCursor(spriteW / 2, -12);
  ofr.cprintf(fourLineScreenTime);
  sprite61.pushSprite(spriteM, 250);
}
/****************************************************************************/
String th(int theDate)
/****************************************************************************/
{
  switch (theDate) {  // Make it English-like a little bit
    case 1: case 21: case 31: return "st"; break;
    case 2: case 22:          return "nd"; break;
    case 3: case 23:          return "rd"; break;
    default:                  return "th"; break;
  }
}
/****************************************************************************/
void getXchangeRate()
/****************************************************************************/
{
  bool fetchOK;
  unsigned long entryEpoch = UTC.now();

  Serial.printf("%02i:%02i:%02i Entering X Rate fetch routine.\r\n",
                homeTime.hour(), homeTime.minute(), homeTime.second());
  if (firstXPass) {
    firstXPass = false;
    Serial.println("This is the initial pass, not fetching X Rate this time.");
  } else {
    Serial.printf("UTC.now = %lu, ", entryEpoch);  // UTC epoch now
    Serial.printf("elapsed seconds: %lu.\r\n", entryEpoch - lastXRateFetchEpoch);
    if (UTC.minute() == 0) {
      // 1 minute of slack added,                             just to be sure.
      if ((entryEpoch - lastXRateFetchEpoch + 60) > XRateFetchInterval) {
        Serial.println("I will try an X Rate fetch now. (try 1)");
        fetchOK = xRateWorker(1);  // Try to get the data from apilayer server.
        if (!fetchOK) {
          Serial.println("First X Rate fetch failed, waiting 5 seconds for a retry. (try 2)");
          delay(5000);  // Wait 5 seconds and try a second time.
          fetchOK = xRateWorker(2);  // Try to get the data from apilayer server again.
        }
        if (!fetchOK) {
          Serial.println("Second X Rate fetch failed, waiting 5 seconds for final retry. (try 3)");
          delay(5000);  // Wait 5 seconds and try a second time.
          fetchOK = xRateWorker(3);  // Try to get the data from apilayer server for the last time.
        }
        if (fetchOK) lastXRateFetchEpoch = entryEpoch;  // Got a live one, update timer.
      } else {
        Serial.println("Not time to fetch rate yet. Not long enough since last fetch.");
      }
    } else {
      Serial.println("Not time to fetch rate yet. Minute not == 0.");
    }
  }
}
/****************************************************************************/
bool xRateWorker(int iTry)
/****************************************************************************/
{
  /* Returned JSON packet looks something like this:
    {
    "success": true,
    "timestamp": 1651599013,
    "base": "USD",
    "date": "2022-05-03",
    "rates": {
    "PHP": 52.511497
    }
    }
  */

  StaticJsonDocument<200> doc;  // Allocate 200 bytes on the stack.
  //Get just PHP compared to USD.  Returns about 136 bytes.
  //https://api.apilayer.com/exchangerates_data/latest?symbols=PHP
  // &base=USD&apikey=k5MJFkvlen6ebpAvKRpUlbbBd7uPAzAC
  //Get every rate they have in one go
  //https://api.apilayer.com/exchangerates_data/latest
  // &apikey=k5MJFkvlen6ebpAvKRpUlbbBd7uPAzAC
  int useAPIkey = 0;
  int httpResponseCode = 429;
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    while (useAPIkey < maxAPIkeys && httpResponseCode == 429) {
      serverPath = "https://api.apilayer.com/exchangerates_data/latest?"
                   "symbols=PHP&base=USD&apikey=";
      serverPath = serverPath + apiArray[useAPIkey];
      Serial.printf("Fetching exchange rate with API key %i with the following URI:\r\n%s\r\n",
                    useAPIkey + 1, serverPath.c_str());

      tft.fillScreen(DarkerRed);

      ofr.setDrawer(tft); // Link renderer to base display.
      ofr.unloadFont();
      if (ofr.loadFont(BritanicBoldTTF, sizeof(BritanicBoldTTF))) {
        Serial.println("Render loadFont error for BritanicBoldTTF. xRateWorker 1");
        while (1);
      }
      ofr.setFontSize(72);
      ofr.setFontColor(TFT_YELLOW, DarkerRed);  // Foreground color, Background color

      sprintf(workDate, "Try %i, Key %i", iTry, useAPIkey + 1);

      int yPos = 40;
      ofr.setCursor(xCenter, yPos);       ofr.cprintf("Attempting to");
      ofr.setCursor(xCenter, yPos + 90);  ofr.cprintf("fetch X rate.");
      ofr.setCursor(xCenter, yPos + 180); ofr.cprintf(workDate);

      http.begin(serverPath.c_str());
      httpResponseCode = http.GET();
      Serial.printf("HTTP Get response code: %i\r\n", httpResponseCode);
      useAPIkey++;
    }

    if (httpResponseCode == 200) {
      String payload = http.getString();
      Serial.println("Returned data:"); Serial.print(payload);
      http.end();  // Free resources
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return false;
      }
      pktValidity = doc["success"];
      // It is called ternary!
      //  Compare ? True return action : False return action
      Serial.print(pktValidity ? "V" : "Inv");
      Serial.println("alid packet received.");
      if (!pktValidity) {
        Serial.println("Rate packet not valid. Not decoded further.");
        PHP_Rate = 0.;
        return pktValidity;
      }
      unsigned long packetTime = doc["timestamp"];
      //      Serial.printf("Packet epoch: %lu\r\n", packetTime);
      long int os = homeTime.getOffset() * 60;
      //      Serial.printf("homeTime Offset: %i\r\n", os);
      tmElements_t tm;
      packetTime -= os;
      //      Serial.printf("Adjusted packet epoch: %lu\r\n", packetTime);
      breakTime(packetTime, tm);
      Serial.printf("Currency Conversion packet time: "
                    "%02i/%02i/%02i %02i:%02i:%02i\r\n",
                    tm.Month, tm.Day, tm.Year + 1970,
                    tm.Hour, tm.Minute, tm.Second);
      PHP_Rate = doc["rates"]["PHP"];
      Serial.printf("Current PHP Conversion rate %.2f\r\n", PHP_Rate);
      sprintf(readingTime, "As of %02i:%02i", homeTime.hour(),
              homeTime.minute());
    } else {
      pktValidity = false;
      Serial.println("Bad HTTP return code. Exchange rate packet invalid.");
      PHP_Rate = 0;
    }
  } else {
    Serial.println("WiFi not available now. No api fetch possible");
  }
  return pktValidity;
}
///****************************************************************************/
//bool getInitialXfetchStatus()
///****************************************************************************/
//{
//  bool doInitialXfetch = true;
//
//  tft.unloadFont(); tft.setTextFont(2); tft.setTextSize(1);
//  tft.setCursor(0, 0); tft.setTextColor(TFT_YELLOW);
//  tft.println("Delaying 10 seconds for");
//  tft.println("screen touch to skip");
//  tft.println("initial rate fetch.");
//
//  int prev_secs = -1;
//  unsigned long endMillis = millis() + 10000;
//  Serial.println("You have 10 secs to touch the screen to disable API fetch.");
//  while (endMillis > millis()) {
//    int secs = (endMillis - millis()) / 1000;
//    if (prev_secs != secs) {
//      prev_secs = secs;
//      Serial.printf("%i seconds remaining.\r\n", secs);
//      tft.printf("%i secs left.\r\n", secs);
//    }
//    if (tft.getTouch(&tX, &tY)) {  // User touched screen.
//      doInitialXfetch = false;
//      while (tft.getTouch(&tX, &tY));  // Wait for untouch
//      break;  // Break out of the while loop.  We have what we came for!
//    }
//  }
//
//  Serial.print("Initial exchange rate fetch will be ");
//  if (doInitialXfetch)
//    Serial.println("done.");     // If true
//  else
//    Serial.println("skipped.");  // If false
//
//  return doInitialXfetch;        // Return the user decision
//}
