Orx Template Project
============================

Building
--------

This project depends on the [Orx game engine](http://orx-project.org/). The first step 
is to get Orx, so do either:

* download ([from here](http://sourceforge.net/projects/orx/files/orx/nightly/)) 
all the orx-nightly development versions for the target platforms you're planning to 
compile the engine against. Extract the archives to a folder (all of the versions 
to the same folder) of your choosing.

or

* clone the orx [mercurial repo](https://bitbucket.org/orx/orx) or 
[the git repo](https://github.com/orx/orx) and build the binaries from source. 

Then create an environment variable called `$ORX_DIR` that points to the folder 
where you've cloned Orx or the extracted `orx-nightly` folder. Important Note: 
A misunderstaning here could cause unnecessary headache; if you're planning to use 
the binary distribution, `$ORX_DIR` should point to the folder where you extract
the zip, not to the `XYZ-dev` folder that comes out of the zip.

Building for Desktop Targets
----------------------------

For building the desktop versions, you need the 
[cmake](http://www.cmake.org/cmake/resources/software.html) build tool. 

To build the project for desktop:

    >> cd <REPO_ROOT>
    >> mkdir .build
    >> cd .build
    >> cmake ../src
    >> make 

In order to generate an Eclipse project for a debug build:

    >> cd <REPO_ROOT>
    >> mkdir .build_eclipse
    >> cd .build_eclipse
    >> cmake -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ../src/

Now you can import the project in Eclipse.

Building for Android
----------------------------------------------

You first need to prepare an Android development environment:

* [Download the Android SDK](http://developer.android.com/sdk/index.html#download) 
and extract it somewhere. Create an environment variable `$ANDROID_HOME` pointing to 
that folder. Use the `tools/android` package manager to download the Android API 
version 21 `SDK Platform`, the `Extras/Android Support Repository` and 
`Extras/Android Support Library`. I also recommend you to add the `platform-tools` 
folder to your `PATH`.
* [Download the Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) 
and extract it somewhere. Add that folder to your `PATH`.

Go to `REPO_ROOT/android` and issue `./gradlew build` to compile the Android 
application. You can use `.gradlew installDebug` to install the `.apk` to a connected 
device, and `.gradlew runDebug` to run it on the device, if you've [set your device 
for debugging directly on it](http://developer.android.com/tools/device.html).
