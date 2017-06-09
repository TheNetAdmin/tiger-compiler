import os
import codecs
import shutil
import sys


def split_files(filename):
    file_path = filename.split('.')[0] + '/'
    try:
        os.mkdir(file_path)
    except Exception as e:
        print("Dir exists: "+file_path+' , remove and remake dir')
        shutil.rmtree(file_path)
        os.mkdir(file_path)
    base_filename = 'graph'
    file_no = 0
    file_ext = '.txt'
    content = str()
    for line in codecs.open(filename, 'r', 'utf-8'):
        if line.startswith('---'):
            file_no += 1
            out_filename = base_filename + str(file_no) + file_ext
            with codecs.open(file_path+out_filename, 'w', 'utf-8') as f:
                f.write(content)
            content = str()
        else:
            content += line


def print_graphs(file_path):
    os.chdir(file_path)
    for parent, dirnames, filenames in os.walk('.'):
        for filename in filenames:
            if filename.endswith('txt'):
                os.system('dot '+filename+' -Tjpg -o '+filename.split('.')[0]+'.jpg')


if __name__ == '__main__':
    filename = sys.argv[1]
    path = filename.split('.')[0]
    split_files(filename)
    print_graphs(path)
