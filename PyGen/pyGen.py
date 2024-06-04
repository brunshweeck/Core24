
# Find the last ID
import sys
import os

if __name__ == '__main__':
    srcFile = open(file="pySrc.txt", mode="rt", encoding="US-ASCII", newline="\n")
    dstFile = open(file="pyDst.txt", mode="wt", encoding="US-ASCII", newline="\n")
    lines = srcFile.readlines()
    text = "".join(lines)
    text = text.upper()
    text = text.replace("\"", "")
    text = text.replace("\r\n", "\n")
    text = text.replace("\n\\U", ",\n0x")
    text = text.replace("\n\\0", ",\n00")
    text = text.replace("\n\\1", ",\n01")
    text = text.replace("\n\\2", ",\n02")
    text = text.replace("\n\\3", ",\n03")
    text = text.replace("\n\\4", ",\n04")
    text = text.replace("\n\\5", ",\n05")
    text = text.replace("\n\\6", ",\n06")
    text = text.replace("\n\\7", ",\n07")
    text = text.replace("\\U", ", 0x")
    text = text.replace("\\0", ", 00")
    text = text.replace("\\1", ", 01")
    text = text.replace("\\2", ", 02")
    text = text.replace("\\3", ", 03")
    text = text.replace("\\4", ", 04")
    text = text.replace("\\5", ", 05")
    text = text.replace("\\6", ", 06")
    text = text.replace("\\7", ", 07")
    text = text.removeprefix(", ")
    dstFile.write("{\n%s\n}" % text)

    srcFile.close()
    dstFile.close()

