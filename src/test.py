import func
import base64
import utility
import os


def test_hex_to_base64():
    hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

    hex_bytes = bytes.fromhex(hex_str)
    
    assert func.hex_to_base64(hex_bytes).decode('utf-8') == result

def test_fixed_xor():
    b_input1 = bytes.fromhex("1c0111001f010100061a024b53535009181c")
    b_input2 = bytes.fromhex("686974207468652062756c6c277320657965")
    result = "746865206b696420646f6e277420706c6179"

    assert func.fixed_xor(b_input1, b_input2).hex() == result

def test_single_xor_cipher():
    result = "Cooking MC's like a pound of bacon"
    input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

    msg_key_pair = func.single_xor_cipher(bytes.fromhex(input))
    msg, key = utility.char_freq_do(msg_key_pair)
    
    assert (msg == result) and (key == '58')

def test_detect_single_character_xor():
    result = "Now that the party is jumping\n"

    current_dir = os.path.dirname(__file__)
    file_path = os.path.join(current_dir, '../rsc/4.txt')
    file_path = os.path.abspath(file_path)

    lines = []
    with open(file_path, 'r') as file:
        while True:
            line = file.readline()
            if not line: 
                break
            lines.append(bytes.fromhex(line))
    
    msg, key = func.detect_single_character_xor(lines)

    assert (msg == result) and (key == '3335')

