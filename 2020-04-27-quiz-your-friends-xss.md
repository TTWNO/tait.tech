---
title: "The \"Quiz Your Friends\" XSS Exploit"
layout: post
---

## TODO write intro

## How I Found This Exploit

While filling in one of my friend's surveys I thought it would be
funny for them to know it is me without anyone else knowing.
We were young and had `Inspect Element`ed a few things together,
so it was a safe bet that an HTML joke would let them know.

So I typed in my name like so:

`BOLD_STEVE.JPG`

Now in theory this should have shown in in the leaderboard as: "&lt;b&gt;Bold Steve&lt;/b&gt;"
However, to my horror and excitement, I saw this in the leaderboard:

`BOLD_STEVE_LEADERBOARD.JPG`

The text "Bold Steve" showed up **in bold** on the leaderboard.
This told me all I needed to know. To add a `<script>` tag was next.

#### Hacking:

So I went on my merry way thinking about ways to use malicious javascript.
Then, I thought that might be mean, so I decided to warn users instead.
I filled in the name with a script tag and a call to `alert()` to warn the user about this site.

`JAVASCRIPT_NAME.JPG`

I ran out of room before I could finish it. Hmmm.
What if I do "Inspect Element" and manually override the max-length attribute?

The unfortunate truth is: this worked as well!

Not only could I manually set the max-length by changing it in the HTML,
but there were no client-side OR server-side checks to make sure the name I was sending was less than or equal to 20 characters.

If Javascript checked it, it would have stopped me (although maybe not a professional).
If the server checked it, it could have stopped almost anyone.

##### Server-Side Validation

As a side note, here is a great reason why you should do most of your validation on the server side.
As a user, I can edit any of the HTML, CSS, or Javascript your server serves to me.

Imagine trying to fit in a script tag doing anything useful with 20 characters?

`<script src="http:">`

There's your 20 characters! No more! Good luck trying to do anything useful with this!

The Quiz My Friends server has *no such checks in place*.
Therefore, I can send an almost arbitrary load to them.
Being able to send something potentially very large (more than a few megabytes) is a vulnerability of its own.
Imagine being able to send entire executable progrmas as your "name" in one of these quizes?


## Executing An Exploit

Suppose we're on a vulnerable site like [Quiz Your Friends](https://www.quizyourfriends.com/)
and you decide you want to hack your friend's quiz!
How can this be done?

#### Creating A Quiz

Here is my quiz below:

`CREATING_QUIZ.IMG`

#### Setting A Name With an HTML Tag

Just like the image above, about how I found out about this vulnerability: go ahead and use an HTML tag in your name to test this out.

`BOLD_ITALIC_STEVE.JPG`


