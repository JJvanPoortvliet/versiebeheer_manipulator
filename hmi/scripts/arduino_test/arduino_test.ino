
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>


#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
#define BUTTON4 11
#define LED1 4
#define LED2 3
#define LED3 2

ros::NodeHandle node_handle;

std_msgs::UInt16 button_msg;
ros::Publisher button_publisher("button_states", &button_msg);

uint8_t last_button = 0;

void ledCallback(const std_msgs::String &led_msg) {
  String feedback;
  feedback = led_msg.data;
  if (feedback.equals("RUN")) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, HIGH);
  } else if (feedback.equals("STOP")) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }else if (feedback.equals("NIKS")){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);    
  }
}
std_msgs::UInt16 led_msg;
ros::Subscriber<std_msgs::String> led_subscriber("led_control", &ledCallback);

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON3, INPUT);
  pinMode(BUTTON4, INPUT);
  node_handle.initNode();
  node_handle.advertise(button_publisher);
  node_handle.subscribe(led_subscriber);
  
}

void loop() {
  uint8_t current_button = 0;
  

  if (digitalRead(BUTTON1) == LOW) {
    current_button = 1;
  } else if (digitalRead(BUTTON2) == LOW) {
    current_button = 2;
  } else if (digitalRead(BUTTON3) == LOW) {
    current_button = 3;
  } else if (digitalRead(BUTTON4) == LOW) {
    current_button = 4;
  }
  if (current_button != 0 && current_button != last_button) {
    last_button = current_button;
  }
  button_msg.data = last_button;
  button_publisher.publish(&button_msg);
  node_handle.spinOnce();
  delay(100);
}
