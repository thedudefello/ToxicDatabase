# Simple image to binary converter used for the MBR payload of VineMEMZ

# The binary data contains the list of used colors and the raw pixel data.
# It is optimized for VGA mode 13h, so the image resolution has to be 320x200
# and the colors are reduced to 256 18-bit ones. No dithering is used, so
# complex pictures look like crap.

import sys, math, struct, os
from PIL import Image

img = Image.open(sys.argv[1])
nx, ny = img.size
if nx <> 320 or ny <> 200:
    img = img.convert('P', palette=Image.NEAREST, colors=256)
    img = img.resize((320, 200), Image.NEAREST)
    img.save(sys.argv[1])

colors = []

def color_distance(a, b):
	return math.sqrt((a[0]-b[0])**2 + (a[1]-b[1])**2 + (a[2]-b[2])**2)
	
def nearest_color(color):
	nearest = 0
	
	for i in range(len(colors)):
		if color_distance(color, colors[i]) < color_distance(color, colors[nearest]):
			nearest = i
	
	return nearest

img = Image.open(sys.argv[1]).convert("RGB")
w, h = img.size

# Generate the color table
for y in xrange(h):
	for x in xrange(w):
		color = img.getpixel((x, y))
		
		f = False
		for c in colors:
			if color == c[0]:
				c[1] += 1
				f = True
				
		if not f:
			colors.append([color, 1])
			
# Get the most used colors (at most 256)
colors = [c[0] for c in sorted(colors, key=lambda x: x[1], reverse=True)[:255]]

# Write the color table information
buf = chr(len(colors)) + "".join([chr(c[0]/4) + chr(c[1]/4) + chr(c[2]/4) for c in colors])

# Write the pixel data
for y in xrange(h):
	for x in xrange(w):
		color = img.getpixel((x, y))
		buf += chr(nearest_color(color))
		
img.close()
	
# Save the shit!
with open(sys.argv[2], "wb") as out:
	out.write(buf)