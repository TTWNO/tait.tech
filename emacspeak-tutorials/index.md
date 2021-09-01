---
layout: default
title: "Emacspeak Tutorial Resources"
---

# Emacspeak Tutorial Resources

This is a list of resources and videos associated with my emacspeak tutorials.
They are grouped by language and library.
Although I try my best to keep each individual video as self-sufficient as possible...
sometimes it's not quite possible. Especially with complex libraries.
The lack of sorting is intentional.
See Luke Smith's video on [why to ramble and not be sequential](https://www.youtube.com/watch?v=ent5g6_gnik).

<!--
TODO: add transcript of me and Emacspeak output, and host on at least one alternate and one self-hosted platform.
MUST be done before making new videos.
-->

<ul>
{% assign languages = site.emacspeak_tutorials | group_by: "language" %}
{% for language in languages %}
  <li id="{{ language.name | downcase }}">{{ language.name }}
  <ul>
  {% assign libraries = language.items | group_by: "library" %}
  {% for library in libraries %}
    <li id="{{ language.name | downcase }}-{{ library.name | downcase }}">{{ library.name }}
    <ul>
    {% for tutorial in library.items %}
      <li id="{{ language.name | downcase }}-{{ library.name | downcase }}-{{ tutorial.name }}"><a href="{{ tutorial.url }}">{{ tutorial.title }}</a></li>
    {% endfor %}
    </ul>
  {% endfor %}
  </li>
{% endfor %}
</ul>
