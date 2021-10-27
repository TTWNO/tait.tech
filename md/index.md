---
title: "Simple Markdown Converter w/ MathML Support"
layout: simple
math: true
---

{% contentfor extrahead %}
<link rel="stylesheet" href="/assets/css/markdown.css">
<script defer src="/assets/js/md/remarkable.js"></script>
<script defer src="/assets/js/katex.js"></script>
<script defer src="/assets/js/katex/auto-render.js"></script>
<script defer src="/assets/js/katex/render-a11y-string.js"></script>
<script defer src="/assets/js/md/handlers.js"></script>
{% endcontentfor %}

# Tait's Simple Markdown Tool

## Info

* You can use `$...$` for inline math.
* You can use `$$...$$` for "display mode" math.
* Display mode will make the equation take up an entire line for itself, and it will display larger and more "formally". It also allows you to have newlines without breaking up the expression, and/or the use of `\newline` to have a multi-line formula.
* You can save the HTML or markdown for future use.
* You can download the HTML or markdown for sharing with others.
* Saving will save it to your browser's local storage so when you load the page again--even after a reboot--it will be pre-populated with what you saved last.
* Converting to HTML automatically saves both the markdown and the HTML.
* This page is fully functional without an internet connection. Ctrl+s to save the page with its CSS and Javascript and you can use this tool offline.

## Editor

<label for="status">Status:</label>
<span id="status" aria-live="polite">OK</span>

<label for="markdown-input">Markdown input:</label>

<textarea id="markdown-input"></textarea>
<br>
## Actions

* <button id="update-html">Update HTML</button>
* <button id="save-markdown">Save Markdown</button>
* <button id="save-html">Save HTML</button>
* <button id="download-markdown">Download Markdown</button>
* <button id="download-html">Download HTML</button>

## HTML is below this section break:

<hr>
<div id="html-output"></div>
