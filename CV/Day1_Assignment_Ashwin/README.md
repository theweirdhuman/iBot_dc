# Pencil Sketch using OpenCV


## Description

This program converts an input image into a pencil sketch using classical computer vision techniques in OpenCV. The sketch effect is created using grayscale conversion, image inversion, Gaussian blur, and dodge blending.

## Requirements
```pip install opencv-python numpy matplotlib```

## Usage
Run the script:
```python3 pencil_sketch.py```


Enter:
 - Image path
 - lur kernel size (odd integer, default = 21)

## Output

Displays original and sketch side-by-side
Saves the sketch to:
```output_sketches/<image_name>_output.jpg```

## Notes

Larger blur kernels produce smoother sketches

Smaller kernels produce sharper lines - which are often more faint
