#define lmf 4
#define lmb 5
#define rmf 6
#define rmb 7
#define front_button 'F'
#define back_button 'B'
#define left_button 'L'
#define right_button 'R'
#define stop_button 'S'
#define ledpin 8
#define Buzzpin 9
#define Gassensor A0

const int trigPin = 2;
const int echoPin = 3;
const int threshold = 500;
long duration, distance_cm;
#define minimum_distance 10

char input;
void setup() {

  pinMode(Gassensor, INPUT);
  pinMode(ledpin, OUTPUT);
  pinMode(Buzzpin, OUTPUT);
  pinMode(lmf, OUTPUT);
  pinMode(lmb, OUTPUT);
  pinMode(rmf, OUTPUT);
  pinMode(rmb, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {

   
  GasSensor();
  //Buletooth to Car control
  bluetoothCar();


}
long Sonar_Check()
{
  // Generating pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //Checking Echo
  duration = pulseIn(echoPin, HIGH);

  distance_cm = duration * 0.0344 / 2;

  //Serial.print("Distance: ");
  Serial.print(distance_cm); // Print the output in serial monitor
  Serial.println(" cm");
  //delay(100);
  return distance_cm;
}

void Forword()
{
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
}



void Backword()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}


void Right()
{
  digitalWrite(lmf, HIGH);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, HIGH);
}


void Left()
{
  digitalWrite(lmf, LOW);
  digitalWrite(lmb, HIGH);
  digitalWrite(rmf, HIGH);
  digitalWrite(rmb, LOW);
  
}


void Stop()
{

  digitalWrite(lmf, LOW);
  digitalWrite(lmb, LOW);
  digitalWrite(rmf, LOW);
  digitalWrite(rmb, LOW);
  
}

void GasSensor()
{
  if(analogRead(Gassensor)>threshold)
  {
    digitalWrite(Buzzpin,HIGH);
    digitalWrite(ledpin,HIGH);
  }
  else
  {
    digitalWrite(Buzzpin,LOW);
    digitalWrite(ledpin,LOW);

  }


}


void bluetoothCar()
{
  if (Serial.available() > 0)
  {
    input = char(Serial.read());
    // Serial.println(input);
    delay(10);

    if (input == front_button)
    {
      long distance_check = Sonar_Check();
      if (distance_check > minimum_distance)
      {
      // Going forward
        Forword();
      }
      else
      {
        Stop();
        digitalWrite(ledpin,HIGH);
        delay(10);
        digitalWrite(ledpin,LOW);
        delay(10);

      }      
    }
    else if (input == back_button) //Going backward 
    {
      Backword();
    }
    else if (input == right_button) // Going right
    {
      Right();
    }
    else if (input == left_button) // Going left
    {
      Left();
    }
    else // Stop Code
    {
      Stop();
    }    
  }  
}




