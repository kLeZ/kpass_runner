# kpass_runner

## Build instructions

cd /where/your/runner/is/installed
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DQT_PLUGIN_INSTALL_DIR=/usr/lib64/qt5/plugins ..
make
make install (as root)

Restart krunner to load the runner
(in a terminal type:
kquitapp krunner
and then
krunner)

After this you should see your runner in the system settings:

systemsettings5 (Head to "Search")

You can also launch KRunner via Alt-F2 and you will find your runner.
