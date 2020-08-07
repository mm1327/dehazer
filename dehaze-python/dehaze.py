# -*- coding: utf-8 -*-
import cv2
import numpy as np
import argparse
import glob


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

    atmo = np.mean(mean_topper)
    avg_bir =  np.mean(mean_perpix)
    return atmo, avg_bir


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

    atom, avg_bir = get_atmo(img)

    trans = get_trans(img, atom)
    trans_guided = guided_filter(trans, img_gray, 5, 0.0001)
    trans_guided = cv2.max(trans_guided, 0.25)

    result = np.empty_like(img)
    for i in range(3):
        result[:, :, i] = (img[:, :, i] - atom) / trans_guided + atom
    result = result*255
    result[result[:,:,:] > 255] = 255
    result[result[:,:,:] < 0] = 0
    result = result.astype('uint8')
    gamma = 1.0 - 0.8 * ( atom - avg_bir )
    lut_table = [0]*256

    for i in range(256):
        lut_table[i] = pow( i / 255.0, gamma ) * 255.0
    n_lut = np.array(lut_table).clip(0,255).astype('uint8')
    lut = np.dstack((n_lut, n_lut, n_lut))

    result = cv2.LUT(result, lut) 

    cv2.imshow("source",img)
    cv2.imshow("result", result)
    cv2.waitKey(3000)
    
    if output is not None and is_save:
        name_sp = path.split('/')[-1]
        save_path = output + '/' + name_sp
        cv2.imwrite(save_path, result)

    



default_image = 'channel_01.jpg'
src_path = 'dehaze-python/image/*'
result_path = 'dehaze-python/result02/'
src_image = src_path + default_image
result_image = result_path + default_image
parser = argparse.ArgumentParser()

parser.add_argument('-i', '--input', type=str, default=src_path)
parser.add_argument('-o', '--output', type=str, default=result_path)
parser.add_argument('-is_save', '--is_save', type=bool, default=True)
args = parser.parse_args()


if __name__ == '__main__':

    image_list = glob.glob( args.input )
    for index, image_file in enumerate(image_list):
        dehaze(image_file, args.output, args.is_save)