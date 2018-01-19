from VideoFingerPrint import *
from multiprocessing import Process
import os
import sys


def compare_videos(filename1, filename2):
    if not os.path.isfile(filename1) or not os.path.isfile(filename2):
        print("[x] Not found src or dst video file.")
        sys.exit(0)

    fingerprint = FingerPrint()
    output = fingerprint.compares(filename1, filename2)
    if output == 1:
        print("[!] Detected "+filename1+" fingerprint in "+filename2)
    if output == 0:
        print("[!] Not detected")


def video_process(src, dst, fingerprint_obj):
    if not os.path.isfile(src) or not os.path.isfile(dst):
        print("[x] Not found file. Please check file path")
        print("[x] Src: "+ src +" Dst: " +dst)
        sys.exit(0)
    if fingerprint_obj.check_video(dst):
        if fingerprint_obj.check_video(src):
            compare_videos(src, dst)
        else:
            fingerprint_obj.search_image(src, dst)
    else:
        print("[x] dst file must be a video. Please check destination file")


def read_filelist(listfile):
    fingerprint_obj = FingerPrint()
    procs = []
    with open(listfile) as f:
        lines = f.readlines()
        for line in lines:
            line = line.replace("\r\n", "").replace("\n","")
            src = line.split(",")[0]
            dst = line.split(",")[1]
            #compare_videos(src, dst)
            proc = Process(target=video_process, args=(src, dst, fingerprint_obj,))
            procs.append(proc)
            proc.start()
        for p in procs:
            p.join()
    f.close()


if __name__ == '__main__':
    option = 0
    if len(sys.argv)<2:
        print("[x] --Help")
        print("[!] Command: {python test.py listfile}")
        print("[!] Listfile format is follow {file1, file2}")
    list_file = sys.argv[1]
    if os.path.isfile(list_file):
        read_filelist(list_file)
    else:
        print("no such file exists at this time")
