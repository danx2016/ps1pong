# PS1 Pong 6

Very simple pong implementation for PS1 using MIPS toolchain + Nugget + Psy-Q Dev Kit.


## How to Build ##

* Install Visual Studio Code + PSX.DEV extension (https://www.youtube.com/watch?v=KbAv-Ao7lzU)
* Clone this repository using:
```
git clone --recurse-submodules https://github.com/danx2016/ps1pong.git
```
psyq-iwyu and nugget folders inside third_party directory are git submodules (independent projects referenced in another locations), so you need to use '--recurse-submodules' flag to include them 
* Inside vscode, Ctrl + Shift + P -> 'PSX.Dev: Show panel > WELCOME > Restore Psy-Q'. This will restore the Psy-Q SDK files inside 'third_party/psyq' folder
* Then, to build ps-exe, just type inside project directory:
```
make
```

