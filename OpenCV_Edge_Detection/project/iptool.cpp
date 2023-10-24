#include "../iptools/core.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <sstream>
#include <math.h>


using namespace std;

#define MAXLEN 256

int main (int argc, char** argv)
{
	image src, tgt;
	FILE *fp;
	char str[MAXLEN];
	char infile[MAXLEN];
	char outfile[MAXLEN];
	char *pch;
	
	if ((fp = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "Can't open file: %s\n", argv[1]);
		exit(1);
	}

	while(fgets(str,MAXLEN,fp) != NULL) {
		if (strncmp(str,"#",1)==0) continue;
		int NumParameters = 0;
		
		pch = strtok(str, " ");
		strcpy(infile, pch);

		pch = strtok(NULL, " ");
		strcpy(outfile, pch);

		pch = strtok(NULL, " ");
		if (strncmp(pch,"opencv",6)==0) {
			cv::Mat I = cv::imread(infile);
			cv::Mat I2;
			
			if( I.empty()) {
				cout << "Could not open or find the image: " << infile << endl;
				return -1;
			}
			
			pch = strtok(NULL, " ");
			if (strncmp(pch,"gray",4)==0) {
				utility::cv_gray(I, I2);
			}
/************************ ADDED FUNCTION ************************/
			else if (strncmp(pch,"gausobel5",8)==0) {
				utility::gausobel5(I, I2);
			}
			else if(strncmp(pch,"sobel3",8)==0){
				utility::cv_sobel3(I, I2);
			}
			else if(strncmp(pch,"sobel5",8)==0){
				utility::cv_sobel5(I, I2);
			}
			else if(strncmp(pch,"canny",8)==0){
				utility::cv_canny(I, I2);
			}
			else if(strncmp(pch,"otsu",8)==0){
				utility::cv_otsu(I, I2);
			}
			else if(strncmp(pch,"extraCredit",8)==0){
				utility::cv_extraCredit(I, I2);
			}

			else if (strncmp(pch,"blur_avg",8)==0) {
				pch = strtok(NULL, " ");
				utility::cv_avgblur(I, I2, atoi(pch));
			}
			else {
				printf("No function: %s\n", pch);
				continue;
			}
			
			cv::imwrite(outfile, I2);
		}
		else {
			src.read(infile);
			if (strncmp(pch,"add",3)==0) {
				pch = strtok(NULL, " ");
				utility::addGrey(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"binarize",8)==0) {
				pch = strtok(NULL, " ");
				utility::binarize(src,tgt,atoi(pch));
			}

			else if (strncmp(pch,"scale",5)==0) {
				pch = strtok(NULL, " ");
				utility::scale(src,tgt,atof(pch));
			}

			else {
				printf("No function: %s\n", pch);
				continue;
			}
			
			tgt.save(outfile);
		}
	}
	fclose(fp);
	return 0;
}

