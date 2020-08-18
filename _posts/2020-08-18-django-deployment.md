---
title: "How to Solve The Django Deployment Puzzle"
layout: post
---

A few days ago I had a Django project I wanted to put on a real server.
This project is still in its infancy, but I thought it would be nice to put it on my resume and show my friends.
Little did I know the headache coming my way.
Here are some tips to help you not make the same mistakes as me.

### ASGI Servers

Because my project used the ASGI (Asynchronous webServer Gateway Interface),
I needed to find a good production ASGI server to handle all the incoming requests.
The best thing I found was [uvicorn](http://www.uvicorn.org/).
It focuses on speed, which is a priority, especially when using the ASGI protocol.

To run uvicorn on the command line for testing purposes, use something like the following:

<pre class="terminal">
$ uvicorn --reload myapp.asgi:application
</pre>

The `--reload` option says to reload the server if any of the files get updated.
This is not recommended in production.
Sadly, I thought this meant I would need to do a hard shutdown of the server process every time I wanted to update.
This turned out to not be the case.

### Workload Managers

There is another equine-named program called [gunicorn](https://gunicorn.org/)
which can hold a number of processes under its control.
An interesting feature of `gunicorn` is that it will gracefully switch from an old to a new deployment,
replacing the subprocesses one-by-one and eventually having only the new deployment active on all subprocesses.
The greatest part? Zero down time.
The server keeps any old processes open if there is communication with them,
then shift and new connections to the new deployment.
This was a very cool feature I wanted to take advantage of.

"Now hold on!" you might protest.
"gunicorn is a WSGI server!" ... oh you got me there!
Yes, that's right, `gunicorn` is paired with `uvicorn` to serve my files.

### systemd

Love it or hate it, the majority of Linux distributions use the `systemd` init system.
I decided it would be very convenient to have a .service file for my Django application to run automatically at boot.
`Systemd` allows me to do this with a file like the following one I stored in `/lib/systemd/system/lamegames.service`.

<pre class="file">
[Unit]
Description=Gunicorn/Uvicorn (lamegames.io)

[Service]
WorkingDirectory=/home/lame/lamegames.io
Type=simple
RemainAfterExit=yes
ExecStart=/home/lame/lamegames.io/env/bin/gunicorn lamegames.asgi:application -w 2 -k uvicorn.workers.UvicornWorker
ExecStop=/bin/kill -HUP $MAINPID
Restart=always

[Install]
WantedBy=multi-user.target
</pre>

### nginx

NGINX (pronounced engine-X) is a performance web server designed for speed and simplicity.
For the front facing side of the site, I do need a production web server like nginx.
Gunicorn simply doesn't need all the features that nginx provides, but I do.
To configure my nginx installation, I used the following few directives to:

1. Redirect most traffic towards the gunicorn server.
2. Redirect statically served files (CSS, JS, images) to the directory specified in the STATIC_ROOT variable of my `settings.py` file.
3. Use TLS to enable https://

Serving the static files from nginx as opposed to the `gunicorn` server is necessary.
Gunicorn and other production A/WSGI web server will not set the proper MIME type over TLS.
This will cause your browser to not load the Javascript/CSS.

This is the important part of my nginx config.

<pre class="file">
server {
    location / {
        proxy_set_header Host $http_host;
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto $scheme;
        # these two lines ensure that WebSocket, and HTTP2 connection are forwarded correctly
        proxy_set_header Upgrade $http_upgrade;
        proxy_set_header Connection "Upgrade";
        proxy_redirect off;
        proxy_buffering off;
        # this forwards all traffic to the local server on port 8000
        proxy_pass http://localhost:8000;
    }

    # This forwards all static requests to Django's STATIC_ROOT set in settings.py; it is generated using the collectstatic command.
    location /static {
        autoindex on;
        alias /home/lame/lamegames.io/static_generated;
    }
}
</pre>

### Setup

After all that, I was able to do the following:

<pre class="terminal">
# systemctl enable lamegames
</pre>

This enabled my `gunicorn` server to run once the server started.
NGINX is that way be default.

And tada! You now have a working Django project on a production server!

#### Notes

* If using ws:// websockets, change them to wss:// for secure web sockets.
* Make sure to use channels.routing.get_default_application() instead of django.get_asgi_application() if your're wanting to use channels/redis WebSockets.