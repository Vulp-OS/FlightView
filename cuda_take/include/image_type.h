#ifndef IMAGE_TYPE_H
#define IMAGE_TYPE_H

#include <unordered_map>
#include <string>


//enum image_t {BASE, DSF, STD_DEV, STD_DEV_HISTOGRAM, VERTICAL_MEAN, HORIZONTAL_MEAN, FFT_MEAN,
//              VERTICAL_CROSS, HORIZONTAL_CROSS, VERT_OVERLAY, WATERFALL, FLIGHT};

//enum image_t {BASE, DSF, STD_DEV, SPATIAL_PROFILE, SPECTRAL_PROFILE, SPATIAL_MEAN, SPECTRAL_MEAN};

enum image_t {BASE, DSF, STD_DEV, SPATIAL_PROFILE, SPECTRAL_PROFILE, SPATIAL_MEAN, SPECTRAL_MEAN,
              STD_DEV_HISTOGRAM, VERTICAL_MEAN, HORIZONTAL_MEAN, FFT_MEAN,\
                            VERTICAL_CROSS, HORIZONTAL_CROSS, VERT_OVERLAY, WATERFALL, FLIGHT};


//enum camera_t {SSD_ENVI, SSD_XIO, CL_6604A, CL_6604B};

enum source_t {
    XIO = 0,
    ENVI = 1,
    CAMERA_LINK = 2};

enum org_t {fwBIL, fwBIP, fwBSQ};

struct save_req_t
{
    org_t bit_org;
    std::string file_name;
    int64_t nFrames;
    int64_t nAvgs;
};

#endif // IMAGE_TYPE_H

