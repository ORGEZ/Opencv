#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
//char* filename = "C:\\Users\\acer1\\Pictures\\pr1.png";



IplImage* image = 0;
IplImage* dst = 0;

// ��� �������� ������� RGB
IplImage* rgb = 0;
IplImage* r_plane = 0;
IplImage* g_plane = 0;
IplImage* b_plane = 0;
// ��� �������� ������� RGB ����� ��������������
IplImage* r_range = 0;
IplImage* g_range = 0;
IplImage* b_range = 0;
// ��� �������� ��������� ��������
IplImage* yellow = 0;

int Rmin = 0;
int Rmax = 256;

int Gmin = 0;
int Gmax = 256;

int Bmin = 0;
int Bmax = 256;

int RGBmax = 256;

//
// �������-����������� ��������
//
/*void myTrackbarRmin(int pos) {
        Rmin = pos;
        cvInRangeS(r_plane, cvScalar(Rmin), cvScalar(Rmax), r_range);
}

void myTrackbarRmax(int pos) {
        Rmax = pos;
        cvInRangeS(r_plane, cvScalar(Rmin), cvScalar(Rmax), r_range);
}

void myTrackbarGmin(int pos) {
        Gmin = pos;
        cvInRangeS(g_plane, cvScalar(Gmin), cvScalar(Gmax), g_range);
}

void myTrackbarGmax(int pos) {
        Gmax = pos;
        cvInRangeS(g_plane, cvScalar(Gmin), cvScalar(Gmax), g_range);
}

void myTrackbarBmin(int pos) {
        Bmin = pos;
        cvInRangeS(b_plane, cvScalar(Bmin), cvScalar(Bmax), b_range);
}

void myTrackbarBmax(int pos) {
        Bmax = pos;
        cvInRangeS(b_plane, cvScalar(Bmin), cvScalar(Bmax), b_range);
}*/

int main(int argc, char* argv[])
{
        // ��� �������� ������� ������ ����������
        char* filename = "C:\\Users\\acer1\\Pictures\\pr1.png";
        // �������� ��������
        image = cvLoadImage(filename,1);
        printf("[i] image: %s\n", filename);
        assert( image != 0 );

        // ������ ��������
        rgb = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
        r_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        g_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        b_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        r_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        g_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        b_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        yellow = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        //  ��������
        cvCopyImage(image, rgb);
        // ��������� �� �������� ������
       cvSplit( rgb, b_plane, g_plane, r_plane, 0 );

        //
        // ���������� ����������� � ������������ ��������
        // � ������� HSV
     /*   double framemin=0;
        double framemax=0;

        cvMinMaxLoc(r_plane, &framemin, &framemax);
        printf("[R] %f x %f\n", framemin, framemax );
        Rmin = 254;
        Rmax = 256;
        cvMinMaxLoc(g_plane, &framemin, &framemax);
        printf("[G] %f x %f\n", framemin, framemax );
        Gmin = 241;
        Gmax = 256;
        cvMinMaxLoc(b_plane, &framemin, &framemax);
        printf("[B] %f x %f\n", framemin, framemax );
        Bmin = 0;
        Bmax = 0;*/

        // ���� ��� ����������� ��������
        cvNamedWindow("original",CV_WINDOW_AUTOSIZE);
        cvNamedWindow("Yellow",CV_WINDOW_AUTOSIZE);
      /*  cvCreateTrackbar("Rmin", "R range", &Rmin, RGBmax, myTrackbarRmin);
        cvCreateTrackbar("Rmax", "R range", &Rmax, RGBmax, myTrackbarRmax);
        cvCreateTrackbar("Gmin", "G range", &Gmin, RGBmax, myTrackbarGmin);
        cvCreateTrackbar("Gmax", "G range", &Gmax, RGBmax, myTrackbarGmax);
        cvCreateTrackbar("Bmin", "B range", &Gmin, RGBmax, myTrackbarBmin);
        cvCreateTrackbar("Bmax", "B range", &Gmax, RGBmax, myTrackbarBmax);*/
		cvInRangeS(r_plane, cvScalar(254), cvScalar(256), r_range);
		cvInRangeS(g_plane, cvScalar(241), cvScalar(256), g_range);
		cvInRangeS(b_plane, cvScalar(0), cvScalar(0), b_range);
        cvMoveWindow("original", 0, 0);
        cvMoveWindow("Yellow", image->width+10, 0);   
        while(true){

                // ���������� ��������
                cvShowImage("original",image);

                // ���������� ����
                /*cvShowImage( "R", r_plane );
                cvShowImage( "G", g_plane );
                cvShowImage( "B", b_plane );*/

                // ���������� ��������� ���������� ��������������
               /* cvShowImage( "R range", r_range );
                cvShowImage( "G range", g_range );
                cvShowImage( "B range", b_range );*/

                // ���������� 
                cvAnd(r_range, g_range, yellow);
                cvAnd(yellow, b_range, yellow);

                // ���������� ���������
                cvShowImage( "Yellow", yellow );
				char c = cvWaitKey(33);
                if (c == 27) { // ���� ������ ESC - �������
                        break;
                }
                
        }
       /* printf("\n[i] Results:\n" );
        printf("[i][R] %d : %d\n", Rmin, Rmax );
        printf("[i][G] %d : %d\n", Gmin, Gmax );
        printf("[i][B] %d : %d\n", Bmin, Bmax );*/


        // ���������� ��������

        // ����������� �������
        cvReleaseImage(&image);
        cvReleaseImage(&rgb);
		cvReleaseImage(&dst);
        cvReleaseImage(&r_plane);
        cvReleaseImage(&g_plane);
        cvReleaseImage(&b_plane);
        cvReleaseImage(&r_range);
        cvReleaseImage(&g_range);
        cvReleaseImage(&b_range);
        cvReleaseImage(&yellow);
        
        // ������� ����
        cvDestroyAllWindows();
        return 0;
}