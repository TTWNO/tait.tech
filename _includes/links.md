{% for types in site.data.links %}
  <h2>{{ types.heading }}</h2>
  <section class="contact-info">
    {% for info in types.values %}
      <p><span>{{ info.name }}</span> -
      <a href="{{ info.value }}" >
        {% if info.label != "INHERIT" %}
          {{ info.label }}
        {% else %}
          {{ info.value }}
        {% endif %}
      </a></p>
    {% endfor %}
  </section>
{% endfor %}

All my big projects are on my [homepage](/).
