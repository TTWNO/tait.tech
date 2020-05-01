---
layout: post
title: "How to use NGINX as a reverse-proxy server for a Node.js application using socket.io"
---
Despite the long name of the article, I have a feeling this may apply to more people than I might think.
If you have a Node.js application which needs socket.io connections that you want to pass throgh nginx's `reverse_proxy` directive then this is the article for you!

You *must* seperate the socket.io sockets and the static resources.

* The socket connections can be routed through the default `$host/socket.io` if you want to ease modifications to the source code.
* The connections to your main npm Node.js application can be routed through the relevant directory.

Here is the relevant part of my `projects.tait.tech.conf` file:

<pre class="terminal">
location /socket.io {
  proxy_pass http://localhost:8080/socket.io/;
  proxy_set_header Upgrade $http_upgrade;
  proxy_set_header Connection "upgrade";
  proxy_http_version 1.1;
  proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
  proxy_set_header Host $host;
}

location /ttrpg {
  proxy_pass http://localhost:8080/;
  proxy_set_header Host $host;
  proxy_set_header X-Real-IP $remote_addr;
  proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
}
</pre>

### Explaination:

For this application,
I needed the `/ttrpg` directory to connect to my main Node.js instance. This was going to be the root of a ttrpg project.
It was to have static files served form my Node.js application.

I also needed `/socket.io` to conenct to my running `npm` instance.
When I tried to route all the traffic through the `/trrpg` location directive
I had no luck whatsoever;
`$host/ttrpg/socket.io/*` calls *always* failed with a 404.

Having two seperate blocks forwarding in different ways seems to fix this.
I am not knowledgable enough to understand how.

For now, the project is alive!!!

Happy hacking!


