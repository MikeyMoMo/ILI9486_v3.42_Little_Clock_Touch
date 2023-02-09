# ILI9486_v3.42_Little_Clock_Touch

Clock with multiple times zones, multiple clock faces, calendar, touch capable and much more.  See the jpgs in the folder for a view of the screens.

Included is a routine I wrote to implement single, double, triple, long and 8-way swipe.  It can be used for any touch screen but may, of course, take some modification.

A single touch rotates between the 5 main screens.  A double tap brings up the calendar.  Today is highlighted as well as any user supplied dates, such as anniversary or birthdays.  A swipe brings up the American Social Security payday.  You enter your birth date (numberic day of monty) and it figures out when your payday is.

When on the calendar screen, a left or right swipe will change the month up or down by one month.  There is no provision for changing year of more than one month at a time.

On any clock screen, a long press brings up a buttons screen that is where you can request Legends (user supplied highlighted days textual reminders) for the month, a second way to see the SS payday and a Reboot button.  Sometimes, it gets the wrong time and I have to reboot to get it right.  Easier and better than power cycling.  I use ezTime and it sometimes fails to get the right time(s).  It is so easy to use, otherwise, that I keep it.

This program has mostly been converted to use OpenFontRender and uses TTF binaries and sets font selection and sizes as needed.  I have not figured out how to interface with the tft_espi button render routine to make it connect with the OFR code so there is still some old binary lines to support that.  Will remove when I can.

![Screenshot](DTZ.jpg)
