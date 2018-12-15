
Debian
====================
This directory contains files used to package viced/vice-qt
for Debian-based Linux systems. If you compile viced/vice-qt yourself, there are some useful files here.

## vice: URI support ##


vice-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install vice-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your viceqt binary to `/usr/bin`
and the `../../share/pixmaps/vice128.png` to `/usr/share/pixmaps`

vice-qt.protocol (KDE)

