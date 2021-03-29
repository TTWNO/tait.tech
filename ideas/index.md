---
layout: default
title: "Ideas"
---
# Ideas

## 1. Accessible BIOS

Some server motherboards include serial UART/I<sup>2</sup>C ports which can be used to manage a BIOS via serial.
If this is possible, would it be able to attach to a braille display via an intermediary like a Rockchip/Pi SBC or Arduino compatible chip using [BRLTTY](https://brltty.app) and serial input from the motherboard?
Maybe not as it [appears to require](https://tldp.org/HOWTO/Remote-Serial-Console-HOWTO/rhl-biosserial.html) a full Unicode terminal, which I have the suspicion that BRLTTY will not be able to automatically filter out the formatting characters.

Just an idea.


## 2. Terminal-oriented browser

Use selenium to allow a cross-engine compatible terminal-browser with JS support. Yes, sure, it has all the bloat of the modern web as it uses the full code of Chrome/Firefox/Webkit---but at least it can be used in the terminal.
Guaranteed to be accessible.

I'm thinking of similar key commands to Orca/NVDA but output is send to the terminal. Unsure of how to handle aria-live regions, but perhaps a queue could be used to print text. Unsure how to calculate delay as the user may be using a screen reader at different speeds and/or a braille display.

Change backend on-the-fly with a page reload. So if a website doesn't work with Webkit, load it in Firefox with a key command.

Just an idea.
