swapusage
=========

**About**

This little utility for Linux shows the amount of swapped memory for running processes.

Contrary to popular belief this is actually _not that easy_, and tools like
```top``` either don't do this at all, or completely wrong; see
[this discussion on StackOverflow](http://stackoverflow.com/questions/479953/how-to-find-out-which-processes-are-swapping-in-linux/) for some background.

After finding some of the proposed scripts unacceptably inefficient, I decided to
rewrite one of them in C++11.

**Installation**

- Type "make" & copy the executable wherever you want.
- If you encounter any problems then please fix them and send a pull request. :)

Gentoo users can find an ebuild in my [overlay](https://github.com/hhoffstaette/portage).

**Usage**

```
$./swapusage -h
Usage: swapusage [pid]

$./swapusage
====================================
 Swap kB   PID  Name
====================================
     976  5531  pulseaudio
     292  2738  zsh
      64  5239  gam_server
------------------------------------
    1332 kB total.

$./swapusage 5531
====================================
 Swap kB   PID  Name
====================================
     976  5531  pulseaudio
```

**More information**

While swapusage is a good first step towards analyzing a swap (and memory) situation,
you might find that you need much more detailed analysis capabilities. In that case
you could look at [smem](http://www.selenic.com/smem/).

