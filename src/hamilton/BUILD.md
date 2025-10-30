# Build

- Linux spezifisch programmiert
- Benötigte Abhängigkeiten:
```sh
sudo apt install make gtk4 libadwaita-1-0 libsecret-1-0 vte-2.91-gtk4 gcc libgtk-4-dev adb fastboot desktop-file-utils make dpkg-dev debhelper ccache libsecret-1-dev build-essential libadwaita-1-dev rsync git curl vte2.91-gtk4-dev curl pkexec xdg-desktop-portal, xdg-desktop-portal-gtk, xdg-utils
```

- Kompilieren:
```sh
make
``` 
→ sollte ein Fehler kommen nochmal `make` ausführen

- Ausführen mit:
```sh 
./hamilton_cli <function>
./hamilton_gui
```

- Aufräumen mit: 
```sh
make clean
```