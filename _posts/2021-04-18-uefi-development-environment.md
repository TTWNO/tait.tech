---
layout: post
title: "UEFI Development On x86 With EDK2"
---

I made this blog so I could remember how to do stuff that had instructions spread around the internet.
So here is how I setup my environment for developing EFI applications.

## Requirements

On Artix or other Arch-based distros like Manjaro I installed the following packages: `gcc nasm iasl`

Here is what the packages do:

* GCC is obviously the GNU Compiler Collection and it allows us to compile C code to machine code.
* NASM stands for Netwide Assembler. It is an assembler and disassembler for 32 and 64 bit Intel x86 platforms.
* IASL stands for the ACPI Source Language Compiler/Decompiler. This will compile any ACPI calls to our local machine's code.

We need all these packages to start our (U)EFI journey.
Now that these are installed, let's setup our environment.

## Building EDK2

I used the stable/202011 branch as that is latest stable version of the EDK2 project.

So first let's pull the project:

`git clone https://github.com/tianocore/edk2.git`

Now, let's fetch the tags and switch to the latest stable version:

```
cd edk2
git fetch
git checkout stable/202011
```

Perfect! We're on stable now! Let's grab all our submodules: `git submodule update --init`

This will take a bit the first time you do it. But no fear, once that's done, we can finally build the base tools.

```
make -C BaseTools
export EDK_TOOLS_PATH=$HOME/Documents/edk2/BaseTools
. edksetup.sh BaseTools
```

Notice we source a file with `.` before continuing. This is needed to load some tools and options into our shell for later. The environment variable `EDK_TOOLS_PATH` is set so that EDK knows where to find itself later. Now that everything is loaded up, we can modify a config file located at `Conf/target.txt`.

The most important options are these, feel free to append them to the end of the file; there is no default value for them.

<pre class="file">
ACTIVE_PLATFORM = MdeModulePkg/MdeModulePkg.dsc
TOOL_CHAIN_TAG = GCC5
# for 64-bit development
TARGET_ARCH = X64
# for 32-bit development
TARGET_ARCH = IA32
# for 32 and 64-bit development
TARGET_ARCH = IA32 X64

# set multithreading to 1 + (2 x # of cores)
MAX_CONCURRENT_THREAD_NUMBER = 9
</pre>

There are other options, but I don't know about them much, so I'm just sticking with this for now.

Finally, after all this work, we can build some .efi files. Let's compile the `Helloworld.efi` file!
Simply run the `build` command in the terminal.
You can find your compiled EFI files by running this `ls` command:

```
ls Build/MdeModule/DEBUG_*/*/HelloWorld.efi
```

This will show all HelloWorld.efi files for all architectures and toolchains (if you decide to change them).

## Running In UEFI Shell

Once all this is complete, you will want to run your EFI files.
To do so, let's first add an EFI shell to use at boot.
This will appear as an option in your bootloader, like GRUB, which is what I will show documentation for in this article.

So, first thing is first,
[download and EFI shell file](https://github.com/tianocore/edk2/blob/UDK2018/ShellBinPkg/UefiShell/X64/Shell.efi?raw=true).
Second, move it to a partition (FAT formatted) which can be used for the UEFI.
On my Linux system, this is /boot. On others there may be no FAT filesystem so attach a USB and format it as FAT.
Third, add the `EFI Shell` option to your grub boot file.
Substitute hdX with the right hard drive (I did it with trial and error) as when it doesn't work I would hit 'e' on grub and add the `ls` GRUB command.
Substitute the gptX with the correct partition, or msdosX if it is a DOS formatted partition table.
My `Shell.efi` was placed in /boot/EFI/.

<label>/etc/grub.d/40_custom</label>
<pre class="file">
menuentry "EFI Shell" {
        insmod part_gpt
        insmod chain
        insmod fat
        set root='(hd4,gpt2)'
        chainloader /EFI/Shell.efi
}
</pre>

Now regenerate your grub configuration file with `grub-update` (Debian-based) or `grub-mkconfig -o /boot/grub/grub.cfg` (Other).

You'll know if your shell is working if you see the following text on boot into the EFI shell:

<pre class="terminal">
UEFI Interactive Shell v2.1
EDK II
UEFI v2.4 (EDI II, 0x000100000)
Mapping table:
	...
Shell> 
</pre>

## Running Hello World

When we run our `ls` command from earlier, remember we saw our `HelloWorld.efi` file.
Let's move this file somewhere useful, like for me, `/boot`.
Then, once we're in our UEFI shell we can run commands:

<pre class="terminal">
Shell> .\HelloWorld.efi
UEFI Hello World!
Shell> 
</pre>

And that... All that is how you set up a UEFI development environment.

## Conclusion

This took me a long time to figure out.
I needed to scrounge resources from around the internet,
and I had to look at my config files for hours to make sure that I hadn't missed a step that I did without thinking.
I hope this will be useful to you and my future self.

Happy UEFI hacking :)
