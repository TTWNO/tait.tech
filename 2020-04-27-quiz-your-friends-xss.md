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

I decided to write my name like so: `<b>Steve</b>`.
Steve is in reference to the [main character](https://minecraft.gamepedia.com/Player) in the video game Minecraft.


<figure>
  <img src="/assets/img/qyf-xss/2-bold.png">
  <figcaption>
    <p>Me typing in my name as <span class="mono">&lt;b&gt;Steve&lt;/b&gt;</span>.</p>
  </figcaption>
</figure>

Now in theory this should have shown in in the leaderboard as: "&lt;b&gt;Steve&lt;/b&gt;"
However, to my horror and excitement, I saw this in the leaderboard:

<figure>
  <img src="/assets/img/qyf-xss/3-steve-board.png">
  <figcaption>
    <p><span class="mono">&lt;b&gt;Steve&lt;/b&gt;</span> displaying in the leaderboard as bold text: <b>Steve</b></p>
  </figcaption>
</figure>

The text "Steve" showed up **in bold** on the leaderboard.
This told me all I needed to know.
How did this happen? You might wonder.

### Server-Side Validation

Here is a great demonstration why you should do most of your validation on the server side.
As a user, I can edit any of the HTML, CSS, or Javascript your server serves to me.

Quiz your friends uses the `maxlength=20` HTML attribute on the name input field.
Imagine trying to fit in a script tag doing anything useful with 20 characters! Don't forget that includes the `<script>` tag.
That would leave 13 characters for Javascript.
Although I'm sure a genius would be able to [code golf](https://code.golf/) that, I know I couldn't.

Now obviously I can edit any HTML that a server has sent to me.
If I open up my inspect element window, I can go ahead and change that `maxlength` attribute to anything I want.
Let's change it to 100!

<figure>
  <img src="/assets/img/qyf-xss/5-maxlength.png" alt='An image of the Quiz Your Friends name input field with inspect element. THe code reads: <font class="style6"><input class="inputbutton" name="takername" type="text" id="takername" maxlength="20" width="425" placeholder="Your First Name" style="text-align: center; text-decoration:inherit; font-size:38px;" tabindex="-1"></font>'>
  <figcaption>
    Manually changing the maxlength attribute. 
  </figcaption>
</figure>

In theory, there is a way that a site can stop people from just putting in their name of any length: server-side validation.
The server *could* check to see if the input is too long and reject it if it is.
The Quiz My Friends server has *no such checks in place*.
Therefore, I can send an almost arbitrary load to them.
Being able to send something potentially very large (more than a few megabytes) is a vulnerability of its own.
Imagine being able to send entire executable programs as your "name" in one of these quizzes?


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


