# FurnaceVGMtoGBStudio
A very simple tool that removes the headers from a VGM file made with Furnace that causes issues within GB Studio.

If you are having issues with the wrong channels being silenced while an FX made in Furnace runs in your GB Studio game this will fix it.

Currently untested with VGM files exported from applications other than Furnace.

# How It Works
The program copies the exact way of removing the headers as though it was done manually with a hex editor but automates the process for you.

Because the program looks for a hardcoded block of data in a vgm file if Furnace ever updates the location of the header the program may no longer work.

This was built on Furnace v0.6.8.3 for the export format version 1.72. Experience may vary depending on version.

# Before You Use This Software
I heavily suggest ending all sounds made in Furnace with EC09 (note cut) and FF99 (End Track) to avoid issues post-conversion.

<img width="380" height="136" alt="image" src="https://github.com/user-attachments/assets/a6f372a0-8e0c-4b64-b912-e5b47f797f11" />


I also HIGHLY recommend reading through the great guide written by Beatscribe as an introduction to Furnace and how to properly export a VGM file for this program.

It'll also give you a better understanding of exactly what this program is doing.

READ IT HERE: https://gbstudiocentral.com/article-series/vgm-sound-effects/

# Installation And Usage

Windows
- Download the most recent release and unzip
- Put any VGM files for conversion into the "src" folder
- Run the FurnaceVGMtoGBstudio.exe
- Source files will be untouched and new files will be output into the "out" folder

Linux
- Clone the repo to your machine
- Compile with ````gcc main.c -o main````
- Run once to setup the directory ````./main```` 
- Put any VGM files for conversion into the "src" folder
- Run again ````./main````
- Source files will be untouched and new files will be output into the "out" folder






