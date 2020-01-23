---
layout: post
author: tait
title: Padding And Margin
---
Many people have expressed confusion over how padding and margins work in HTML/CSS. I have been one of those people. In this short article I will explain what the differences are between the two, and how it may affect the functionality of your site.

Here is an image from the World Wide Web Consortium (W3C) who sets the standards for the web.

![The W3C standard for padding, margin, borders and width. Width encompases the inner element + padding; the border then encompases it. The margin is the space beyond the border and in between other elements.](/assets/img/w3c-padding-margin.png "W3C border, padding, margin standard.")

Now although this image shows all the different types of spacing as equal, the majority of the time these will mostly be padding (inner) and margin (outer). Padding is the inner space between the element and its border; margin is the outer space between two different elements.

Within the margin the user is unable to press any links or execute any javascript code. It is *empty* space. If each `<link>` on your navigation bar has 10 pixels of margin, then there would be 20 pixels in between each `<link>` that would *not* be clickable by the user.

If you have `<link>`s on your navigation bar with *padding* set to 20 pixels, however, then there will be 20 pixels on each side of the `<link>` text where the user *is* able to click.

If that part is confusing, try thinking about it in terms of whether `background-color` would apply.

Attribute | **Padding** | **Margin**
--- | --- | ---
Spacing | within element | between elements
`background-color` applies | Yes | No


In summary:
* **Padding**: the space within a tag which is still part of the same tag. `background-color` applies.
* **Margin**: the space in between two seperate tags. `background-color` does not apply; it is empty space.
* **Border**: the space in between the two; it surrounds the padding, but is not the margin. It looks nice somtimes, but it has no non-visual function. `background-color` does not apply.

I hope this covers the basics of margin and padding! Happy coding!

