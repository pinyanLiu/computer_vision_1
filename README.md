# computer_vision_1
homework 1 of computer vision

# pre-setting up
### Required Packages
* cmake or ccmake 3.10
* git
* opencv 4.4.0 
`$ sudo apt install git `
`$ sudo apt install cmake `
method of building opencv in linux,please refer to the follow tutorial link:
https://docs.opencv.org/4.4.0/d7/d9f/tutorial_linux_install.html
Please make sure to make install the opencv library


#build method
    $ git clone https://github.com/pinyanLiu/computer_vision_1
    $ cd computer_vision_1/
    $ mkdir build
    $ cmake ..
    $ make


#execut method
### with opencv 
`./build/util/with_lib *path to the sample picture InputImage*`
for example 
`./build/util/with_lib ../../HW1/InputImage`

### without opencv 
`./build/test/no_lib  *path to the sample picture InputImage*`
for example 
`./build/test/no_lib  ../../HW1/InputImage`