import string
import sys


def _char_freq(input: str) -> int:
    '''
    Determines the frequency of valid plaintext characters
    '''
    english_freq = "etaoinshrdlcumwfgypbvkjxqz "
    
    score = 0
    for char in input.lower():
        if char in english_freq:
            score += 1
    return score

