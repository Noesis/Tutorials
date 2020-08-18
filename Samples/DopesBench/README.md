# Dopes Test Benchmark

![Screenshot](https://raw.githubusercontent.com/Noesis/Noesis.github.io/master/NoesisGUI/Samples/DopesBench/Screenshot.png)

NoesisGUI version of Dopes test benchmark shown on this [reddit post](https://www.reddit.com/r/FlutterDev/comments/gztwcu/flutter_performance_considerations_vs_react_and/?utm_source=share&utm_medium=web2x).

Used the following repositories as reference:
 * https://github.com/unoplatform/uno.dopesbench
 * https://github.com/maxim-saplin/dopetest_flutter

These are the results for the @Build test, where new TextBlocks are continuously created every frame.

## Results on Desktop

![DesktopChart](https://raw.githubusercontent.com/Noesis/Noesis.github.io/master/NoesisGUI/Samples/DopesBench/chartDesktop.png)

| Technology | Core i7-7900F |
| ---------- | ------------: |
| NoesisGUI | 63873 |
| NoesisGUI/web | 8019 |
| WPF | 7590 |
| Uno/UWP | 5640 |

EXE:

* [DopesBench-native-Noesis.exe](https://github.com/Noesis/Tutorials/releases/download/3.0.0/DopesBench-native-Noesis.exe)
* [DopesBench.html](https://noesisengine.com/webgl/DopesBench.html)

## Results on Android

![AndroidChart](https://raw.githubusercontent.com/Noesis/Noesis.github.io/master/NoesisGUI/Samples/DopesBench/chartAndroid.png)

| Technology | Snapdragon 730 |
| ---------- | -------------: |
| NoesisGUI | 17726 |
| Flutter | 5365 |
| NoesisGUI | 1670 |
| Uno/UWP | 352 |

APKs:

* [DopesBench-android-Noesis.apk](https://github.com/Noesis/Tutorials/releases/download/3.0.0/DopesBench-android-Noesis.apk)
* [DopesBench-android-Flutter.apk](https://github.com/Noesis/Tutorials/releases/download/3.0.0/DopesBench-android-Flutter.apk)
* [DopesBench-android-Uno.apk](https://github.com/Noesis/Tutorials/releases/download/3.0.0/DopesBench-android-Uno.apk)
