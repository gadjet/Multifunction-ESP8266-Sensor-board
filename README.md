# Multifunction-ESP8266-Sensor-board
AKA Wireless window/door sensor version 4

This is another in the series of wireless Window/Door sensor boards I've been designing, yes I know I've already published version 5 but this is the design before that one, I considered it a bit of a failure really because I was aiming for lower power consumption than version 3 but because I misread the LDO's specification I ended up using more power, around 85uA against the 20uA for version 3.

This board is different to version 3 because as well as being able to be triggered with a reed switch it also has the ability to have a button added to trigger the transmission instead or as well as the reed switch (doorbell?) also there is the mounting position to add an I2C sensor board such as the BME280 or AHT10 or even an OLED display or both.

The other key difference is the ability to power the ESP8266 from a Li-Ion cell (4.2v) via the LDO or directly from a 3V source such as a couple of AA cells, this bypasses the LDO completely.

There are also a couple of jumpers on the PCB for configuring the ADC input: -
 - JP1 is open circuit by default and when shorted out it modifies the voltage divider to increase the max ADC voltage to 14V, the LDO is capable of 16V input.
 - JP2 is short circuit by default and when open circuited it disconnects the ADC input from the voltage divider, used to monitor supply voltage, allowing the internal VCCread() function to be used in the code when powering the circuit directly from the 3V input.

Improvements that can be made
Use the previous LDO (HT7333) which uses less quiescent current
Power the Sensor board from a pin of the ESP so it's only powered up when used

              *********  PLEASE NOTE  *********

Some I2C boards do not have the same pinout so please check your I2C board has the same pinout as the PCB before using it.
