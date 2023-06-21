for number in range(101):
    if number % 3 == 0 and number % 5 == 0:
        print("foobar")
    elif number % 3 == 0:
        print("foo")
    elif number % 5 == 0:
        print("bar")
    else:
        print(number)
