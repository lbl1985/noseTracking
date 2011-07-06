/** @file */
/* The MIT License
* 
* Copyright (c) 2008, Naotoshi Seo <sonots(at)sonots.com>
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
#ifndef CV_CROPIMAGEROI_INCLUDED
#define CV_CROPIMAGEROI_INCLUDED

#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "cvcreateaffine.h"
#include "cvrect32f.h"
#include "cvget2dinter.h"

//CVAPI(void) 
//cvCropImageROI( const IplImage* img, IplImage* dst, 
//                CvRect32f rect32f = cvRect32f(0,0,1,1,0),
//                CvPoint2D32f shear = cvPoint2D32f(0,0) );
//CV_INLINE void 
//cvShowCroppedImage( const char* w_name, IplImage* img,
//                    CvRect32f rect32f = cvRect32f(0,0,1,1,0),
//                    CvPoint2D32f shear = cvPoint2D32f(0,0) );

/**
 * Crop image with rotated and sheared rectangle
 *
 * @code
 * IplImage* dst = cvCreateImage( cvSize( rect.width, rect.height ), img->depth, img->nChannels );
 * @endcode
 * If you want define rotation center as the center of the rectangle,
 * use CvBox32f and use cvRect32fBox32( box32f ) for the rect32f argument. 
 *
 * @param img          The target image
 * @param dst          The cropped image
 * @param rect32f      The rectangle region (x,y,width,height) to crop and 
 *                     the rotation angle in degree where the rotation center is (x,y)
 * @param shear        The shear deformation parameter shx and shy
 * @param interpolation The interpolation method. 
 *                     CV_INTER_NN - Nearest Neighborhood method
 *                     CV_INTER_LINEAR - Bilinear interpolation
 * @return CVAPI(void)
 */
CVAPI(void) 
cvCropImageROI( const IplImage* img, IplImage* dst, 
                CvRect32f rect32f CV_DEFAULT(cvRect32f(0,0,1,1,0)),
                CvPoint2D32f shear CV_DEFAULT(cvPoint2D32f(0,0)),
                int interpolation CV_DEFAULT(CV_INTER_LINEAR) )
{
    CvRect rect = cvRectFromRect32f( rect32f );
    float angle = rect32f.angle;
    CV_FUNCNAME( "cvCropImageROI" );
    __BEGIN__;
    CV_ASSERT( rect.width > 0 && rect.height > 0 );
    CV_ASSERT( dst->width == rect.width );
    CV_ASSERT( dst->height == rect.height );

    if( angle == 0 && shear.x == 0 && shear.y == 0 && 
        rect.x >= 0 && rect.y >= 0 && 
        rect.x + rect.width < img->width && rect.y + rect.height < img->height )
    {
        CvMat subimg;
        cvGetSubRect( img, &subimg, rect );
        cvConvert( &subimg, dst );
    }
    else if( shear.x == 0 && shear.y == 0 )
    {
        int x, y;
        float xp, yp;
        double c = cos( -M_PI / 180 * angle );
        double s = sin( -M_PI / 180 * angle );
        CvScalar color;
        /*CvMat* R = cvCreateMat( 2, 3, CV_32FC1 );
        cv2DRotationMatrix( cvPoint2D32f( 0, 0 ), angle, 1.0, R );
        double c = cvmGet( R, 0, 0 );
        double s = cvmGet( R, 1, 0 );
        cvReleaseMat( &R );*/
        cvZero( dst );

        for( x = 0; x < rect.width; x++ )
        {
            for( y = 0; y < rect.height; y++ )
            {
                xp = ( c * x + -s * y ) + rect.x;
                yp = ( s * x + c * y ) + rect.y;
                if( xp <= -0.5 || xp >= img->width - 0.5 || yp <= -0.5 || yp >= img->height - 0.5 ) continue;
                color = cvGet2DInter( img, yp, xp, interpolation );
                cvSet2D( dst, y, x, color );
                //xp = cvRound( c * x + -s * y ) + rect.x;
                //yp = cvRound( s * x + c * y ) + rect.y;
                //if( xp < 0 || xp >= img->width || yp < 0 || yp >= img->height ) continue;
                //for( ch = 0; ch < img->nChannels; ch++ )
                //{
                //    dst->imageData[dst->widthStep * y + x * dst->nChannels + ch]
                //        = img->imageData[img->widthStep * yp + xp * img->nChannels + ch];
                //}
            }
        }
    }
    else
    {
        int x, y;
        float xp, yp;
        CvScalar color;
        CvMat* affine = cvCreateMat( 2, 3, CV_32FC1 );
        CvMat* xy     = cvCreateMat( 3, 1, CV_32FC1 );
        CvMat* xyp    = cvCreateMat( 2, 1, CV_32FC1 );
        cvCreateAffine( affine, rect32f, shear );
        cvmSet( xy, 2, 0, 1.0 );
        cvZero( dst );

        for( x = 0; x < rect.width; x++ )
        {
            cvmSet( xy, 0, 0, x / rect32f.width );
            for( y = 0; y < rect.height; y++ )
            {
                cvmSet( xy, 1, 0, y / rect32f.height );
                cvMatMul( affine, xy, xyp );
                xp = cvmGet( xyp, 0, 0 );
                yp = cvmGet( xyp, 1, 0 );
                if( xp <= -0.5 || xp >= img->width - 0.5 || yp <= -0.5 || yp >= img->height - 0.5 ) continue;
                color = cvGet2DInter( img, yp, xp, interpolation );
                cvSet2D( dst, y, x, color );
                //xp = cvRound( cvmGet( xyp, 0, 0 ) );
                //yp = cvRound( cvmGet( xyp, 1, 0 ) );
                //if( xp < 0 || xp >= img->width || yp < 0 || yp >= img->height ) continue;
                //for( ch = 0; ch < img->nChannels; ch++ )
                //{
                //    dst->imageData[dst->widthStep * y + x * dst->nChannels + ch]
                //        = img->imageData[img->widthStep * yp + xp * img->nChannels + ch];
                //}
            }
        }
        cvReleaseMat( &affine );
        cvReleaseMat( &xy );
        cvReleaseMat( &xyp );
    }
    __END__;
}

/**
 * Crop and show the Cropped Image
 *
 * @param w_name       Window name
 * @param img          Image to be cropped
 * @param rect32f      The rectangle region (x,y,width,height) to crop and 
 *                     the rotation angle in degree
 * @param shear        The shear deformation parameter shx and shy
 * @return CVAPI(void)
 * @uses cvCropImageROI
 */
CV_INLINE void 
cvShowCroppedImage( const char* w_name, IplImage* img, 
                    CvRect32f rect32f CV_DEFAULT(cvRect32f(0,0,1,1,0)),
                    CvPoint2D32f shear CV_DEFAULT(cvPoint2D32f(0,0)) )
{
    CvRect rect = cvRectFromRect32f( rect32f );
    if( rect.width <= 0 || rect.height <= 0 ) return;
    IplImage* crop = cvCreateImage( cvSize( rect.width, rect.height ), img->depth, img->nChannels );
    cvCropImageROI( img, crop, rect32f, shear );
    cvShowImage( w_name, crop );
    cvReleaseImage( &crop );
}


#endif
