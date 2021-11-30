---
layout: default
title: "Ideas"
---
# Ideas

## 1. Accessible BIOS

Update:
See my blog post with the guy who's writing the [new audio driver into EDK2](/2021/06/21/uefi-audio/).

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

## 3. Dead Simple Chess App

I want to make a simple chess app which can connect to multiple backends
(i.e. Lichess, Chess.com, etc.) and then users can use one app to play many games.
This should be quite simple given how easy the lichess API is, and the [chess.com API](https://www.chess.com/news/view/published-data-api) coming soon!

> This is read-only data. You cannot send game-moves or other commands to Chess.com from this system. ***If you wish to send commands, you will be interested in the Interactive API releasing later this year.***

## 4. Open-Source VPN Deployment System

Help my business and others start their own.

* Update active servers with pings from said server. Encrypt with GPG to verify, send over HTTPS. Use sub-keys (?) so they may be revoked anytime. Use token to login server.
* Ability to create new tokens with no priviledges; only to say "Hi I'm still here."
* All IP address changes need to be manually approved.
* Status queries, must be logged in: POST /status/[id/] should give back info about:
  * Number of connections.
  * Level (paid, free, plus when I can find out how to get Netflix working).
  * Protocol (OpenVPN/Wireguard). Wireguard should be default.
  * Max throughput (i.e. 1Gb/sec, 100Mb/sec)
  * Current average throughput over last minute, 15 minutes, hour and day. (i.e. 15Mb/sec 12Mb/sec)
* Decide server: POST /new/[coutnry_code/] should send a response of a possible server to connect to (or even the full Wireguard file possibly)
* Get server files: POST /download/[country_code/[number/]] return the wireguard config file for that region, or a zip file containing the group of them.
* A client would be able to use a native wireguard client on linux (i.e. store in `/etc/wireguard` (or its default location).
* A client would allow local options like blocking LAN, kill-switch support, and the ability to change your VPN region based on latest list of servers.
* The list of servers will be updated manually with `bt update`.

I love this idea, but unfortunately, Canada has data retention laws that would stop me from protecting the privacy of anyone using a system delivered by me.
Unless I incorporate in Switzerland or the Seychelles, this is not a viable option.
Doing the above costs a fair amount in up-front investment that I am not willing to make at this point in time.

## 5. 3d printing of Google Maps/OpenStreetMaps data for the visually impaired.

A larger project, to be sure, but one I think could be of interest.
Imagine being able to download some data from Google or OpenStrretMaps,
then put it into a program and have it generate a 3d map which can be printed.
Unsure what to do, as the braille overlay on top of the streets and important buildings, etc. needs to be of a uniform size (braille cannot be scaled) but the buildings, streets, and parks do need to be scaled in size.

I think for beginning, forget the braille entirely and simply product a map.
This can be done in the STL file format or some intermediary if that is easier.
Roads will have a slight border on the side,
parks will have a diamond texture,
buildings will have slight rectangular borders (slightly wider than the roads),
paths will be a thin line, and the label for the path will need to extend the thin line into a (rounded) rectangle with text on it. 

Start with roads.
Get a road, get it to generate the correct shape.
Then add a border around the side.
Then, add 4 more roads and figure out how to intersect them.

If it can be done on a display, it can be done in a file.

Start with that. Wow what a daunting project!

This is being worked on through the [touch-mapper](https://github.com/skarkkai/touch-mapper) project.
They do not, however, have labels yet.

## 6. 3D Printed Binary Trees

A simple hub/connection system to connect nodes of a binary tree together to have a physical object for visually impaired computer science students to use for initial introduction into the subject of (binary) trees.

## 6.5 Javascript Binary Trees

Have a simple module for loading in an SVG of a tree, along with Javascript to make the diagram accessible by jumping left/right with the arrow keys and up to a parent with the up arrow.

## 7. Lego/Pi-Powered Logic Gates

Lego or 3d printed logic gates with physical switches for in and out.
Again, sore of as an introductory tool for blind students learning computer science.

## 8. More Tutorials/Materials

Perhaps a broader selection of materials for computer science students with proper transcriptions for everything in this list:

* UML diagrams
* UML sequence diagrams
* Gantt charts
* Advanced math equations
* Stacks, Queues and Linked Lists
* Memory layout tables
* Logic gate diagrams
* Decision charts; I think I could add some macros on top of 
* Timing diagrams (i.e., watching the state of various inputs and outputs over time [usually in relation to a clock cycle]); my current idea for this is a dynamic audiogram where you can listen to the clock + any other tracks at the same time to "see" the diagram
* Circuit diagrams (not 100% relevant, but I have seen it in CS courses)
* Database tables as HTML tables
* Properly transcribed security content like buffer-overflows, underflows and similar things

Although developing these is good, I think it is worthwhile to also create tools that make creation of these easier for both sighted and blind individuals.
This will make it easier for course transcribers who are not tech-savy and will enable the blind student to create the diagrams and send them back to their teachers.
Preferably have a "plain text" version which can be rendered as an SVG for use by visual learners, then make sure the SVG can be accessible with a Javascript hook.
This would (in theory) make it possible for a teacher to create the graphic in the specialized tool for that kind of chart, put it in their slides/course info/textbook/whatever and have the student able to extract the SVG and paste it somewhere where a script could make it readable.
Yes, the best case is the teacher cooperates 100%, but considering that is never the case, I figure making it easier to convert between the two is the best I can hope for.

Some other things I would like to do, if I could find the time:

* How to get started with Linux.
* Text-based tutorials from start-to-finish with various frameworks: SpringBoot (Java), Django/Flask (Python), JavaEE.
* Specific programming language instruction in all the basics: C/C++, Bash, Python, Javascript, HTML, Java. Perhaps in the future branch into Rust, Golang, Zig or Haskell.
* Custom-made braille manuals for a set of affordable computer parts which can be purchased to assemble a computer from scratch, without sighted assistance (see [current status of accessible BIOSes](/2021/06/21/uefi-audio/)).

This would all be licensed as CC-BY-NC-SA.
I may drop the NC. As long as I have specified SA, then anyone (even for-profit companies) can use it as long as any changes are shared to the public as well.

