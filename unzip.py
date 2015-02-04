#!/usr/bin/python

import glob
import os
import os.path
import zipfile

if __name__ == '__main__':
    names = glob.glob('*.abc.zip')
    cwd = os.getcwd()
    for name in names:
        short_name = name.split('/')[-1]
        pre = short_name.split('.')[0]
        pwd = 'cocos2d: ERROR: Invalid filename ' + pre
        try:
            zf = zipfile.ZipFile(name)
            zf.extractall(os.path.join(cwd, pre), None, pwd)
            zf.close()
        except zipfile.BadZipfile:
            print(name)
