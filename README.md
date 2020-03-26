# tait.tech
The uncompiled version of my website. Compiled files in _site

### To compile

To compile the files, simply use the bundle Ruby gem.

```
bundle exec jekyll build
```

to compile once. If you decide you want to actually have changes appear instantly, use the following

```
bundle exec jekyll watch
```

To run a local web server to view the changes on:
```
bundle exec jekyll server -w
```

This will watch for the latest changes, compile them, and make them available on localhost:4000
