#!/usr/bin/python3
from PIL import Image

intensitySwap = " .:-|io@"

jpgfile = Image.open("pokeball.jpg")

print(jpgfile.getdata(), jpgfile.size, jpgfile.format)

asciiString = ""
n = 0
for i in jpgfile.getdata():
    if n % 50 == 0:
        n=0
        asciiString+="\n"
    intensity = (i[0]*75 + i[1]*155 + i[2]*25) // 255 //32
    asciiString += " " + str(intensitySwap[intensity])
    n += 1
print(asciiString)
