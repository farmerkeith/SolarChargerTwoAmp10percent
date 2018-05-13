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
Sheet 2 10
Title "Solar Charger V3.01"
Date "2018-01-02"
Rev ""
Comp "farmerkeith"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L C C2
U 1 1 5873A991
P 7975 3150
F 0 "C2" H 8025 3250 100 0000 L CNN
F 1 "470uF" H 8025 3050 50  0000 L CNN
F 2 "" H 7975 3150 60  0001 C CNN
F 3 "" H 7975 3150 60  0001 C CNN
	1    7975 3150
	-1   0    0    1   
$EndComp
$Comp
L GNDPWR #PWR9
U 1 1 5873A992
P 7975 3475
F 0 "#PWR9" H 7975 3525 40  0001 C CNN
F 1 "GNDPWR" H 7975 3395 40  0000 C CNN
F 2 "" H 7975 3475 60  0001 C CNN
F 3 "" H 7975 3475 60  0001 C CNN
	1    7975 3475
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR3
U 1 1 5873A993
P 3500 1100
F 0 "#PWR3" H 3500 1150 40  0001 C CNN
F 1 "GNDPWR" H 3500 975 40  0000 C CNN
F 2 "" H 3500 1100 60  0001 C CNN
F 3 "" H 3500 1100 60  0001 C CNN
	1    3500 1100
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR8
U 1 1 5873A998
P 10000 3450
F 0 "#PWR8" H 10000 3500 40  0001 C CNN
F 1 "GNDPWR" H 10000 3300 40  0000 C CNN
F 2 "" H 10000 3450 60  0001 C CNN
F 3 "" H 10000 3450 60  0001 C CNN
	1    10000 3450
	1    0    0    -1  
$EndComp
$Comp
L RKH R3
U 1 1 5873A99A
P 7100 3250
F 0 "R3" V 7180 3250 50  0000 C CNN
F 1 "100K" V 7025 3250 50  0000 C CNN
F 2 "" H 7100 3250 60  0001 C CNN
F 3 "" H 7100 3250 60  0001 C CNN
	1    7100 3250
	1    0    0    -1  
$EndComp
$Comp
L RKH R4
U 1 1 5873A99B
P 7100 3750
F 0 "R4" V 7180 3750 50  0000 C CNN
F 1 "20K" V 7025 3750 50  0000 C CNN
F 2 "" H 7100 3750 60  0001 C CNN
F 3 "" H 7100 3750 60  0001 C CNN
	1    7100 3750
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR11
U 1 1 5873A99C
P 7100 4250
F 0 "#PWR11" H 7100 4250 30  0001 C CNN
F 1 "GND" H 7100 4180 30  0001 C CNN
F 2 "" H 7100 4250 60  0001 C CNN
F 3 "" H 7100 4250 60  0001 C CNN
	1    7100 4250
	1    0    0    -1  
$EndComp
$Comp
L C C4
U 1 1 5873A99D
P 7350 3750
F 0 "C4" H 7400 3850 50  0000 L CNN
F 1 "0.1uF" H 7400 3650 50  0000 L CNN
F 2 "" H 7350 3750 60  0001 C CNN
F 3 "" H 7350 3750 60  0001 C CNN
	1    7350 3750
	1    0    0    -1  
$EndComp
$Comp
L C C7
U 1 1 5873A9A2
P 3400 3700
F 0 "C7" V 3450 3800 50  0000 L CNN
F 1 "0.1uF" V 3300 3850 50  0000 L CNN
F 2 "" H 3400 3700 60  0001 C CNN
F 3 "" H 3400 3700 60  0001 C CNN
	1    3400 3700
	0    1    1    0   
$EndComp
$Comp
L DIODE D2
U 1 1 5873A9A6
P 2500 3500
F 0 "D2" H 2400 3600 40  0000 C CNN
F 1 "1N4148" H 2650 3600 40  0000 C CNN
F 2 "" H 2500 3500 60  0001 C CNN
F 3 "" H 2500 3500 60  0001 C CNN
	1    2500 3500
	1    0    0    -1  
$EndComp
$Comp
L ACS712module U3
U 1 1 5873A9A7
P 2600 1600
AR Path="/5873A9A7" Ref="U3"  Part="1" 
AR Path="/58731385/5873A9A7" Ref="U3"  Part="1" 
F 0 "U3" H 2650 1600 60  0000 C CNN
F 1 "ACS712MODULE" H 2600 2150 60  0000 C CNN
F 2 "" H 2600 1600 60  0001 C CNN
F 3 "" H 2600 1600 60  0001 C CNN
	1    2600 1600
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 5873A9A8
P 1700 2250
F 0 "C3" H 1750 2350 50  0000 L CNN
F 1 "0.1uF" H 1750 2150 50  0000 L CNN
F 2 "" H 1700 2250 60  0001 C CNN
F 3 "" H 1700 2250 60  0001 C CNN
	1    1700 2250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR6
U 1 1 5873A9A9
P 2100 2400
F 0 "#PWR6" H 2100 2400 30  0001 C CNN
F 1 "GND" H 2100 2330 30  0001 C CNN
F 2 "" H 2100 2400 60  0001 C CNN
F 3 "" H 2100 2400 60  0001 C CNN
	1    2100 2400
	1    0    0    -1  
$EndComp
$Comp
L RKH R2
U 1 1 5873A9AA
P 1497 2147
F 0 "R2" V 1577 2147 50  0000 C CNN
F 1 "20K" V 1422 2147 50  0000 C CNN
F 2 "" H 1497 2147 60  0001 C CNN
F 3 "" H 1497 2147 60  0001 C CNN
	1    1497 2147
	1    0    0    -1  
