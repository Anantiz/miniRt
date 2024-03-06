def print_bits_with_padding(n, width):
    """
    Prints the binary representation of an integer with leading zeros for padding.

    Args:
        n (int): The integer to print.
        width (int): The total width of the binary representation, including padding.
    """
    binary_str = bin(n)[2:]  # Convert integer to binary string and remove '0b' prefix
    padded_str = binary_str.zfill(width)  # Add leading zeros for padding
    print(padded_str)

# Test the function
if __name__ == "__main__":
    number = -2
    width = 32  # Total width of the binary representation, including padding
    print("Binary representation of", number, "with padding is:")
    print_bits_with_padding(number, width)
