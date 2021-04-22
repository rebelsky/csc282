---
title: EBoards
permalink: /eboards/
---
# EBoards
Here you can find a record of what we talked about each day of class
(more of less).

{% assign eboards = site.eboards | sort: 'held' | reverse %}
{% for eboard in eboards %}
  {% if eboard.link %}
    {% assign num = eboard.number %}
    {% assign index = num | plus: '-1' %}
    {% assign twodig = num %}
    {% if num < 10 %}{% assign twodig = num | prepend: '0' %}{% endif %}
* <a href="{{ site.baseurl }}{{ eboard.id }}">{{ eboard.title }}</a> 
    {% if eboard.held %}(held {{ eboard.held | date: '%A, %-d %B %Y' }}){% endif %}
  {% endif %}
{% endfor %}
