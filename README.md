# mwfilesignature

mwfilesignature is a fast and small (one header and source file) C++11 library for identifying image files based on their binary signature.

## File types
The library recognized the following image files: DICOM, PNG, TIFF, JPEG, GIF, XCF, PSD, BMP, NEF, ICO. Few others, non-image types are also recognized (e.g. MAT, ZIP, XML, ASCII). However, non-image types are not a priority and their recoginition is limmited. 

## Example

```C++
#include <iostream>

#include "filesignature.h"

using namespace std;

int main()
{

    //string in_path {"/a/path/to/some/file"};
    string file_path {"/media/sf_D_DRIVE/dcm_for_tests/ida/037/DHS1275249/0/im_1/i0000_0000b.dcm"};

    // create an impty mw::Signature object
    mw::Signature empty_signature;

    // check if a given file is an image.
    if (mw::is_image(file_path, &empty_signature))
    {
       cout << " type: " <<  empty_signature.img_type << endl;
    }
    else
    {
        cout << "Non-recognized image type" << endl;
    }

    return 0;
}
```

