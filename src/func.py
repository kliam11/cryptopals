import base64
import utility


def hex_to_base64(input: bytes) -> bytes:
    return base64.b64encode(input)

def fixed_xor(input1: bytes, input2: bytes):
    if(len(input1) != len(input2)): return
    return bytes([b1 ^ b2 for b1, b2 in zip(input1, input2)])

def single_xor_cipher(input: bytes) -> [(bytes, str)]:
    for byte in input:
        for i in range(128):
            print(chr(i))


        # msg += byte ^ key

def 