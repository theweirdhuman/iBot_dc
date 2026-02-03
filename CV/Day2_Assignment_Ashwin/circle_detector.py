import cv2
import numpy as np
import matplotlib.pyplot as plt
import os


def preprocess_image(image_path):
    '''
    Docstring for preprocess_image
    
    Args:
        :param image_path: Path of the input image
    '''


    image = cv2.imread(image_path) #load image

    if image is None:
        print("Error! Image not found!")
        return (None, None)
    
    grayscale = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    incContrast = cv2.equalizeHist(grayscale)
    gaussBlurred = cv2.GaussianBlur(incContrast, (11,11), 0)

    return (image, gaussBlurred)


def detect_circles(gray_image, dp=1, minDist=20, param1=50, param2=40, minRadius=10, maxRadius=100):
    '''
    Docstring for detect_circles

    Detects circles using Hough Circle Transform
    
    Args:
        :param gray_image: pre-processed image
        :param dp: ratio between image resolution and the Hough accumulator resolution
        :param minDist: minimum distance between two circles
        :param param1: Canny edge threshold
        :param param2: accumulator threshold (min. no. of votes to consider a circle)
        :param minRadius: minimum circle radius
        :param maxRadius: maximum circle radius

    Returns:
        circles: numpy array of circles (x,y,r) (or None)
    '''

    circles = cv2.HoughCircles(
        gray_image,
        cv2.HOUGH_GRADIENT,
        dp=dp,
        minDist=minDist,
        param1=param1,
        param2=param2,
        minRadius=minRadius,
        maxRadius=maxRadius
    )

    if circles is not None:
        circles = np.uint16(np.around(circles))

    return circles


def visualize_circles(image, circles, minRadius, maxRadius, save_path=None):
    '''
    Docstring for visualize_circles
    
    :param image: Original colour image
    :param circles: Array of detected circles
    :param save_path: Optional path to save the image (with circles shown)
    '''

    SIZE_COLOURS = {
        "small": (255, 0, 0),    # blue
        "medium": (0, 255, 255), # yellow
        "large": (0, 255, 0)     # green
    }


    annotated = image.copy()

    if circles is not None:
        for i, (x, y, r) in enumerate(circles[0]):
            size = classify_size(r, minRadius, maxRadius)
            colour = SIZE_COLOURS[size]

            cv2.circle(annotated, (x, y), r, colour, 2)

            cv2.circle(annotated, (x, y), 2, (0, 0, 255), 3)
            cv2.putText(
                annotated,
                f"ID {i}: r={r} ({size})",
                (x - 40, y - r - 10),
                cv2.FONT_HERSHEY_SIMPLEX,
                0.5,
                colour,
                1
            )

    # display
    plt.figure(figsize=(10, 5))
    plt.subplot(1, 2, 1)
    plt.imshow(cv2.cvtColor(image, cv2.COLOR_BGR2RGB))
    plt.title("Original")
    plt.axis("off")

    plt.subplot(1, 2, 2)
    plt.imshow(cv2.cvtColor(annotated, cv2.COLOR_BGR2RGB))
    plt.title("Detected Circles")
    plt.axis("off")

    plt.show()

    if save_path:
        cv2.imwrite(save_path, annotated)


def calculate_statistics(circles):
    '''
    Docstring for calculate_statistics
    
    :param circles: Array of detected circles

    Returns:
        a dictionary containing statistics of all the circles
    '''
    if circles is None:
        return {
            "count": 0,
            "min_radius": None,
            "max_radius": None,
            "avg_radius": None
        }

    radii = circles[0][:, 2]

    stats = {
        "count": len(radii),
        "min_radius": int(np.min(radii)),
        "max_radius": int(np.max(radii)),
        "avg_radius": float(np.mean(radii))
    }



    return stats

def classify_size(radius, min_r, max_r):
    """
    Docstring for classify_size
    
    Args:
        :param radius: radius of the considered circle
        :param min_r: min radius of all detected
        :param max_r: max radius of all detected

    Return:
        :rtype: Literal['small', 'medium', 'large']
    """

    if max_r - min_r < 10:
        return "medium"

    if radius < min_r + (max_r - min_r) / 3:
        return "small"
    elif radius < min_r + 2 * (max_r - min_r) / 3:
        return "medium"
    else:
        return "large"


def main():
    '''
    Docstring for main

    Main function.
    '''
    image_path = input("Enter image path: ").strip()

    try:
        acc = int(input("Enter accumulator threshold value (default 40): ") or 40)
    except ValueError:
        acc = 40

    if not os.path.exists(image_path):
        print("Error: File does not exist")
        return

    image, gray = preprocess_image(image_path)
    if image is None:
        return

    circles = detect_circles(gray, param2=acc)
    stats = calculate_statistics(circles)

    results_dir = "results"
    os.makedirs(results_dir, exist_ok=True)
    stats_path = os.path.join(results_dir, "statistics.txt")

    base_name = os.path.splitext(os.path.basename(image_path))[0]

    with open(stats_path, "a") as f:
        f.write(f"Circle Detection Statistics for file {base_name}\n\n")
        for key, value in stats.items():
            f.write(f"{key}: {value}\n")
        f.write(f"accumulator threshold: {acc}\n\n\n")


    print("Circle Statistics:")
    for key, value in stats.items():
        print(f"{key}: {value}")

    if circles is not None:
        visualize_circles(image, circles, minRadius=stats["min_radius"], maxRadius=stats["max_radius"], save_path=os.path.join(results_dir,f"{base_name}_result.jpg"))


if __name__ == "__main__":
    main()
