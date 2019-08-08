# Colorir438 ![project icon](res/48x48.ico)
Colorir438 is a super-tiny editor for its own simple image format made to draw and visualize small images/pixel arts on the Command Prompt
by mimicking pixels using two ASCII 219 characters together (██).

## Table of contents
- [Editor](#editor)
- [The Colorir438 (``.c438``) file format](#the-Colorir438-c438-file-format)
  - [Format](#format)
  - [Definitions](#definitions)
  - [Example](#example)
- [**Download**](#download)
- [Built with](#built-with)
- [Acknoledgments](#acknowledgements)

## Editor
**(Not implemented yet)**
While in the editor, you can edit the currently opened image by using the editor commands. 

Use a command by pressing its key shortcut, for example, 
pressing ``h`` will show a list of commands (the keys varies according to the executable language).

## The Colorir438 (``.c438``) file format
Sometimes editing with the editor can be slow, but with the Colorir438 format it's easy to edit the images manually with any text editor.

### Format
When you open a ``.c438`` file with a text editor, you will find something this format:
```
Colorir438 <Image height> <Image width> <Background color>
<Matrix of pixels (characters)>
```
### Definitions
- **``Colorir438 ``**: Case sensitive characters sequence that ``Colorir438.exe`` uses to identify the file 
and start reading it with the Colorir438 format.
- **Image height**: A positive integer which tells the width in "pixels" of the image. 
  - It is recommended to be <= 300, and
for a width > 100, is it recommended to reduce the font size of the cmd to be able to properly see the image.
- **Image width**: A positive integer which tells the height in "pixels" of the image. 
  - It is recommended to be <= 500.
- **Background color**: The character that represents a color that the Command Prompt will change its background to while visualizing the image.
This is recommended when using black outline pixels in Command Prompts with black background. The available characters are:
  - ``[0-9]|[A-F]``: A numerical or alphabethic (A-F only) that represents an hexadecimal number from 0 to 16 where which number represents a color.
  Available colors: 
  ![0](https://placehold.it/10/000000/?text=+) 0 
  ![1](https://placehold.it/10/0000ff/?text=+) 1 
  ![2](https://placehold.it/10/008000/?text=+) 2 
  ![3](https://placehold.it/10/008080/?text=+) 3 
  ![4](https://placehold.it/10/800000/?text=+) 4 
  ![5](https://placehold.it/10/800080/?text=+) 5 
  ![6](https://placehold.it/10/808000/?text=+) 6 
  ![7](https://placehold.it/10/c0c0c0/?text=+) 7 
  ![8](https://placehold.it/10/808080/?text=+) 8 
  ![9](https://placehold.it/10/0000ff/?text=+) 9 
  ![A](https://placehold.it/10/00ff00/?text=+) A 
  ![B](https://placehold.it/10/00ffff/?text=+) B 
  ![C](https://placehold.it/10/ff0000/?text=+) C 
  ![D](https://placehold.it/10/ff00ff/?text=+) D 
  ![E](https://placehold.it/10/ffff00/?text=+) E 
  ![F](https://placehold.it/10/ffffff/?text=+) F.
  - ``-`` (dash): You can disable the change in the background color by using a dash instead of one of the above. 
  The background then will not change and it will be the normal current color of the cmd's background.

- **Matrix of pixels**: A sequence of characters where each character represents a pixel. Line breaks are ignored. 
 The available characters are: 
  - ``[0-9]|[A-F]``: A numerical or alphabethic (A-F only) that represents an hexadecimal number from 0 to 16 where which number represents a color.
  Available colors: 
  ![0](https://placehold.it/10/000000/?text=+) 0 
  ![1](https://placehold.it/10/0000ff/?text=+) 1 
  ![2](https://placehold.it/10/008000/?text=+) 2 
  ![3](https://placehold.it/10/008080/?text=+) 3 
  ![4](https://placehold.it/10/800000/?text=+) 4 
  ![5](https://placehold.it/10/800080/?text=+) 5 
  ![6](https://placehold.it/10/808000/?text=+) 6 
  ![7](https://placehold.it/10/c0c0c0/?text=+) 7
  ![8](https://placehold.it/10/808080/?text=+) 8 
  ![9](https://placehold.it/10/0000ff/?text=+) 9 
  ![A](https://placehold.it/10/00ff00/?text=+) A 
  ![B](https://placehold.it/10/00ffff/?text=+) B 
  ![C](https://placehold.it/10/ff0000/?text=+) C 
  ![D](https://placehold.it/10/ff00ff/?text=+) D 
  ![E](https://placehold.it/10/ffff00/?text=+) E 
  ![F](https://placehold.it/10/ffffff/?text=+) F.
  - (space): You can mark a pixel as transparent with an space, it will then be covered by the background color. 
 ### Example
 Using the definitions above, a ``.c438`` file containing the below will result on the image:
```
Colorir438 16 16 F
     000000     
   00CCCCFF00   
  0FFCCCCFFFF0  
 0FFCCCCCCFFFF0 
 0FCCFFFFCCFFF0 
0CCCFFFFFFCCCCC0
0CCCFFFFFFCCFFC0
0FCCFFFFFFCFFFF0
0FFCCFFFFCCFFFF0
0FFCCCCCCCCCFFC0
0FCC00000000CCC0
 000FF0FF0FF000 
  0FFF0FF0FFF0  
  0FFFFFFFFFF0  
   0FFFFFFFF0   
    00000000    
```
![example_mushroom](https://user-images.githubusercontent.com/44736064/62418620-e1457380-b643-11e9-8f76-51228e9c8687.png)

## Directly visualizing images
If you made or saved a ``.c438`` file, you don't need to open the editor just to visualize the image. Try using:
### Right click "Open With"
  1. Right click on the file and click on "Open With"
  2. Find and select ``Colorir438.exe``
  3. Opening the ``.c438`` file now will launch a pop-up console showing the image
### Path argument
``Colorir438.exe`` will try to open a image located in path given by the first argument, 
so running in the cmd the command ``Colorir438 path/to/image`` will launch a pop-up console showing the image. Example:

<p align="center">
  <img src="https://user-images.githubusercontent.com/44736064/62417338-5a809e80-b623-11e9-8770-087b8ce7771d.gif">
</p>

## Download
See [Releases](https://github.com/g-otn/Colorir438/releases/), the ``.zip`` containing the executable is in the "Assets" of a release.

## Built with
This project uses the ``_textcolor`` and the ``_textbackground`` functions from the [Pelles C](https://www.pellesc.de/index.php?page=overview) ``conio.h``.
It allows to change the text color or background of a single character, instead of the whole Command Prompt (like the ``color`` cmd command).

## Acknowledgements
This project was inspired by the Coloring (IED-001) slideshow by Prof. Dr. Silvio do Lago Pereira of FATEC-SP's TI dept.
