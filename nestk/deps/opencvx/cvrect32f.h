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
#ifndef CV_RECT32F_INCLUDED
#define CV_RECT32F_INCLUDED

#include "cv.h"
#include "cvaux.h"
#include "cxcore.h"

/************************* Structure Definitions ******************************/

/**
 * Floating Rectangle Structure
 */
typedef struct CvRect32f {
    float x;      /**< left x coord of rectangle */
    float y;      /**< top y coord of rectangle */
    float width;  /**< width of rectangle */
    float height; /**< height of rectangle */
    float angle;  /**< counter-clockwise rotation angle in degree
                       rotation center is (x, y) coordinates */
} CvRect32f;

/**
 * Center Coordinate Floating Rectangle Structure
 *
 * This is equivalent with CvBox2D, but I wanted this structure because
 * CvBox2D's parameters are too long such as box.center.x, box.size.width and
 * CvBox2D does not have a constructor cvBox2D(...). 
 */
typedef struct CvBox32f { 
    float cx;     /**< center x coord of rectangle */
    float cy;     /**< center y coord of center of rectangle */
    float width;  /**< width of rectangle */
    float height; /**< height of rectangle */
    float angle;  /**< counter-clockwise rotation angle in degree
                       rotation center is center of rectangle */
} CvBox32f;

/***************************** Prototypes *************************************/

//CV_INLINE CvRect32f cvRect32f( float x, float y, float width, float height, 
//                               float angle = 0.0 );
//CV_INLINE CvBox32f  cvBox32f( float cx, float cy, float width, float height, 
//                              float angle = 0.0 );

//CVAPI(CvBox32f)     cvBox32fFromRect32f( CvRect32f rect );
//CVAPI(CvRect32f)    cvRect32fFromBox32f( CvBox32f box );
//CV_INLINE CvRect32f cvRect32fFromRect( CvRect rect, float angle = 0 );
//CV_INLINE CvRect    cvRectFromRect32f( CvRect32f rect );
//CV_INLINE CvBox32f  cvBox32fFromBox2D( CvBox2D box );
//CV_INLINE CvBox2D   cvBox2DFromBox32f( CvBox32f box );
//CV_INLINE CvBox32f  cvBox32fFromRect( CvRect rect );
//CV_INLINE CvRect cvRectFromBox32f( CvBox32f box );
//CV_INLINE CvRect cvRectFromBox2D( CvBox2D box );
//CV_INLINE CvBox2D cvBox2DFromRect32f( CvRect32f rect );
//CV_INLINE CvRect32f cvRect32fFromBox2D( CvBox2D box );

// CV_INLINE void cvPrintRect32f( CvRect32f rect );
// CV_INLINE void cvPrintBox32f( CvBox32f box );
// CV_INLINE void cvPrintBox2D( CvBox2D box );
// CV_INLINE void cvPrintRect( CvRect rect );

/******************************* Constructor **********************************/

/**
 * The Constructor of Floating Rectangle Structure
 *
 * @param x      left x coord of rectangle
 * @param y      top y coord of center of rectangle
 * @param width  width of rectangle
 * @param height height of rectangle
 * @param angle  counter-clockwise rotation angle in degree
 *               rotation center is (x, y) coordinates
 */
CV_INLINE CvRect32f cvRect32f( float x, float y, float width, float height, 
                               float angle CV_DEFAULT(0.0) )
{
    CvRect32f rect = { x, y, width, height, angle };
    return rect;
}

/**
 * The Constructor of Center Coordinate Floating Rectangle Structure
 *
 * @param cx     center x coord of rectangle
 * @param cy     center y coord of center of rectangle
 * @param width  width of rectangle
 * @param height height of rectangle
 * @param angle  counter-clockwise rotation angle in degree
 *               rotation center is center of rectangle
 */
CV_INLINE CvBox32f cvBox32f( float cx, float cy, float width, float height, 
                             float angle CV_DEFAULT(0.0) )
{
    CvBox32f box = { cx, cy, width, height, angle };
    return box;
}

/****************************** Converter *************************************/
/**
 *cvRect32f from cvRect
 */
CV_INLINE CvRect32f cvRect32fFromRect( CvRect rect, float angle CV_DEFAULT(0.0) )
{
    return cvRect32f( rect.x, rect.y, rect.width, rect.height, angle );
}

/**
 * cvRect from cvRect32f
 */
CV_INLINE CvRect cvRectFromRect32f( CvRect32f rect )
{
    return cvRect( cvRound( rect.x ), cvRound( rect.y ),
                   cvRound( rect.width ), cvRound( rect.height ) );
}

/**
 * cvBox32f from cvBox2D
 */
CV_INLINE CvBox32f cvBox32fFromBox2D( CvBox2D box )
{
    return cvBox32f( box.center.x, box.center.y,
                     box.size.width, box.size.height,
                     box.angle );
}

/**
 * cvBox2D from cvBox32f
 */