$EndComp
$Comp
L RKH R1
U 1 1 5873A9AB
P 1500 1650
F 0 "R1" V 1580 1650 50  0000 C CNN
F 1 "150K" V 1425 1650 50  0000 C CNN
F 2 "" H 1500 1650 60  0001 C CNN
F 3 "" H 1500 1650 60  0001 C CNN
	1    1500 1650
	1    0    0    -1  
$EndComp
Text Notes 1100 750  0    99   ~ 0
Vpp
$Comp
L RKH R8
U 1 1 5873A9B8
P 1250 4100
F 0 "R8" V 1350 4000 50  0000 C CNN
F 1 "200R" V 1350 4200 50  0000 C CNN
F 2 "" H 1250 4100 60  0001 C CNN
F 3 "" H 1250 4100 60  0001 C CNN
	1    1250 4100
	0    1    1    0   
$EndComp
$Comp
L RKH R7
U 1 1 5873A9B9
P 1250 3900
F 0 "R7" V 1350 3800 50  0000 C CNN
F 1 "200R" V 1350 4000 50  0000 C CNN
F 2 "" H 1250 3900 60  0001 C CNN
F 3 "" H 1250 3900 60  0001 C CNN
	1    1250 3900
	0    1    1    0   
$EndComp
$Comp
L GNDPWR #PWR13
U 1 1 5873A9BB
P 2300 4650
F 0 "#PWR13" H 2300 4700 40  0001 C CNN
F 1 "GNDPWR" H 2300 4500 40  0000 C CNN
F 2 "" H 2300 4650 60  0001 C CNN
F 3 "" H 2300 4650 60  0001 C CNN
	1    2300 4650
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR14
U 1 1 5873A9BD
P 5100 5000
F 0 "#PWR14" H 5100 5050 40  0001 C CNN
F 1 "GNDPWR" H 5100 4850 40  0000 C CNN
F 2 "" H 5100 5000 60  0001 C CNN
F 3 "" H 5100 5000 60  0001 C CNN
	1    5100 5000
	1    0    0    -1  
$EndComp
$Comp
L RKH R11
U 1 1 5873A9BE
P 4550 4100
F 0 "R11" V 4650 4000 50  0000 C CNN
F 1 "10R" V 4650 4200 50  0000 C CNN
F 2 "" H 4550 4100 60  0001 C CNN
F 3 "" H 4550 4100 60  0001 C CNN
	1    4550 4100
	0    1    1    0   
$EndComp
$Comp
L RKH R12
U 1 1 5873A9BF
P 4550 4600
F 0 "R12" V 4650 4450 50  0000 C CNN
F 1 "10R" V 4650 4700 50  0000 C CNN
F 2 "" H 4550 4600 60  0001 C CNN
F 3 "" H 4550 4600 60  0001 C CNN
	1    4550 4600
	0    1    1    0   
$EndComp
$Comp
L RKH R13
U 1 1 5873A9C0
P 4550 2600
F 0 "R13" V 4650 2550 50  0000 C CNN
F 1 "10R" V 4650 2750 50  0000 C CNN
F 2 "" H 4550 2600 60  0001 C CNN
F 3 "" H 4550 2600 60  0001 C CNN
	1    4550 2600
	0    1    1    0   
$EndComp
$Comp
L IR2104 U1
U 1 1 5873A9C1
P 2800 4000
F 0 "U1" H 2800 4050 60  0000 C CNN
F 1 "IR2104" H 2800 3650 60  0000 C CNN
F 2 "" H 2800 4000 60  0001 C CNN
F 3 "" H 2800 4000 60  0001 C CNN
	1    2800 4000
	1    0    0    -1  
$EndComp
$Comp
L C C8
U 1 1 5873A9C2
P 6650 2600
F 0 "C8" V 6700 2700 50  0000 L CNN
F 1 "0.01uF" V 6500 2600 50  0000 L CNN
F 2 "" H 6650 2600 60  0001 C CNN
F 3 "" H 6650 2600 60  0001 C CNN
	1    6650 2600
	0    -1   -1   0   
$EndComp
$Comp
L RKH R6
U 1 1 5873A9C3
P 6150 2600
F 0 "R6" V 6230 2600 50  0000 C CNN
F 1 "180" V 6050 2600 50  0000 C CNN
F 2 "" H 6150 2600 60  0001 C CNN
F 3 "" H 6150 2600 60  0001 C CNN
	1    6150 2600
	0    -1   -1   0   
$EndComp
$Comp
L INDUCTOR L1
U 1 1 5873A9C4
P 6400 3000
F 0 "L1" V 6350 3000 40  0000 C CNN
F 1 "INDUCTOR 33uH" V 6500 3000 40  0000 C CNN
F 2 "" H 6400 3000 60  0001 C CNN
F 3 "" H 6400 3000 60  0001 C CNN
	1    6400 3000
	0    1    1    0   
$EndComp
$Comp
L C C9
U 1 1 5873A9C5
P 3800 1350
F 0 "C9" H 3650 1250 50  0000 L CNN
F 1 "0.1uF" H 3850 1250 50  0000 L CNN
F 2 "" H 3800 1350 60  0001 C CNN
F 3 "" H 3800 1350 60  0001 C CNN
	1    3800 1350
	1    0    0    -1  
$EndComp
$Comp
L RKH R10
U 1 1 5873A9C6
P 4050 1200
F 0 "R10" V 4000 1050 50  0000 C CNN
F 1 "10K" V 4000 1250 50  0000 C CNN
F 2 "" H 4050 1200 60  0001 C CNN
F 3 "" H 4050 1200 60  0001 C CNN
	1    4050 1200
	0    1    1    0   
