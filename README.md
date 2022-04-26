# MQTT Hello World
## Broker Setup
- Ubuntu 20.04.4
- https://mosquitto.org/download/#ubuntu
- /etc/mosquitto/conf.d/
    ```bash
    listener 1883
    allow_anonymous true
    ```
  further reading
  - https://mosquitto.org/man/mosquitto-conf-5.html
  - https://mosquitto.org/documentation/authentication-methods
- sudo service mosquitto restart

## Node-RED Setup
- Install docker: https://docs.docker.com/get-docker/
- ```bash
  docker run -it -p 1880:1880 -v node_red_data:/data --name mynodered nodered/node-red
  ```
  https://nodered.org/docs/getting-started/docker
- Visit http://localhost:1880

## ESP Setup
- https://platformio.org/install
- Have a look at the bin folder inside this repo. *(made for macOS)*

## Work with MQTT messages
### Implemented Topics
- led_red (blinks for 1 second)
- led_green (blinks for 1 second)
- buzzer (buzzes for 100 milliseconds)

Based on https://github.com/knolleary/pubsubclient/blob/master/examples/mqtt_basic/mqtt_basic.ino

### Node-RED
Use the flow inside node-red-mqtt-hello-world-flow.json (you need to change at least domain.tld to sth else).
![key visual](https://raw.githubusercontent.com/nikcani/iot-mqtt-hello-world/main/node-red-mqtt-hello-world.png)

### MQTTAnalyzer *(only macOS, iOS & iPadOS)*
Install https://apps.apple.com/de/app/mqttanalyzer/id1493015317?l=en and connect to the broker.  
You can observe all messages inside the app or send a message.

Further reading: https://github.com/philipparndt/mqtt-analyzer
