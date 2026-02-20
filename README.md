# IR-Remote-Controlled-Binary-Decimal-Counter
This project implements an IR remote–controlled digital counter using an Arduino, displaying the count in binary (LEDs + LCD) and decimal (7-segment via CD4511). The counter can be incremented, decremented, or reset using an IR remote, making it a great demonstration of digital I/O, external IC interfacing, and user input handling.

**How It Works:**
The IR receiver listens for button presses from the remote. Each button sends a unique hexadecimal IR code.
**Based on the button:**
Increment counter
Decrement counter
Reset counter

**The counter value is:**
Converted to binary and sent to LEDs + CD4511
Displayed on the LCD in both decimal and binary formats
