EESchema Schematic File Version 2
LIBS:Modules
LIBS:modules
LIBS:Solar_Charger3-rescue
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Solar_Charger3-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 10
Title "Solar Charger V3"
Date "2017-01-10"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Sheet
S 2050 850  2550 3300
U 58731385
F0 "Charger3a" 60
F1 "Solar_charger3a.sch" 60
F2 "A0" I R 4600 3900 60 
F3 "+5V" I R 4600 1400 60 
F4 "D3" I R 4600 1700 60 
F5 "+12V" I R 4600 1100 60 
F6 "D9" I R 4600 2300 60 
F7 "D10" I R 4600 2400 60 
F8 "A3" I R 4600 3600 60 
F9 "D4" I R 4600 1800 60 
F10 "A2" I R 4600 3700 60 
F11 "A7" I R 4600 3100 60 
F12 "A6" I R 4600 3200 60 
F13 "+3.3V" I R 4600 1500 39 
F14 "BUTTON-OUT" I R 4600 4000 39 
F15 "A1" I R 4600 3800 59 
F16 "D6" I R 4600 2000 60 
F17 "D6R" I R 4600 4100 60 
$EndSheet
$Sheet
S 8200 750  1400 1250
U 58731388
F0 "Buttons" 60
F1 "Solar_chargerButtons.sch" 60
F2 "+5V" I L 8200 1500 60 
F3 "GND" I L 8200 1700 60 
F4 "RST" I L 8200 1300 39 
F5 "BUTTON-OUT" I L 8200 1900 39 
$EndSheet
$Sheet
S 8200 2300 1750 1200
U 5873138B
F0 "LED" 60
F1 "Solar_chargerLED.sch" 60
F2 "D2" I L 8200 2500 60 
F3 "D8" I L 8200 2700 60 
F4 "D7" I L 8200 2600 60 
F5 "GND" I L 8200 3100 60 
$EndSheet
$Sheet
S 5200 1000 1600 1700
U 58734B26
F0 "Nano" 60
F1 "Solar_charger3Nano.sch" 60
F2 "TX1" I L 5200 1100 39 
F3 "RX0" I L 5200 1200 39 
F4 "RST" I L 5200 1300 39 
F5 "GND" I L 5200 1400 39 
F6 "D2" I L 5200 1500 39 
F7 "D3" I L 5200 1700 39 
F8 "D4" I L 5200 1800 39 
F9 "D5" I L 5200 1900 39 
F10 "D6" I L 5200 2000 39 
F11 "D7" I L 5200 2100 39 
F12 "D8" I L 5200 2200 39 
F13 "D9" I L 5200 2300 39 
F14 "D10" I L 5200 2400 39 
F15 "D11" I L 5200 2500 39 
F16 "D12" I L 5200 2600 39 
F17 "D13" I R 6800 2600 39 
F18 "3V3" I R 6800 2500 39 
F19 "AREF" I R 6800 2400 39 
F20 "A0" I R 6800 2300 39 
F21 "A1" I R 6800 2200 39 
F22 "A2" I R 6800 2100 39 
F23 "A3" I R 6800 2000 39 
F24 "A4" I R 6800 1900 39 
F25 "A5" I R 6800 1800 39 
F26 "A6" I R 6800 1700 39 
F27 "A7" I R 6800 1600 39 
F28 "+5V" I R 6800 1500 39 
F29 "VIN" I R 6800 1200 39 
$EndSheet
Wire Wire Line
	4600 1400 4900 1400
Wire Wire Line
	4900 1400 4900 700 
Wire Wire Line
	4900 700  7600 700 
Wire Wire Line
	6800 1500 8200 1500
Wire Wire Line
	7600 700  7600 1500
Wire Wire Line
	8200 1300 7500 1300
Wire Wire Line
	7500 1300 7500 800 
Wire Wire Line
	7500 800  5000 800 
Wire Wire Line
	5000 1300 5200 1300
Connection ~ 7600 1500
Wire Wire Line
	4600 4000 4900 4000
Wire Wire Line
	4900 4000 4900 4400
Wire Wire Line
	4900 4400 7500 4400
Wire Wire Line
	7500 4400 7500 1900
Wire Wire Line
	7500 1900 8200 1900
Wire Wire Line
	4600 1700 5200 1700
Wire Wire Line
	4600 1800 5200 1800
Wire Wire Line
	4600 2400 5200 2400
Entry Wire Line
	4900 3600 5000 3700
Entry Wire Line
	4900 3600 5000 3700
