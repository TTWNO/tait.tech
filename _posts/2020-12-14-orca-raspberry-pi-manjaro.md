---
title: "Orca, Emacspeak and Chromium Accessibility on A Raspberry Pi Running Manjaro ARM"
keywords: "orca linux raspberry-pi rpi raspberry pi screen reader screen-reader 64 bit 64-bit 64bit aarch64 emacs emacspeak manjaro manjaro-arm manjaro-aarch64"
layout: post
draft: true
---

I wanted to get a gift for my blind friend who has been interested in learning Linux for a while now.
Just when I was about to start looking for something I decided to take a look at [Brian Lunduke's newest video](https://lbry.tv/@Lunduke:e/raspberry-pi-400-looks-rad:c) featuring the [Raspberry Pi 400](https://www.raspberrypi.org/products/raspberry-pi-400/?resellerType=home).
The Raspberry Pi 400 has come full circle in terms of computing.
It is a keyboard. All the computing is done from within the keyboard.
Much like the Comodore64, this computer comes without a screen but is still technically fully functional without one.
I had my 'Aha!' moment, and decided that the Raspberry Pi 400 would be a very cool present. 

## No Headphone Jack

My first problem was that the Raspberry Pi 400 does not come with a headphone jack,
even though every other Raspberry Pi A/B/B+ board with the exception of the compute modules and Zero series have included one.
That said, the Raspberry Pi audio jacks are also known to crackle and pop due to either bad drivers or cheap manufacturing.

To compensate, I got an external USB audio card.
I ended up going with the [DuKabel USB to 3.5mm Jack Adapter (Amazon)](https://www.amazon.ca/DuKabel-ProSeries-Mic-Supported-Headphone-External/dp/B07RS11M1T/).

There are cheaper options for sure, but when I was looking around Raspberry Pi forums and Amazon reviews, this specific model seemed to come out on top in terms of performance.
It costed me around 40 Canadian dollars.
I figure this isn't too bad considering my friend doesn't need a screen, haha!

## Distribution

I wanted to choose something which will age well, and run the latest and greatest.
For visually impaired users, the most important piece of software is the screen reader. If the screen reader doesn't work, the rest of the work is toast!
Some Raspberry Pi Orca installation guides [like this one](https://techesoterica.com/getting-the-orca-screen-reader-working-on-a-raspberry-pi-4-with-raspbian-buster-and-the-mate-desktop/),
have actually asked the user to _compile Orca from source_ to get the latest version due to how out-of-date Debian's package repositories are.
A distribution which has none of these fusses was top priority,
especially because Orca receives frequent updates.

I decided to go with [Manjaro ARM Xfce](https://manjaro.org/download/#raspberry-pi-4-xfce):

* Xfce is lightweight.
* Runs a 64-bit kernel.
* Is based on Arch Linux, so receives very frequent package updates.
* Has the AUR ([with some effort](#aur), as we'll see).

The only downside of Manjaro ARM, and likewise other Aarch64 (ARM 64-bit) architecture kernels is that it did not have HEVC nor H264 hardware decoding available.
Apparently, support for the Raspberry Pi's VC4 graphics is getting mainlined [in Linux kernel 5.10](https://www.debugpoint.com/2020/12/linux-kernel-5-10-features/).
Unfortunately, running the release candidate (RC) kernel did not make the Raspberry Pi 400 use hardware decoding.
Perhaps other applications like `ffmpeg` and Chromium need to add support as well before this works.

## Orca

As stated before, minimum requirement for a visually impaired desktop Linux user is a screen reader.
The most used screen reader for Linux is Orca, headed by the [GNOME Project](https://wiki.gnome.org/Projects/Orca).
This is relatively easy to install with a standard `pacman` command.

<pre class="terminal">
# pacman -S orca
</pre>

If logged in via SSH, you can start Orca with the `orca` command. This will start reading the screen to you so you can do the next parts.

To activate Orca on login with LightDM, enable it in the 'LightDM GTK+ Greeter Settings' application. The 'Misc.' tab will have a drop-down for asking which screen reader you want to use.
This will start Orca when the LightDM login system starts.

LightDM's Orca will not help us once we are logged in however.
To activate Orca on login, open the 'Session And Startup application' program, then add Orca to the "startup" list of apps.

And now Orca will be activated on boot and login.

## AUR

The AUR, or the Arch User Repository has community maintained and distributed packages.
Basically, you download a file which will tell your computer how to download, build and install a package for you.

To get the AUR working in a more automatic way, we need to install the `pacaur` helper.
This merited its own article, so check that out here:
[How to Install Pacaur on Manjaro ARM]({% post_url 2020-12-01-pacaur-rpi %})

The TL;DR is that we need to open the `/etc/makepkg.conf` file and replace any mention of `-march=armv8-a` with `-march=armv8-a+crypto`.

This can be done as a oneliner, thanks to the `sed` command.

<pre class="terminal">
# sed -i 's/-march=armv8-a/-march=armv8-a+crypto/' /etc/makepkg.conf
</pre>

## Emacspeak

[Emacs](https://www.gnu.org/software/emacs/) is a scriptable document editor run by the [GNU Project](https://gnu.org/).
Infamous for its high learning curve though it may be,
there is a very extensive speech extension for it called [Emacspeak](http://emacspeak.sourceforge.net/).
Emacspeak is built entirely by [T. V. Ramen](https://tvraman.github.io/vita/resume.html) and has been freely available since its inception in 1999.
Due to its age (and thus maturity), Emacspeak is an important tool in any "eyes-free" software developer toolkit.

Lucky for me, Emacspeak appears to not only to be available in the AUR,
but also compilable with the Aarch64 architecture---the architecture of the Raspberry Pi 400.
So this is as easy to install as:

<pre class="terminal">
$ pacaur -S emacspeak
</pre>

## Web Browsers

I'll cover a couple web browsers here based on how they worked.

### Firefox

Firefox will run in accessibility mode with [caret browsing](https://en.wikipedia.org/wiki/Caret_navigation) enabled automatically when it detects Orca is running.
This makes Firefox _by far_ the best browser for the job.

### Chromium

Chromium... Ugh. So it works, sort of.
You need to enable two special flags, and add an environment variable.

To do this, I suggest editing the main profile in `/etc/profile`.
Add the following line to the end of that file:

<pre class="file">
export ENABLE_ACCESSIBILITY=1
</pre>

Next, add two flags to the `$HOME/.config/chromium-flags.conf` file.

<pre class="file">
--force-renderer-accessibility
--enable-caret-browsing
</pre>

You will need to relog to set the ENABLE_ACCESSIBILITY environment variable. Now Chromium should work with Orca.

### Badwolf

The [Badwolf browser](https://www.mankier.com/1/badwolf)
is based on the WebkitGTK engine, as opposed to Firefox's Gecko and Google's Blink engines.
It _almost_ works out of the box. It is really fast compared to the other two,
but it lacks some features like announcing a page is done loading and it doesn't appear to support caret browsing,
which will cause some other problems.
Interesting though for such a young browser to have a minimal level of accessibility so early!

I would be interested where this goes in the future.

## P.S.

Somehow I forgot that you would need to setup the dummy display driver to work with the graphics without a display attached.
To do this, install the `xf86-video-dummy` pacakge:
<pre class="terminal">
# pacman -S xf86-video-dummy
</pre>

Next, override any `/etc/X11/xorg.conf` you may have with this:

<pre class="file">
Section "Monitor"
	Identifier "Monitor0"
	HorizSync 28.0-80.0
	VertRefresh 48.0-75.0
	# https://arachnoid.com/modelines/
	# 1920x1080 @ 60.00 Hz (GTF) hsync: 67.08 kHz; pclk: 172.80 MHz
	Modeline "1920x1080_60.00" 172.80 1920 2040 2248 2576 1080 1081 1084 1118 -HSync +Vsync
EndSection

Section "Device"
	Identifier "Card0"
	Driver "dummy"
	VideoRam 256000
EndSection

Section "Screen"
	DefaultDepth 24
	Identifier "Screen0"
	Device "Card0"
	Monitor "Monitor0"
	SubSection "Display"
		Depth 24
		Modes "1920x1080_60.00"
	EndSubSection
EndSection
</pre>

Now, when you boot, you should head 'Screen reader on'.

## Conclusion

It took a bit of messing around to get this working, but I'm glad I did!
Now I can nerd out with another Linux friend and given how well they seem to find problems with accessibility, hopefully a few upstream patches can be made.

Happy hacking, for everyone!
