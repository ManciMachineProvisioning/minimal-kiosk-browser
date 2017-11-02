# Minimalistic Kiosk browser

Based on:
https://github.com/pschultz/kiosk-browser

And the tutorial available here:
https://wiki.gnome.org/Projects/WebKitGtk/ProgrammingGuide/Tutorial

# Changes from the Original

* Use WebKit2.
* Remove unused features (reload, fullscreen toggle, signal handling).
* The X11 session started by the live image (https://github.com/ManciMachineProvisioning/browser-live-cd) does not have any kind of window manager so requesting the window to maximize wouldn't work. While a minimalistic window manager could be included later on right now it is implemented by querying the primary monitor width and height and setting it as the default window size.

# Building

```
apt-get install libwebkit2gtk-4.0-dev
make
```

# Usage

```
./provisioning-browser <url>
```
