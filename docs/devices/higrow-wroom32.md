|                       |                   |                       |
| --------------------- | ----------------- | --------------------- |
| [micropython code](#) | [arduino code](#) | mqtt platform: flespi |

![](https://m.media-amazon.com/images/I/51yMpury-cL._AC_SL1000_.jpg)

<!-- Izpolzva micropython -->

``` c++
#define DHTTYPE DHT11

const int LEDPIN = 16;
const int DHTPIN = 22;
const int SOILPIN = 32;
```

## micropython

`$ python -m pip install --upgrade pip`

`$ python -m pip install --upgrade --user esptool`

svalqme nai-novata versiq na micropython ot [tuk](https://micropython.org/download/esp32/)

otvarqme terminal v papkata pri svaleniq _.bin_ fail i pishem

`$ esptool.py --port /dev/tty<port> erase_flash`

`$ esptool.py --chip esp32 --port /dev/tty<port> write_flash -z 0x1000 esp32-idf3-<downloaded file name>.bin`

`$ sudo pacman -S picocom`

`$ picocom /dev/tty<port> -b 115200`

otvarq REPL.

```python
>>> import machine
>>> import dht
>>> d = dht.DHT11(machine.Pin(22))
>>> d.measure()
>>> d.humidity()
45
>>> d.temperature()
23
```

## Arduino IDE
```c++
#include "DHTesp.h"
#include "Ticker.h"

#ifndef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP32 ONLY!)
#error Select ESP32 board.
#endif

/**************************************************************/
/* Example how to read DHT sensors from an ESP32 using multi- */
/* tasking.                                                   */
/* This example depends on the ESP32Ticker library to wake up */
/* the task every 20 seconds                                  */
/* Please install Ticker-esp32 library first                  */
/* bertmelis/Ticker-esp32                                     */
/* https://github.com/bertmelis/Ticker-esp32                  */
/**************************************************************/

DHTesp dht;

void tempTask(void *pvParameters);
bool getTemperature();
void triggerGetTemp();

/** Task handle for the light value read task */
TaskHandle_t tempTaskHandle = NULL;
/** Ticker for temperature reading */
Ticker tempTicker;
/** Comfort profile */
ComfortState cf;
/** Flag if task should run */
bool tasksEnabled = false;
/** Pin number for DHT11 data pin */
int dhtPin = 22;

/**
 * initTemp
 * Setup DHT library
 * Setup task and timer for repeated measurement
 * @return bool
 *    true if task and timer are started
 *    false if task or timer couldn't be started
 */
bool initTemp() {
  byte resultValue = 0;
  // Initialize temperature sensor
	dht.setup(dhtPin, DHTesp::DHT11);
	Serial.println("DHT initiated");

  // Start task to get temperature
	xTaskCreatePinnedToCore(
			tempTask,                       /* Function to implement the task */
			"tempTask ",                    /* Name of the task */
			4000,                           /* Stack size in words */
			NULL,                           /* Task input parameter */
			5,                              /* Priority of the task */
			&tempTaskHandle,                /* Task handle. */
			1);                             /* Core where the task should run */

  if (tempTaskHandle == NULL) {
    Serial.println("Failed to start task for temperature update");
    return false;
  } else {
    // Start update of environment data every 20 seconds
    tempTicker.attach(2, triggerGetTemp);
  }
  return true;
}

/**
 * triggerGetTemp
 * Sets flag dhtUpdated to true for handling in loop()
 * called by Ticker getTempTimer
 */
void triggerGetTemp() {
  if (tempTaskHandle != NULL) {
	   xTaskResumeFromISR(tempTaskHandle);
  }
}

/**
 * Task to reads temperature from DHT11 sensor
 * @param pvParameters
 *    pointer to task parameters
 */
void tempTask(void *pvParameters) {
	Serial.println("tempTask loop started");
	while (1) // tempTask loop
  {
    if (tasksEnabled) {
      // Get temperature values
			getTemperature();
		}
    // Got sleep again
		vTaskSuspend(NULL);
	}
}

/**
 * getTemperature
 * Reads temperature from DHT11 sensor
 * @return bool
 *    true if temperature could be aquired
 *    false if aquisition failed
*/
bool getTemperature() {
	// Reading temperature for humidity takes about 250 milliseconds!
	// Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  TempAndHumidity newValues = dht.getTempAndHumidity();
	// Check if any reads failed and exit early (to try again).
	if (dht.getStatus() != 0) {
		Serial.println("DHT11 error status: " + String(dht.getStatusString()));
		return false;
	}

	float heatIndex = dht.computeHeatIndex(newValues.temperature, newValues.humidity);
  float dewPoint = dht.computeDewPoint(newValues.temperature, newValues.humidity);
  float cr = dht.getComfortRatio(cf, newValues.temperature, newValues.humidity);

  String comfortStatus;
  switch(cf) {
    case Comfort_OK:
      comfortStatus = "Comfort_OK";
      break;
    case Comfort_TooHot:
      comfortStatus = "Comfort_TooHot";
      break;
    case Comfort_TooCold:
      comfortStatus = "Comfort_TooCold";
      break;
    case Comfort_TooDry:
      comfortStatus = "Comfort_TooDry";
      break;
    case Comfort_TooHumid:
      comfortStatus = "Comfort_TooHumid";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "Comfort_HotAndHumid";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "Comfort_HotAndDry";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = "Comfort_ColdAndHumid";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = "Comfort_ColdAndDry";
      break;
    default:
      comfortStatus = "Unknown:";
      break;
  };

  Serial.println(" T:" + String(newValues.temperature) + " H:" + String(newValues.humidity) + " I:" + String(heatIndex) + " D:" + String(dewPoint) + " " + comfortStatus);
	return true;
}

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("DHT ESP32 example with tasks");
  initTemp();
  // Signal end of setup() to tasks
  tasksEnabled = true;
}

void loop() {
  if (!tasksEnabled) {
    // Wait 2 seconds to let system settle down
    delay(2000);
    // Enable task that will read values from the DHT sensor
    tasksEnabled = true;
    if (tempTaskHandle != NULL) {
			vTaskResume(tempTaskHandle);
		}
  }
  yield();
}
```

download and install [Arduino IDE](https://www.arduino.cc/en/software) 

v programata otvarqme File -> Preferences _(Ctrl+Comma)_ 

v poleto _Additional Boards Manager URLs_ dobavqme tozi link -> https://dl.espressif.com/dl/package_esp32_index.json

**<p style="text-align: center;"> ![preferences-boards.png](../assets/images/higrow-wroom32/preferences-boards.png) </p>** **<p style="text-align: center;"> Image 3.1. (<a href="../assets/images/higrow-wroom32/preferences-boards.png">see full-size image</a>) </p>**

**<p style="text-align: center;"> ![addOkOk.png](../assets/images/higrow-wroom32/add-ok-ok.png) </p>** **<p style="text-align: center;"> Image 3.1. (<a href="../assets/images/higrow-wroom32/add-ok-ok.png">see full-size image</a>) </p>**



sled tova ot menu-to otvarqme Boards Manager - _Tools -> Board -> Boards Manager_ 

**<p style="text-align: center;"> ![boards-manager.png](../assets/images/higrow-wroom32/boards-manager.png) </p>** **<p style="text-align: center;"> Image 3.1. (<a href="../assets/images/higrow-wroom32/boards-manager.png">see full-size image</a>) </p>**

trqbva da instalirame support za esp32 (by espressif systems)

**<p style="text-align: center;"> ![search-install-esp32.png](../assets/images/higrow-wroom32/search-install-esp32.png) </p>** **<p style="text-align: center;"> Image 3.1. (<a href="../assets/images/higrow-wroom32/search-install-esp32.png">see full-size image</a>) </p>**

syshto taka trqva da instalirame biblioteka za rabota sus senzora za vlajnost (DHT)

v menu _Tools -> Manage Libraries_ tursim DHT sensor library **by Adafruit** 

**<p style="text-align: center;"> ![install-dht-lib.png](../assets/images/higrow-wroom32/install-dht-lib.png) </p>** **<p style="text-align: center;"> Image 3.1. (<a href="../assets/images/higrow-wroom32/install-dht-lib.png">see full-size image</a>) </p>**

### <!--Za arch linux-->
