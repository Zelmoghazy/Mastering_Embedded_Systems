![alt text](./images/NVIC.png)

* **Clock Security System (CSS):** is a self diagnostic peripheral that detects the failure of the external clock, called HSE.
    * If this happens, HSE is automatically disabled (this means that the internal HSI is automatically enabled) and an NMI interrupt is raised to inform the software that something is wrong with the HSE.

<p align="center">
  <img src="./images/Vector.svg"
       width="100%" 
       style="border-radius: 30px;"/>
</p>
