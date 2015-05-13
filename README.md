# arduino-lightbar 

This code drives a set of daisy chained 74HC595 shift registers to light scoring poles for an exhibition display. 

The clear pin isn't required as we drive 256 zeros through the chain to clear it. Because of this we only need three signal wires with +5v and ground to drive as many score poles in sequence as we like. External power is required to drive the LEDs as 10mm extra bright modules were used.
