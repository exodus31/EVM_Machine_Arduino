#include <LiquidCrystal.h>
#include <Keypad.h>

char no_parties;
int selectedCandidate = -1;

int c1 = 0;
int c2 = 0;
int c3 = 0;
int c4 = 0;
int c5 = 0;
int c6 = 0;

char key_select;

const String password = "1412";
String input_password = "";
boolean access = false;


int cursr=0;

boolean candidate_flag;
boolean vote_flag;
boolean pwdA=false;
boolean pwdB=false;
boolean pwdC=false;
boolean clear_flag = false;
boolean tieflag=0;
boolean zeroflag=0;

String winner;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {7, 6, A4, A5};
byte colPins[COLS] = {A0, A1, A2, A3};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {

  Serial.begin(9600);

  pinMode(8, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.clear();
  displayWelcomeScreen();
}

void loop() {
   char key = customKeypad.getKey();   
   if(key){
    analogWrite(9, 180);
    delay(100);
    
   }
   else{
    digitalWrite(9, LOW);
   }
  
  if (key && candidate_flag) {
    if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6') {
      selectedCandidate = key - '1';
      key_select = key;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Selected: ");
      lcd.print(key);
    }
    else if(key == '7' || key == '8' || key == '9' || key == '0'){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Invalid input");
      delay(500);
      key='*';
    }
    else if(key == '#'){
      key='#';
    }
    else{
      candidate_flag=false;      
    }
  }
  if (key == '*') {
    displayCandidates();
  }

  if (key == '#' && selectedCandidate >= 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vote confirmed");
    
    if(key_select == '1'){
      c1++;
    }
    if(key_select == '2'){
      c2++;
    }
    if(key_select == '3'){
      c3++;
    }
    if(key_select == '4'){
      c4++;
    }
    if(key_select == '5'){
      c5++;
    }
    if(key_select == '6'){
      c6++;
    }
    
    delay(500);
    selectedCandidate = -1;
    lcd.clear();
    candidate_flag = false;
    displayWelcomeScreen();
  }
  
  if (key == 'A' || pwdA && !pwdB && !pwdC) {
    
     access=false;
    if(!clear_flag){
      lcd.clear();
      clear_flag = true;  
    }
    pwdA=true;    
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    lcd.setCursor(cursr, 1);
    
    if(key && key != 'A' && key != '#'){
      lcd.print(key);
      cursr++;      
      input_password += key;
      Serial.println(input_password);    
    }
    
  
  
  if(key == '#'){
    if(input_password == password){
      lcd.clear();
      lcd.print("Correct Password");
      delay(500);
      access = true;
      pwdA=false;
      clear_flag = false; 
      cursr=0;  
      input_password="";           
    }
    else{
      lcd.clear();
      lcd.print("Wrong Password!");
      delay(1000);
      access = false;
      input_password = "";
      cursr=0;
      clear_flag = false;      
    }
    
  }
    if(access){
     displayVote(); 
    }
  }

  if (key == 'B' || pwdB && !pwdA && !pwdC){
   
    access=false;
    if(!clear_flag){
      lcd.clear();
      clear_flag = true;  
    }
    pwdB=true;    
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    lcd.setCursor(cursr, 1);
    
    if(key && key != 'B' && key != '#'){
      lcd.print(key);
      cursr++;      
      input_password += key;
      Serial.println(input_password);    
    }
    
  
  
  if(key == '#'){
    if(input_password == password){
      lcd.clear();
      lcd.print("Correct Password");
      delay(500);
      access = true;
      pwdB=false;
      clear_flag = false;  
      cursr=0;
      input_password="";    
    }
    else{
      lcd.clear();
      lcd.print("Wrong Password!");
      delay(1000);
      access = false;
      input_password = "";
      cursr=0;
      clear_flag = false;      
    }
    
  }
    if(access){
      displayResult(); 
    }    
  }

  if (key == 'C' || pwdC && !pwdB && !pwdA){
    
    access=false;
    if(!clear_flag){
      lcd.clear();
      clear_flag = true;  
    }
    pwdC=true;    
    lcd.setCursor(0, 0);
    lcd.print("Enter Password:");
    lcd.setCursor(cursr, 1);
    
    if(key && key != 'C' && key != '#'){
      lcd.print(key);
      cursr++;      
      input_password += key;
      Serial.println(input_password);    
    }
    
  
  
  if(key == '#'){
    if(input_password == password){
      lcd.clear();
      lcd.print("Votes Cleared!");
      delay(500);
      access = true;
      pwdB=false;
      clear_flag = false;  
      cursr=0;
      input_password="";    
    }
    else{
      lcd.clear();
      lcd.print("Wrong Password!");
      delay(1000);
      access = false;
      input_password = "";
      cursr=0;
      clear_flag = false;      
    }
    
  }
    if(access){
      resetVotes(); 
    }    
  }
  
  if(key == 'D'){
    displayWelcomeScreen();
  }

}

