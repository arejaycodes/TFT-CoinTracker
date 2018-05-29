# TFT-CoinTracker
![screenshot-1](https://raw.githubusercontent.com/arejaycodes/TFT-CoinTracker/master/images/web_1.jpg)

combining an esp8266 with a ILI9341 240x320 TFT display. connects to local wifi network, then proceeds to query both api.coindesk.com and coinmarketcap.com every 60 seconds to retrieve a JSON formatted replies of the data we want. ArduinoJSON then handles the parsing the data while TFT_eSPI displays the information we're interested in.

Made for fun and mainly to pass time, but also wanted to learn more about displaying data on the TFT screens. 

For converting jpg/png images to be displayed on the TFT, [ruison](http://www.riuson.com/lcd-image-converter) has made lcd-image-converter for making the images into a format the TFT can understand
