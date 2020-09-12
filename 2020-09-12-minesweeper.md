---
title: "Minesweeper Bomb Generation And Tile Revealing"
layout: post
---

When I was creating a little Minesweeper game, I got confused at some points.
My bomb generation didn't look quite right, and I for sure didn't quite get the whole cascading tile reveal thing.
With a bit of internet research, I found what I was looking for.
I'll explain it all in one place for my own and others' purposes.

### Bomb Generation

When I started this project I attempted to use a random bomb generator.
By this I mean on each square, before it gets generated, give it a one in 15 change of being a bomb.
Personally, I'm not sure why this never looked right.
Something about the layout of the bombs did not mimic the classic Minesweeper game.

After looking at some open source Minesweeper examples, I found the following algorithms:

* `X = R % W`
* `Y = R // H`

Where % is a [modulo] operator