void displayWelcomeScreen() {
  lcd.setCursor(0, 0);
  lcd.print("Welcome to EVM");
  lcd.setCursor(0, 1);
  lcd.print("Press * to vote");
  access = false;
  pwdA=false;
  pwdB=false;
  pwdC=false;
  clear_flag = false;  
  cursr=0;
  input_password="";    
}

void displayCandidates() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Candidates:");
  lcd.setCursor(0, 1);
  lcd.print("1 2 3 4 5 6");
  candidate_flag = true;
}

void displayResult(){
  calcWinner();
  lcd.clear();
  lcd.setCursor(0, 0);
  if(tieflag){
    lcd.print("Tie between:");
    lcd.setCursor(0, 1);  
    lcd.print(winner);
  }
  else if(zeroflag){        
    lcd.print(winner);
    zeroflag=0;
  }
  else{
   lcd.print("The Winner is");
    lcd.setCursor(0, 1);
    lcd.print("Candidate ");
    lcd.print(winner); 
  }
  
  Serial.println(winner);
}

void calcWinner(){
  int arr[6]={c1,c2,c3,c4,c5,c6};
  int brr[6]={0};
  String temp = "";  
  for(int i=0;i<6;i++){
    for(int j=i+1;j<6;j++){
      if(arr[i] != 0 && arr[i] == arr[j] && brr[j]==0){
        tieflag=1;      
        if(temp == ""){
          String x = "c";
          x+=i+1;
          temp+=x;
          temp+=" ";
          brr[i]=1;        
        }
        String y = "c";
        y+=j+1;
        temp+=y;
        temp+=" ";
        brr[j]=1;   
      }
    }
  }
  

  if(c1>c2 && c1>c3 && c1>c4 && c1>c5 && c1>c6){
    winner = "1";
    tieflag=0;
  }
  if(c2>c1 && c2>c3 && c2>c4 && c2>c5 && c2>c6){
    winner = "2";
    tieflag=0;
  }
  if(c3>c1 && c3>c2 && c3>c4 && c3>c5 && c3>c6){
    winner = "3";
    tieflag=0;
  }
  if(c4>c1 && c4>c2 && c4>c3 && c4>c5 && c4 >c6){
    winner = "4";
    tieflag=0;
  }
  if(c5>c1 && c5>c2 && c5>c3 && c5>c4 && c5>c6){
    winner = "5";
    tieflag=0;
  }
  if(c6>c1 && c6>c2 && c6>c3 && c6>c4 && c6>c5){
    winner = "6";
    tieflag=0;
  }
  if(c1 == 0 && c2 == 0 && c3 == 0 && c4 == 0 && c5 == 0 && c6 == 0){
    winner = "Zero votes";
    tieflag=0;
    zeroflag=1;
  }
  if(tieflag){
    winner = temp;
  }
}

void displayVote(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("C1:");
  lcd.print(c1);
  lcd.print(" C2:");
  lcd.print(c2);
  lcd.print(" C3:");
  lcd.print(c3);
  lcd.setCursor(0, 1);
  lcd.print("C4:");
  lcd.print(c4);
  lcd.print(" C5:");
  lcd.print(c5);
  lcd.print(" C6:");
  lcd.print(c6);
  
}

void resetVotes(){
  c1=0;
  c2=0;
  c3=0;
  c4=0;
  c5=0;
  c6=0;    
  displayWelcomeScreen();
}
