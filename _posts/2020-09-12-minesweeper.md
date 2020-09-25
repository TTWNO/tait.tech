---
title: "Minesweeper Bomb Generation And Tile Revealing"
layout: post
math: true
---

When I was creating a little Minesweeper game, I got confused at some points.
My bomb generation didn't look quite right, and I for sure didn't quite get the whole cascading tile reveal thing.
With a bit of internet research, I found what I was looking for.
I'll explain it all in one place for my own research purposes.

## Bomb Generation

When I started this project I attempted to use a random bomb generator.
By this I mean on each square, before it gets generated, give it a one in 15 change of being a bomb.
Personally, I'm not sure why this never looked right.
Something about the layout of the bombs did not mimic the classic Minesweeper game.

After looking at some open source Minesweeper examples, I started to get the idea.
I wrote some mathematical statements describing the generation of bombs and how to get their x,y position from an appropriate number.
For those non-mathy people, don't leave just yet;
there will be code equivalents to the math.

W and H are the width and height of the board respectively.

{% katex display %}
\it 0 \leq r \leq \text W \times \text H
{% endkatex %}
{% katex display %}
\it x = r \bmod \text W
{% endkatex %}
{% katex display %}
\it y = \left\lfloor\frac{r}{\text H}\right\rfloor
{% endkatex %}

The code equivalent to this in Python is below:

```python
import random
# r <= 0 <= W*H
r = random.randint(1, W*H)-1

# x = r mod W
x = r % W

# y = floor(r/H); note the special syntax python has for this operation
y = r // H
```

So that's that, we can put this in a big 'ol for loop and generate an arbitrary *n* number of bombs given a width and height of a Minesweeper board.

## Cascading Tile Revealing

This one is hard to describe;
I am adapting this from [leetcode.com](https://leetcode.com/problems/minesweeper/).
Whenever a player clicks a tile, the following logic should be used:

1. If a mine is revealed, the game is over. (obviously)
2. If a tile with *no* adjacent mines is revealed, recursively reveal all eight adjacent tiles.
3. If a tile with one or more adjacent mines is revealed, display the number of mines next to it.

Here is the code in Python for this algorithm.

```python
def reveal_square(x, y, board, alread_revealed):
  # if already checked
  if (x, y) in already_revealed:
    return
  # if it's a bomb
  if board[x][y] == 'B':
    you_lose()
    return
  # if the bomb number is more than 0
  already_revealed.append((nx, ny))

  # from -1 to 1
  for xd in range(-1, 2):
    for yd in range(-1, 2):
      # skip if it is this the center tile
      if x+xd == x and y+yd == y:
        continue
      # recursively check the adjacent square
      reveal(x+xd, y+yd, board, already_revealed)
  return already_revealed
```

This has no checks for valid squares, but it's the general idea.
This function returns an array of tile coordinates which should be revealed.

## Conclusion

I wrote this because in the first place because I was writing my own Minesweeper game.
I hope that this helps you with getting the general idea of a Minesweeper game.
The completed version of this game is available on my [lamegames](https://lamegames.tait.tech/) site.
Let me know what you think!

Happy hacking!
