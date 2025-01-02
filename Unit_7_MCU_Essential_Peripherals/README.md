# GPIO

<p align="center">
  <img src="./Images/GPIO.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

# Output Configuration
## Push-Pull Mode

<p align="center">
  <img src="./Images/PushPull.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

## Open Drain Mode

<p align="center">
  <img src="./Images/OpenDrain.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

# Input Configuration

<p align="center">
  <img src="./Images/Input.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

## Floating state Input Mode
* Whenever the microcontroller is powered ON, the GPIO pins are by default in this HIGH impedance state input mode. 
    * You only want to configure a pin as floating if you know it will be driven externally such as in an input mode. 
    * It is recommended to keep the unused pins in either a pull-up or pull-down state to avoid leakage of current.
* Pull-up and pull-down are used to ensure the input pin has a valid high (logic 1) or a valid low (logic 0) when the external circuit does not drive the pin.
    * **pull-up:** the pin is internally connected to the power supply via a resistor and is always read as high (logic 1) unless the external circuit drives this pin low.
    * **pull-down:** the pin is internally connected to the ground via a resistor, The pin is always read as low (logic 0) unless the external circuit drives this pin high.

<p align="center">
  <img src="./Images/pur.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

<p align="center">
  <img src="./Images/pdr.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

* **Note that :**
* When a pin is internally pulled up, but the external circuit drives the pin low, a pull-up current is generated and is drawn internally from the processor chip.
* When a pin is pulled down within the chip, but the external circuit drives the pin to high, a pull-down current is drawn to the processor chip.
    * To limit the pull-up/pull-down current, the internal resistors usually have a large impedance
* When an external circuit connected to a GPIO pin has a fair amount of capacitance, the process of pulling the pin voltage to the level of logic high or logic low takes a long time because the impedance of the pull-up and pull-down resistors is too large.
    * The internal pulling often does not meet the speed requirement for fast communication protocols, such as I2C. To change the pin voltage rapidly,

## Shmitt triggered input

* A Schmitt trigger is a voltage comparator that turns ON only when the input voltage gets pass an upper threshold and once running it will turn OFF only when the input voltage goes below the lower threshold.
* a Schmitt triggered input is useful in noisy environments.

<p align="center">
  <img src="./Images/Schmitt.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

---

## Case Study : STM32

<p align="center">
  <img src="./Images/stm32_input.png"
       width="100%" "/>
</p>

<p align="center">
  <img src="./Images/stm32_output.png"
       width="100%" "/>
</p>
