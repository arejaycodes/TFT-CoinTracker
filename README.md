# TFT-CoinTracker
combining an esp8266 with a ILI9341 240x320 TFT display. connects to local wifi network, then proceeds to query both api.coindesk.com and coinmarketcap.com every 60 seconds to retrieve a JSON formatted replies of the data we want. ArduinoJSON then handles the parsing the data while TFT_eSPI displays the information we're interested in. 
