# [Coding Math](https://www.youtube.com/playlist?list=PL7wAPgl1JVvUEb0dIygHzO4698tmcwLk9)

## Setup
* Linux:
    * Install libffi-dev and libsdl2-dev.
* Windows:
    * I've kept a copy of the dlls you need on windows in this repo as libs.zip
      so you don't have to download everything if you're working on 64bit Win10.
    * Get [SDL2](https://www.libsdl.org/download-2.0.php)
    * Get [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
    * Get [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
    * Get [libffi](Install Gimp or Emacs and steal its libffi-6.dll)
    * Get GCC, etc. (for configuring libffi stuff):
        * Install [MSYS2](https://msys2.github.io/)
        * In MSYS2 Install: `pacman -S gcc libffi libffi-devel pkg-config`
        * Add `msys64/usr/bin` to your path. (so you can access gcc, etc.)


## Episodes
First: `(ql:quickload :sketch)`

* Ep 1:
    * No script, just an introduction.
* Ep 2:
    * `ep02.lisp`, basic trig, drawing a sine wave.
* Ep 3:
    * `ep03.lisp`, more trig, animating based on sine waves.
* Ep 4:
    * `ep04.lisp`, circles, lissajouse, how sin and cos make circles and animating using them.
* Ep 5:
    * `ep05.lisp`, atan, using arc tangent to angle an object at another object.
* Ep 6:
    * No script, just some basic theory about vectors.
* Ep 7:
    * `ep07.lisp`, vector.lisp, add some vector types.
* Ep 8:
    * `ep08.lisp`, particle.lisp, add a particle type that handles a position and velocity vector.
* Ep 9:
    * `ep09.lisp`, create and accelerate our particles to make fireworks.
* Ep 10:
    * `ep10.lisp`, handle a thrust vector and flight angle.
