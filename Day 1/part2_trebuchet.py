valid_digits = {
        'one':   1,
        'two':   2,
        'three': 3,
        'four':  4,
        'five':  5,
        'six':   6,
        'seven': 7,
        'eight': 8,
        'nine':  9,
        }

def main():
    sum = 0
    with open('input', 'r') as input:
        lines: list[str] = input.readlines()
        lines = list(map(lambda line: line.strip(), lines))

        for line in lines:
            digits: list[int] = []

            for index, character in enumerate(line):
                if character.isdigit():
                    digits.append(int(character))
                    continue

                for valid_digit_str, valid_digit in valid_digits.items():
                    line_sub = line[index:index+len(valid_digit_str)]
                    if line_sub != valid_digit_str:
                        continue

                    digits.append(valid_digit)
                    break

            number = digits[0] * 10 + digits[-1]
            sum += number
    print(f'{sum=}')

if __name__ == "__main__":
    main()
