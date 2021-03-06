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
#ifndef CV_GAUSSNORM_INCLUDED
#define CV_GAUSSNORM_INCLUDED


#include "cv.h"
#include "cvaux.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "cvmatelemcn.h"

// @todo
// CVAPI(void) cvMatGaussNorm( const CvMat* samples, CvMat* dst );
// #define cvGaussNorm( sample, dst ) cvMatGaussNorm( sample, dst )
// CVAPI(void) cvImgGaussNorm( const IplImage* img, IplImage* normed ) {
//    IplImage* sample, samplehdr;
//    IplImage* dst, dsthdr;
//    sample = cvReshape( img, &samplehdr, 1, img->nChannels );
//    dst = cvReshape( normed, &dsthdr, 1, dst->nChannels );
//    // make sure how it is reshaped
//    cvMatGaussNorm( sample, dst );
// }

/**
 * Zero mean and unit covariance normalization of an image
 * Each channel is processed independently
 *
 * @param src       input image
 * @param dst       normalized image. 32F or 64F should be preferred.
*/
CVAPI(void) cvGaussNormImage( const CvArr* src, CvArr* dst )
{
    CvMat instub, *in = (CvMat*)src;
    CvMat outstub, *out = (CvMat*)dst;
    int coi = 0;
    CvScalar mean, std;
    int rows, cols, nChannels;
    int ch, row, col;
    CvScalar inval;
    CvMat *tmp_in;
    CvMat *sub_in;
    CV_FUNCNAME( "cvGaussNormImage" );
    __BEGIN__;
    if( !CV_IS_MAT(in) )
    {
        CV_CALL( in = cvGetMat( in, &instub, &coi ) );
        if (coi != 0) CV_ERROR_FROM_CODE(CV_BadCOI);
    }
    if( !CV_IS_MAT(out) )
    {
        CV_CALL( out = cvGetMat( out, &outstub, &coi ) );
        if (coi != 0) CV_ERROR_FROM_CODE(CV_BadCOI);
    }
    CV_ASSERT( in->rows == out->rows && in->cols == out->cols );
    CV_ASSERT( CV_MAT_CN(in->type) == CV_MAT_CN(out->type) );

    if( in->type != out->type ) {
        tmp_in = cvCreateMat( out->rows, out->cols, out->type );
        cvConvert( in, tmp_in );
    } else {
        tmp_in = in;
    }
    sub_in = cvCreateMat( out->rows, out->cols, out->type );
    
    cvAvgSdv( tmp_in, &mean, &std );
    cvSubS( tmp_in, mean, sub_in );
    //cvScale( sub_in, out, 1.0/std.val[0] ); // do channel
    rows = out->rows;
    cols = out->cols;
    nChannels = CV_MAT_CN(out->type);
    for( row = 0; row < rows; row++ ) {
        for( col = 0; col < cols; col++ ) {
            inval = cvGet2D( sub_in, row, col );
            for( ch = 0; ch < nChannels; ch++ ) {
                inval.val[ch] /= std.val[ch];
            }
            cvSet2D( out, row, col, inval );
        }
    }        

    if( in->type != out->type ) {
        cvReleaseMat( &tmp_in );
    }
    cvReleaseMat( &sub_in );
    __END__;
}


#endif
