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
