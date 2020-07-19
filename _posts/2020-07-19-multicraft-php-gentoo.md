---
title: "Installing MultiCraft on Gentoo Linux"
layout: post
---

In a very odd combination of requirements,
I needed to install [MultiCraft](https://multicraft.org) on a Gentoo Linux system.
The PHP `USE` flags are important so you don't have to recompile it three times like I did.

Here are some useful tips I came across:

### PHP `USE` flags

In `/etc/portage/package.use/php` I placed the following line:

<pre class="terminal">
dev-lang/php cgi mysql mysqli fpm pdo gd truetype
</pre>

This should give you enough for a mysql backended MultiCraft installation.
The `cgi` option may not be required as `fpm` stands for *FastCGI Process Managment*.
I don't know for sure though.

### Paper

This will grab the latest version of the Paper jar file using [YivesMirror](https://yivesmirror.com).
I'm not sure how reputable it is,
but my buddy who works with this stuff more often than me seemed to recognize it.

<pre class="terminal">
## See the default craftbukkit.jar.conf for a detailed documentation of the
## format of this file.
[config]
name = Paper 1.16.1 Latest
source = https://yivesmirror.com/files/paper/Paper-1.16.1-latest.jar
category = Mods

[encoding]
#encode = system
#decode = system
#fileEncoding = latin-1

[start]
command = "{JAVA}" -Xmx{MAX_MEMORY}M -Xms{START_MEMORY}M -XX:MaxPermSize=128M -Djline.terminal=jline.UnsupportedTerminal -jar "{JAR}" nogui
</pre>

### Other Tips

Do not use the option to setup a separate user for each server.
This completely stalled any work getting done with a ton of 'permission denied' errors.

#### Security

If the panel is in the root directory of your NGINX web server,
use the following in your server block to deny access to the `/protected` directory.

<pre class="terminal">
location /protected {
  deny all;
  return 404;
}
</pre>

##### MySQL

It is always good practice to separate privileges.
The MultiCraft daemon should have one SQL login,
with one database allocated to it.
The MultiCraft panel should have a separate SQL login,
with a separate database allocated to it.

You can do this with the following commands in your MySQL prompt:

<pre class="terminal">
sql> CREATE DATABASE multicraft_daemon_database;
Query OK, 0 rows affected (0.01 sec)

sql> CREATE DATABASE multicraft_panel_database;
Query OK, 0 rows affected (0.01 sec)

sql> CREATE USER 'muilticraft_daemon'@'localhost' IDENTIFIED BY 'strong password here';
Query OK, 0 rows affected (0.01 sec)

sql> CREATE USER 'multicraft_panel'@'localhost' IDENTIFIED BY 'different strong password here';
Query OK, 0 rows affected (0.01 sec)

sql> GRANT ALL PRIVILEGES ON multicraft_daemon_database . * TO 'multicraft_daemon'@'localhost';
Query OK, 0 rows affected (0.01 sec)

sql> GRANT ALL PRIVILEGES ON multicraft_panel_database . * TO 'mutlicraft_panel'@'localhost';
Query OK, 0 rows affected (0.01 sec)

</pre>

During setup, make sure the proper credentials are used for each step.
Database 1 is the panel database.
Database 2 is the daemon database.

Happy hacking :)