$EndComp
$Comp
L RKH R19
U 1 1 5873A9C7
P 4600 1050
F 0 "R19" V 4680 1050 50  0000 C CNN
F 1 "1M" V 4500 1000 50  0000 C CNN
F 2 "" H 4600 1050 60  0001 C CNN
F 3 "" H 4600 1050 60  0001 C CNN
	1    4600 1050
	1    0    0    -1  
$EndComp
$Comp
L DIODE D7
U 1 1 5873A9C8
P 4300 1400
F 0 "D7" H 4300 1500 40  0000 C CNN
F 1 "1N4148" H 4300 1300 40  0000 C CNN
F 2 "" H 4300 1400 60  0001 C CNN
F 3 "" H 4300 1400 60  0001 C CNN
	1    4300 1400
	0    1    1    0   
$EndComp
$Comp
L DIODE D8
U 1 1 5873A9C9
P 4300 1000
F 0 "D8" H 4300 1100 40  0000 C CNN
F 1 "1N4148" H 4300 900 40  0000 C CNN
F 2 "" H 4300 1000 60  0001 C CNN
F 3 "" H 4300 1000 60  0001 C CNN
	1    4300 1000
	0    1    1    0   
$EndComp
$Comp
L MOS_NKH Q4
U 1 1 5873A9CA
P 9100 1300
F 0 "Q4" H 9500 1300 60  0000 R CNN
F 1 "IRFZ44N" H 9200 1600 60  0000 R CNN
F 2 "" H 9100 1300 60  0001 C CNN
F 3 "" H 9100 1300 60  0001 C CNN
	1    9100 1300
	1    0    0    -1  
$EndComp
$Comp
L MOS_NKH Q3
U 1 1 5873A9CB
P 5000 4500
F 0 "Q3" H 5350 4650 60  0000 R CNN
F 1 "IRFZ44N" H 5450 4750 60  0000 R CNN
F 2 "" H 5000 4500 60  0001 C CNN
F 3 "" H 5000 4500 60  0001 C CNN
	1    5000 4500
	1    0    0    -1  
$EndComp
$Comp
L MOS_NKH Q2
U 1 1 5873A9CC
P 5000 2500
F 0 "Q2" H 5300 2650 60  0000 R CNN
F 1 "IRFZ44N" H 5250 2750 60  0000 R CNN
F 2 "" H 5000 2500 60  0001 C CNN
F 3 "" H 5000 2500 60  0001 C CNN
	1    5000 2500
	1    0    0    -1  
$EndComp
$Comp
L MOS_NKH Q1
U 1 1 5873A9CD
P 5000 1700
F 0 "Q1" H 5010 1870 60  0000 R CNN
F 1 "IRFZ44N" H 5400 1400 60  0000 R CNN
F 2 "" H 5000 1700 60  0001 C CNN
F 3 "" H 5000 1700 60  0001 C CNN
	1    5000 1700
	1    0    0    1   
$EndComp
$Comp
L RKH R20
U 1 1 5873A9CE
P 3400 4550
F 0 "R20" V 3500 4400 50  0000 C CNN
F 1 "100K" V 3500 4650 50  0000 C CNN
F 2 "" H 3400 4550 60  0001 C CNN
F 3 "" H 3400 4550 60  0001 C CNN
	1    3400 4550
	-1   0    0    1   
$EndComp
$Comp
L C C10
U 1 1 5873A9D3
P 900 2555
F 0 "C10" H 950 2655 50  0000 L CNN
F 1 "0.1uF" H 950 2455 50  0000 L CNN
F 2 "" H 900 2555 60  0001 C CNN
F 3 "" H 900 2555 60  0001 C CNN
	1    900  2555
	1    0    0    -1  
$EndComp
$Comp
L RKH R24
U 1 1 5873A9D4
P 2400 2600
F 0 "R24" V 2500 2500 50  0000 C CNN
F 1 "100R" V 2500 2700 50  0000 C CNN
F 2 "" H 2400 2600 60  0001 C CNN
F 3 "" H 2400 2600 60  0001 C CNN
	1    2400 2600
	0    1    1    0   
$EndComp
$Comp
L GND #PWR7
U 1 1 5873A9D5
P 900 2700
F 0 "#PWR7" H 900 2700 30  0001 C CNN
F 1 "GND" H 900 2630 30  0001 C CNN
F 2 "" H 900 2700 60  0001 C CNN
F 3 "" H 900 2700 60  0001 C CNN
	1    900  2700
	1    0    0    -1  
$EndComp
Text Label 6300 3250 0    60   ~ 0
SEE_TEXT
$Comp
L DS18B20 U6
U 1 1 5873A9DE
P 1400 6650
F 0 "U6" H 1600 6800 60  0000 C CNN
F 1 "DS18B20" H 1400 6850 40  0000 C CNN
F 2 "" H 1400 6850 60  0001 C CNN
F 3 "" H 1400 6850 60  0001 C CNN
	1    1400 6650
	1    0    0    -1  
$EndComp
$Comp
L RKH R27
U 1 1 5873A9DF
P 1150 7350
F 0 "R27" V 1230 7350 50  0000 C CNN
F 1 "4K7" V 1050 7350 50  0000 C CNN
F 2 "" H 1150 7350 60  0001 C CNN
F 3 "" H 1150 7350 60  0001 C CNN
	1    1150 7350
	-1   0    0    1   
