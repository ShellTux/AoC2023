def main():
    sum = 0
    with open('input', 'r') as input:
        lines: list[str] = input.readlines()
        lines = list(map(lambda line: line.strip(), lines))
        for line in lines:
            digits = tuple(filter(lambda c: c.isdigit(), line))

            number = int(digits[0] + digits[-1])
            sum += number
    print(f'{sum=}')

if __name__ == "__main__":
    main()
