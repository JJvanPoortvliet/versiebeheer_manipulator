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

std_msgs::UInt16 button_msg;
ros::Publisher button_publisher("button_states", &button_msg);

void ledCallback(const std_msgs::String &msg) {
  if (msg == "RUN") {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
  } else if (msg == "STOP") {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
}

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
  button_msg.data = (digitalRead(BUTTON1) << 0) |
                    (digitalRead(BUTTON2) << 1) |
                    (digitalRead(BUTTON3) << 2) |
                    (digitalRead(BUTTON4) << 3);
  button_publisher.publish(&button_msg);
  node_handle.spinOnce();
  delay(100);
}