$EndComp
Text Label 1200 6400 0    60   ~ 0
TempBat
Text HLabel 700  1900 0    60   Input ~ 0
A0
Text HLabel 700  2400 0    60   Input ~ 0
A1
Text HLabel 800  2850 0    60   Input ~ 0
+5V
Text HLabel 750  3900 0    60   Input ~ 0
D9
Text HLabel 750  4100 0    60   Input ~ 0
D10
Text HLabel 800  7100 0    60   Input ~ 0
D4
Text HLabel 850  7600 0    60   Input ~ 0
+5V
Text HLabel 6550 3500 0    60   Input ~ 0
A2
Connection ~ 5100 4825
Wire Wire Line
	3400 4825 5100 4825
Wire Wire Line
	10000 3100 10000 3450
Wire Wire Line
	7350 3500 7350 3600
Wire Wire Line
	6550 3500 7100 3500
Wire Wire Line
	7100 3500 7350 3500
Connection ~ 7100 3500
Wire Wire Line
	2300 3700 2300 3500
Wire Wire Line
	2700 3500 3250 3500
Wire Wire Line
	3250 3500 3250 3700
Connection ~ 1500 1900
Wire Wire Line
	700  1900 1500 1900
Wire Wire Line
	1500 1900 1700 1900
Wire Wire Line
	750  4100 1000 4100
Wire Wire Line
	4300 3900 3250 3900
Wire Wire Line
	5100 3000 5900 3000
Wire Wire Line
	5900 3000 6100 3000
Wire Wire Line
	4600 1300 4600 1600
Wire Wire Line
	5100 800  5100 4100
Wire Wire Line
	5100 4100 5100 4300
Wire Wire Line
	4300 1600 4600 1600
Wire Wire Line
	4600 1600 4800 1600
Wire Wire Line
	5900 2600 5900 3000
Wire Wire Line
	5100 4100 4800 4100
Connection ~ 5100 4100
Wire Wire Line
	3250 4300 3400 4300
Wire Wire Line
	3400 4300 3800 4300
Wire Wire Line
	3800 4300 4300 4300
Wire Wire Line
	4300 4300 4300 4600
Wire Wire Line
	1000 3900 750  3900
Wire Wire Line
	800  2850 2850 2850
Wire Wire Line
	3225 4100 3700 4100
Wire Wire Line
	3700 4100 4300 4100
Wire Wire Line
	1150 800  1500 800 
Wire Wire Line
	1500 800  2350 800 
Connection ~ 2300 3500
Wire Wire Line
	2800 800  4300 800 
Wire Wire Line
	4300 800  4600 800 
Wire Wire Line
	4600 800  5100 800 
Connection ~ 4300 800 
Connection ~ 4600 800 
Wire Bus Line
	7975 3325 7975 3525
Connection ~ 3700 4100
Connection ~ 5900 3000
Connection ~ 7100 3000
Connection ~ 7975 3300
Connection ~ 4300 1200
Connection ~ 4600 1600
Wire Wire Line
	1700 1900 1700 2100
Wire Wire Line
	1500 2400 2100 2400
Wire Wire Line
	2100 2400 2250 2400
Wire Wire Line
	2850 2850 2850 2400
Wire Wire Line
	3700 3700 3550 3700
Wire Wire Line
	3400 4800 3400 4825
Connection ~ 3400 4300
Wire Wire Line
	7350 3900 7350 4250
Wire Wire Line
	7100 4250 7100 4000
Connection ~ 7100 4250
Wire Wire Line
	2650 2600 2650 2400
Wire Wire Line
	1200 2600 2150 2600
Wire Wire Line
	1200 2400 1200 2600
Wire Wire Line
	7350 4250 7100 4250
Wire Wire Line
	700  6800 1300 6800
Wire Wire Line
	1500 7600 850  7600
Wire Wire Line
	800  7100 1400 7100
Connection ~ 7400 3000
Wire Wire Line
	6400 2600 6500 2600
$Comp
L DIODE D11
U 1 1 5874EB95
P 5300 800
F 0 "D11" H 5300 900 40  0000 C CNN
F 1 "1N4148" H 5300 700 40  0000 C CNN
F 2 "" H 5300 800 60  0001 C CNN
F 3 "" H 5300 800 60  0001 C CNN
	1    5300 800 
	1    0    0    -1  
$EndComp
$Comp
L DIODE D12
U 1 1 587544A0
P 6800 800
F 0 "D12" H 6800 900 40  0000 C CNN
F 1 "1N4148" H 6800 700 40  0000 C CNN
F 2 "" H 6800 800 60  0001 C CNN
F 3 "" H 6800 800 60  0001 C CNN
	1    6800 800 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7000 800  9150 800 
Wire Wire Line
	5500 800  6400 800 
Wire Wire Line
	6400 800  6600 800 
Wire Wire Line
	7400 3000 7400 800 
Text Notes 6150 1200 0    39   ~ 0
DC-DC \nbuck \nconverter
Wire Notes Line
	6075 975  6475 975 
Wire Notes Line
	6475 975  6475 1250
Wire Notes Line
	6475 1250 6075 1250
Wire Notes Line
	6075 1250 6075 975 
Wire Wire Line
	6400 800  6400 1000
Connection ~ 6400 800 
Wire Wire Line
	6150 950  6150 1000
Wire Wire Line
	5900 950  6025 950 
Wire Wire Line
	6025 950  6150 950 
Wire Wire Line
	5900 950  5900 1000
$Comp
L Earth #PWR1
U 1 1 5875C1F3
P 5900 1000
F 0 "#PWR1" H 5900 750 50  0001 C CNN
F 1 "Earth" H 5900 850 50  0001 C CNN
F 2 "" H 5900 1000 50  0000 C CNN
F 3 "" H 5900 1000 50  0000 C CNN
	1    5900 1000
	1    0    0    -1  
