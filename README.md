# Colorir438 ![project icon](res/48x48.ico)
Colorir438 is a tiny editor for its own simple image format made to draw and visualize small images/pixel arts on the Command Prompt
by mimicking pixels using two ASCII 219 characters together (██).

## Table of contents
- [Editor](#editor)
  - [Paint commands](#paint-commands)
  - [Image commands](#image-commands)
  - [File commands](#file-commands)
- [The Colorir438 (``.c438``) file format](#the-colorir438-c438-file-format)
  - [Format](#format)
  - [Definitions](#definitions)
  - [Example](#example)
- [Opening and running the project](#opening-and-running-the-project)
- [**Download**](#download)
- [Built with](#built-with)
- [Acknoledgments](#acknowledgements)

## Editor
You can edit images by using the editor commands. Use a command by pressing its case insensitive key shortcuts:
- **A** (Help): Show a list of commands and its shortcuts.
### Paint commands
- **1** or **P** (Point): Paints one pixel.
- **2** or **L** (Line): Draws an one pixel wide line from a pixel to another.

![linha](https://user-images.githubusercontent.com/44736064/62830763-60a9e880-bbea-11e9-8b70-7a5cf4a38d7f.gif)

### Image commands
- **4** or **B** (Background): Changes the background color.

![fundo](https://user-images.githubusercontent.com/44736064/62830761-5e478e80-bbea-11e9-84d1-7c44976a6944.gif)

- **Arrow keys** (Change size): Resizes the image from the right or bottom corner.

![tamanho](https://user-images.githubusercontent.com/44736064/62830765-630c4280-bbea-11e9-8b46-171a16c2bac1.gif)

- **5** or **M** (Move): Move the entire image to one direction.

![mover](https://user-images.githubusercontent.com/44736064/62830764-6273ac00-bbea-11e9-9e7c-7020a93b95d1.gif)

- **8** or **V** (Visualize): Displays the image with its color background and without the editor's rulers.

![visualizar](https://user-images.githubusercontent.com/44736064/62830766-656e9c80-bbea-11e9-9932-2f4285c2d185.gif)

### File commands
- **Esc** or **S** (Exit): Exits the editor and returns to the main menu.

## The Colorir438 (``.c438``) file format
Sometimes editing with the editor can be slow, but with the Colorir438 format it's easy to edit the images manually with any text editor.

### Format
When you open a ``.c438`` file with a text editor, you will find something within this format:
```
Colorir438 <Image height> <Image width> <Background color>
<Matrix of pixels (characters)>
```
### Definitions
- **``Colorir438 ``**: Case sensitive characters sequence that ``Colorir438.exe`` uses to identify the file 
and start reading it with the Colorir438 format.
- **Image height**: A positive integer which tells the height in "pixels" of the image. Recommended to be <= 300.
- **Image width**: A positive integer which tells the width in "pixels" of the image. Recommended to be <= 100.
- **Background color**: The character that represents a color that the Command Prompt will change its background to while visualizing the image. The available characters are:
  - ``[0-9]|[A-F]``: An hexadecimal digit.
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
  - ``[0-9]|[A-F]``: An hexadecimal digit.
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

You can find more examples in the ``images/`` project folder.

## Directly visualizing images
If you made or saved a ``.c438`` file, you don't need to open the editor just to visualize the image. Try using:
### Explorer's "Open With"
  1. Right click on the file and click on "Open With"
  2. Find and select ``Colorir438.exe``
  3. Opening the ``.c438`` file now will launch a pop-up console showing the image
### Path argument
``Colorir438.exe`` will try to open a image located in path given by the first argument, 
so running in the cmd the command ``Colorir438 path/to/image`` will launch a pop-up console showing the image. Example:

<p align="center">
  <img src="https://user-images.githubusercontent.com/44736064/62417338-5a809e80-b623-11e9-8770-087b8ce7771d.gif">
</p>

## Opening and running the project
1. Install [Pelles C](https://www.pellesc.de/index.php?page=download) (compatible with 9.0.0).
2. Open ``Colorir438.ppj``.
3. Click on Execute (Ctrl+F5).

## Download
See [Releases](https://github.com/g-otn/Colorir438/releases/), the ``.zip`` containing the executable is in the "Assets" of a release.

## Built with
This project uses the ``_textcolor`` and the ``_textbackground`` functions from the [Pelles C](https://www.pellesc.de/index.php?page=overview) ``conio.h``.
It allows to change the text color or background of a single character, instead of the whole Command Prompt (like the ``color`` cmd command).

## Acknowledgements
This project was inspired by the Coloring (IED-001) slideshow by Prof. Dr. Silvio do Lago Pereira of FATEC-SP's TI dept.
