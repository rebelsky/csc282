{% capture problem_number %}{{ problem_number | plus: '1' }}{% endcapture %}

{% assign fullpath = include.file | prepend: "_problems/" %}
{% assign problem = site.problems | where: "path", fullpath | first %}
{% if problem %}

## Problem {{ problem_number }}: {{ problem.title }}
*Topics:* {{ problem.topics | join: ", " }}

{{ problem.content }}

{% else %}

## Problem {{ problem_number }}: Uh oh!
Something has gone wrong here...

{% endif %}