---
title: "Pinebook Pro, The Ultimate ARM Laptop"
layout: post
---

I recently got my Pinebook Pro.
It was more expensive than I was expecting, coming in at (including shipping and handling) at C$335.
I always forget the exchange rate and assume it's similar to the U.S. dollar, but it never is, haha!
Anyway, this is just my first impressions and what I did to fix a few issues.

## Initial Impressions

My first impressions of this are quite good.
I like the keyboard; it is firm and not mushy for the price.
It actually has a similar keyboard to my school-supplied Dell, which I quite enjoyed typing on.
The shell is aluminium and doesn't feel *too* cheap, but I should note that it sure doesn't feel like a Macbook if that's what you're expecting.
All in all build quality seems pretty good for a product in this price range.
I'm actually using it right now to write this article, and I'm actually typing faster than I would on my desktop.

The screen is bright enough and has anti-glare applied to it. I can use it with moderate light behind me, but not a sunset. Decent, and I can't even use my phone with a sunset right on it, so that's not a huge loss at all as I think my phone costs more than this haha!

The trackpad is fine.
I don't use the mouse very often, and if I need it I'm more likely to bring an external one.
It works for what I need though.
I can't seem to get the glossy protector off the trackpad though so maybe it would be better if I did haha!

The temperatures are okay. I would consider them not ideal.
The left side closer to the hinge can get quite warm when I push it.
To be expected in some respects, but the metal case certainly makes the heat come out fast and hot!
It is also passively cooled, so a bit of heat makes sense and is reasonable.
I wonder if I could mod this to have an active low-profile fan?
A project for later, I suppose.

The keyboard is pretty standard for a 14-inch laptop.
No numpad (except with function key), has F1-12 and media keys using function+F1-12.
Screen brightness, sound up, down and mute, and num and scroll lock.
These seem to work no matter what distribution you have (I've used Manjaro KDE and Manjaro Sway).
Perhaps this would react differently on Arch for ARM with no key bindings.
I'm not sure if this is implemented in software or hardware.

The speakers and very tin-y and do not sound good at all.
That said, they look very replaceable, so I'll look into a mod in the future.
The Pinebook Pro comes with a headphone port, so you could just use that if the sound bothers you.

## Some suggestions

I had some issues when it first arrived.

1. Reboot did not work. The display would glitch out and show horizontal lines. It would only work after a full shutdown.
2. Booting would sometimes not work at all. My SD card would sometimes boot, sometimes not. eMMC would sometimes work and sometimes now. Sometimes I would even get to the login screen, or fully logged in before it decided to freeze/hang. I could "drop to console" (Ctrl+Alt+Fx), but it only made my mouse stop showing, it would not actually display a console. This problem was worse when not plugged in.
3. Performance was not stellar, even for the RK3399.
4. I don't like the Manjaro logo that displays during boot.

### Don't use KDE

KDE for me is a bit slow.
It is not a keyboard-driven desktop.
To give it some credit though, it does at least have zoom support built in; this is something I wish other desktops would have enabled by default.
I'm looking at your, Xfce.

I switched to Manjaro Sway, which is a Wayland-based i3-like tiling window manager.
I've used this on my Raspberry Pi 4, and it is by far my preference among other default distro configurations.

This can be done by flashing an SD card with any random Linux distro, then download [Manjaro Sway ARM for the Pinebook Pro]().

Quickly, we should prepare the eMMC. Open `fdisk` with your eMMC module and remove all partitions.
If you have issues with this, check if any partition is mounted, unmount it, then try again. 
`fdisk` is well documented elsewhere, so I won't cover it here.

Once your .xz file is downloaded, `unxz` the .xz file downloaded.

<pre class="terminal">
$ cd ~/Downloads
$ unxz Manjaro-Sway-ARM-pbp-20.10.img.xz
</pre>

Not exactly those commands, but close.

Once you have that, flash your eMMC by using `dd`.

<pre class="terminal">
# dd if=./Manjaro-Sway-ARM-pbp-20.10.img of=/dev/mmcblkX bs=1M conv=fsync
</pre>

Now remove your SD card.
U-Boot will prefer your SD card over your eMMC, so if you leave it in, it *will* boot to your SD card.

### Flash Your U-Boot (BSP)

U-Boot appeared to be the solution to my other two issues.
I was able to flash a new U-Boot program by using the following commands.
Be sure to run `lsblk` beforehand to know which `/dev/emmcblk` to write to.
Replace `X` with the correct number for your system.

<pre class="terminal">
# pacman -S uboot-pinebookpro-bsp
# dd if=/boot/idbloader.img of=/dev/mmcblkX seek=64 conv=notrunc
# dd if=/boot/uboot.img of=/dev/mmcblkX seek=16384 conv=Notrunc
# dd if=/boot/trust.img of=/dev/mmcblkX seek=24576 conv=notrunc
</pre>

The `dd` instructions are printed out after installing the `uboot-pinebookpro-bsp` package, so make sure to follow what is printed there if it is different that what I have provided.

After doing this, not only have I since booted 100% of the time,
but my display now works correctly after a reboot without a full shutdown.

Whew! Looking good!!!

### Maybe get some of the accessories

I didn't buy any accessories from Pine64.
I regret this somewhat.
For one thing, without an accessory to read the eMMC over USB, you need to have a working Linux distro on the SD card to get anywhere with it.
Flashing directly to the eMMC would have saved me a *lot* of time.

The other accessory I could see the occasional use for is the Ethernet adapter.
When downloading a big update (1GB+), it could be useful to wire in just temporarily.
Not a huge deal, but worth mentioning.

I would also be interested in the other batteries they have available.
Even though it comes with a battery, and I also don't think you can install a second one, I would be interested to see if I could get more life out of it with an improved battery.
If this is a standard battery (Pine64 tends to use standard parts), then I would consider getting it from a supplier as well.

The Pinebook Pro does not come with any HDMI ports.
It comes with a USB type-C port that can be adapted to HDMI.
Or you can get a display that supports USB type-C.
I do not have a display that supports USB type-C, so it might be worth it for me to buy an adapter or find a compatible one more locally.
Shipping from Hong Kong ain't cheap.

### Replace the boot logo

The boot splash screen can be replaced, but I haven't figured out how yet.
I will post an update to the blog when I do find out.

## Conclusion

I really want to use the Pinebook Pro more.
Pine6t4 do a lot for the open-source community and they do their best to use only open hardware.
They do fail in some respects, but they do much better than the mainline distributors like Dell, HP or ASUS.

Thanks, Pine64! I'm excited to use your products!

Happy ARM hacking :)
