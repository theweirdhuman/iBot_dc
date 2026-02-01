import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def pencil_sketch(image_path, blur_kernel=21):
    """
    Converts an image into a pencil sketch.

    Args:
        image_path (str): path of the image that is input
        blur_kernel (int): Gaussian blur size, default set to 21

    Returns:
        original_rgb, sketch (or None, None incase of an error)
    """

    if blur_kernel%2 == 0:
        blur_kernel+=1


    image = cv2.imread(image_path) #load image

    if image is None:
        print("Error! Image not found!")
        return None, None
    
    grayscale = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

    inverted = 255 - grayscale

    gaussBlurred = cv2.GaussianBlur(inverted, (blur_kernel,blur_kernel), 0)

    invertedBlur = 255 - gaussBlurred

    sketch = grayscale.astype(np.float32) / (invertedBlur.astype(np.float32) + 1e-6)
    sketch = sketch * 256
    sketch = np.clip(sketch, 0, 255).astype(np.uint8)
    #sketch = cv2.convertScaleAbs(sketch, alpha=1.2, beta=0)



    original_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    return original_rgb, sketch


def display_result (original, sketch, save_path = None ):
    """
    Displays original and sketch side -by - side .
    
    Args:
        original: Original image (RGB)
        sketch: Sketch image (grayscale)
        save_path: Optional path to save the sketch
    """

    plt.figure(figsize=(10, 5))

    plt.subplot(1, 2, 1)
    plt.imshow(original)
    plt.title("Original")
    plt.axis("off")

    plt.subplot(1, 2, 2)
    plt.imshow(sketch, cmap="gray")
    plt.title("Pencil Sketch")
    plt.axis("off")

    plt.show()

    if save_path is not None:
        cv2.imwrite(save_path, sketch)


def main():
    '''
    Docstring for main

    Calls the other functions
    '''

    image_path = input("Enter image path: ").strip()
    kernel_input = input("Enter kernel size for blurring (default 21): ").strip()

    blur_kernel = int(kernel_input) if kernel_input else 21

    if not os.path.exists(image_path):
        print("Error: File does not exist")
        return

    original, sketch = pencil_sketch(image_path,blur_kernel)

    if original is None:
        return

    base_name = os.path.splitext(os.path.basename(image_path))[0]
    output_path = f"output_sketches/{base_name}_output.jpg"
    display_result(original, sketch, output_path)


if __name__ == "__main__":
    main()
