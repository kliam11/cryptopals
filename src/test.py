import func
import base64
import utility


def test_hex_to_base64():
    hex_str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

    hex_bytes = bytes.fromhex(hex_str)
    
    return func.hex_to_base64(hex_bytes).decode('utf-8') == result

def test_fixed_xor():
    b_input1 = bytes.fromhex("1c0111001f010100061a024b53535009181c")
    b_input2 = bytes.fromhex("686974207468652062756c6c277320657965")
    result = "746865206b696420646f6e277420706c6179"

    return func.fixed_xor(b_input1, b_input2).hex() == result

def test_single_xor_cipher():
    result = "Cooking MC's like a pound of bacon"
    input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"
    msg_key_pair = func.single_xor_cipher(bytes.fromhex(input))

    msg: str = ""
    key = None
    maxScore: int = 0
    for (msg_b, key_b) in msg_key_pair:
        msg_h = msg_b.decode(errors="ignore")
        score = utility._char_freq(msg_h)
        if score > maxScore: 
            maxScore = score
            msg = msg_h
            key = key_b.hex()

    return msg == result and key == '58'


if __name__ == '__main__':
    print("test_hex_to_base64:", test_hex_to_base64())
    print("test_fixed_xor:", test_fixed_xor())
    print("test_single_xor_cipher:", test_single_xor_cipher())

