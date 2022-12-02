import string
import glob
import sys

if __name__ == '__main__':
    if len(sys.argv)<3:
        print("three arguments is needed")
        exit()
    template=sys.argv[1]
    with open(template, 'r', encoding='utf-8') as f:
        template_txt = string.Template(f.read())
    d = {}
    for i in range(2,len(sys.argv)):
        file=sys.argv[i]
        with open(file, 'r', encoding='utf-8') as f:
            file_txt = f.read()
            file_txt = file_txt[:-1]
            d[file]=file_txt
    result = template_txt.safe_substitute(d)
    print(result)