Wire Wire Line
	4600 3600 4900 3600
Entry Wire Line
	4900 3700 5000 3800
Entry Wire Line
	4900 3700 5000 3800
Wire Wire Line
	4600 3700 4900 3700
Entry Wire Line
	4900 3800 5000 3900
Entry Wire Line
	4900 3800 5000 3900
Wire Wire Line
	4600 3800 4900 3800
Entry Wire Line
	4900 3900 5000 4000
Entry Wire Line
	4900 3900 5000 4000
Wire Wire Line
	4600 3900 4900 3900
Entry Wire Line
	7100 2000 7200 2100
Entry Wire Line
	7100 2000 7200 2100
Wire Wire Line
	6800 2000 7100 2000
Entry Wire Line
	7100 2100 7200 2200
Entry Wire Line
	7100 2100 7200 2200
Wire Wire Line
	6800 2100 7100 2100
Entry Wire Line
	7100 2200 7200 2300
Entry Wire Line
	7100 2200 7200 2300
Wire Wire Line
	6800 2200 7100 2200
Entry Wire Line
	7100 2300 7200 2400
Entry Wire Line
	7100 2300 7200 2400
Wire Wire Line
	6800 2300 7100 2300
Wire Bus Line
	7200 1700 7200 4000
Wire Bus Line
	7200 4000 5000 4000
Wire Bus Line
	5000 4000 5000 3200
Entry Wire Line
	4900 3100 5000 3200
Entry Wire Line
	4900 3100 5000 3200
Wire Wire Line
	4600 3100 4900 3100
Entry Wire Line
	4900 3200 5000 3300
Entry Wire Line
	4900 3200 5000 3300
Wire Wire Line
	4600 3200 4900 3200
Entry Wire Line
	7100 1600 7200 1700
Entry Wire Line
	7100 1600 7200 1700
Wire Wire Line
	6800 1600 7100 1600
Entry Wire Line
	7100 1700 7200 1800
Entry Wire Line
	7100 1700 7200 1800
Wire Wire Line
	6800 1700 7100 1700
Wire Wire Line
	8200 2500 8100 2500
Entry Wire Line
	8000 2600 8100 2500
Wire Wire Line
	5200 1500 5100 1500
Entry Wire Line
	5000 1600 5100 1500
Wire Wire Line
	5000 800  5000 1300
Wire Wire Line
	5200 2100 5100 2100
Entry Wire Line
	5000 2200 5100 2100
Wire Wire Line
	5200 2200 5100 2200
Entry Wire Line
	5000 2300 5100 2200
Wire Wire Line
	8200 2600 8100 2600
Entry Wire Line
	8000 2700 8100 2600
Wire Wire Line
	8200 2700 8100 2700
Entry Wire Line
	8000 2800 8100 2700
Wire Bus Line
	8000 2600 8000 2950
Wire Bus Line
	8000 2950 5000 2950
Wire Bus Line
	5000 2950 5000 1600
Wire Wire Line
	4600 2300 4700 2300
Wire Wire Line
	4700 2300 4700 2350
Wire Wire Line
	4700 2350 5150 2350
Wire Wire Line
	5150 2350 5150 2300
Wire Wire Line
	5150 2300 5200 2300
$Sheet
S 2100 4650 2500 850 
U 587FF208
F0 "LCD" 39
F1 "Solar_chargerLCD.sch" 39
F2 "GND" I R 4600 4900 39 
F3 "+5V" I R 4600 5000 39 
F4 "A5" I R 4600 5100 39 
F5 "A4" I R 4600 5200 39 
$EndSheet
$Sheet
S 2150 5800 2450 650 
U 587FF2A1
F0 "RTC" 39
F1 "Solar_chargerRTC.sch" 39
F2 "GND" I R 4600 5900 60 
F3 "+5V" I R 4600 6000 60 
F4 "A5" I R 4600 6100 60 
F5 "A4" I R 4600 6200 60 
$EndSheet
$Sheet
S 2150 6750 2450 750 
U 587FF33A
F0 "SDcard" 39
F1 "Solar_chargerSDcard.sch" 39
F2 "GND" I R 4600 6900 60 
F3 "+5V" I R 4600 7000 60 
F4 "D11" I R 4600 7100 60 
F5 "D12" I R 4600 7200 60 
F6 "D13" I R 4600 7300 60 
F7 "D8" I R 4600 7400 60 
$EndSheet
$Sheet
S 8300 4300 1650 700 
U 587FF3D3
F0 "WiFi" 39
F1 "Solar_chargerWiFi.sch" 39
F2 "GND" I L 8300 4400 60 
F3 "3.3V" I L 8300 4500 60 
F4 "D6R" I L 8300 4800 60 
F5 "D5" I L 8300 4700 60 
$EndSheet
Text Label 4000 7150 0    60   ~ 0
MOSI
Text Label 4000 7250 0    60   ~ 0
MISO
Text Label 4000 7350 0    60   ~ 0
SCK
Text Label 4000 7450 0    60   ~ 0
CS
Text Label 4100 5250 0    60   ~ 0
SDA
Text Label 4100 5150 0    60   ~ 0
SCL
Wire Wire Line
	4600 2000 5200 2000
