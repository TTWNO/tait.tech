---
layout: default
title: "Ideas"
---
# Ideas

## 1. Accessible BIOS

Some server motherboards include serial UART/I<sup>2</sup>C ports which can be used to manage a BIOS via serial.
If this is possible, would it be able to attach to a braille display via an intermediary like a Rockchip/Pi SBC or Arduino compatible chip using [BRLTTY](https://brltty.app) and serial input from the motherboard?
Maybe not as it [appears to require](https://tldp.org/HOWTO/Remote-Serial-Console-HOWTO/rhl-biosserial.html) a full Unicode terminal, which I have the suspicion that BRLTTY will not be able to automatically filter out the formatting characters.

I found one paper referencing the (in)accessibility of BIOS, specifically UEFI BIOS from Brazil.
I have downloaded the paper and uploaded it here for reference.
[PDF of "UEFI BIOS Accessibility for the Visually Impaired"](/assets/pdf/bios-accessibility.pdf).

After emailing the authors of the paper, I found out that one of them, Rafael Machado, was able to get a song playing in UEFI as a part of his masters.
Here is a link to the Github [Msc UEFI PreOS Accessibility](https://github.com/RafaelRMachado/Msc_UefiHda_PreOs_Accessibility);
he has links to YouTube videos where he is shown playing a song on an ASUS laptop with PCIe connected speakers: [Song Playing in UEFI](https://www.youtube.com/watch?v=2De9dI9WbwM)

I have downloaded and played around with his Github project but to no avail.
Either I am not setting it up correctly, or I do not have the proper sound setup, but in any case no sound plays from either my laptop or desktop.

This requires more research and investment to understand UEFI, HDA audio, what systems have it and how to work with words and other sounds.

## 2. Terminal-oriented browser

Use selenium to allow a cross-engine compatible terminal-browser with JS support. Yes, sure, it has all the bloat of the modern web as it uses the full code of Chrome/Firefox/Webkit---but at least it can be used in the terminal.
Guaranteed to be accessible.

I'm thinking of similar key commands to Orca/NVDA but output is send to the terminal. Unsure of how to handle aria-live regions, but perhaps a queue could be used to print text. Unsure how to calculate delay as the user may be using a screen reader at different speeds and/or a braille display.

Change backend on-the-fly with a page reload. So if a website doesn't work with Webkit, load it in Firefox with a key command.

Just an idea.