CV_INLINE CvBox2D cvBox2DFromBox32f( CvBox32f box )
{
    CvBox2D box2d;
    box2d.center.x = box.cx;
    box2d.center.y = box.cy;
    box2d.size.width = box.width;
    box2d.size.height = box.height;
    box2d.angle = box.angle;
    return box2d;
}

/**
 * cvBox32f from cvRect32f
 *
 * Convert upper-left coordinate to center coordinate of the rectangle
 */
CvBox32f cvBox32fFromRect32f( CvRect32f rect )
{
    CvPoint2D32f c;
    // x + ( x + width - 1 ) / 2 = cx
    c.x = ( 2 * rect.x + rect.width - 1 ) / 2.0;
    c.y = ( 2 * rect.y + rect.height - 1 ) / 2.0;
    if( rect.angle != 0 )
    {
        CvMat* R = cvCreateMat( 2, 3, CV_32FC1 );
        cv2DRotationMatrix( cvPoint2D32f( rect.x, rect.y ), rect.angle, 1.0, R );
        c = cvPoint2D32f (
            cvmGet( R, 0, 0 ) * c.x + cvmGet( R, 0, 1 ) * c.y + cvmGet( R, 0, 2 ),
            cvmGet( R, 1, 0 ) * c.x + cvmGet( R, 1, 1 ) * c.y + cvmGet( R, 1, 2 ) );
        cvReleaseMat( &R );
    }
    return cvBox32f( c.x, c.y, rect.width, rect.height, rect.angle );
}

/**
 * cvRect32f from cvBox32f
 *
 * Convert center coordinate to upper-left coordinate of the rectangle
 */
CvRect32f cvRect32fFromBox32f( CvBox32f box )
{
    CvPoint2D32f l;
    // x + ( x + width - 1 ) / 2 = cx
    l.x = ( 2 * box.cx + 1 - box.width ) / 2.0;
    l.y = ( 2 * box.cy + 1 - box.height ) / 2.0;
    if( box.angle != 0.0 )
    {
        CvMat* R = cvCreateMat( 2, 3, CV_32FC1 );
        cv2DRotationMatrix( cvPoint2D32f( box.cx, box.cy ), box.angle, 1.0, R );
        l = cvPoint2D32f (
            cvmGet( R, 0, 0 ) * l.x + cvmGet( R, 0, 1 ) * l.y + cvmGet( R, 0, 2 ),
            cvmGet( R, 1, 0 ) * l.x + cvmGet( R, 1, 1 ) * l.y + cvmGet( R, 1, 2 ) );
        cvReleaseMat( &R );
    }
    return cvRect32f( l.x, l.y, box.width, box.height, box.angle );
}

/**
 * CvBox32f from CvRect
 */
CV_INLINE CvBox32f cvBox32fFromRect( CvRect rect )
{
    return cvBox32fFromRect32f( cvRect32fFromRect( rect ) );
}
/**
 * CvRect from CvBox32f
 */
CV_INLINE CvRect cvRectFromBox32f( CvBox32f box )
{
    return cvRectFromRect32f( cvRect32fFromBox32f( box ) );
}
/**
 * CvRect from CvBox2D
 */
CV_INLINE CvRect cvRectFromBox2D( CvBox2D box )
{
    return cvRectFromBox32f( cvBox32fFromBox2D( box ) );
}
/**
 * CvBox2D from CvRect32f
 */
CV_INLINE CvBox2D cvBox2DFromRect32f( CvRect32f rect )
{
    return cvBox2DFromBox32f( cvBox32fFromRect32f( rect ) );
}
/**
 * CvRect32f from CvBox2D
 */
CV_INLINE CvRect32f cvRect32fFromBox2D( CvBox2D box )
{
    return cvRect32fFromBox32f( cvBox32fFromBox2D( box ) );
}

/************************************ Print ***********************************/
/**
 * Print CvRect32f
 */
CV_INLINE void cvPrintRect32f( CvRect32f rect )
{
    printf( "x=%f y=%f width=%f height=%f angle=%f\n",
            rect.x, rect.y, rect.width, rect.height, rect.angle );
    fflush( stdout );
}
/**
 * Print CvBox32f
 */
CV_INLINE void cvPrintBox32f( CvBox32f box )
{
    printf( "cx=%f cy=%f width=%f height=%f angle=%f\n",
            box.cx, box.cy, box.width, box.height, box.angle );
    fflush( stdout );
}
/**
 * Print CvBox2D
 */
CV_INLINE void cvPrintBox2D( CvBox2D box )
{
    printf( "cx=%f cy=%f width=%f height=%f angle=%f\n",
            box.center.x, box.center.y, box.size.width,
            box.size.height, box.angle );
    fflush( stdout );
}
/**
 * Print CvRect
 */
CV_INLINE void cvPrintRect( CvRect rect )
{
    printf( "x=%d y=%d width=%d height=%d",
            rect.x, rect.y, rect.width, rect.height );
    fflush( stdout );
}

#endif