$EndComp
Text Label 6400 975  0    39   ~ 0
IN
Wire Wire Line
	6150 1250 6150 1300
Wire Wire Line
	6150 1300 6150 1450
Wire Wire Line
	6025 1300 6150 1300
Wire Wire Line
	6025 950  6025 1300
Wire Wire Line
	6025 1300 6025 1775
Connection ~ 6025 950 
Text Notes 6150 1675 0    39   ~ 0
DC-DC \nbuck \nconverter
Wire Notes Line
	6075 1450 6475 1450
Wire Notes Line
	6475 1450 6475 1725
Wire Notes Line
	6475 1725 6075 1725
Wire Notes Line
	6075 1725 6075 1450
Text Label 6400 1450 0    39   ~ 0
IN
Wire Wire Line
	6150 1725 6150 1775
Wire Wire Line
	6150 1775 6150 2025
Wire Wire Line
	6025 1775 6150 1775
Connection ~ 6150 1300
Connection ~ 6025 1300
Wire Wire Line
	6400 1250 6400 1350
Wire Wire Line
	6400 1350 6400 1450
Wire Wire Line
	6400 1350 6550 1350
Connection ~ 6400 1350
Text Label 6425 1325 0    39   ~ 0
OUT
$Comp
L +12V #PWR4
U 1 1 5875EC00
P 6550 1350
F 0 "#PWR4" H 6550 1200 50  0001 C CNN
F 1 "+12V" V 6525 1550 50  0000 C CNN
F 2 "" H 6550 1350 50  0000 C CNN
F 3 "" H 6550 1350 50  0000 C CNN
	1    6550 1350
	0    1    1    0   
$EndComp
Text Label 6425 1800 0    39   ~ 0
OUT
Wire Wire Line
	6400 1850 6550 1850
Connection ~ 6400 1850
Text Notes 6125 2225 0    39   ~ 0
LM1117\nREGULATOR
Wire Notes Line
	6075 2025 6475 2025
Wire Notes Line
	6475 2025 6475 2300
Wire Notes Line
	6475 2300 6075 2300
Wire Notes Line
	6075 2300 6075 2050
Wire Wire Line
	6400 1725 6400 1850
Wire Wire Line
	6400 1850 6400 2025
Connection ~ 6150 1775
Text Label 6425 2000 0    39   ~ 0
IN
Wire Wire Line
	6400 2300 6400 2375
Wire Wire Line
	6400 2375 6550 2375
Text Label 6250 2375 0    39   ~ 0
OUT
Text HLabel 6550 1850 2    39   Input ~ 0
+5V
Text HLabel 6550 2375 2    39   Input ~ 0
+3.3V
Wire Wire Line
	700  2400 1200 2400
Wire Wire Line
	2300 3500 800  3500
$Comp
L RKH R27
U 1 1 5878C47E
P 3050 7500
F 0 "R27" V 3150 7350 50  0000 C CNN
F 1 "1K" V 3150 7600 50  0000 C CNN
F 2 "" H 3050 7500 60  0001 C CNN
F 3 "" H 3050 7500 60  0001 C CNN
	1    3050 7500
	0    1    1    0   
$EndComp
$Comp
L RKH R28
U 1 1 5878C5C2
P 3550 7500
F 0 "R28" V 3650 7350 50  0000 C CNN
F 1 "2K" V 3650 7600 50  0000 C CNN
F 2 "" H 3550 7500 60  0001 C CNN
F 3 "" H 3550 7500 60  0001 C CNN
	1    3550 7500
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 7500 3300 7200
Wire Wire Line
	3300 7200 3100 7200
Text HLabel 2800 7500 0    60   Input ~ 0
D6
$Comp
L +12V #PWR10
U 1 1 58816AB3
P 800 3500
F 0 "#PWR10" H 800 3350 50  0001 C CNN
F 1 "+12V" V 800 3700 50  0000 C CNN
F 2 "" H 800 3500 50  0000 C CNN
F 3 "" H 800 3500 50  0000 C CNN
	1    800  3500
	0    -1   -1   0   
$EndComp
$Comp
L Screw_Terminal_01x02 J1
U 1 1 5A4B34AD
P 950 800
F 0 "J1" H 950 900 50  0000 C CNN
F 1 "SOLAR INPUT" H 950 1000 50  0000 C CNN
F 2 "" H 950 800 50  0001 C CNN
F 3 "" H 950 800 50  0001 C CNN
	1    950  800 
	-1   0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR2
U 1 1 5A4BE150
P 1200 1100
F 0 "#PWR2" H 1200 1150 40  0001 C CNN
F 1 "GNDPWR" H 1200 975 40  0000 C CNN
F 2 "" H 1200 1100 60  0001 C CNN
F 3 "" H 1200 1100 60  0001 C CNN
	1    1200 1100
	1    0    0    -1  
$EndComp
$Comp
L D_TVS_ALT D4
U 1 1 5A4D9EAC
P 1200 950
F 0 "D4" H 1200 1050 50  0000 C CNN
F 1 "P6KE36CA" H 1250 1150 50  0000 C CNN
F 2 "" H 1200 950 50  0001 C CNN
F 3 "" H 1200 950 50  0001 C CNN
	1    1200 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	1000 900  1000 1100
Wire Wire Line
	1000 1100 1200 1100
Wire Wire Line
	1500 1400 1500 800 
