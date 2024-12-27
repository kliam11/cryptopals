import base64
import utility
from typing import List, Tuple


def hex_to_base64(input: bytes) -> bytes:
    return base64.b64encode(input)

def fixed_xor(input1: bytes, input2: bytes):
    if(len(input1) != len(input2)): return
    return bytes([b1 ^ b2 for b1, b2 in zip(input1, input2)])

def single_xor_cipher(input: bytes) -> List[Tuple[bytes, bytes]]:
    msg_key_pair = []
    for i in range(256):
        b_i = bytes([i])
        xored = bytes([byte ^ i for byte in input])
        msg_key_pair.append((xored, b_i))
    return msg_key_pair

