/*  

Bitcoin, Ethereum & Ripple Coin Tracker

May 28th 2018
arejay

Relies on: 

 */
 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

#include "dennis.h"

TFT_eSPI tft = TFT_eSPI();

#define TFT_GREY 0x5AEB 
const char *ssid         = "...........";
const char *password     = "...........";
String payload = "";


void connect() {
	tft.setCursor(0, 0, 2);
	tft.setTextColor(TFT_WHITE,TFT_BLACK);
	tft.print("connecting to wifi ");
	WiFi.begin ( ssid, password );
	while ( WiFi.status() != WL_CONNECTED ) {
		// do stuff while connecting
		//  tft.setCursor(70, 70, 2);
		//   tft.setTextColor(TFT_WHITE,TFT_BLACK);
		tft.print(".");
		delay (500);
	}
	tft.print(" connnected!");
	delay(500);

}


void getbtc() {
	if((WiFi.status() == WL_CONNECTED)) {
	HTTPClient http;
	http.begin("http://api.coindesk.com/v1/bpi/currentprice.json"); //HTTP
	int httpCode = http.GET();
	if(httpCode > 0) {	
		if(httpCode == HTTP_CODE_OK) {
			String APIString = http.getString();
			http.end();
			const size_t bufferSize = 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(5) + 650;
			DynamicJsonBuffer jsonBuffer(bufferSize);
			JsonObject& root = jsonBuffer.parseObject(APIString);
			JsonObject& time = root["time"];
			const char* time_updated = time["updated"]; // "May 24, 2018 22:54:00 UTC"
			const char* time_updatedISO = time["updatedISO"]; // "2018-05-24T22:54:00+00:00"
			const char* time_updateduk = time["updateduk"]; // "May 24, 2018 at 23:54 BST"

			const char* disclaimer = root["disclaimer"]; // "This data was produced from the CoinDesk Bitcoin Price Index (USD). Non-USD currency data converted using hourly conversion rate from openexchangerates.org"
			const char* chartName = root["chartName"]; // "Bitcoin"

			JsonObject& bpi = root["bpi"];

			JsonObject& bpi_USD = bpi["USD"];
			const char* bpi_USD_code = bpi_USD["code"]; // "USD"
			const char* bpi_USD_symbol = bpi_USD["symbol"]; // "$"
			const char* bpi_USD_rate = bpi_USD["rate"]; // "7,560.4750"
			const char* bpi_USD_description = bpi_USD["description"];
			float bpi_USD_rate_float = bpi_USD["rate_float"];

			JsonObject& bpi_GBP = bpi["GBP"];
			const char* bpi_GBP_code = bpi_GBP["code"];
			const char* bpi_GBP_symbol = bpi_GBP["symbol"]; 
			const char* bpi_GBP_rate = bpi_GBP["rate"];
			const char* bpi_GBP_description = bpi_GBP["description"];
			float bpi_GBP_rate_float = bpi_GBP["rate_float"]; 
			JsonObject& bpi_EUR = bpi["EUR"];
			const char* bpi_EUR_code = bpi_EUR["code"];
			const char* bpi_EUR_symbol = bpi_EUR["symbol"]; 
			const char* bpi_EUR_rate = bpi_EUR["rate"];
			const char* bpi_EUR_description = bpi_EUR["description"]; 
			float bpi_EUR_rate_float = bpi_EUR["rate_float"]; 

			tft.setCursor(50, 220, 2);
			tft.setTextColor(TFT_GREEN);
			tft.print("Updated: ");
			tft.println(String(time_updated));
                              
			}
        } else {
             tft.println("not connected");
       }
    }  
  
}


