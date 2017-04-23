import cs50

def main():

    while True:
        print("Height: ", end="")
        i = cs50.get_int()


        if i > 0 and i < 24:
            break


    for k in range (i):
        a = i - k
        print(' ' * a, end="")
        print('#' * (k+2), end="")
        print()

if __name__ == "__main__":
    main()