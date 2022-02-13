import os


def main():
    PWD = os.getcwd()
    LABELS = ["cameraman", "lena", "mandril", "pirate"]
    OUTPUT_DIRECTORIES = [f"{PWD}/output/{label}/" for label in LABELS]
    test = OUTPUT_DIRECTORIES[0]
    print(PWD)
    print(test)
    print(os.listdir(test))

    for label, dir in zip(LABELS, OUTPUT_DIRECTORIES):
        for file in os.listdir(dir):
            command = f"convert {dir}{file} {dir}{file.split('.pgm')[0] + '.png'}"
            os.system(command)










if __name__ == "__main__":
    main()