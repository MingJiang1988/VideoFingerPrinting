import cv2
from PIL import Image


def dhash(image, hash_size = 8):
    image = image.convert('L').resize((hash_size+1, hash_size), Image.ANTIALIAS)
    pixels = list(image.getdata())
    difference = []
    for row in xrange(hash_size):
        for col in xrange(hash_size):
            pixel_left = image.getpixel((col, row))
            pixel_right = image.getpixel((col+1, row))
            difference.append(pixel_left > pixel_right)

    decimal_value = 0
    hex_string = []
    for index, value in enumerate(difference):
        if value:
            decimal_value += 2**(index % 8)
        if (index % 8 ) == 7:
            hex_string.append(hex(decimal_value)[2:].rjust(2, '0'))
            decimal_value = 0
    return ''.join(hex_string)


if __name__ == '__main__':
    image1 = cv2.imread("3_img_o.jpg")
    image2 = cv2.imread("333.jpg")



    cv2_im1 = cv2.cvtColor(image1, cv2.COLOR_BGR2RGB)
    pil_im1 = Image.fromarray(cv2_im1)
    gray_pil_img1 = pil_im1.convert('LA')
    hash1 = dhash(gray_pil_img1)
    print(hash1)


    cv2_im2 = cv2.cvtColor(image2, cv2.COLOR_BGR2RGB)
    pil_im2 = Image.fromarray(cv2_im2)
    gray_pil_img2 = pil_im2.convert('LA')
    hash2 = dhash(gray_pil_img2)
    print(hash2)
