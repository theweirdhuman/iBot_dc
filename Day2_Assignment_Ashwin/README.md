# Circle Detector using OpenCV


## Objective

Implement a circle detection program using the Hough Circle Transform to detect, visualize, and analyze circular objects in images.

## Implementation Summary

 - Images are loaded and converted to grayscale

 - Histogram equalization is applied to enhance contrast (helps low-contrast images)

 - Gaussian blur (11×11) reduces noise before detection

 - Circles are detected using cv2.HoughCircles

 - Results are visualized with:

    - Green circle outlines

    - Red center points

    - ID and radius labels

 - Detection statistics are computed and saved to file

## Parameter Tuning

The accumulator threshold (param2) is taken as user input at runtime, allowing interactive tuning for different images. Other parameters are set to stable defaults and adjusted during testing as needed.

## Size Classification

Detected circles are classified into small, medium, and large categories based on their relative radii. Each category is visualized using a distinct color to enable intuitive comparison.


## Statistics

For each image, the following are reported:

 - Total number of circles

 - Minimum radius

 - Maximum radius

 - Average radius

Statistics are:

 - Printed to the terminal

 - Appended to results/statistics.txt (labeled by image name and parameter value)

## Testing

The program was tested on:

 - Clean circular objects (e.g. basketball)

 - Overlapping circular patterns (e.g. bubbles)

 - Challenging images (noise, transparency, texture)

Strong results are obtained for images with clear circular edges. Performance degrades for transparent or highly textured objects, which is a known limitation of edge-based Hough detection.

## How to Run
```python3 circle_detector.py```


Enter:

 - Image path

 - Accumulator threshold (param2) when prompted

## Output Structure

results/  
├── <image_name>_result.jpg  
└── statistics.txt



## Notes

Histogram equalization improves detection in low-contrast images but may amplify noise in textured scenes.

Imperfect detection in challenging images reflects algorithm limitations, not implementation errors.