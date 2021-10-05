---
layout: default
title: "Book Notes"
---

<ul>
{% for notes in site.book_notes %}
  <li><a href="{{ notes.url }}">{{ notes.title }}</a></li>
{% endfor %}
</ul>
