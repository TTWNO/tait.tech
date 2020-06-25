---
title: "How to use tmux to send and receive things from your Minecraft server"
layout: post
---

So recently I had problem.
I run a Minecraft server on a big Linux computer I have running in my room.
Now, as a system administrator it is very helpful to be able to run some simple commands without needing to login with my key, password, TFA, etc.
It is, frankly, a lot of work.
Especially when I really just want to be playing games but I just need to check something quickly.

So for simple things like finding out of the network, CPU, memory or disk usage is my bottleneck, I wrote this really nifty script to connect the world of Minecraft and the Linux shell.

My completed solution for what I needed can be found at [https://github.com/TTWNO/termcraft](https://github.com/TTWNO/termcraft/).

If you want some of the implementation details, stick around.

## Solution

So to solve this interesting problem, I decided to use `tmux`.
`tmux` is a **t**terminal **mu**ltiple**x**er.
This allows you to run a terminal session, then detach fromc it while it  still runs in the background.

This is very valuable when running command line applications that need to have an active console connection, like a Minecraft server.

So first I looked at the `tmux` command `send-keys`.

#### `send-keys`

`send-keys` allows you to send text, and key presses to a `tmux` session.
Now assuming this `tmux` session is attached to a Minecraft server,
there is no reason you could not run a command like this:

<pre class="terminal">
$ tmux send-keys "tell @a This is a Test" Enter
</pre>

This will send the text "tell @a This is a Test" to the Minecraft server.
Then, it will hit the newline character, this will execute the command.


So now we can send information to the server and have it tell the users something.

But how do we get information about who is typing what in the Minecraft chat?

### `tmux`'s `capture-pane` is painful

So in the manual page for `tmux` I can see a section recorded below for options I can give to the `capture-pane` subcommand.

<pre class="terminal">
  -S and -E specify the starting and ending line numbers,
  zero is the first line of the visible pane and negative
  numbers are lines in the history.  ‘-’ to -S is the start
  of the history and to -E the end of the visible pane.  The
  default is to capture only the visible contents of the pane.
</pre>

What it seems to be saying is I can start at line `-S n` and end at line `-E n`.
Negative numbers start from the bottom, so *in theory* I can do the following: `tmux capture-pane -S -1` should capture only the last line, because I'm starting from the last line. Right?

No. It just doesn't work. Negative numbers do *not* work with the `tmux capture-pane` subcommand.

So I did some simple UNIX piping, like so, to get just the last thing in the chat.

<pre class="terminal">
$ tmux capture-pane -p -t steve | tail -n1
[SERVER] [ExtraDebuggingInfoHere]: &lt;TaterTheTot&gt; MY_MESSAGE
</pre>
TaterTheTot is my Minecraft username :)

`-p` prints the result to the terminal/stdout.

`steve` is the name of the tmux session I'm trying to pull form.

So that's done! Beauty!

Now that we have that, how can we extract the username and the message from the latest line?

### `grep`

`grep` is a command to find patterns of text.
`grep` has an option to only show a matching pattern of text.
This option is `-o`.

Let's see how we can use this in conjunction with our latest line of server output to get our results.

<pre class="terminal">
$ echo "[DEBUG] [SERVER] blah blah: &lt;TaterTheTot&gt; MY_MESAGE" | grep -o "&lt;.&ast;&gt;"
&lt;TaterTheTot&gt;
</pre>

Now, that's my name with the &lt; and &gt; attached. Not bad!
We can use the `sed` command to clean it up a bit.

The syntax is like so: `select/somepattern/replacewith/global`

So the following command is: `s/[<>]//g`

Select any characters that are either &lt; or &gt;.
Replace with nothing.
Do so globally (as in, don't stop after you replace only one character).

Take two!

<pre class="terminal">
$ echo "[DEBUG] [SERVER] blah blah: &lt;TaterTheTot&gt; MY_MESAGE" | grep -o "&lt;.&ast;&gt;" | sed 's/[&lt;&gt;]//g'
TaterTheTot
</pre>

Beautiful!

Now what about that pesky message?

### more `grep`; more `sed`

Simple: capture everything after the &gt;. Leaving the user's message entirely in tact.

<pre class="terminal">
$ echo "[DEBUG] [SERVER] blah blah: &lt;TaterTheTot&gt; MY_MESAGE" | grep -o "&gt;.&ast;$" | sed 's/&gt; //'
MY_MESSAGE
</pre>

So now we have a way to get the username of someone typing in the Minecraft server chat.
We have a way to find out what they said.
And, we have a way to respond.

You can imagine how these might go together for your own use case.

### Conclusion

This shows some pretty fun stuff you can do with a few simple Linux commands and a Minecraft server.

I hope you learned something and found my explanations not horrific haha!

Remember to checkout the git repository to see what I did with it: [https://github.com/TTWNO/termcraft](https://github.com/TTWNO/termcraft).

Happy hacking!
