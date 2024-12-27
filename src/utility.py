import string


def _char_freq(input: str) -> int:
    '''
    Determines the frequency of valid plaintext characters
    '''
    char_s = set(string.printable)
    return sum(1 for char in input if char in char_s)

