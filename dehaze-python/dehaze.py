# -*- coding: utf-8 -*-
import cv2
import numpy as np
import argparse


def dark_channel(img, size = 7):
    r, g, b = cv2.split(img)
    min_img = cv2.min(r, cv2.min(g, b))
    kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (size, size))
    dc_img = cv2.erode(min_img,kernel)
    return dc_img


def get_atmo(img, percent =0.1):
    mean_perpix = np.mean(img, axis = 2).reshape(-1)
    mean_perpix = np.sort(mean_perpix)
    mean_topper = mean_perpix[int(img.shape[0] * img.shape[1] * (1-percent) ):]
    return np.mean(mean_topper)


def get_trans(img, atom, w = 0.95):
    x = img / atom
    t = 1 - w * dark_channel(x, 3)
    return t


def guided_filter(p, i, r, e):
    """
    :param p: input image
    :param i: guidance image
    :param r: radius
    :param e: regularization
    :return: filtering output q
    """
    #1
    mean_I = cv2.boxFilter(i, cv2.CV_64F, (r, r))
    mean_p = cv2.boxFilter(p, cv2.CV_64F, (r, r))
    corr_I = cv2.boxFilter(i * i, cv2.CV_64F, (r, r))
    corr_Ip = cv2.boxFilter(i * p, cv2.CV_64F, (r, r))
    #2
    var_I = ( corr_I - mean_I * mean_I ) + e
    cov_Ip = corr_Ip - mean_I * mean_p
    #3
    a = cov_Ip / var_I
    b = mean_p - a * mean_I
    #4
    print(a)
    mean_a = cv2.boxFilter(a, cv2.CV_64F, (r, r))
    mean_b = cv2.boxFilter(b, cv2.CV_64F, (r, r))
    #5
    q = mean_a * i + mean_b
    return q


def dehaze(path, output = None, is_save = True):
    im = cv2.imread(path)
    img = im.astype('float64') / 255
    img_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY).astype('float64') / 255

    atom = get_atmo(img)

    trans = get_trans(img, atom)
    trans_guided = guided_filter(trans, img_gray, 10, 0.0001)
    trans_guided = cv2.max(trans_guided, 0.25)

    result = np.empty_like(img)
    for i in range(3):
        result[:, :, i] = (img[:, :, i] - atom) / trans_guided + atom

    cv2.imshow("source",img)
    cv2.imshow("result", result)
    cv2.waitKey()
    
    if output is not None and is_save:
        cv2.imwrite(output, result * 255)


default_image = 'foggyHouse.jpg'
src_path = 'image/'
result_path = 'result02/'
src_image = src_path + default_image
result_image = result_path + default_image
parser = argparse.ArgumentParser()

parser.add_argument('-i', '--input', type=str, default=src_image)
parser.add_argument('-o', '--output', type=str, default=result_image)
parser.add_argument('-is_save', '--is_save', type=bool, default=True)
args = parser.parse_args()


if __name__ == '__main__':
    if args.input is None:
        dehaze('image/canon3.bmp')
    else:
        dehaze(args.input, args.output, args.is_save)