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
Sheet 4 10
Title "Solar Charger V3"
Date "2017-01-10"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED_ALT D1
U 1 1 5873139D
P 4800 2100
F 0 "D1" H 4800 2200 50  0000 C CNN
F 1 "LED GREEN" H 4800 2000 50  0000 C CNN
F 2 "" H 4800 2100 50  0000 C CNN
F 3 "" H 4800 2100 50  0000 C CNN
	1    4800 2100
	-1   0    0    -1  
$EndComp
$Comp
L LED_ALT D2
U 1 1 587313F4
P 4800 2700
F 0 "D2" H 4800 2800 50  0000 C CNN
F 1 "LED YELLOW" H 4800 2600 50  0000 C CNN
F 2 "" H 4800 2700 50  0000 C CNN
F 3 "" H 4800 2700 50  0000 C CNN
	1    4800 2700
	-1   0    0    -1  
$EndComp
$Comp
L LED_ALT D3
U 1 1 58731441
P 4800 3250
F 0 "D3" H 4800 3350 50  0000 C CNN
F 1 "LED RED" H 4800 3150 50  0000 C CNN
F 2 "" H 4800 3250 50  0000 C CNN
F 3 "" H 4800 3250 50  0000 C CNN
	1    4800 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5200 3650 4150 3650
$Comp
L Earth #PWR17
U 1 1 58731B94
P 4150 3650
F 0 "#PWR17" H 4150 3400 50  0001 C CNN
F 1 "Earth" H 4150 3500 50  0001 C CNN
F 2 "" H 4150 3650 50  0000 C CNN
F 3 "" H 4150 3650 50  0000 C CNN
	1    4150 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2700 4950 2700
Wire Wire Line
	5200 2100 4950 2100
Wire Wire Line
	5200 3250 4950 3250
Wire Wire Line
	5200 2100 5200 3650
Connection ~ 5200 2700
Connection ~ 5200 3250
Text HLabel 4150 2100 0    60   Input ~ 0
D8
Text HLabel 4150 2700 0    60   Input ~ 0
D7
Text HLabel 4150 3250 0    60   Input ~ 0
D2
Text HLabel 4150 3650 0    60   Input ~ 0
GND
$Comp
L RKH R11
U 1 1 5A5224E2
P 4400 2100
F 0 "R11" V 4480 2100 50  0000 C CNN
F 1 "330R" V 4325 2100 50  0000 C CNN
F 2 "" H 4400 2100 60  0001 C CNN
F 3 "" H 4400 2100 60  0001 C CNN
	1    4400 2100
	0    1    1    0   
$EndComp
$Comp
L RKH R12
U 1 1 5A52263A
P 4400 2700
F 0 "R12" V 4480 2700 50  0000 C CNN
F 1 "330R" V 4325 2700 50  0000 C CNN
F 2 "" H 4400 2700 60  0001 C CNN
F 3 "" H 4400 2700 60  0001 C CNN
	1    4400 2700
	0    1    1    0   
$EndComp
$Comp
L RKH R13
U 1 1 5A522672
P 4400 3250
F 0 "R13" V 4480 3250 50  0000 C CNN
F 1 "330R" V 4325 3250 50  0000 C CNN
F 2 "" H 4400 3250 60  0001 C CNN
F 3 "" H 4400 3250 60  0001 C CNN
	1    4400 3250
	0    1    1    0   
$EndComp
$EndSCHEMATC
