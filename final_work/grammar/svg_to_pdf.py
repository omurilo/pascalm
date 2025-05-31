import cairosvg
import re
import os

def svg_to_pdf(svg_path):
    file_name = re.sub(r'.svg', '', svg_path)
    cairosvg.svg2pdf(url=svg_path, write_to=f"{file_name}.pdf")

for dirpath, dirnames, filenames, in os.walk("./diagram"):
    for filename in filenames:
        svg_to_pdf(f"diagram/{filename}")