Wire Wire Line
	5200 1900 4900 1900
Wire Wire Line
	4900 1900 4900 3000
Wire Wire Line
	4900 3000 8000 3000
Wire Wire Line
	8000 3000 8000 4700
Wire Wire Line
	8000 4700 8300 4700
Wire Wire Line
	4600 4100 4800 4100
Wire Wire Line
	4800 4100 4800 4800
Wire Wire Line
	4800 4800 8300 4800
Entry Wire Line
	5100 2600 5200 2500
Entry Wire Line
	5100 2700 5200 2600
Wire Wire Line
	6800 2600 6900 2600
Wire Wire Line
	6900 2600 6900 2800
Wire Wire Line
	6900 2800 5200 2800
Entry Wire Line
	5100 2900 5200 2800
Entry Wire Line
	5100 2300 5200 2200
Wire Bus Line
	5100 2300 5100 7300
Entry Wire Line
	5000 7400 5100 7300
Wire Wire Line
	4600 7400 5000 7400
Entry Wire Line
	5000 7300 5100 7200
Wire Wire Line
	4600 7300 5000 7300
Entry Wire Line
	5000 7200 5100 7100
Wire Wire Line
	4600 7200 5000 7200
Entry Wire Line
	5000 7100 5100 7000
Wire Wire Line
	4600 7100 5000 7100
Entry Wire Line
	7250 1850 7350 1950
Wire Wire Line
	6800 1800 6950 1800
Wire Wire Line
	6950 1800 6950 1850
Wire Wire Line
	6950 1850 7250 1850
Entry Wire Line
	7250 1900 7350 2000
Wire Wire Line
	6800 1900 7250 1900
Wire Wire Line
	4600 5200 4700 5200
Wire Wire Line
	4700 5200 4700 6200
Wire Wire Line
	4600 6200 4800 6200
Wire Wire Line
	4600 5100 4800 5100
Wire Wire Line
	4800 5100 4800 6100
Wire Wire Line
	4800 6100 4600 6100
Connection ~ 4700 6200
Entry Wire Line
	4800 6100 4900 6200
Entry Wire Line
	4800 6200 4900 6300
Wire Bus Line
	4900 6200 4900 6300
Wire Bus Line
	4900 6300 7350 6300
Wire Bus Line
	7350 6300 7350 1950
Text Label 4100 6150 0    60   ~ 0
SCL
Text Label 4100 6250 0    60   ~ 0
SDA
Text Label 2850 1950 0    99   ~ 0
CHARGER
Text Label 2900 2300 0    99   ~ 0
LOWER
Text Label 2950 2650 0    99   ~ 0
CIRCUIT
Text Label 2950 3050 0    99   ~ 0
BOARD
Text Label 2400 5150 0    99   ~ 0
LCD
Text Label 2850 5150 0    99   ~ 0
DISPLAY
Text Label 2400 6200 0    99   ~ 0
REAL
Text Label 2850 6200 0    99   ~ 0
TIME
Text Label 3350 6200 0    99   ~ 0
CLOCK
Text Label 2400 7150 0    99   ~ 0
SD
Text Label 2750 7150 0    99   ~ 0
CARD
Text Label 9500 4700 0    99   ~ 0
WiFi
Text Label 8800 4700 0    99   ~ 0
ESP8266
Text Label 8800 2900 0    99   ~ 0
LED
Text Label 8800 1400 0    99   ~ 0
BUTTONS
Text Label 5750 1600 0    99   ~ 0
ARDUINO
Text Label 5750 1950 0    99   ~ 0
NANO
$Sheet
S 8300 5500 1800 600 
U 5A5F03C3
F0 "Deba168_SolarCharger3mods" 99
F1 "Deba168_Solar_Charger3b.sch" 99
$EndSheet
$EndSCHEMATC
