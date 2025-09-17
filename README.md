# LightYears
A 2D bullet-hell scrolling shooter spaceship fighting game made with **C++**, **SFML**, and **CMake**.

---

## To fix linking error after making a visual studio build

1. In Visual Studio, right-click **LightYearsGame Project** in the **Solution Explorer**.
2. Go to: Properties -> Linker -> Input -> Additional Dependencies
3. Copy and Paste the following libraries:
```plaintext
..\LightYearsEngine\Debug\LightYearsEngine.lib
..\_deps\sfml-build\lib\Debug\sfml-window-d.lib
..\_deps\sfml-build\lib\Debug\sfml-system-d.lib
..\_deps\sfml-build\lib\Debug\sfml-audio-d.lib
..\_deps\sfml-build\lib\Debug\sfml-graphics-d.lib
kernel32.lib
user32.lib
gdi32.lib
winspool.lib
shell32.lib
ole32.lib
oleaut32.lib
uuid.lib
comdlg32.lib
advapi32.lib
