from tkinter.tix import IMAGE
from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
import cv2

ROOT_DIR = "C:/Users/Christian/Desktop/School/Research/edge_detection/"
OUTPUT_DIR = ROOT_DIR + "output/"
IMAGE_DIR = ROOT_DIR + "images/"
IMAGE_LABELS = ["cameraman", "lena", "mandril", "pirate"]

ORIGINAL_IMAGE_PATHS = [f"{IMAGE_DIR}{label}_gray.tif" for label in IMAGE_LABELS]
EQUALIZED_IMAGE_PATHS = [f"{OUTPUT_DIR}{label}/histogram/{label}_equalized_histogram.pgm" for label in IMAGE_LABELS]

ORIGINAL_RELATIVE_PATHS = [f"{OUTPUT_DIR}{label}/histogram/{label}_original.csv" for label in IMAGE_LABELS]
ORIGINAL_CUMULATIVE_PATHS = [f"{OUTPUT_DIR}{label}/histogram/{label}_cumulative_original.csv" for label in IMAGE_LABELS]

EQUALIZED_RELATIVE_PATHS = [f"{OUTPUT_DIR}{label}/histogram/{label}_equalized.csv" for label in IMAGE_LABELS]
EQUALIZED_CUMULATIVE_PATHS = [f"{OUTPUT_DIR}{label}/histogram/{label}_cumulative_equalized.csv" for label in IMAGE_LABELS]


for index, label in enumerate(IMAGE_LABELS):
    original_relative_path = ORIGINAL_RELATIVE_PATHS[index]
    original_cumulative_path = ORIGINAL_CUMULATIVE_PATHS[index]

    equalized_relative_path = EQUALIZED_RELATIVE_PATHS[index]
    equalized_cumulative_path = EQUALIZED_CUMULATIVE_PATHS[index]


    original_df = pd.read_csv(original_cumulative_path, header=None)
    original_df2 = pd.read_csv(original_relative_path, header=None)
    original_relative_freq = [x / 262_144 for x in original_df2.iloc[:, 1]]

    equalized_df = pd.read_csv(equalized_cumulative_path, header=None)
    equalized_df2 = pd.read_csv(equalized_relative_path, header=None)
    equalized_relative_freq = [x / 262_144 for x in equalized_df2.iloc[:, 1]]

    original_path = ORIGINAL_IMAGE_PATHS[index]
    equalized_path = EQUALIZED_IMAGE_PATHS[index]

    original = cv2.imread(original_path)
    cumulative = cv2.imread(equalized_path)

    fig = plt.figure(figsize=(9, 9))
    rows, columns = 3, 2

    fig.add_subplot(rows, columns, 1)
    plt.imshow(original)
    plt.axis('off')
    plt.title("Original Image")

    fig.add_subplot(rows, columns, 2)
    plt.imshow(cumulative)
    plt.axis('off')
    plt.title("Equalized Image")


    fig.add_subplot(rows, columns, 3)
    plt.grid(True)
    plt.plot(list(range(0, 256)), original_relative_freq, color="b")
    plt.xlabel("Intensity Value")
    plt.ylabel("Relative Frequency")

    fig.add_subplot(rows, columns, 4)
    plt.grid(True)
    plt.plot(list(range(0, 256)), equalized_relative_freq, color="b")
    plt.xlabel("Intensity Value")
    plt.ylabel("Relative Frequency")


    fig.add_subplot(rows, columns, 5)
    plt.grid(True)
    plt.plot(list(range(0, 256)), original_df.iloc[:, 1], color="b")
    plt.xlabel("Intensity Value")
    plt.ylabel("Cumulative Frequency")

    fig.add_subplot(rows, columns, 6)
    plt.grid(True)
    plt.plot(list(range(0, 256)), equalized_df.iloc[:, 1], color="b")
    plt.xlabel("Intensity Value")
    plt.ylabel("Cumulative Frequency")

    plt.savefig(f"figures/{label}_equalization.png")

# hist = {x: flat_df.count(x) for x in list(range(0, 256))}

# for key, value in hist.items():
#     print(f"{key}: {value}")
