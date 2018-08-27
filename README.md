# containerized_multimake
Make system for producing Win, Linux, and Mac binaries using Docker containers

You provide C or CPP source code for:
 * An executable
 * A library
 * Or both

And this containerized make system will produce a `.tar.gz` archive of the build products for Windows, Linux, and Mac.  

Note: for the Mac outputs you have to run the build on a mac, as that part of the build process is not containerized. If you run the containerized_multimake on Windows or Linux you only get Windows and Linux outputs.


#### Host Environment Prequisites
| Host    | GNU Tools                                                 | Python                           | Docker                                                                    |
| ------- |:---------------------------------------------------------:|:--------------------------------:|:-------------------------------------------------------------------------:|
| Windows | [make](http://gnuwin32.sourceforge.net/packages/make.htm)<br/> *make sure make.exe is added to the PATH* | [python](https://www.python.org/)<br /> *make sure python.exe is added to the PATH*| [Docker For Windows](https://docs.docker.com/docker-for-windows/install/)<br />-or-<br /> [Docker Toolbox](https://docs.docker.com/toolbox/toolbox_install_windows/) |
| Mac     | [XCode Command line tools](http://railsapps.github.io/xcode-command-line-tools.html) | (python pre-installed)| [Docker For Mac](https://docs.docker.com/docker-for-mac/install/) |
| Linux   | ```sudo apt-get install build-essential``` | ```sudo apt-get install python```| See Linux Docker instructions below |

#### Advanced Docker Setup

I typically set up Docker on my Linux machine thusly:
```
# First import the GPG key
sudo apt-key adv --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys \
58118E89F3A912897C070ADBF76221572C52609D

# Next, point the package manager to the official Docker repository
sudo apt-add-repository 'deb https://apt.dockerproject.org/repo ubuntu-xenial main'

# Installing both packages will eliminate an unmet dependencies error when you try to install the 
# linux-image-extra-virtual by itself
sudo apt install -y linux-image-generic linux-image-extra-virtual
 
# Reboot the system so it would be running on the newly installed kernel image 
sudo reboot
```

Then do this.  The group add step is to make sure you can run the makefile without needing to `sudo` all the time:
```
sudo apt install -y docker.io
sudo groupadd docker
sudo usermod -aG docker $USER
```


#### Containers Being Used
| Target OS         | Container        |  Source  |
| -------------- |-------------|------------|
| Windows  | [https://hub.docker.com/r/kbrafford/win-gcc/](https://hub.docker.com/r/kbrafford/win-gcc/) | [https://github.com/kbrafford/win-gcc](https://github.com/kbrafford/win-gcc)|
| Linux    | [https://hub.docker.com/r/kbrafford/x86_64-linux-gcc/](https://hub.docker.com/r/kbrafford/x86_64-linux-gcc/) |[https://github.com/kbrafford/x86_64-linux-gcc](https://github.com/kbrafford/x86_64-linux-gcc)|
| Mac OS X | (N/A -- Mac builds are handled natively, but on mac only)


**Note:** On Windows 7 and 10 using Docker Toolbox, I find that I need to check out this repo in C:\Users\Public in order for Docker to correctly get the *-v* volume mapping option to work. I do not know why this is, but it appears to be normally expected behavior, so I don't assume it's a big problem.

**Note:** This has been tested on Windows, Linux, and Mac.

**Note:** If you're on Linux or Mac, make sure `_getcwd.py` is marked as executable.  I'll stop using this python hack once I figure out the best way to migrate that hack into the makefile, but that will have to wait until I get all of my test setups working.


#### How to use the Makefile
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

