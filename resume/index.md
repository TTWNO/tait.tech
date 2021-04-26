--- 
layout: simple
title: "Resume"
--- 
<h1 class="center">Tait Hoyem</h1>

## Experience
<ul class="clear-list">
{% for job in site.data.experience %}
  <li>
  <strong>{{ job.company }}</strong> &mdash; <em>{{ job.position }}</em> ({{ job.years }})
  
  <p>{{ job.description }}</p>
  </li>
{% endfor %}
</ul>

## Education
<ul class="clear-list">
{% for education in site.data.education %}
<li>
  <strong>{{ education.institution }}</strong> &mdash; {{ education.level }} / <em>{{ education.name }}</em> ({{ education.years }})

  {{ education.description | markdownify }}
</li>
{% endfor %}
</ul>

## Projects
<ul class="clear-list">
{% for project in site.data.projects %}
<li>
  <strong><a href="{{ project.link }}">{{ project.name }}</a></strong>

  <p>{{ project.description }}</p>
</li>
{% endfor %}
</ul>

## Skills
{% for list in site.data.skills %}
  <h3>{{ list.section }}</h3>
<ul>
  {% for skill in list.skilllist %}
    <li>{{ skill.skill }}</li>
  {% endfor %}
</ul>
{% endfor %}

