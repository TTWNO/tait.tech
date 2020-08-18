---
layout: simple
title: "Resume"
---
# Tait Hoyem


### Experience
{% for job in site.data.experience %}
  **{{ job.company }}**---*{{ job.position }}* ({{ job.years }})
  
  {{ job.description }}
{% endfor %}

### Education
{% for education in site.data.education %}
  **{{ education.institution }}**---{{ education.level }} / *{{ education.name }}* ({{ education.years }})

  {{ education.description }}
{% endfor %}

### Professional Development
{% for education in site.data.proffedu %}
  **{{ education.institution }}**---{{ education.level }} / *{{ education.name }}* ({{ education.years }})

  {{ education.description }}
{% endfor %}

### Projects
{% for project in site.data.projects %}
  **[{{ project.name }}]({{ project.link }})**

  *{{ project.description }}*
{% endfor %}
### Languages
##### Human
{% for lang in site.data.languages %}
  * {{ lang.name }} ({{ lang.level }})
{% endfor %}
##### Computer
{% for lang in site.data.comp-langs %}
  * {{ lang.name }} ({{ lang.level }}/5)
{% endfor %}
