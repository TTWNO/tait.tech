---
title: "How to Deploy Lichess's Lila With Nginx"
layout: post
---

I was getting ready to have a public test of some changes I made to [lichess.org](https://lichess.org)'s [open source chess platform](https://lichess.org/source).
In preperation, I got my Let's Encrypt certificates and nginx configurations setup...
and it wouldn't work.
Here are some tips for myself and future Lichess developers.

## Reasoning

My pull request involves accessibility.
It will extend Lichess's NVUI (Non-Visual User Interface) to be more accessible to beginner level chess players.
At the time of writing this, Lichess's NVUI only supports searching pieces by type, rank and file.
It does not support any kind of interactive board.

I wanted to play chess with a friend of mine who uses a screen reader.
Even though Lichess does indeed have a separate rendering of the page for visually impaired users,
I have heard from a few people that it is not the best.

I don't use a screen reader myself, so I thought having a public latest changes deployed server would work better for testing.
It would certainly work better than getting some of my less computer literate friends to connect to me via VSCode/VPN and view my local repository.

So here is how to deploy it:

## Setup a development environment

This is described [in Lichess's documentation itself](https://github.com/ornicar/lila/wiki/Lichess-Development-Onboarding).
I will not elaborate further as it is not necessary.

## Setup nginx

This is the part that stumps most people.
Getting a local development server usually works alright, but once you want to reverse proxy it for security and professionalism purposes, it get more interesting.

Here is the relevant portion of my nginx configuration:

<pre class="file">
server_name chess.tait.tech;

location / {
  proxy_pass http://127.0.0.1:9663;
  proxy_set_header Host $host;
  proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
  proxy_set_header X-NginX-Proxy true;
  proxy_set_header X-Real-IP $remote_addr;
}
</pre>

<pre class="file">
server_name ws.chess.tait.tech;

location / {
  proxy_pass http://127.0.0.1:9664;
  proxy_http_version 1.1;
  proxy_set_header Upgrade $http_upgrade;
  proxy_set_header Connection "upgrade";
}
</pre>

You will need to deploy these on two virtual hosts.

## Lila

[Lila](https://github.com/ornicar/lila/) is the name for the main chess server, we need to change a few settings. Here is my git diff for the `conf/base.conf` file:

<pre class="file">
-  domain = "localhost:9663"
-  socket.domains = [ "localhost:9664" ]
+  domain = "chess.tait.tech"
+  socket.domains = [ "ws.chess.tait.tech" ]
   asset.domain = ${net.domain}
-  asset.base_url = "http://"${net.asset.domain}
+  asset.base_url = "https://"${net.asset.domain}
   asset.minified = false
-  base_url = "http://"${net.domain}
+  base_url = "https://"${net.domain}
</pre>

### Lila-ws

[Lila-ws](https://github.com/ornicar/lila-ws/) is the websocket component of Lila.

The most common complaint amongst aspiring Lichess developers is websockets not working.
They constantly get these '101' responses from the websocket,
and it also seems that the websocket returns instead of staying in the 'pending' state as it should be.

Here is how to fix that (in diff format):

<pre class="file">
-csrf.origin = "http://127.0.0.1:9000"
+csrf.origin = "https://chess.tait.tech"
</pre>

You need to tell lila-ws where the websocket requests will be coming from. This is how to do that.

## Conclusion

This is not a long article, but just some notes for future me and Lila developers.
