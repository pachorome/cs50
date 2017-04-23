import cs50

def main():
    print ("Hello, how much change is owed?", end="")
    print()
    change1 = cs50.get_float()

    coins = 0
    change = change1 * 100

    while change > 0:
        if change >= 25:
            change -= 25
            coins += 1

        elif change >= 10:
            change -= 10
            coins += 1

        elif change >= 5:
            change -= 5
            coins += 1

        elif change >= 1:
            change -= 1
            coins += 1

    print (coins)

if __name__ == "__main__":
    main()