Connection ~ 1500 800 
$Comp
L CP C1
U 1 1 5A4DE2AF
P 3500 950
F 0 "C1" H 3525 1050 50  0000 L CNN
F 1 "220 uF *2" H 3525 850 50  0000 L CNN
F 2 "" H 3538 800 50  0001 C CNN
F 3 "" H 3500 950 50  0001 C CNN
	1    3500 950 
	1    0    0    -1  
$EndComp
Text Notes 750  2050 0    99   ~ 0
Solar \nVoltage \nSense
Text Notes 3250 2150 0    99   ~ 0
Solar\nCurrent\nSense
Wire Wire Line
	5100 1900 5100 2300
Wire Wire Line
	5100 4700 5100 4825
Wire Wire Line
	5100 4825 5100 5000
Wire Wire Line
	4300 2600 4300 3900
Wire Wire Line
	2300 4300 2300 4600
Wire Wire Line
	2300 4600 2300 4650
Wire Wire Line
	3700 3700 3700 4100
Wire Wire Line
	1500 3900 2300 3900
Wire Wire Line
	1500 4100 2300 4100
$Comp
L CP C5
U 1 1 5A4EDDE7
P 1600 4450
F 0 "C5" H 1625 4550 50  0000 L CNN
F 1 "CP" H 1625 4350 50  0000 L CNN
F 2 "" H 1638 4300 50  0001 C CNN
F 3 "" H 1600 4450 50  0001 C CNN
	1    1600 4450
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 5A4EDF68
P 1900 4450
F 0 "C6" H 1925 4550 50  0000 L CNN
F 1 "C" H 1925 4350 50  0000 L CNN
F 2 "" H 1938 4300 50  0001 C CNN
F 3 "" H 1900 4450 50  0001 C CNN
	1    1900 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 4600 1900 4600
Wire Wire Line
	1900 4600 2300 4600
Connection ~ 2300 4600
Connection ~ 1900 4600
Wire Wire Line
	1900 4300 1900 3700
Wire Wire Line
	1600 3700 1900 3700
Wire Wire Line
	1900 3700 2300 3700
Wire Wire Line
	1600 4300 1600 3700
Connection ~ 1900 3700
Connection ~ 2300 3700
Wire Wire Line
	1500 7600 1500 6800
Wire Wire Line
	1400 7100 1400 6800
Wire Wire Line
	6800 2600 6800 3000
Connection ~ 6800 3000
Text Notes 6400 4100 0    99   ~ 0
Battery\nVoltage\nSense
$Comp
L D_ALT D3
U 1 1 5A4F4FB2
P 5500 4850
F 0 "D3" H 5500 4950 50  0000 C CNN
F 1 "UF4007" H 5500 4750 50  0000 C CNN
F 2 "" H 5500 4850 50  0001 C CNN
F 3 "" H 5500 4850 50  0001 C CNN
	1    5500 4850
	0    1    1    0   
$EndComp
Wire Wire Line
	5100 5000 5500 5000
Wire Wire Line
	5500 4700 5500 3000
$Comp
L Screw_Terminal_01x02 J3
U 1 1 5A4F6F50
P 10200 3000
F 0 "J3" H 10200 3100 50  0000 C CNN
F 1 "BATTERY" H 10200 2800 50  0000 C CNN
F 2 "" H 10200 3000 50  0001 C CNN
F 3 "" H 10200 3000 50  0001 C CNN
	1    10200 3000
	1    0    0    -1  
$EndComp
$Comp
L GNDPWR #PWR5
U 1 1 5A4FC85C
P 9200 1900
F 0 "#PWR5" H 9200 1700 50  0001 C CNN
F 1 "GNDPWR" H 9200 1770 50  0000 C CNN
F 2 "" H 9200 1850 50  0001 C CNN
F 3 "" H 9200 1850 50  0001 C CNN
	1    9200 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9200 1500 9200 1900
$Comp
L Screw_Terminal_01x02 J2
U 1 1 5A4FCDF2
P 10200 1000
F 0 "J2" H 10200 1100 50  0000 C CNN
F 1 "Load Terminal" H 10200 800 50  0000 C CNN
F 2 "" H 10200 1000 50  0001 C CNN
F 3 "" H 10200 1000 50  0001 C CNN
	1    10200 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 1100 9200 1100
$Comp
L D_TVS_ALT D5
U 1 1 5A4FD0AD
P 9600 1750
F 0 "D5" H 9600 1850 50  0000 C CNN
F 1 "P6KE36CA" H 9600 1650 50  0000 C CNN
F 2 "" H 9600 1750 50  0001 C CNN
F 3 "" H 9600 1750 50  0001 C CNN
	1    9600 1750
	0    1    1    0   
$EndComp
Wire Wire Line
	8650 1900 9200 1900
Wire Wire Line
	9200 1900 9600 1900
Wire Wire Line
	10000 1000 9600 1000
Wire Wire Line
	9600 800  9600 1000
Wire Wire Line
	9600 1000 9600 1600
$Comp
L Fuse F2
U 1 1 5A4FD8E7
P 9300 800
F 0 "F2" V 9380 800 50  0000 C CNN
F 1 "Fuse 5A" V 9225 800 50  0000 C CNN
F 2 "" V 9230 800 50  0001 C CNN
F 3 "" H 9300 800 50  0001 C CNN
	1    9300 800 
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 800  9450 800 
Connection ~ 9600 1000
$Comp
L RKH R9
U 1 1 5A500055
P 8650 1050
F 0 "R9" V 8730 1050 50  0000 C CNN
F 1 "10K" V 8575 1050 50  0000 C CNN
F 2 "" H 8650 1050 60  0001 C CNN
F 3 "" H 8650 1050 60  0001 C CNN
	1    8650 1050
	1    0    0    -1  
