#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
#define BUTTON4 11
#define LED1 12
#define LED2 13
#define LED3 2

ros::NodeHandle node_handle;

std_msgs::String button_msg;
std_msgs::UInt16 led_msg;



ros::Publisher button_publisher("button_press", &button_msg);


void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  node_handle.initNode();
  node_handle.advertise(button_publisher);
  
}

void loop(){ 
  while (digitalRead(BUTTON1) != LOW){
    digitalWrite(LED1, HIGH);
    delay(1000);
    digitalWrite(LED1, LOW);
    delay(1000);
  }
  if (digitalRead(BUTTON2) == LOW) {
    button_msg.data = "Pressed2";
    digitalWrite(LED2, HIGH);
  }
  if (digitalRead(BUTTON3) == LOW) {
    button_msg.data = "Pressed3";
    digitalWrite(LED3, HIGH);
  } 
  if (digitalRead(BUTTON4) == LOW) {
    button_msg.data = "Pressed4";
    digitalWrite(LED1, LOW); 
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  } 

  button_publisher.publish( &button_msg );
  node_handle.spinOnce();
  
  delay(100);
}
