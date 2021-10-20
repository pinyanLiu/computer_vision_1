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


# build method
    $ git clone https://github.com/pinyanLiu/computer_vision_1
    $ cd computer_vision_1/
    $ mkdir build
    $ cmake ..
    $ make


# execute method
### with opencv 
`./build/util/with_lib *path to the sample picture InputImage*`  
for example   
`./build/util/with_lib ../../HW1/InputImage`  

### without opencv 
`./build/test/no_lib  *path to the sample picture InputImage*`  
for example   
`./build/test/no_lib  ../../HW1/InputImage`  

# program describe
### with opencv
which is processing in build/util/with_lib
using opencv functions like `imread` `imwrite` `rotate` `resize` to easily make changes to pictures.  
Mat is a convenient type to read rgb data ,so getting r,g,b pic respectively,just set the other two channel to 0.  

### without opencv
which is processing in build/test/no_lib   
I construct a class for this HW which contain the FILEs, the structure type of rgb,and three function for doing readwrite,channel_separation,and clock_wise_rotation.  
in the constructor , First reading the path which user type in,and get the input image.Then it will open file for the rest of pic by calling fopen().  
read_img() : cause we are not doing any change to the pic ,so i just use while() to read write the whole img data.   
channel_separation() : separate two phase to read the img. First,read the header,which is the first 54 unsigned char.Second,using two for loop to read data in the rgb structure.Then,for each channel we want to sepatate,just need to set the other channels to zero and write the remain channel .   
clock_wise_rotation() : cause the HW only request for a clock wise rotation, so I would rather not use a rotation matrix. Use two for loop, change the start point and the direction of writing img.   
