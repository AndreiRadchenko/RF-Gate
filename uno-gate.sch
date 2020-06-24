EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L arduino:Arduino_Uno_Shield XA?
U 1 1 5DF25C1D
P 3750 3700
F 0 "XA?" H 3750 5087 60  0000 C CNN
F 1 "Arduino_Uno_Shield" H 3750 4981 60  0000 C CNN
F 2 "" H 5550 7450 60  0001 C CNN
F 3 "https://store.arduino.cc/arduino-uno-rev3" H 5550 7450 60  0001 C CNN
	1    3750 3700
	1    0    0    -1  
$EndComp
$Comp
L Relay:DIPxx-1Cxx-51x K&
U 1 1 5DF48177
P 8250 3200
F 0 "K&" V 7683 3200 50  0001 C CNN
F 1 "Relay 2 (left leaf)" V 7774 3200 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 8700 3150 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 8250 3200 50  0001 C CNN
	1    8250 3200
	0    -1   -1   0   
$EndComp
$Comp
L Relay:DIPxx-1Cxx-51x K?
U 1 1 5DF577D6
P 8250 4250
F 0 "K?" V 7683 4250 50  0001 C CNN
F 1 "Relay 3 (Right leaf)" V 7774 4250 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 8700 4200 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 8250 4250 50  0001 C CNN
	1    8250 4250
	0    -1   -1   0   
$EndComp
$Comp
L Relay:DIPxx-1Cxx-51x K?
U 1 1 5DF577DC
P 8250 5350
F 0 "K?" V 7683 5350 50  0001 C CNN
F 1 "Relay 4 (Right leaf)" V 7774 5350 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 8700 5300 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 8250 5350 50  0001 C CNN
	1    8250 5350
	0    -1   -1   0   
$EndComp
$Comp
L Relay:DIPxx-1Cxx-51x K&?
U 1 1 5DF61A10
P 8250 2150
F 0 "K&?" V 7683 2150 50  0001 C CNN
F 1 "Relay 1 (left leaf)" V 7774 2150 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 8700 2100 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 8250 2150 50  0001 C CNN
	1    8250 2150
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7300 5050 7950 5050
Wire Wire Line
	7950 3950 7300 3950
Connection ~ 7300 3950
Wire Wire Line
	7300 3950 7300 5050
Wire Wire Line
	7950 2900 7300 2900
Connection ~ 7300 2900
Wire Wire Line
	7300 2900 7300 3950
Wire Wire Line
	7950 5250 7400 5250
Wire Wire Line
	7950 4150 7400 4150
Connection ~ 7400 4150
Wire Wire Line
	7400 4150 7400 5250
Connection ~ 7400 3100
Wire Wire Line
	7400 3100 7400 4150
Wire Wire Line
	7950 3100 7400 3100
Wire Wire Line
	7400 2050 7400 3100
Wire Wire Line
	7300 1850 7300 2900
Wire Wire Line
	7300 1300 7300 1850
Connection ~ 7300 1850
Wire Wire Line
	7950 1850 7300 1850
Wire Wire Line
	7950 2050 7400 2050
$Comp
L power:+12V #PWR?
U 1 1 5DF9664F
P 7300 1300
F 0 "#PWR?" H 7300 1150 50  0001 C CNN
F 1 "+12V" H 7315 1473 50  0000 C CNN
F 2 "" H 7300 1300 50  0001 C CNN
F 3 "" H 7300 1300 50  0001 C CNN
	1    7300 1300
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC_ALT M?
U 1 1 5DFA034D
P 9450 2600
F 0 "M?" H 9597 2596 50  0000 L CNN
F 1 "Motor_DC_ALT" H 9597 2505 50  0000 L CNN
F 2 "" H 9450 2510 50  0001 C CNN
F 3 "~" H 9450 2510 50  0001 C CNN
	1    9450 2600
	1    0    0    -1  
