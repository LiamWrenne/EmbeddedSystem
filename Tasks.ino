// Initalization with included libaries  

  

#include <Keypad.h> 

#include <LiquidCrystal.h> 

const int rs = 12, en = 11, d4 = 9, d5 = 8, d6 = 7, d7 = 6; 

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); 

  

const int SWMain = 2; 

const int SW2 = 3; 

const int SW3 = 4; 

const int SW4 = 5; 

const int buzz = 13; 

  

const byte ROWS = 4; //four rows 

const byte COLS = 4; //four columns 

  

char keys[ROWS][COLS] = { 

  {'1','2','3','A'}, 

  {'4','5','6','B'}, 

  {'7','8','9','C'}, 

  {'*','0','#','D'} 

}; 

  

byte rowPins[ROWS] = {30, 31, 32, 33}; //connect to the row pinouts of the keypad 

byte colPins[COLS] = {34, 35, 36, 37}; //connect to the column pinouts of the keypad 

  

//Create an object of keypad 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); 

  

bool hexkey = false; 

bool keybool = false; 

bool lock = false; 

bool rebool1 = false; 

bool rebool2 = false; 

bool rebool3 = false; 

bool rebool4 = false; 

bool rebool5 = false; 

bool rebool6 = false; 

bool rebool7 = false; 

bool rebool8 = false; 

bool ccount1 = false; 

bool ccount2 = false; 

bool ccount3 = false; 

bool ccount4 = false; 

  

int switchstate1; 

int switchstate2; 

int switchstate3; 

int switchstate4; 

  

int counter; 

int dcount = 0; 

int rcount = 0; 

  

char ccount[] = {'A','1','C','4'}; 

char nocount[] = {'B','D','E','F','0','2','3','5','6','7','8','9'}; 

