# unsolvable_word_search

This project allows generating word searches that are guaranteed to contain zero English words!

To get started, run `make`. Note that this project requires my `libzed` library to be installed!

After building succeeds, you can generate word search images by running the following:
```
./unsolvable_word_search <rows> <columns> | ./ws_to_png.py <title> <output.png>
```

So an example usage could be:
```
./unsolvable_word_search 20 20 | ./ws_to_png.py "Unsolvable Word Search" out.png
```

Enjoy! :)
