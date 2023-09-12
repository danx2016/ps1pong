# PS1 Pong 6

Very simple pong implementation for PS1 using MIPS toolchain + Nugget + Psy-Q Dev Kit.

<b>warning:</b> this project uses <b>float</b> type which is strongly discouraged for consoles like PS1 according to the most experienced people in the PSX.Dev. The recommendation is to use <b>fixed point math</b> insted.

## How to Build ##

* Install Visual Studio Code + PSX.DEV extension (https://www.youtube.com/watch?v=KbAv-Ao7lzU)
* Clone this repository using:
```
git clone --recurse-submodules https://github.com/danx2016/ps1pong.git
```
<b>note:</b> psyq-iwyu and nugget folders inside third_party directory are git submodules (independent projects referenced in another locations), so you need to use '--recurse-submodules' flag to include them 
* Open the folder in vscode, then 'Ctrl + Shift + P -> PSX.Dev: Show panel > WELCOME > Restore Psy-Q'. This will restore the Psy-Q SDK files inside 'third_party/psyq' folder
* Then, to build ps-exe, just type inside project directory:
```
make
```


## Special Thanks To ##

* @Nicolas Noble
* @spicyjpeg
* @Lily
* @poly
* and all people from PSX.Dev
