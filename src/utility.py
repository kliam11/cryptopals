import string
import sys
from typing import List, Tuple


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

def char_freq_do(input: List[Tuple[bytes, bytes]]) -> str:
    msg: str = ""
    key = None
    maxScore: int = 0
    for (msg_b, key_b) in input:
        msg_h = msg_b.decode(errors="ignore")
        score = _char_freq(msg_h)
        if score > maxScore: 
            maxScore = score
            msg = msg_h
            key = key_b.hex()
    
    return msg, key

