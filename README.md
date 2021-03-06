# IOT-Greenhouse-Monitoring-NodeMCU-TelegramBot

I. INTRODUCTION
This section contains a general information about the two modern technologies-Greenhouse farming and Internet of Things, used and connected to each other in order to in this project Greenhouse is a house like structure made of transparent material like glass, inside of which crops can be grown under partial or complete regulated weather conditions. The size of this structure can vary from a shed to very large industrial buildings.
         A Greenhouse facilitates its proprietor a basic method of employment by allowing to grow a particular crop even in its off season i.e. a crop can be grown throughout the year. Moreover in a controlled atmosphere with less water requiurement and protected surrounding which saves it from locust attack, a high quality crop can be obtained easily. 
        The term Internet of Things covers everything connected to the internet, in simple terms it defines the objects who “talk” to each other. It is made of devices like different sensors, smartphones, smartwatches and wearables connected together. By automating these connected systems it is easier to gather information, analyse it and create a suitable action to complete a particular task or to learn from a certain process.
         IoT offers a chance to be more efficient in how we do variety of tasks, from our daily life activities to industrial activities, by saving time, reducing human efforts, efficient management of resources thus making our activities economically more viable.
         This research paper has been written to show that IoT can reduce human efforts and can contributes significantly in improvising the  quality and monitoring of crops being grown.

II. THE PROPOSED GREENHOUSE SYSTEM

The recent developments in IoT technology field has led to a increased interest in developing greenhouse technology. The major problems reported by farmers are plants suffering due to bad temperature, light and difficulty in keeping tracks of soil moisture level manually. This paper gives detail about an intelligent system which allows peasants to monitor and control major aspects which are required for growing a greenhouse crop i.e. light, temperature, humidity, soil moisture level. The assumed structure has ability to monitor and control all these aspects of greenhouse system from anyplace where internet is accessible.

The overall system can be divided into three parts – hardware, software and IoT structure.

A. Hardware Design:
         To apply the automation process in the system, it is required to feed the intelligent control system with information. The following sensor components are used to collect the required information:
1) Temperature and humidity sensor (DHT11): it is an advanced temperature and moistness sensor with many advantages such as small size, basic interface, cheap in cost and quick reactions.
2) Soil humidity sensor (YL-69): this sensor measures the moisture content of soil by measuring the dielectric tolerance of soil.
3) Light Dependent Resistor (LDR): It is an electronic component whose resistance decreases as light intesity increases. Hence it is a light sensitive gadget.
4) ESP8266 module: It is a 3V, low-cost Wi-Fi microchip module, with a full TCP/IP stack and microcontroller capability. It’s maximum working voltage is 3.6V. ESP8266 comes with libraries to communicate over Wi-Fi using TCP and UDP, set up HTTP, SSDP, and DNS servers, do OTA updates, use a file system in flash memory.
All the data colllected by the sensors are transmitted to user via ESP8266 and further actions can be taken accordingly.

B. Software Design: 
This part is the “brain” of our system. The software is pre-fed with a range of set values of temperature, humidity, light and soil humdity for the crop and is programmed in such a way that whenever the sensors detect the values exceed or goes down the given range, it gives a message to user about the critical condition and also tells whether to control light, or to increase water or to turn on the cooler etc.

C. IoT Structure: As previously explained, the IoT structure is made to bridge the gap between sensor components and the proprietor of greenhouse. For achieve the proposed IoT structure some program applications should be used as follows:

a) User application: The first step is to create a user interface in order to display the information to the user. There are several applications available on Playstore to achieve the purpose. Here we have used two applications “Blynk” and “Telegram” to display the information to the user. 
   Steps to use Telegram and Telegram Bot – 
First download Telegram application from playstore. Bots are like small programs that run right inside Telegram. They are made by third-party developers using the Telegram Bot API. Users can interact with bots by sending them messages, commands and inline requests. 
     To create Telegram Bot open Telegram and search BotFather - Type command /newbot for creating new Bot. Then type the name and username of Bot. After creation, token will be provided for 
contacting BOT, note down the Token.

#To create a Telegram Bot
Steps to use Blynk application –
Install the Blynk app from Play store/ App store and login to your account. Create a new project by selecting NodeMCU as the device and Wi-Fi as the connection type. (Auth token will be sent to your mail id, this will be used later in the code). Click + icon and add 2 widgets superchart and one Button. Name one superchart Temperature and set DataStream’s input to V6. Similarly, Name second superchart Soil Moisture and set DataStream’s input to V7. Select Button and set Mode to Push.


III. RESULT
After completing the required connections, we start our ESP8266 for monitoring. The operation works as follows: The predefined set points or critical points of minimum soil moisture is 30 and maximum temperature is 40°C. We can change these critical values in our code using Arduino IDE. As soon as ESP8266 is powered up, it will connect to a local hotspot whose login credentials are provided in code. Once a connection is occurred, we will get a “connected” message via Telegram Bot. We can read current Temperature, Humidity and soil moisture by sending commands to our Telegram Bot and we can also control pumps and fan and can check their status. Average time of receiving sensor value via Telegram Bot lies around 5-10 seconds. We can see graphical representation of our input data by using Blynk App. It provides real time updates and view all data in a tabular manner. Using these applications, we are able to achieve remote connection and control of actuators in real time and with almost accuracy. As a result, we are able to monitor the status of plants in greenhouse in real time.






IV. CONCLUSION
The design and construction method has been demonstrated in " IOT Based Green House Monitoring System" for the betterment of small-scale farmers to large scale farmers, backyard farming to industrial farming and so on. It has been designed to detect the temperature, humidity and soil moisture of subjected atmosphere (Cultivable land) so that all these things remain favorable for farming. Wi-Fi module ESP8266 is used in this project for internet connectivity. Telegram and Blynk apps have been used for sending notifications and current reading of the sensors. These features make it remotely accessible as you can control the climate from your mobile by being anywhere in the world. For safety and precaution an alarm is present in structure so that if anything changes beyond a threshold point, the alarm goes off alerting the farmers. Due to its simple design and remotely accessible feature it can even be used in backyard or even at remote places where reaching every day is not feasible.
 
With little modifications, as per one’s requirement, this model is highly useful for everyone specially the farmers in adverse climatic conditions and drought prone regions. It will not only help them in drought but will also increase their productivity which will help them immensely and eventually it will help the society.

The only weak points in the system are described below:
        The IoT structure depends completely on internet availability to deliver data to user or to command the different components such as fan, heater, water pumps etc., in any case of internet failure the whole system could crumble and human effort would be required to take care of greenhouse once again.

V. REFRENCES

[1] L. Coetzee and J. Eksteen, "The Internet of
      Things-promise for the future? An introduction," 
      in IST-Africa Conference Proceedings, 2011, 
      pp. 1-9, 2011.

[2] ncpahindia.com
[3] C. Wenshun, Y. Lizhe, C. Shuo, and S. 
        Jiancheng, "Design and implementation of 
        sunlight greenhouse service platform based on 
        IOT and cloud computing," in Measurement, 
        Information and Control (ICMIC), 2013 
        International Conference on, pp. 141-144,
        2013.
[4] https://github.com/Gianbacchio/ESP8266- 
      TelegramBot
[5] https://core.telegram.org/bots
[6] https://blynk.io/
[7] J.-c. Zhao, J.-f. Zhang, Y. Feng, and J.-x. Guo, 
      "The study and application of the IOT     
      technology in agriculture," in Computer Science 
      and Information Technology (ICCSIT), 2010
      3rd IEEE International Conference on, pp. 462-
      465, 2010.
 













































