char hex[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'}; 

char up[] = {'A','1','2','3','4','5','6','7'}; 

char notup[] = {'8','9','0','B','C','D','*','#'}; 

  

// Setup of pins on the arduino and the lcd screen default message 

  

void setup() { 

  

pinMode(SWMain, INPUT); 

pinMode(SW2, INPUT); 

pinMode(SW3, INPUT); 

pinMode(SW4, INPUT); 

pinMode(buzz, OUTPUT); 

  

Serial.begin(9600); 

  

lcd.begin(16, 2); 

lcd.clear(); 

lcd.print("Drive Disabled"); 

} 

  

// The main code in the loop 

  

void loop() { 

  

// Button reads 

   

switchstate2 = digitalRead(SW2); 

switchstate3 = digitalRead(SW3); 

switchstate4 = digitalRead(SW4); 

  

// The sequence lock system correct comparison changing a flag to true for later 

  

if (switchstate2 == 1 and switchstate3 == 0 and switchstate4 == 1){ 

  keybool = true; 

} 

  

// The Alarm system that increments the delay  

  

if (switchstate3 == 1 and counter == 0){ 

  tone(13, 1000, 1000); 

  delay(2000); 

  counter ++; 

} 

  

switchstate3 = digitalRead(SW3); 

if (switchstate3 == 1 and counter == 1){ 

  tone(13, 1000, 1000); 

  delay(5000); 

  counter ++; 

} 

  

switchstate3 = digitalRead(SW3); 

if (switchstate3 == 1 and counter == 2){ 

  tone(13, 1000, 1000); 

  delay(10000); 

  counter ++; 

} 

  

// After 3 alarms it triggers a lock down of the system that needs a diagnostic tool to reset back to default 

  

switchstate3 = digitalRead(SW3); 

if (switchstate3 == 1 and counter == 3){ 

  tone(13, 1000, 1000); 

  lock = true; 

  lcd.clear(); 

  lcd.setCursor(0,0); 

  lcd.print("LOCKED"); 

  delay(100); 

} 

  

// Using the correct sequence flag and checks if the system is under lock down and gives message drive enabled 

  

if (keybool == true and lock == false) 

  switchstate1 = digitalRead(SWMain); 

  if (switchstate1 == 1){ 

    lcd.clear(); 

    lcd.print("Drive Enabled"); 

} 

  

// Incrementer for the two switch hex password to allow the Diagnostic tool to reset the device and its lockdown the Hex Key Password is "A1 C4" 

  

switchstate4 = digitalRead(SW4); 

if (switchstate4 == 1 and counter > 0){ 

  dcount ++; 

  delay(300); 

  Serial.println(hex[dcount]);} 

  

// Hex numbering scheme so that it does not exceed 15 

  

if (dcount > 15){ 

  dcount = 0;} 

  

// "Selects" the Incrementator at its current state so that the comaprison can be done this uses the second button for the hex pass, gives feedback upon selection of the hex 

  

switchstate2 = digitalRead(SW2); 

if (switchstate2 == 1 and counter > 0){ 

  rcount = dcount; 

  delay(300); 

  lcd.setCursor(0,1); 

  lcd.print("Selected : "); 

  lcd.print(hex[rcount]); 

  delay(300); 

  lcd.print("     "); 

  Serial.print("Selected : "); 

  Serial.println(hex[rcount]); 

  

// From the selected hex it checks to see if it is correct within the array 

  

  if (hex[rcount] == nocount[0] or hex[rcount] == nocount[1] or hex[rcount] == nocount[2] or hex[rcount] == nocount[3] or hex[rcount] == nocount[4] or hex[rcount] == nocount[5] or hex[rcount] == nocount[6] or hex[rcount] == nocount[7]){ 

    ccount1 = false; 

    ccount2 = false; 

    ccount3 = false; 

    ccount4 = false; 

    Serial.println("hex-reset"); 

    delay(300);} 

  if (ccount[0] == hex[rcount]){ 

    ccount1 = true;} 

  if (ccount[1] == hex[rcount] and ccount1 == true){ 

    ccount2 = true;} 

  if (ccount[2] == hex[rcount] and ccount2 == true){ 

    ccount3 = true;} 

  if (ccount[3] == hex[rcount] and ccount3 == true){ 

    ccount4 = true;} 

} 

  

// The Final comparison to check if all of the Hex chars are correct 

  

if (ccount1 == true and ccount2 == true and ccount3 == true and ccount4 == true){  

  hexkey = true; 

  Serial.println("hexkey true");} 

  

// Read the key 

  

char key = keypad.getKey(); 

  

// The reset function of the diagnostic tool so that the sytem and its flags are set back to default, effectivly resseting the system 

  

if (key == 'D' and hexkey == true){ 

  keybool = false; 

  lock = false; 

  rebool1 = false; 

  rebool2 = false; 

  rebool3 = false; 

  rebool4 = false; 

  rebool5 = false; 

  rebool6 = false; 

  rebool7 = false; 

  rebool8 = false; 

  hexkey = false; 

  ccount1 = false; 

  ccount2 = false; 

  ccount3 = false; 

  ccount4 = false; 

  lcd.clear(); 

  lcd.setCursor(0,0); 

  lcd.print("Drive Disabled"); 

  delay(300); 

  Serial.println("Full-Reset");} 

  

// Diagnostic tool update function checks to see if the keys pressed are correct and will then give an update ready message 

  

if (key == up[0]){ 

  rebool1 = true; 

  Serial.println("1");} 

if (key == up[1] and rebool1 == true){ 

  rebool2 = true; 

  Serial.println("2");} 

if (key == up[2] and rebool2 == true){ 

  rebool3 = true; 

  Serial.println("3");} 

if (key == up[3] and rebool3 == true){ 

  rebool4 = true; 

  Serial.println("4");} 

if (key == up[4] and rebool4 == true){ 

  rebool5 = true; 

  Serial.println("5");} 

if (key == up[5] and rebool5 == true){ 

  rebool6 = true; 

  Serial.println("6");} 

if (key == up[6] and rebool6 == true){ 

  rebool7 = true; 

  Serial.println("7");} 

if (key == up[7] and rebool7 == true){ 

  rebool8 = true; 

  Serial.println("8");} 

  

if (key == notup[0] or key == notup[1] or key == notup[2] or key == notup[3] or key == notup[4] or key == notup[5] or key == notup[6] or key == notup[7]){ 

  rebool1 = false; 

  rebool2 = false; 

  rebool3 = false; 

  rebool4 = false; 

  rebool5 = false; 

  rebool6 = false; 

  rebool7 = false; 

  rebool8 = false; 

  Serial.println("up-reset"); 

  delay(300);} 

  

if (rebool8 == true){ 

  lcd.clear(); 

  lcd.print("Update Ready"); 

  delay(300);} 

  

} 
