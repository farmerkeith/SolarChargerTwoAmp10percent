EESchema Schematic File Version 2
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
LIBS:Buttons-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
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
F 1 "LED RED" H 4800 2000 50  0000 C CNN
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
F 1 "LED GREEN" H 4800 3150 50  0000 C CNN
F 2 "" H 4800 3250 50  0000 C CNN
F 3 "" H 4800 3250 50  0000 C CNN
	1    4800 3250
	-1   0    0    -1  
$EndComp
Connection ~ 4950 2700
Wire Wire Line
	4650 2100 4100 2100
Wire Wire Line
	4650 2700 4150 2700
Wire Wire Line
	4650 3250 4150 3250
Wire Wire Line
	5200 3650 4150 3650
Connection ~ 4950 3250
Text Label 3950 2100 0    60   ~ 0
D2
Text Label 4000 2700 0    60   ~ 0
D8
Text Label 3950 3250 0    60   ~ 0
D7
$Comp
L Earth #PWR?
U 1 1 58731B94
P 4150 3650
F 0 "#PWR?" H 4150 3400 50  0001 C CNN
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
$EndSCHEMATC
