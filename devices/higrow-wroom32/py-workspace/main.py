def print_dht_values():
    import dht
    import machine
    d = dht.DHT11(machine.Pin(22))
    d.measure()
    temp_measurement = d.temperature()
    humidity_measurement = d.humidity()
    print("\nShowing measurements from DHT11")
    print("="*20)
    print("Temperature is %d C" % (temp_measurement))
    print("-"*20)
    print("Humidity is %d" % (humidity_measurement)+"% (% RH)")
    print("-"*20)


def print_soil_values():
    import machine
    import time
    adc = machine.ADC(machine.Pin(32))  # Pin to Read sensor voltage
    sensor_value = adc.read()
    print("\nShowing measurements from soil sensor")
    print("="*20)
    print("Sensor value is %d" % (sensor_value))
    print("-"*20)


def print_all_sensor_values():
    import machine
    import dht
    import time
    d = dht.DHT11(machine.Pin(22))
    d.measure()
    temp_measurement = d.temperature()
    humidity_measurement = d.humidity()
    adc = machine.ADC(machine.Pin(32))  # Pin to Read sensor voltage
    sensor_value = adc.read()
    print("\nShowing measurements from DHT11")
    print("="*20)
    print("Temperature is %d C" % (temp_measurement))
    print("-"*20)
    print("Humidity is %d" % (humidity_measurement)+"% (% RH)")
    print("-"*20)
    print("\nShowing measurements from soil sensor")
    print("="*20)
    print("Sensor value is %d" % (sensor_value))
    print("-"*20)

# # uncomment following 3 lines if you want to print everything every 10 seconds
# from machine import Timer
# tim0 = Timer(0)
# tim0.init(period=10000, mode=Timer.PERIODIC, callback=lambda t:print_all_sensor_values())

def send_all_sensor_data():
    import machine
    import dht
    import time
    import esp32
    d = dht.DHT11(machine.Pin(22))
    d.measure()
    temp_measurement = d.temperature()
    humidity_measurement = d.humidity()
    adc = machine.ADC(machine.Pin(32))  # Pin to Read sensor voltage
    sensor_value = adc.read()
    internal_temp = esp32.raw_temperature()
    internal_hall = esp32.hall_sensor()
    internal_temp_c = (internal_temp - 32) * 5/9
    all_sensor_data = b'{"temperature":%d,"humidity":%d,"vlajnost_pochva":%d,"internal_temperature_Farenheit":%d,"internal_temp_C":%d,"internal_hall_sensor":%d}' % (temp_measurement,humidity_measurement,sensor_value,internal_temp,internal_temp_c,internal_hall)
    return all_sensor_data

def sub_cb(topic, msg):
    print((topic, msg))
    if topic == b'notification' and msg == b'received':
        print('ESP received hello message')


def connect_and_subscribe():
    global client_id, mqtt_server, mqtt_port, mqtt_user, mqtt_token, topic_sub, topic_pub
    client = MQTTClient(client_id, mqtt_server, mqtt_port)
    client.set_callback(sub_cb)
    client.user = mqtt_token
    client.pswd = ''
    client.connect()
    client.subscribe(topic_sub)
    print('Connected to %s MQTT broker, subscribed to %s topic' % (mqtt_server, topic_sub))
    # if machine.reset_cause() == machine.DEEPSLEEP_RESET:
    #     print('woke from a deep sleep')
    # else:
    #     print('power on or hard reset')
    return client


def restart_and_reconnect():
    print('Failed to connect to MQTT broker. Reconnecting...')
    time.sleep(10)
    machine.reset()


try:
    client = connect_and_subscribe()
except OSError as e:
    restart_and_reconnect()

while True:
    from machine import Pin, Signal
    p0 = Signal(16, Pin.OUT, invert=True)
    try:
        p0.off()
        client.check_msg()
        if (time.time() - last_message) > message_interval:
            # msg = b'Hello #%d' % counter
            p0.on()
            msg = send_all_sensor_data()
            print(msg)
            client.publish(topic_pub, msg)
            last_message = time.time()
            counter += 1
    except OSError as e:
        restart_and_reconnect()