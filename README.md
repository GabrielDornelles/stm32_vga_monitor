# STM32F446RE VGA Display
--------------
Displaying data  in VGA Monitor using the stm32f4 microcontroller.

Following data is about 800x600@60hz signal on VGA.
## Horizontal timing (line)
Polarity of horizontal sync pulse is positive.

|Scanline part	|Pixels	|Time [µs]|
|----------|:----------:|:----------:|
Visible area	|800|		20
Front porch		|40|		1
Sync pulse		|128|		3.2
Back porch		|88|		2.2
Whole line		|1056|	26.4

## Vertical timing (frame)
Polarity of vertical sync pulse is positive.

| Frame part | Lines | Time [ms] |
|----------|:----------:|:----------:|
Visible area	|600|		15.84
Front porch		|1|		0.0264
Sync pulse		|4|		0.1056
Back porch		|23|		0.6072
Whole frame		|628|		16.5792


## Timers for sync:
Microcontroller clock is 84mHz
For a 1 second timer we need two values that multiplied will be 84mhz, like 42000 and 2000.
The equation to create a timer of x hz is:

x = 84mhz/arr*psc

where:
psc = Prescaler
arr = AutoReload Register (counter period)

I wrote simple Python script to find values that would be closest to integer.
### H-Sync(TIM10-PC0):
	Whole line takes 26.4µs, which is 37.878787878788 kHz
	
	37.87 kHz = 84mhz/arr*psc
	arr*psc = 84mHz/37.87kHz
	arr*psc = 2217.6
	
	I'll choose arr=738, cause 2217.6/738 is 3.004, which is really close to 3, and we can only pick integer values
	then: arr=738 psc=3
	
	Turns out I realized we need a half cycle timer to toggle the pin properly so:
	
	13.2µs, which is 75.75757576 kHz
	75.76 kHz = 84mhz/arr*psc
	arr*psc = 84mHz/75.75kHz
	arr*psc = 1108.8
	(everything is half but here's the calculations just in case you think its not)
	then  arr=370 psc=3 (370*3=1110) better more than less

### V-Sync (TIM11-PC1): 
	Whole frame takes 16.5792ms, which is 60.316hz
	
	60.316 = 84mhz/arr*psc
	arr*psc = 84mHz/60.316
	arr*psc =1,392,665.296
	9877*141.0008 = 1,392,665.296
	then: arr=9877 psc=141
	
	half cycle:
	arr*psc =1,392,665.296/2=696,332.648
	then: arr=9808 psc=71
	

**Note: we always take -1 from arr and psc**
	
