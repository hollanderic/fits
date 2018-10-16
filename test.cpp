
#include "fits.h"

#include <stdio.h>


#include <opencv2/highgui.hpp>

int main(int argc, const char **argv) {
	//std::shared_ptr<Fits> f;
	auto f=Fits::Open("500.fit");
    f->printRecords();
    imshow("plot", f->getMatRGB(0.24));
    cv::waitKey();
	return 0;

}