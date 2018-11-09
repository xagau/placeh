WINDOWS BUILD NOTES
====================

Below are some notes on how to build placeh core for Windows.

Most developers use cross-compilation from Ubuntu to build executables for
Windows. Cross-compilation is also used to build the release binaries.

Currently only building on Ubuntu Trusty 14.04 or Ubuntu Zesty 17.04 or later is supported.
Building on Ubuntu Xenial 16.04 is known to be broken, see extensive discussion in issue [8732](https://github.com/bitcoin/bitcoin/issues/8732).
While it may be possible to do so with work arounds, it's potentially dangerous and not recommended.

While there are potentially a number of ways to build on Windows (for example using msys / mingw-w64),
using the Windows Subsystem For Linux is the most straightforward. If you are building with
another method, please contribute the instructions here for others who are running versions
of Windows that are not compatible with the Windows Subsystem for Linux.

Compiling with Windows Subsystem For Linux
-------------------------------------------

With Windows 10, Microsoft has released a new feature named the [Windows
Subsystem for Linux](https://msdn.microsoft.com/commandline/wsl/about). This
feature allows you to run a bash shell directly on Windows in an Ubuntu-based
environment. Within this environment you can cross compile for Windows without
the need for a separate Linux VM or server.

This feature is not supported in versions of Windows prior to Windows 10 or on
Windows Server SKUs. In addition, it is available [only for 64-bit versions of
Windows](https://msdn.microsoft.com/en-us/commandline/wsl/install_guide).

To get the bash shell, you must first activate the feature in Windows.

1. Turn on Developer Mode
  * Open Settings -> Update and Security -> For developers
  * Select the Developer Mode radio button
  * Restart if necessary
2. Enable the Windows Subsystem for Linux feature
  * From Start, search for "Turn Windows features on or off" (type 'turn')
  * Select Windows Subsystem for Linux (beta)
  * Click OK
  * Restart if necessary
3. Complete Installation
  * Open a cmd prompt and type "bash"
  * Accept the license
  * Create a new UNIX user account (this is a separate account from your Windows account)

After the bash shell is active, you can follow the instructions below, starting
with the "Cross-compilation" section. Compiling the 64-bit version is
recommended but it is possible to compile the 32-bit version.

Github:
-------------------
Get a copy of the repo from github
0. If you are cloning under WSL make sure you use git config --global core.autocrlf true
1. git clone https://www.githu.com/xagau/placeh.git
2. See further build instructions below.

Cross-compilation
-------------------

These steps can be performed on, for example, an Ubuntu VM. The depends system
will also work on other Linux distributions, however the commands for
installing the toolchain will be different.

First, install the general dependencies:

    sudo apt-get install build-essential libtool autotools-dev automake pkg-config bsdmainutils curl

A host toolchain (`build-essential`) is necessary because some dependency
packages (such as `protobuf`) need to build host utilities that are used in the
build process.


If you're building on Ubuntu 17.04 or later, run these two commands, selecting the 'posix' variant for both,
to work around issues with mingw-w64. See issue [8732](https://github.com/xagau/placeh/issues/8732) for more information.
```
sudo update-alternatives --config x86_64-w64-mingw32-g++
sudo update-alternatives --config x86_64-w64-mingw32-gcc
```

## Building for 64-bit Windows

* At present, getting placeh to build on windows 64 running WSL has not been accomplished.
If you run into difficulty, try to build for windows 32 bit.

To build executables for Windows 64-bit, install the following dependencies:

    sudo apt-get install g++-mingw-w64-x86-64 mingw-w64-x86-64-dev

Then build using:

    PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') # strip out problematic Windows %PATH% imported var
    cd depends
    make HOST=x86_64-w64-mingw32
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/x86_64-w64-mingw32/share/config.site ./configure --prefix=/
    make HOST=x86_64-w64-mingw32

## Building for 32-bit Windows

To build executables for Windows 32-bit, install the following dependencies:

    sudo apt-get install g++-mingw-w64-i686 mingw-w64-i686-dev

Then build (if you are using WSL you must be using from ROOT) using:

    PATH=$(echo "$PATH" | sed -e 's/:\/mnt.*//g') # strip out problematic Windows %PATH% imported var
    cd depends
    make HOST=i686-w64-mingw32 V=1 AUTOCONF=: AUTOHEADER=: AUTOMAKE=: ACLOCAL=:
    # if it stops, try building again with 
    cd ..
    ./autogen.sh # not required when building from tarball
    CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=/
    make -j8 -k V=1

Sometimes, depending on how you have setup WSL you may need to either remove or add "AUTOCONF=: AUTOHEADER=: AUTOMAKE=: ACLOCAL=:" according to your system.

You may need to 

## Depends system

For further documentation on the depends system see [README.md](../depends/README.md) in the depends directory.

Bundling
-------------
You will want to make sure you bundle up placeh-qt.exe, placeh-cli.exe, placeh-tx.exe, placehd.exe, placeh.conf with  your distribution.

Installation
-------------

After building using the Windows subsystem it can be useful to copy the compiled
executables to a directory on the windows drive in the same directory structure
as they appear in the release `.zip` archive. This can be done in the following
way. This will install to `c:\workspace\placeh`, for example:

    make install DESTDIR=/mnt/c/workspace/placeh
    
    
Xagau's Build Notes for WSL
--------------
If you have problems with the above, please try build from a clean WSL installation with this script

```
sudo apt-get install libdb4.8-dev libdb4.8++-dev
sudo apt-get install libssl-dev libevent-dev libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-test-dev libboost-thread-dev

sudo apt install software-properties-common
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu zesty universe"
sudo apt update
sudo apt install build-essential libtool autotools-dev automake pkg-config bsdmainutils curl git
sudo apt install g++-mingw-w64-i686 mingw-w64-i686-dev
git clone https://github.com/xagau/placeh.git
cd placeh/
cd depends/
make HOST=i686-w64-mingw32 V=1
cd ..
./autogen.sh
./configure --prefix=`pwd`/depends/i686-w64-mingw32 --enable-static --disable-shared --with-qt
make V=1
```

