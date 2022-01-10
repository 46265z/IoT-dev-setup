# from network import WLAN
# import machine
# wlan = WLAN(mode=WLAN.STA)

# nets = wlan.scan()
# for net in nets:
#     if net.ssid == 'IoT-dev-env': # <Your-Wifi-SSID> е името на вашата мрежа
#         print('[INFO]\tNetwork found!')
#         wlan.connect(net.ssid, auth=(net.sec, '12345678'), timeout=5000) # <yourWifiKey> Трябва да бъде паролата за вашата мрежа
#         while not wlan.isconnected():
#             machine.idle() # save power while waiting
#         print('[INFO]\tWLAN connection succeeded!')
#         break
#     else:
#         print('[WARNING]\tThe network you are searching for could not be found.')
#         break