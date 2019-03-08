#!python3
#
# download_dep.py
#
# Purpose:
# Get all required Windows 64 dependencies using a single file
#
# Usage:
# Simple run the file from within its folder
#

# put here a list of all libraries which have to be present
libraries = ['boost-1.64.0', 'glew-2.0.0', 'glfw-3.2.1', 'glm-0.9.8.4', 'libpng-1.6.28', 'zlib-1.2.1']

# establish path
import os              # os functions
import urllib.request  # downloading files
import zipfile         # unzipping files

script_path = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_path, '..'))
lib_dir = os.path.abspath(os.path.join(root_dir, 'vendor'))

print("Checking for root library folder...")
if(os.path.exists(lib_dir)):
    print("%s folder found." % str(lib_dir))
else:
    print("%s folder not present, creating..." % str(lib_dir))
    os.makedirs(lib_dir)
print("\n")

for lib in libraries:
    print("Checking for: %s" % lib)
    lib_path = os.path.abspath(os.path.join(lib_dir, lib + '-win-x64'))
    if(os.path.exists(lib_path)):
        print("%s folder already exists, assuming library is correctly installed." % str(lib_path))
    else:
        print("%s folder not found, downloading package..." % str(lib_path))
        libname = "%s-win-x64.zip" % lib
        url = "http://www.ivofilot.nl/downloads/packages/%s" % libname
        target = os.path.abspath(os.path.join(lib_dir, libname))
        print("Downloading %s" % url)
        urllib.request.urlretrieve(url, target)
        print("Download complete, unzipping...")
        zip_ref = zipfile.ZipFile(target, 'r')
        zip_ref.extractall(lib_dir)
        zip_ref.close()

print("\n")
print("All done!")
print("--------------------------")
print("Press [ENTER] key to close")
input()