$EndComp
$Comp
L Motor:Motor_DC_ALT M?
U 1 1 5DFA1B40
P 9500 4650
F 0 "M?" H 9647 4646 50  0000 L CNN
F 1 "Motor_DC_ALT" H 9647 4555 50  0000 L CNN
F 2 "" H 9500 4560 50  0001 C CNN
F 3 "~" H 9500 4560 50  0001 C CNN
	1    9500 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1950 9450 1950
Wire Wire Line
	9450 1950 9450 2400
Wire Wire Line
	9450 2900 9450 3000
Wire Wire Line
	9450 3000 8550 3000
Wire Wire Line
	8550 4050 9500 4050
Wire Wire Line
	9500 4050 9500 4450
Wire Wire Line
	9500 4950 9500 5150
Wire Wire Line
	9500 5150 8550 5150
Wire Wire Line
	7050 2850 7050 2350
Wire Wire Line
	7050 2350 7950 2350
Wire Wire Line
	7050 2950 7050 3400
Wire Wire Line
	7050 3400 7950 3400
Wire Wire Line
	7000 3050 7000 4450
Wire Wire Line
	7000 4450 7950 4450
Wire Wire Line
	6950 3150 6950 5550
Wire Wire Line
	6950 5550 7950 5550
$Comp
L RF_Module:RXB6-REV08 RF_resiever
U 1 1 5DFF669D
P 6550 1700
F 0 "RF_resiever" H 6678 1446 50  0000 L CNN
F 1 "RXB6-REV08" H 6678 1355 50  0000 L CNN
F 2 "" H 6550 1700 50  0001 C CNN
F 3 "" H 6550 1700 50  0001 C CNN
	1    6550 1700
	1    0    0    -1  
$EndComp
Connection ~ 7400 5250
Wire Wire Line
	7400 5250 7400 5850
$Comp
L power:GNDD #PWR?
U 1 1 5DF7296F
P 7400 5850
F 0 "#PWR?" H 7400 5600 50  0001 C CNN
F 1 "GNDD" H 7404 5695 50  0000 C CNN
F 2 "" H 7400 5850 50  0001 C CNN
F 3 "" H 7400 5850 50  0001 C CNN
	1    7400 5850
	1    0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5E0015A4
P 6150 2250
F 0 "#PWR?" H 6150 2000 50  0001 C CNN
F 1 "GNDD" H 6154 2095 50  0000 C CNN
F 2 "" H 6150 2250 50  0001 C CNN
F 3 "" H 6150 2250 50  0001 C CNN
	1    6150 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2000 6250 2000
Wire Wire Line
	6150 2250 6150 2150
Wire Wire Line
	6150 2150 6250 2150
Wire Wire Line
	6250 1850 6150 1850
$Comp
L power:+5V #PWR?
U 1 1 5E019974
P 6150 1300
F 0 "#PWR?" H 6150 1150 50  0001 C CNN
F 1 "+5V" H 6165 1473 50  0000 C CNN
F 2 "" H 6150 1300 50  0001 C CNN
F 3 "" H 6150 1300 50  0001 C CNN
	1    6150 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 1300 6150 1850
Wire Wire Line
	5050 2850 7050 2850
Wire Wire Line
	5050 2950 7050 2950
Wire Wire Line
	5050 3050 7000 3050
Wire Wire Line
	5050 3150 6950 3150
Wire Wire Line
	5050 2650 5900 2650
Wire Wire Line
	5900 2000 5900 2650
$Comp
L power:GNDD #PWR?
U 1 1 5E02AF7A
P 1850 3000
F 0 "#PWR?" H 1850 2750 50  0001 C CNN
F 1 "GNDD" H 1854 2845 50  0000 C CNN
F 2 "" H 1850 3000 50  0001 C CNN
F 3 "" H 1850 3000 50  0001 C CNN
	1    1850 3000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1850 3000 1850 2900
Wire Wire Line
	1850 2900 1750 2900
Wire Wire Line
	2000 2050 2000 2600
