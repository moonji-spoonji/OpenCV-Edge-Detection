This software is architectured as follows.

iptools -This folder hosts the files that are compiled into a static library. 
	image - This folder hosts the files that define an image. (without OpenCV)
	utility - This folder hosts the implemented algorithms.
	roi - This folder hosts the roi structure
	
lib- This folder hosts the static libraries associated with this software.

project- This folder hosts the files that will be compiled into executables.
	bin- This folder hosts the binary executables created in the project directory.



*** INSTALATION ***

On Linux

Enter the project directory in terminal and run make
The executable file will be created in bin/



*** Run the program:
cd bin/
./iptool parameters.txt
./iptool parameters2.txt
./iptool parameters3.txt
./iptool parameters4.txt


*** FUNCTIONS (without OpenCV) ***

1. Add intensity: add
Increase the intensity for a gray-level image.
parameter: intensity

2. Binarization: binarize
Binarize the pixels with the threshold.
parameter: threshold

3. Scaling: Scale
Reduce or expand the heigh and width with two scale factors.
Scaling factor = 2: double height and width of the input image.
Scaling factor = 0.5: half height and width of the input image.
parameter: scaling_factor



*** FUNCTIONS (with OpenCV) ***

1. Gray Scale: gray
Change whole image to gray-level.
parameter: no

2. Average Blur: blur_avg
Uniform smoothing.
parameter: window_size

3. Gaussian Smoothing and Sobel: gausobel5


4. Sobel with Kernel Size 3x3: sobel3


5. Sobel with Kernel Size 5x5: sobel5


6. Otsu Thresholding: Otsu


7. Canny Technique: canny


8: Extra Credit: extraCredit




*** PARAMETERS FILE ***
(Please check parameters.txt)
There are four parameters:
1. the input file name
2. the output file name
3. opencv / FUNCTIONS (without OpenCV): skip to 5 for parameters
4. the name of the function with OpenCV. Check FUNCTIONS (with OpenCV).
5. parameters (Check FUNCTIONS (with OpenCV) for parameters)





These are the given parameters from original download:
baboon.pgm baboon_bi125.pgm binarize 125
baboon.pgm baboon_add50.pgm add 50
baboon.pgm baboon_s200.pgm scale 2
baboon.pgm baboon_s50.pgm scale 0.5
11.jpg 11_gray.jpg opencv gray
11.jpg 11_blur.jpg opencv blur_avg 5


These are tests for the given parameters but with my images:
jackie-chan-confused.jpg jackie-gray.jpg opencv gray
jackie-chan-confused.jpg jackie-blur.jpg opencv blur_avg 15


These are parameters I used to test my own gausobel5 function: 
baboon.pgm baboon_gaus5.ppm opencv gausobel5
jackie-chan-confused.pgm jackie_gaus5.ppm opencv gausobel5
11.jpg 11_gaus9.ppm opencv gausobel5

baboon.pgm baboon-otsu-1.pgm opencv otsu
jackie-chan-confused.pgm jackie-otsu-1.pgm opencv otsu

jackie-chan-confused.jpg jackie-canny-BEST.pgm opencv canny
shrek-gallery-3.jpg shrek-canny5.pgm opencv canny

baboon.pgm baboon-sobel3-1.pgm opencv sobel3
Lenna.png Lenna-sobel3-1.pgm opencv sobel3

baboon.pgm baboon-sobel-1.pgm opencv sobel5
Lenna.png Lenna-sobel-1.pgm opencv sobel5