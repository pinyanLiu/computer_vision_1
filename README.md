# computer_vision_1
homework  of computer vision

# pre-setting up
### Required Packages
* cmake or ccmake 3.10
* git
* opencv 4.4.0   
* opencv_contrib 4.4.0   

`$ sudo apt install git `  
`$ sudo apt install cmake `  
method of building *opencv* and *opencv_contrib* in linux,please refer to the follow tutorial link:  
https://docs.opencv.org/4.4.0/d7/d9f/tutorial_linux_install.html  
Please make sure to make install the opencv library  


# build method
    $ git clone https://github.com/pinyanLiu/computer_vision_1
    $ cd computer_vision_1/
    $ mkdir build
    $ cd build
    $ cmake ..
    $ make


# execute method
### with opencv 
`./build/util/with_lib 1.path to the video 2. level `
for example   
`./build/util/with_lib ./with_lib MOT17-09-SDP-raw.webm 5`    

# Final Project describe
## program describe

1. `which is processing in build/util/with_lib`   
2. `which gives you 6 result : video of each level`
2. `Use CV::Tracker for object tracking `
3. `Use CSRT as the main tracker`
32. `When the object been blocked by another object,especially Level3 and Level4,stop the upgrade of cv::Tracker`
23. `restart upgrade after they have crossed by `

# Third homework describe
## program describe
### with opencv
1. `which is processing in build/util/with_lib`   
2. `which gives you four result 1.cannyBGR.bmp 2.bird.bmg 3.bird_crop.bmp 4.stitch.bmp locate at build/util`
2. `use canny() to detect edge`
3. `use HoughLinesP() to find line and colored with RGB`
32. `use getPerspectiveTransform() to get the transform matrix`
23. `use warpPerspective() to transform origin img to warping data`
23. `create stitcher to stitch two picture`

### without opencv
1. `which is processing in build/test/warpWithCpp`
2. `which gives you two result 1.World.bmp 2.Image.bmg locate at build/test`
2. `lib is locate at lib/img_warp`
1. `a very fatal mistake i made is that i set the initial variables with 'int' which makes the whole transform incorrect,they should be set as 'float' or 'double' . It cost me two days for this stupid bug  :(`
23. `imageToWorld() using X() and Y() to transform each pixel,and then forward warp the origin img`
23. `worldToImage() using U() and V() to transform each pixel,and then inverse warp the origin img `
# Second homework describe
## program describe
### with opencv
1. `which is processing in build/util/with_lib`   
2. `using opencv functions such as cvtcolor(),threshold(),dilate(),erode(),connectedComponentsWithStats()`      

### without opencv
1. `which is processing in build/test/no_lib`   
2. `My binarizing method is different from the general one ,cause i didn't write the gray_scale function,so it may only usable in this case.`     
3. `I use while loop check every pixel from top-left to bot-right,and then do it again in the inverse direction utill no changes happended.`  
4. `I spend to much time on debuging the connectedcomponent part,so I didn't finish the remain part.`   
   



# First homework
## program describe
### with opencv
1. `which is processing in build/util/with_lib`   
2. `using opencv functions like imread() imwrite() rotate() resize() to easily make changes to pictures.`     
3. `Mat is a convenient type to read rgb data ,so getting r,g,b pic respectively,just set the other two channel to 0.`     

### without opencv
1. `which is processing in build/test/no_lib`   
2. `I construct a class for this HW which contain the FILEs, the structure type of rgb,and three function for doing readwrite,channel_separation,and clock_wise_rotation.`     
3. `In the constructor , First reading the path which user type in,and get the input image.Then it will open file for the rest of pic by calling fopen().`  
4. `read_img() : cause we are not doing any change to the pic ,so i just use while() to read write the whole img data.`   
5. `channel_separation() : separate two phase to read the img. First,read the header,which is the first 54 unsigned char.Second,using two for loop to read data in the rgb structure.Then,for each channel we want to sepatate,just need to set the other channels to zero and write the remain channel .`   
6. `clock_wise_rotation() : cause the HW only request for a clock wise rotation, so I would rather not use a rotation matrix. Use two for loop, change the start point and the direction of writing img.`   