Wire Wire Line
	4750 4750 5050 4750
$Comp
L power:+5V #PWR?
U 1 1 5E05BFCC
P 2000 2050
F 0 "#PWR?" H 2000 1900 50  0001 C CNN
F 1 "+5V" H 2015 2223 50  0000 C CNN
F 2 "" H 2000 2050 50  0001 C CNN
F 3 "" H 2000 2050 50  0001 C CNN
	1    2000 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 2750 2150 3850
$Comp
L RF_Module:RXB6-REV08 Current_sensor?
U 1 1 5E06BFA4
P 1500 4350
F 0 "Current_sensor?" H 1628 4096 50  0000 L CNN
F 1 "ACS 712 30A" H 1628 4005 50  0000 L CNN
F 2 "" H 1500 4350 50  0001 C CNN
F 3 "" H 1500 4350 50  0001 C CNN
	1    1500 4350
	-1   0    0    -1  
$EndComp
$Comp
L power:GNDD #PWR?
U 1 1 5E06BFAA
P 1900 4900
F 0 "#PWR?" H 1900 4650 50  0001 C CNN
F 1 "GNDD" H 1904 4745 50  0000 C CNN
F 2 "" H 1900 4900 50  0001 C CNN
F 3 "" H 1900 4900 50  0001 C CNN
	1    1900 4900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1900 4900 1900 4800
Wire Wire Line
	1900 4800 1800 4800
Wire Wire Line
	1800 4650 2300 4650
Wire Wire Line
	2300 4650 2300 3750
Wire Wire Line
	2300 3750 2450 3750
Wire Wire Line
	1750 2600 2000 2600
Wire Wire Line
	2000 2600 2000 4500
Wire Wire Line
	1800 4500 2000 4500
Connection ~ 2000 2600
Wire Wire Line
	2150 3850 2450 3850
$Comp
L RF_Module:RXB6-REV08 Current_sensor
U 1 1 5E02AF74
P 1450 2450
F 0 "Current_sensor" H 1578 2196 50  0000 L CNN
F 1 "ACS 712 30A" H 1578 2105 50  0000 L CNN
F 2 "" H 1450 2450 50  0001 C CNN
F 3 "" H 1450 2450 50  0001 C CNN
	1    1450 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1700 2750 1750 2750
Connection ~ 1750 2750
Wire Wire Line
	1750 2750 2150 2750
$Comp
L Relay:DIPxx-1Cxx-51x K&?
U 1 1 5EF179F1
P 6050 4200
F 0 "K&?" V 5483 4200 50  0001 C CNN
F 1 "Relay 5 (lamp)" V 5574 4200 50  0000 C CNN
F 2 "Relay_THT:Relay_StandexMeder_DIP_LowProfile" H 6500 4150 50  0001 L CNN
F 3 "https://standexelectronics.com/wp-content/uploads/datasheet_reed_relay_DIP.pdf" H 6050 4200 50  0001 C CNN
	1    6050 4200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5050 3250 5400 3250
$Comp
L Device:Lamp LA?
U 1 1 5EF374CD
P 6600 3700
F 0 "LA?" H 6728 3746 50  0000 L CNN
F 1 "Lamp" H 6728 3655 50  0000 L CNN
F 2 "" V 6600 3800 50  0001 C CNN
F 3 "~" V 6600 3800 50  0001 C CNN
	1    6600 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 4100 5800 4100
Wire Wire Line
	5400 4400 5750 4400
Wire Wire Line
	5400 3250 5400 4400
Wire Wire Line
	6350 4000 6600 4000
Wire Wire Line
	6600 4000 6600 3900
Wire Wire Line
	5750 3900 5600 3900
Wire Wire Line
	5600 3900 5600 3450
Wire Wire Line
	5600 3450 5850 3450
Wire Wire Line
	6600 3500 6600 3450
Wire Wire Line
	6600 3450 6250 3450
Text Label 5950 3450 0    50   ~ 0
220V
$EndSCHEMATC
