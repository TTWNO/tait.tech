---
layout: default
title: "Links"
---
{% for types in site.data.links %}
<section>
  <header>
    <h2>{{ types.heading }}</h2>
  </header>
  {% for info in types.values %}
  <ul>
    <li>
      <span class="bold">{{ info.name }}</span> -
      <a href="{{ info.value }}" class="mono">
        {% if info.label != "INHERIT" %}
          {{ info.label }}
        {% else %}
          {{ info.value }}
        {% endif %}
      </a>
    </li>
  </ul>
  {% endfor %}
</section>
{% endfor %}

All my big projects are on my [homepage](/).
