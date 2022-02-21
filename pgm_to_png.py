import os

PWD = os.getcwd()
LABELS = ["cameraman", "lena", "mandril", "pirate"]
OUTPUT_DIRECTORIES = [f"{PWD}/output/{label}/histogram/" for label in LABELS]
CAMERAMAN_DIR = f"{PWD}\\output\\cameraman\\histogram\\"

def main():
    #for dir in OUTPUT_DIRECTORIES:
    print(PWD)
    print(CAMERAMAN_DIR)
    for file in os.listdir(CAMERAMAN_DIR):
        if not "png" in file and not "csv" in file:
            command = f"convert {CAMERAMAN_DIR}{file} {CAMERAMAN_DIR}png/{file.split('.pgm')[0] + '.png'}"
            os.system(command)

if __name__ == "__main__":
    main()