void geteth() {
	if((WiFi.status() == WL_CONNECTED)) {
		HTTPClient http;
		http.begin("http://lookuptool.work/testbed/price.php"); //HTTP
		int httpCode = http.GET();
		if(httpCode > 0) {
			if(httpCode == HTTP_CODE_OK) {
			String ETHString = http.getString();
			http.end();
			const size_t bufferSize = 3*JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 3*JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(10) + 1090;
			DynamicJsonBuffer jsonBuffer(bufferSize);

			JsonObject& root = jsonBuffer.parseObject(ETHString);

			JsonObject& data = root["data"];

			JsonObject& data_1 = data["1"];
			int data_1_id = data_1["id"]; // 1
			const char* data_1_name = data_1["name"]; // "Bitcoin"
			const char* data_1_symbol = data_1["symbol"]; // "BTC"
			const char* data_1_website_slug = data_1["website_slug"]; // "bitcoin"
			int data_1_rank = data_1["rank"]; // 1
			long data_1_circulating_supply = data_1["circulating_supply"]; // 17060525
			long data_1_total_supply = data_1["total_supply"]; // 17060525
			long data_1_max_supply = data_1["max_supply"]; // 21000000

			JsonObject& data_1_quotes_USD = data_1["quotes"]["USD"];
			float data_1_quotes_USD_price = data_1_quotes_USD["price"]; // 7241.49
			long data_1_quotes_USD_volume_24h = data_1_quotes_USD["volume_24h"]; // 4915860000
			long data_1_quotes_USD_market_cap = data_1_quotes_USD["market_cap"]; // 123543621182
			float data_1_quotes_USD_percent_change_1h = data_1_quotes_USD["percent_change_1h"]; // -0.12
			float data_1_quotes_USD_percent_change_24h = data_1_quotes_USD["percent_change_24h"]; // -1.53
			float data_1_quotes_USD_percent_change_7d = data_1_quotes_USD["percent_change_7d"]; // -14.08
			
			long data_1_last_updated = data_1["last_updated"]; // 1527529474

			JsonObject& data_52 = data["52"];
			int data_52_id = data_52["id"]; // 52
			const char* data_52_name = data_52["name"]; // "Ripple"
			const char* data_52_symbol = data_52["symbol"]; // "XRP"
			const char* data_52_website_slug = data_52["website_slug"]; // "ripple"
			int data_52_rank = data_52["rank"]; // 3
			long data_52_circulating_supply = data_52["circulating_supply"]; // 39189968239
			long data_52_total_supply = data_52["total_supply"]; // 99992233977
			long data_52_max_supply = data_52["max_supply"]; // 100000000000

			JsonObject& data_52_quotes_USD = data_52["quotes"]["USD"];
			float data_52_quotes_USD_price = data_52_quotes_USD["price"]; // 0.576903
			long data_52_quotes_USD_volume_24h = data_52_quotes_USD["volume_24h"]; // 305998000
			long data_52_quotes_USD_market_cap = data_52_quotes_USD["market_cap"]; // 22608810247
			float data_52_quotes_USD_percent_change_1h = data_52_quotes_USD["percent_change_1h"]; // -0.19
			float data_52_quotes_USD_percent_change_24h = data_52_quotes_USD["percent_change_24h"]; // -5.21
			float data_52_quotes_USD_percent_change_7d = data_52_quotes_USD["percent_change_7d"]; // -15.47

			long data_52_last_updated = data_52["last_updated"]; // 1527529441

			JsonObject& data_1027 = data["1027"];
			int data_1027_id = data_1027["id"]; // 1027
			const char* data_1027_name = data_1027["name"]; // "Ethereum"
			const char* data_1027_symbol = data_1027["symbol"]; // "ETH"
			const char* data_1027_website_slug = data_1027["website_slug"]; // "ethereum"
			int data_1027_rank = data_1027["rank"]; // 2
			long data_1027_circulating_supply = data_1027["circulating_supply"]; // 99722351
			long data_1027_total_supply = data_1027["total_supply"]; // 99722351

			JsonObject& data_1027_quotes_USD = data_1027["quotes"]["USD"];
			float data_1027_quotes_USD_price = data_1027_quotes_USD["price"]; // 529.903
			long data_1027_quotes_USD_volume_24h = data_1027_quotes_USD["volume_24h"]; // 2288260000
			long data_1027_quotes_USD_market_cap = data_1027_quotes_USD["market_cap"]; // 52843172763
			float data_1027_quotes_USD_percent_change_1h = data_1027_quotes_USD["percent_change_1h"]; // -0.48
			float data_1027_quotes_USD_percent_change_24h = data_1027_quotes_USD["percent_change_24h"]; // -7.17
			float data_1027_quotes_USD_percent_change_7d = data_1027_quotes_USD["percent_change_7d"]; // -24.44

			long data_1027_last_updated = data_1027["last_updated"]; // 1527529460

			JsonObject& metadata = root["metadata"];
			long metadata_timestamp = metadata["timestamp"]; // 1527529285
			int metadata_num_cryptocurrencies = metadata["num_cryptocurrencies"]; // 1624

			tft.setTextColor(TFT_WHITE);
			tft.setCursor(15, 40, 4);
			tft.print(data_1_symbol); /// bitcoin
			tft.drawFloat(data_1_quotes_USD_price, 2, 0, 60, 4); 
			tft.setCursor(120, 40, 4);
			tft.print(data_1027_symbol); // ethereum
			tft.drawFloat(data_1027_quotes_USD_price, 2, 110, 60, 4);
			tft.setCursor(220, 40, 4);
			tft.print(data_52_symbol);  // ripple
			tft.drawFloat(data_52_quotes_USD_price, 2, 230, 60, 4);


			// % Change BTC 
               
			tft.setCursor(10, 90, 2);
			tft.print("1h: ");
			
			if(data_1_quotes_USD_percent_change_1h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1_quotes_USD_percent_change_1h, 2, 45, 90, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_1_quotes_USD_percent_change_1h, 2, 45, 90, 2);         
			}
			tft.setTextColor(TFT_WHITE);
			tft.setCursor(10, 105, 2);
			tft.print("24h: ");

			if(data_1_quotes_USD_percent_change_24h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1_quotes_USD_percent_change_24h, 2, 45, 105, 2);
			}
			else {
			tft.setTextColor(TFT_GREEN);
			tft.drawFloat(data_1_quotes_USD_percent_change_24h, 2, 45, 105, 2);
			}

			tft.setTextColor(TFT_WHITE);
			tft.setCursor(10, 120, 2);
			tft.print("7d: ");

			if(data_1_quotes_USD_percent_change_7d < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1_quotes_USD_percent_change_7d, 2, 45, 120, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_1_quotes_USD_percent_change_7d, 2, 45, 120, 2);          
			}

			// % Change ETH
			
			
			tft.setTextColor(TFT_WHITE);
			tft.setCursor(110, 90, 2);
			tft.print("1h: ");

			if(data_1027_quotes_USD_percent_change_1h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1027_quotes_USD_percent_change_1h, 2, 145, 90, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_1027_quotes_USD_percent_change_1h, 2, 145, 90, 2);
			}
                
			tft.setTextColor(TFT_WHITE);
			tft.setCursor(110, 105, 2);
			tft.print("24h: ");
			
			if(data_1027_quotes_USD_percent_change_24h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1027_quotes_USD_percent_change_24h, 2, 145, 105, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_1027_quotes_USD_percent_change_24h, 2, 145, 105, 2);
			}

			tft.setTextColor(TFT_WHITE);
			tft.setCursor(110, 120, 2);
			tft.print("7d: ");

			if(data_1027_quotes_USD_percent_change_7d < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_1027_quotes_USD_percent_change_7d, 2, 145, 120, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_1027_quotes_USD_percent_change_7d, 2, 145, 120, 2);
			}
                

			// % Change XRP (Ripple)

			tft.setTextColor(TFT_WHITE);
			tft.setCursor(210, 90, 2);
			tft.print("1h: ");

			if(data_52_quotes_USD_percent_change_1h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_52_quotes_USD_percent_change_1h, 2, 245, 90, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_52_quotes_USD_percent_change_1h, 2, 245, 90, 2);
			}

                

			tft.setTextColor(TFT_WHITE);
			tft.setCursor(210, 105, 2);
			tft.print("24h: ");

			if(data_52_quotes_USD_percent_change_24h < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_52_quotes_USD_percent_change_24h, 2, 245, 105, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_52_quotes_USD_percent_change_24h, 2, 245, 105, 2);
			}
                
			tft.setTextColor(TFT_WHITE);
			tft.setCursor(210, 120, 2);
			tft.print("7d: ");

			if(data_52_quotes_USD_percent_change_7d < 0) {
				tft.setTextColor(TFT_RED);
				tft.drawFloat(data_52_quotes_USD_percent_change_7d, 2, 245, 120, 2);
			}
			else {
				tft.setTextColor(TFT_GREEN);
				tft.drawFloat(data_52_quotes_USD_percent_change_7d, 2, 245, 120, 2);
			}
            }
		} else {
		tft.println("Not Connected");}
	} 
}

