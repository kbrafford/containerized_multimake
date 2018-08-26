# containerized_multimake
Make system for producing Win, Linux, and Mac binaries using Docker containers

You provide C or CPP source code for:
 * An executable
 * A library
 * Or both

And this containerized make system will produce a `.tar.gz` archive of the build products for Windows, Linux, and Mac.  

Note: for the Mac outputs you have to run the build on a mac, as that part of the build process is not containerized. If you run the containerized_multimake on Windows or Linux you only get Windows and Linux outputs.

The sample included in this repo defines an application with one source file (`main.c`) that also has a library with one source file (`mylib.c`):

```#
# SECTION 1: What we are making
#
# APPNAME is the name of the executable
APPNAME := example

# LIBNAME is the name of the static lib and DLL
LIBNAME := mylib

# ARCHIVENAME is the name of the gzipped up bundle of deliverables
ARCHIVENAME := bundle

#
# SECTION 2: What our inputs are (i.e. the source files)
#

# APPSRC is the list of source files for the application
_SRCDIR := src
_APPSRCFILES := main.c 
APPSRC := $(addprefix $(_SRCDIR)/, $(_APPSRCFILES))

# LIBSRC is the list of source files for the library
_LIBSRCFILES := mylib.c
LIBSRC := $(addprefix $(_SRCDIR)/, $(_LIBSRCFILES))
```
And the result of the build is an archive with the following contents:

#### Linux Deliverables
| File                              | Description                     |
| --------------------------------- |:-------------------------------:|
| /bundle/build/linux/example       |   32-bit linux application      |
| /bundle/build/linux/example64     |   64-bit linux application      |
| /bundle/build/linux/libmylib.a    |   32-bit linux static library   |
| /bundle/build/linux/libmylib.so   |   32-bit linux shared library   |
| /bundle/build/linux/libmylib64.a  |   64-bit linux static library   |
| /bundle/build/linux/libmylib64.so |   64-bit linux shared library   |

#### Mac Deliverables
| File                               | Description            |
| -----------------------------------|:----------------------:|
| /bundle/build/mac/example          |   Mac application      |
| /bundle/build/mac/libmylib.a       |   Mac static library   |
| /bundle/build/mac/libmylib.dynlib  |   Mac shared library   |

#### Windows Deliverables
| File                             | Description                     |
| ---------------------------------|:-------------------------------:|
| /bundle/build/win/example.exe    |   32-bit Windows application      |
| /bundle/build/win/example64.exe  |   64-bit Windows application      |
| /bundle/build/win/libmylib.a     |   32-bit Windows static library   |
| /bundle/build/win/libmylib.dll   |   32-bit Windows shared library   |
| /bundle/build/win/libmylib64.a   |   64-bit Windows static library   |
| /bundle/build/win/libmylib64.dll |   64-bit Windows shared library   |
