int ledPin = 13;  

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  
}

void loop() {
  if (Serial.available() > 0) {
    int blinkCount = Serial.parseInt();  
    Serial.println(blinkCount);          
    
    
    for (int i = 0; i < blinkCount; i++) {
      digitalWrite(ledPin, HIGH);
      delay(500);
      digitalWrite(ledPin, LOW);
      delay(500);
    }
    
    
    int waitTime = random(1, 6);
    Serial.println(waitTime);
  }
}