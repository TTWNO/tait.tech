---
title: "Orca, Emacspeak and Chromium Accessibility on A Raspberry Pi Running Manjaro ARM"
keywords: "orca linux raspberry-pi rpi raspberry pi screen reader screen-reader 64 bit 64-bit 64bit aarch64 emacs emacspeak manjaro manjaro-arm manjaro-aarch64"
layout: post
draft: true
---

I wanted to get a gift for my blind friend who has been interested in learning Linux for a while now.
Just when I was about to start looking for a gift I decided to take a look at [Brian Lunduke's newest video](https://lbry.tv/@Lunduke:e/raspberry-pi-400-looks-rad:c) featuring the [Raspberry Pi 400](https://www.raspberrypi.org/products/raspberry-pi-400/?resellerType=home).
The Raspberry Pi 400 has come full circle in terms of computing.
It is a keyboard. All the computing is done from within the keyboard.
Much like the Comodore64, this computer comes without a screen but is still technically fully functional without one.
I had my 'Aha!' moment and decided that could be a very cool gift. 

## Distribution

I wanted to choose something which will age well, and run the latest and greatest.
Some Raspberry Pi Orca installation guides [like this one](https://techesoterica.com/getting-the-orca-screen-reader-working-on-a-raspberry-pi-4-with-raspbian-buster-and-the-mate-desktop/),
have actually asked the user to _compile from source_ to get the latest Orca version due to how out-of-date Debian's package repositories are.
A distribution which has none of these fusses was top priority,
especially because Orca receives a lot of updates and it would make sense to not lag behind for the most critical piece of software.

I decided to go with [Manjaro ARM Xfce](https://manjaro.org/download/#raspberry-pi-4-xfce):

* Xfce is lightweight (especially good for a VI user who will be using the screen reader).
* Runs the 64-bit kernel instead of Raspberry Pi OS's 32-bit kernel.
* Is based on Arch Linux, so receives very frequent package updates.
* Has the AUR ([with some effort](#aur), as we'll see).

The only downside of Manjaro ARM, and likewise other Aarch64 architecture kernels is that it did not have HEVC nor H264 hardware decoding available.
Apparently this is getting mainlined in Linux kernel 5.10, but I still don't quite understand how it works as using 5.10-rc4 did not activate it.
I suppose time will tell by end of year how this will be implemented.

## Orca

The minimum requirement for a visually impaired desktop Linux user is a screen reader.
The most used screen reader for Linux is Orca, headed by the [GNOME Project](https://wiki.gnome.org/Projects/Orca).
This is relatively easy to install with standard `pacman` commands.

<pre class="terminal">
# pacman -S orca
</pre>

If logged in via SSH, you can start Orca with the `orca` command. This will start reading the screen to you so you can do the next parts.

To activate Orca on login and on LightDM activation, add it to the LightDM GTK+ Greeter Settings application on the Misc. menu.
This will start it when the LightDM login system starts.

LightDM's Orca will not help us once we are logged in however.
To activate Orca on login, open the Session And Startup application, and add Orca to the "startup" list of apps.

### TODO: add commands

And now Orca will be activated on boot and login.

## AUR

To get the AUR working, we need to install the `pacaur` helper.
This merited its own article, so check that out here:

[How to Install Pacaur on Manjaro ARM](/2020/12/01/pacaur-rpi.html)

## 
