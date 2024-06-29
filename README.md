# Minesweeper

This is a game in which you, well, sweep mines. Doesn't get any simpler than
this. Oh, and also, this game ships with AI because, well, isn't it a trend
nowadays? I wanna also get on the AI bandwagon, ya know?

## Setup

Of course, you would need to setup the actual environment to run this game. I
wouldn't wish upon you an adventure across the internet, wading through the
thicket of advertisements only to find two libraries you need to run the game.

Instead, out of the goodness of my heart, I am providing a tool for that. Step
1, install `make` (the GNU kind). Most distros will also have `pkg-config`
installed. To check, literally type that in your terminal, and it will give you
an error if it doesn't exist. The most difficult part is now over! Okay\
not really. I lied. You also need to install `glfw`. BUT! That should be it. If
not, then either you did something wrong, or I did. (it's most likely the
former).

Now, onto the final step of installing dependencies! Simply run the following
command in the project root!

```sh
make deps
```

This command will (wait for it) make the dependencies! How easy was that! Of
course, if this command errors, then you simply are using the wrong OS! (i use
arch btw). If you are a programmer, then solve the bug yourself - don't trouble
me! If you're the average Joe, then feel free to raise an issue!

For nerds who want to understand how `make deps` works (and trust me you want to
know how it works, it's amazing!), then read the damn code and not the README!

## Usage

I'm assuming that you have properly setup the environment like an intelligent
human being. In that case, to compile the program, simply run this command from
the project root.

```sh
make
```

And that's it! This command will automatically link against the downloaded
dependencies (from the setup stage), compile each source file, link them
together, then also run the compiled game. Sorry, no precompiled packages yet. I
can't be bothered.

Anyways, enjoy minesweeper! With AI, even!

## NixOS

Some of the keen among you might have noticed a wild `flake.nix` in this
project. Not to be the bearer of dashed hopes, but I have been unable to get the
project working under Nix using flakes (yet). You might just have to wait for
proper nix/flake support to be implemented. Worry not, though, as I'm
(semi-actively) working on it!
