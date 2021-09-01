---
layout: post
title: "UEFI Audio Protocol & UEFI BIOS Accessibility"
---

Good news about the state of accessibility in the BIOS!

## Preamble

On my [ideas page](/ideas/), I have always had up the idea of an accessibility layer for blind people to be able to use their BIOS.
Although it targets a very small percentage of the population,
computer programming is often at least a hobby of visually imapired individuals as it is (mostly) a text-based job:
You write code in plain text, then run it to get either plain text or some kind of HTML output.
Mostly an accessible career for those who cannot see.
That said, there has always been an issue with low-level computer infrastructure (i.e. the BIOS/UEFI).
These menus---which let you edit your boot order, RAM timings, CPU and GPU overclocking and sometimes even fan speed---they were completely inaccessible to those who could not see them.
Well, until... soon. I had a talk with one of the big bois working on EDK2, the UEFI implementation which is used by most motherboard vendors to create their firmware.
I thought I would share the info I understand, and the conversation in full.



## News

Here is what I know:

1. This year, the GSoC (Google Summer of Code) project had [a submission of Ethin Probst](https://summerofcode.withgoogle.com/projects/#6499615798460416) to implement VirtIO audio drivers for EDK2.
2. [QEMU](https://qemu.org), the emulator that was chosen to test for this project does not have VirtIO support (yet). I haven't found info on when this will be done.
3. Because of 2, Ethin and his mentors for his project, Ray Ni and Leif Lindholm decided to first implement USB-dongle audio support first, as this is a) supported in QEMU, and b) is good enough to start squashing bugs at the audio level.
4. Because GSoC is usually over around September, there will likely be some more news coming soon!

## The IRC Chat

Here is the log of the IRC chat for anyone who is interested in anything I might have missed:

<pre class="terminal">
tait_dot_tech: Hello there, I'm new to IRC so just checking my messages are coming through.
tait_dot_tech: Looks light it's alright. Ok so I have a question: does anyone know of an active project looking at making UEFI accessible to the blind (i.e. speec) [sic] from within the UEFI environment? Main concern is having blind users be able to boot Linux USBs (I know, very niche thing), but depending on how good it is, could potentially be used to allow blind individuals to change their overclocking,
tait_dot_tech: hardware RAID, boot order, RAM timings, etc. all on their own. Just wondering if there is any project doing this? I have tried my best to find anything, and am just trying not to duplicate effort. Thanks :)
leiflindholm: tait_dot_tech: we have a google summer of code project running this year, prototyping a standard for audio output. To hopefully be added to the UEFI specification in the future.
leiflindholm: once we have a standard for audio output, we can work on adding support for audio output to the Human Interface Infrastructure
leiflindholm: which is the thing that lets menus be loaded and displayed independent of specific graphical implementation
tait_dot_tech: Oh wow! Glad to hear there is progress on this! Is there a link to the Google summer of code project, or anything else where I can keep tabs?
leiflindholm: tait_dot_tech: there isn't much yet, we're only on week 3 of GSoC.
leiflindholm: https://summerofcode.withgoogle.com/projects/#6499615798460416 is the link if it's something you want to point others to, but any discussion/reporting is likely to hapen [sic] on our mailing lists
tait_dot_tech: By "our" mailing list, do you mean GSoC, or Edk2?
leiflindholm: edk2
leiflindholm: although, on average, at least 99% of edk2-devel will *not* be about audio support
leiflindholm: When we have anything interesting to say, we'll also post to edk2-discuss/edk2-announce
tait_dot_tech: Sweet! I'll join that one just in case! I'd be happy to test anything in beta-ish state and report back with any device I can get my hands on. Is that the right list to watch for hepling test it out?
leiflindholm: I'd say so.
leiflindholm: The original plan was to start with wirtio [sic] audio support, so anyone could help out anywhere, but that support is not yet upstream in qemu. So for now we're working on an [sic] USB audio class driver. That will certainly be useful to have more people testing with different equipment once we have something working.
tait_dot_tech: Ahh! So if I want to test, I should get a USB audio dongle. Gotcha! Thank you so much! You've been super helpful!
leiflindholm: np :)
</pre>

Things are (slowly) looking up for audio (and eventually screen-reader support) in UEFI!
Phew! Glad I'm not the only one thinking about this!

Happy UEFI hacking :)
