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
* You only want to configure a pin as floating if you know it will be driven externally. 
* Otherwise, It is recommended to keep the unused pins in either a pull-up or pull-down state to avoid leakage of current.

<p align="center">
  <img src="./Images/pdrpur.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>

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
