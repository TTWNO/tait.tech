---
title: "Getting Pacaur Working on a Raspberry Pi 4 with Manjaro ARM or Arch Linux"
layout: post
---

I recently installed Manjaro ARM (based on Arch Linux ARM) on a Raspberry Pi 4.
I used some standard commands to start to add the `pacaur` package so I can easily retrieve [AUR packages](https://wiki.archlinux.org/index.php/Arch_User_Repository) without needing to do it manually.
Unfortunately, there is a small problem with compiling this on ARM.

## always_inline 

To setup the install for `pacaur`, I first needed to download [auracle-git](https://aur.archlinux.org/packages/auracle-git) AUR package manually.
I ran into an error when compiling this package.

But first, my setup:
<pre class="terminal">
$ git clone https://aur.archlinux.org/auracle-git
$ cd auracle-git
$ makepkg -sri
</pre>

Around half way through compiling this project, I got this cryptic message telling me there was a "target specific option mismatch"...Whatever that means.
The full error is below, hopefully that helps my chances on the search engines.

<pre class="terminal">
In file included from ../subprojects/abseil-cpp-20200225.2/absl/random/internal/randen_hwaes.cc:225:
/usr/lib/gcc/aarch64-unknown-linux-gnu/9.3.0/include/arm_neon.h: In function 'Vector128 {anonymous}::AesRound(const Vector128&, const Vector128&)':
/usr/lib/gcc/aarch64-unknown-linux-gnu/9.3.0/include/arm_neon.h:12452:1: error: inlining failed in call to always_inline 'uint8x16_t vaesmcq_u8(uint8x16_t)': target specific option mismatch
12452 | vaesmcq_u8 (uint8x16_t data)
</pre>

Luckily, there is a very easy fix for this.
The user redfish [helpfully pointed out](https://aur.archlinux.org/packages/auracle-git#comment-762117)
on the `auracle-git` package page that you need to add a special make option to your `/etc/make.conf` file to make this work.

His solution, as commented is like so:

> If you get this error when building for ARM aarch64:
>
> (insert error message from before)
>
> Then check that in /etc/makepkg.conf CFLAGS and CXXFLAGS have the +crypto suffix in -march flag, like -march=armv8-a+crypto (the base identifier may very depending on your hardware)

Basically, there is a file on Linux: `/etc/makepkg.conf` which tells your computer how to compile *all* programs on the system.
By default the Manjaro ARM (RPi4) edition has the following relevant lines in `makepkg.conf`.

<pre class="file">
CFLAGS="-march=armv8-a -O2 -pipe -fstack-protector-strong -fno-plt"
CXXFLAGS="-march=armv8-a -O2 -pipe -fstack-protector-strong -fno-plt"
</pre>

What Mr. redfish is telling us is that we must add '+crypto' to the end of the -march compiler flag so that our compiler will know how to inline that pesky vaesmcq_u8 function.

So in the end, your `makepkg.conf`'s relevant lines will look like so:
<pre class="file">
CFLAGS="-march=armv8-a+crypto -O2 -pipe -fstack-protector-strong -fno-plt"
CXXFLAGS="-march=armv8-a+crypto -O2 -pipe -fstack-protector-strong -fno-plt"
</pre>

## Why?

Redfish continues:

> Build of abseil-cpp package works because it uses CMake which adds the correct -march flag regardless of makepkg.conf, whereas when abseil-cpp is build as a subproject within this package, it uses meson, which does not add the flag and thus fails with the above error.

In other words, one of the dependencies pulled in with auracle is not compiling without this special compiler flag enabled.


## Conclusion

Thanks to redfish for posting this solution to the forums!
Would've been quite the rabbit hole for me to figure out how to do that.
In fact, it is very likely I would have never figured that one out.

After this issue is resolved, the installation of `pacaur` goes as expected. Nice and easy!
Pacuar will compile on any architecture so it's smooth sailing from here.

Happy hacking!
