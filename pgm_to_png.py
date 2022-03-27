import os

PWD = os.getcwd()
LABELS = ["cameraman", "lena", "mandril", "pirate", "peppers", "house"]
OUTPUT_DIRECTORIES = [f"{PWD}/output/{label}/histogram/" for label in LABELS]
CAMERAMAN_DIR = f"{PWD}\\output\\cameraman\\histogram\\"

def main():
    #for dir in OUTPUT_DIRECTORIES:
    print(PWD)
    print(CAMERAMAN_DIR)
    for dir in OUTPUT_DIRECTORIES:
        for file in os.listdir(dir):
            if not "png" in file and not "csv" in file:
                command = f"convert {dir}{file} {dir}png/{file.split('.pgm')[0] + '.png'}"
                os.system(command)

if __name__ == "__main__":
    main()