void ui(){
	tft.setCursor(50, 5, 4);
	tft.fillRect(0, 0, 320, 33, TFT_BLUE);
	tft.setTextColor(TFT_WHITE); 
	tft.println("Crypto Currencies");
	drawIcon(dennis, 10, 1, dennisWidth, dennisHeight);
	drawIcon(btclogo, 74, 40, btclogoWidth, btclogoHeight);
	drawIcon(ethlogo, 170, 40, ethlogoWidth, ethlogoHeight);
	drawIcon(xrplogo, 280, 40, xrplogoWidth, xrplogoHeight);
}

void setup(void) {
	Serial.begin(115200);
	tft.init();
	tft.fillScreen(TFT_BLACK);
	tft.setRotation(3); // horizontal display
	connect();  // call connect to wifi
}

void loop() {
	tft.fillScreen(TFT_BLACK);
	tft.setCursor(0, 0, 2);
	tft.setTextColor(TFT_WHITE,TFT_BLACK); 
	tft.setTextFont(2);
	ui();
	getbtc();
	geteth();
	delay(60000); // wait 60 seconds 
}

#define BUFF_SIZE 64

void drawIcon(const unsigned short* icon, int16_t x, int16_t y, int8_t width, int8_t height) {

	uint16_t  pix_buffer[BUFF_SIZE];   // Pixel buffer (16 bits per pixel)

	// Set up a window the right size to stream pixels into
	tft.setWindow(x, y, x + width - 1, y + height - 1);

	// Work out the number whole buffers to send
	uint16_t nb = ((uint16_t)height * width) / BUFF_SIZE;

	// Fill and send "nb" buffers to TFT
	for (int i = 0; i < nb; i++) {
		for (int j = 0; j < BUFF_SIZE; j++) {
			pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
		}
		tft.pushColors(pix_buffer, BUFF_SIZE);
	}

	// Work out number of pixels not yet sent
	uint16_t np = ((uint16_t)height * width) % BUFF_SIZE;

	// Send any partial buffer left over
	if (np) {
		for (int i = 0; i < np; i++) pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
			tft.pushColors(pix_buffer, np);
		}
}