$EndComp
$Comp
L Q_NPN_CBE Q5
U 1 1 5A500280
P 8550 1700
F 0 "Q5" H 8750 1750 50  0000 L CNN
F 1 "Q_NPN_CBE" H 8750 1650 50  0000 L CNN
F 2 "" H 8750 1800 50  0001 C CNN
F 3 "" H 8550 1700 50  0001 C CNN
	1    8550 1700
	1    0    0    -1  
$EndComp
Connection ~ 9200 1900
Wire Wire Line
	8900 1400 8650 1400
Wire Wire Line
	8650 1300 8650 1400
Wire Wire Line
	8650 1400 8650 1500
Connection ~ 8650 1400
$Comp
L RKH R10
U 1 1 5A500558
P 8100 1700
F 0 "R10" V 8180 1700 50  0000 C CNN
F 1 "1K" V 8025 1700 50  0000 C CNN
F 2 "" H 8100 1700 60  0001 C CNN
F 3 "" H 8100 1700 60  0001 C CNN
	1    8100 1700
	0    1    1    0   
$EndComp
$Comp
L GND #PWR15
U 1 1 5A508B90
P 700 6800
F 0 "#PWR15" H 700 6550 50  0001 C CNN
F 1 "GND" H 700 6650 50  0000 C CNN
F 2 "" H 700 6800 50  0001 C CNN
F 3 "" H 700 6800 50  0001 C CNN
	1    700  6800
	1    0    0    -1  
$EndComp
$Comp
L Conn_02x04_Counter_Clockwise J4
U 1 1 5A50CAC6
P 2800 7000
F 0 "J4" H 2850 7200 50  0000 C CNN
F 1 "ESP01 connector" H 2850 6700 50  0000 C CNN
F 2 "" H 2800 7000 50  0001 C CNN
F 3 "" H 2800 7000 50  0001 C CNN
	1    2800 7000
	1    0    0    -1  
$EndComp
Text HLabel 2000 7200 0    59   Input ~ 0
+3.3V
Wire Wire Line
	2000 7200 2100 7200
Wire Wire Line
	2100 7200 2600 7200
$Comp
L RKH R15
U 1 1 5A50E657
P 2350 7000
F 0 "R15" V 2430 7000 50  0000 C CNN
F 1 "10K" V 2275 7000 50  0000 C CNN
F 2 "" H 2350 7000 60  0001 C CNN
F 3 "" H 2350 7000 60  0001 C CNN
	1    2350 7000
	0    1    1    0   
$EndComp
Wire Wire Line
	2100 7000 2100 7200
Connection ~ 2100 7200
NoConn ~ 2600 7100
Wire Wire Line
	2000 6800 2600 6800
Wire Wire Line
	2600 6800 2600 6900
Wire Wire Line
	3100 6900 3800 6900
Wire Wire Line
	3800 6900 3800 7500
$Comp
L GND #PWR16
U 1 1 5A511A67
P 3800 7500
F 0 "#PWR16" H 3800 7250 50  0001 C CNN
F 1 "GND" H 3800 7350 50  0000 C CNN
F 2 "" H 3800 7500 50  0001 C CNN
F 3 "" H 3800 7500 50  0001 C CNN
	1    3800 7500
	1    0    0    -1  
$EndComp
Text Notes 2400 6800 0    99   ~ 0
Tx
Text Notes 3200 7200 0    99   ~ 0
Rx
$Comp
L Button SW1
U 1 1 5A512765
P 4100 7250
F 0 "SW1" H 4100 7405 50  0000 C CNN
F 1 "Reset Button" H 4100 7225 50  0000 C CNN
F 2 "" H 4100 7330 50  0000 C CNN
F 3 "" V 4100 7225 50  0000 C CNN
	1    4100 7250
	0    -1   1    0   
$EndComp
Wire Wire Line
	3800 7500 4100 7500
Wire Wire Line
	4100 7500 4400 7500
Wire Wire Line
	4400 7500 4800 7500
Wire Wire Line
	4800 7500 5850 7500
Wire Wire Line
	4100 7500 4100 7400
Wire Wire Line
	4100 6800 4100 7100
$Comp
L Button SW2
U 1 1 5A515DBA
P 4400 6450
F 0 "SW2" H 4400 6605 50  0000 C CNN
F 1 "Backlight Button" H 4400 6425 50  0000 C CNN
F 2 "" H 4400 6530 50  0000 C CNN
F 3 "" V 4400 6425 50  0000 C CNN
	1    4400 6450
	0    -1   -1   0   
$EndComp
$Comp
L RKH R14
U 1 1 5A515E47
P 4400 7250
F 0 "R14" V 4480 7250 50  0000 C CNN
F 1 "10K" V 4325 7250 50  0000 C CNN
F 2 "" H 4400 7250 60  0001 C CNN
F 3 "" H 4400 7250 60  0001 C CNN
	1    4400 7250
	1    0    0    -1  
$EndComp
Connection ~ 4100 7500
Wire Wire Line
	4400 6600 4400 7000
Text HLabel 4400 6100 0    60   Input ~ 0
+5V
Wire Wire Line
	4400 6100 4400 6300
Wire Wire Line
	3800 1500 3800 4300
Connection ~ 3800 4300
$Comp
L Conn_01x04_Female J5
U 1 1 5A52176D
P 5200 7100
F 0 "J5" H 5200 7300 50  0000 C CNN
F 1 "LED Conn" H 5200 6800 50  0000 C CNN
F 2 "" H 5200 7100 50  0001 C CNN
F 3 "" H 5200 7100 50  0001 C CNN
	1    5200 7100
	1    0    0    1   
