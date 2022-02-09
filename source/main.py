import matplotlib.pyplot as plt
import numpy as np

IMAGES_DIR = "images/"
#IMAGE_LABELS = ["lena", "mandril", "pirate", "cameraman"]
IMAGE_LABELS = ["house"]
IMAGE_PATHS = [f"{IMAGES_DIR}{label}_gray.tif" for label in IMAGE_LABELS]

OUTPUT_DIR = "output/"
SOBEL_OUTPUT_DIR = OUTPUT_DIR + "sobel/"
ROBERTS_OUTPUT_DIR = OUTPUT_DIR + "roberts/"
SOBEL_OUTPUT_PATHS = [f"{SOBEL_OUTPUT_DIR}{label}_gray_sobel.tiff" for label in IMAGE_LABELS]
ROBERTS_OUTPUT_PATHS = [f"{ROBERTS_OUTPUT_DIR}{label}_gray_roberts.tiff" for label in IMAGE_LABELS]

def main():
    S_v = np.matrix("-1 0 1; -2 0 2; -1 0 1")
    S_h = S_v.transpose()

    width, height = 512, 512
    V = np.zeros((width, height))  # Vertical edges
    H = np.zeros((width, height))  # Horizontal edges
    W = np.zeros((width, height))  # Convolution of vertical and horizontal edges

    # Sobel Operator
    for original_path, sobel_path in zip(IMAGE_PATHS, SOBEL_OUTPUT_PATHS):
        I = plt.imread(original_path)
        for i in range(1, width - 1):
            for j in range(1, height - 1):
                V[i, j] = I[i-1, j-1] * S_v[0, 0] \
                        + I[i-1, j+1] * S_v[0, 2] \
                        + I[i, j-1] * S_v[1, 0] \
                        + I[i, j+1] * S_v[1, 2] \
                        + I[i+1, j-1] * S_v[2, 0] \
                        + I[i+1, j+1] * S_v[2, 2]
                
                H[i, j] = I[i-1, j-1] * S_h[0, 0] \
                        + I[i-1, j+1] * S_h[0, 2] \
                        + I[i, j-1] * S_h[1, 0] \
                        + I[i, j+1] * S_h[1, 2] \
                        + I[i+1, j-1] * S_h[2, 0] \
                        + I[i+1, j+1] * S_h[2, 2]
                
                W[i, j] = np.sqrt(np.power(V[i, j], 2) + np.power(H[i, j], 2))

        plt.imsave(sobel_path, W)


if __name__ == "__main__":
    main()