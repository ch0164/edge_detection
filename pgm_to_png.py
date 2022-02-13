import os

PWD = os.getcwd()
LABELS = ["cameraman", "lena", "mandril", "pirate"]
OUTPUT_DIRECTORIES = [f"{PWD}/output/{label}/" for label in LABELS]

def main():
    for dir in OUTPUT_DIRECTORIES:
        for file in os.listdir(dir):
            if not "png" in file:
                command = f"convert {dir}{file} {dir}png/{file.split('.pgm')[0] + '.png'}"
                os.system(command)

if __name__ == "__main__":
    main()