$EndComp
Text HLabel 5000 6900 0    60   Input ~ 0
D8
Text HLabel 5000 7000 0    60   Input ~ 0
D7
Text HLabel 5000 7100 0    60   Input ~ 0
D2
Wire Wire Line
	5000 7200 4800 7200
Wire Wire Line
	4800 7200 4800 7500
Connection ~ 4400 7500
$Comp
L Conn_01x04_Female J6
U 1 1 5A523008
P 6200 7100
F 0 "J6" H 6200 7300 50  0000 C CNN
F 1 "LCD Conn" H 6200 6800 50  0000 C CNN
F 2 "" H 6200 7100 50  0001 C CNN
F 3 "" H 6200 7100 50  0001 C CNN
	1    6200 7100
	1    0    0    1   
$EndComp
Wire Wire Line
	5850 7500 5850 7200
Wire Wire Line
	5850 7200 6000 7200
Connection ~ 4800 7500
Text HLabel 6000 7100 0    60   Input ~ 0
A5/SCL
Text HLabel 6000 7000 0    60   Input ~ 0
A4/SDA
Text HLabel 5950 6900 0    60   Input ~ 0
+5V
$Comp
L ArduinoNano U2
U 1 1 5A523886
P 8600 5200
F 0 "U2" H 8725 5100 50  0000 C CNN
F 1 "ArduinoNano" V 8500 5100 50  0000 C CNN
F 2 "" H 8600 5200 50  0000 C CNN
F 3 "" H 8600 5200 50  0000 C CNN
	1    8600 5200
	1    0    0    -1  
$EndComp
Text HLabel 9100 4900 2    60   Input ~ 0
A0
Text HLabel 9100 5000 2    60   Input ~ 0
A1
Text Notes 9300 4950 0    60   ~ 0
Solar Voltage Sense
Text Notes 9300 5050 0    60   ~ 0
Solar Current Sense
Text HLabel 9100 5100 2    60   Input ~ 0
A2
Text Notes 9300 5150 0    60   ~ 0
Battery Voltage Sense
Text HLabel 9100 5300 2    60   Input ~ 0
A4/SDA
Text HLabel 9100 5400 2    60   Input ~ 0
A5/SCL
Text HLabel 8100 5600 0    60   Input ~ 0
D9
Text Notes 7300 5650 0    60   ~ 0
PWM to IN
Text Notes 7250 5750 0    60   ~ 0
PWM to SD\
Text HLabel 8100 5700 0    60   Input ~ 0
D10
Text HLabel 9100 4700 2    60   Input ~ 0
RST
Text HLabel 8100 4900 0    60   Input ~ 0
D2
Text Notes 7350 5550 0    60   ~ 0
GREEN LED
Text Notes 7450 4950 0    60   ~ 0
RED LED
Text Notes 7300 5450 0    60   ~ 0
YELLOW LED
Text HLabel 8100 5200 0    60   Input ~ 0
D5
Text Notes 9350 5250 0    60   ~ 0
BACKLIGHT Button
Text HLabel 8100 5100 0    60   Input ~ 0
D4
Text Notes 6850 5150 0    60   ~ 0
Temperature sensor(s)
Text HLabel 8100 5300 0    60   Input ~ 0
D6
Text Notes 7400 5350 0    60   ~ 0
Tx to WiFi
Text HLabel 8100 5000 0    60   Input ~ 0
D3
Text Notes 7250 5250 0    60   ~ 0
Rx from WiFi
Text Notes 7250 5050 0    60   ~ 0
Load control
NoConn ~ 9100 5500
NoConn ~ 9100 5600
NoConn ~ 9100 5700
NoConn ~ 9100 5800
Text HLabel 9100 5200 2    60   Input ~ 0
A3
Text HLabel 8100 5400 0    60   Input ~ 0
D7
Text HLabel 8100 5500 0    60   Input ~ 0
D8
NoConn ~ 8100 5800
NoConn ~ 8100 5900
NoConn ~ 9100 5900
NoConn ~ 9100 4500
NoConn ~ 8100 4500
NoConn ~ 8100 4600
Text HLabel 2000 6800 0    60   Input ~ 0
D5
Text HLabel 4400 6900 0    60   Input ~ 0
A3
Text HLabel 4100 6800 0    60   Input ~ 0
RST
$Comp
L GND #PWR12
U 1 1 5A54C41C
P 9550 4600
F 0 "#PWR12" H 9550 4350 50  0001 C CNN
F 1 "GND" H 9550 4450 50  0000 C CNN
F 2 "" H 9550 4600 50  0001 C CNN
F 3 "" H 9550 4600 50  0001 C CNN
	1    9550 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 4600 9550 4600
Wire Wire Line
	9100 4800 10400 4800
Text HLabel 10400 4800 2    60   Input ~ 0
+5V
Text HLabel 7850 1700 0    60   Input ~ 0
D3
$Comp
L Fuse F1
U 1 1 5A5604C3
P 9400 3000
F 0 "F1" V 9480 3000 50  0000 C CNN
F 1 "Fuse 5A" V 9325 3000 50  0000 C CNN
F 2 "" V 9330 3000 50  0001 C CNN
F 3 "" H 9400 3000 50  0001 C CNN
	1    9400 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	9550 3000 10000 3000
Wire Wire Line
	6700 3000 6800 3000
Wire Wire Line
	6800 3000 7100 3000
Wire Wire Line
	7100 3000 7400 3000
Wire Wire Line
	7400 3000 9250 3000
Text Notes 9700 2900 0    99   ~ 0
Vbb
Connection ~ 2100 2400
$EndSCHEMATC
