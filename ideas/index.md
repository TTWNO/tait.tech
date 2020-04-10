---
layout: default
---

## Ideas

### 1. Accessibility Ideas

#### 1.1 BSD Accessibility

An Open/FreeBSD driver to make bootup and shutdown (as well as any plain tty) accessible by visually impaired users.
Speech and/or braille display.

The console is the perfect interface for visually impaired users,
as the console is required to be text based (damn you ncurses!).

##### Inspiration: [Speakup](http://linux-speakup.org/)

#### 1.2 BSD/Linux Braille Notetakers

Use standard UNIX tools and command line interface instead of custom
systems for each notetaker.

Being able to use standard utilities not only helps with transferable skills,
but it also opens up the world of Linux tools to visually impaired users.
Enabling them to use any tool compatible with the command line,
not just any tool installed on their system or written for their device.

I have the suspicion that the fancier notetakers are using Windows at this point.
But for low-cost braille notetakers, it certainly could be plausible.

#### 1.3 Raspberry Pi-based notetaker

This could potentially decreese the size and expense of notetakers,
and if running a \*NIX
system would also integrate well with idea 1.2

Would need to:
1. Find a manual for controlling a braille display.
2. Implement a driver within the raspberry pi Raspbian OS using USB/gpio.
3. Package it up.

With the Linux Speakup project already written, would this mean I
could just plug a RPi up to a braille display and be on my merry way?

### 2. *NIX Ideas

#### 2.1 Fan/Sensor Driver for My Old Toshiba

FreeBSD and Linux both have the right driver for sensing my CPU
temp/spinning my fan properly.

OpenBSD does not have this working, and it is annoying to run it this way.
Full fans at all times on OpenBSD.

#### 2.2 ZFS NAS

I would really like to setup my own NAS with the ZFS file system.
I'd want to chronicle the adventure of finding hardware,
setting up OS, ZFS, frontend.

#### 2.3 Mirror Important Open-Source Projects

Setup a mirror for OpenBSD, Arch Linux, and other important projects
I want to contribute to where I know my level of coding is not helpful.

##### Also considering: [Tor Relay](https://community.torproject.org/relay/), [Void Linux](https://voidlinux.org/download/#mirrors)

#### 2.4 Systemd Service Randomizer

Systemd can start a VPN on startup with the following command:

`systemctl enable wg-quick@mullvad-ca1`

or 

`systemctl enable openvpn-client@mullvad_ca`

These commands are nice, but why is there not a `openvpn-client@random` so that I can randomize out of the possible files?

I am sure there would be a way to have a systemd service envoked like so:

`systemctl enable random@[wg-quick|openvpn-client]`

This would enable a randomization service for that interface, relinking
the boot-time process by looking in the directory the VPN interface
should be looking in, and chosing a random file.

Very useful for VPN clients. I have no idea if this has currency anywhere else.

### 3. Language Ideas

#### 3.1 Add Zhuyin Support for [epub-with-pinyin](https://github.com/TTWNO/epub-with-pinyin)

It currently only supports Pinyin.
At the time, HTML `<ruby>` support was low,
and so even when implemented properly the characters showed at the top.
They should be shown on the left hand side.

#### 3.1.2 Make [epub-with-pinyin](https://github.com/TTWNO/epub-with-pinyin) Easier To Use

Currently it requires setting up Python and some libraries.

Ideally it could be a web application, executing in Javascript.
Storing .epub files on a webserver even temporarily (especially if they are copywrited) is 
a legal risk I am not willing to take.

#### 3.2 Look Into [LinQ](https://www.lingq.com/en/)

I have heard this system implements something very similar to an idea I had called "Minks".

The general idea was that you could save words you knew,
thus stopping their pronunciation to appear above them (Pinyin/Zhuyin).

Given my interest in similar things, possibly apply to work for them,
or encourage them to BSD some of their libraries. 

### 4. Other Crazy Ideas

#### 4.1 Podcast: Not Sure What About

I've always wanted to interview people.
Seems liks fun.

