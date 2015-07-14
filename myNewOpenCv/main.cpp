#include <opencv\cv.h>
#include <opencv\highgui.h>
#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <stdio.h>
//char* filename = "C:\\Users\\acer1\\Pictures\\pr1.png";



IplImage* image = 0;
IplImage* dst = 0;

// для хранения каналов RGB
IplImage* rgb = 0;
IplImage* r_plane = 0;
IplImage* g_plane = 0;
IplImage* b_plane = 0;
// для хранения каналов RGB после преобразования
IplImage* r_range = 0;
IplImage* g_range = 0;
IplImage* b_range = 0;
// для хранения суммарной картинки
IplImage* yellow = 0;

int Rmin = 0;
int Rmax = 256;

int Gmin = 0;
int Gmax = 256;

int Bmin = 0;
int Bmax = 256;

int RGBmax = 256;

//
// функции-обработчики ползунка
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
        // имя картинки задаётся первым параметром
        char* filename = "C:\\Users\\acer1\\Pictures\\pr1.png";
        // получаем картинку
        image = cvLoadImage(filename,1);
        printf("[i] image: %s\n", filename);
        assert( image != 0 );

        // создаём картинки
        rgb = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 3 );
        r_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        g_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        b_plane = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        r_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        g_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        b_range = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        yellow = cvCreateImage( cvGetSize(image), IPL_DEPTH_8U, 1 );
        //  копируем
        cvCopyImage(image, rgb);
        // разбиваем на отельные каналы
       cvSplit( rgb, b_plane, g_plane, r_plane, 0 );

        //
        // определяем минимальное и максимальное значение
        // у каналов HSV
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

        // окна для отображения картинки
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

                // показываем картинку
                cvShowImage("original",image);

                // показываем слои
                /*cvShowImage( "R", r_plane );
                cvShowImage( "G", g_plane );
                cvShowImage( "B", b_plane );*/

                // показываем результат порогового преобразования
               /* cvShowImage( "R range", r_range );
                cvShowImage( "G range", g_range );
                cvShowImage( "B range", b_range );*/

                // складываем 
                cvAnd(r_range, g_range, yellow);
                cvAnd(yellow, b_range, yellow);

                // показываем результат
                cvShowImage( "Yellow", yellow );
				char c = cvWaitKey(33);
                if (c == 27) { // если нажата ESC - выходим
                        break;
                }
                
        }
       /* printf("\n[i] Results:\n" );
        printf("[i][R] %d : %d\n", Rmin, Rmax );
        printf("[i][G] %d : %d\n", Gmin, Gmax );
        printf("[i][B] %d : %d\n", Bmin, Bmax );*/


        // показываем картинки

        // освобождаем ресурсы
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
        
        // удаляем окна
        cvDestroyAllWindows();
        return 0;
}