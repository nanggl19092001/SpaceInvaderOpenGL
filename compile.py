from xml.etree.ElementInclude import include
import subprocess

file_name = "SpaceInvaderRe"

include_dir = "dependencies/include"
lib_dir = "dependencies/lib"

lib = "-lglfw3 -lglew32s -lopengl32 -lgdi32"

preprocess = "-DGLEW_STATIC"
def main():

    subprocess.call(f"g++ {preprocess} -c *.cpp -I {include_dir}")

    #link
    subprocess.call(f"g++ *.o -o {file_name} -L {lib_dir} {lib}")

if "__main__" == __name__:
    main()
