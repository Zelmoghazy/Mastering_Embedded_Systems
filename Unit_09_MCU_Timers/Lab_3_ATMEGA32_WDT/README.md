## Watchdog Timer
* The WDT is a timer counting cycles of a separate on-chip 128kHz oscillator.
*  The WDT gives an interrupt or a system reset when the counter reaches a given time-out value.
* In normal operation mode, it is required that the system uses the WDR - watchdog timer reset - instruction to restart the counter before the time-out value is reached.
* If the system doesn't restart the counter, an interrupt or system reset will be issued.