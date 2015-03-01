# mwfilesignature

mwfilesignature is a fast and small (one header and one source file) C++11 library for identifying image files based on their binary signature.

## File types
The library recognizes the following image types: DICOM, PNG, TIFF, JPEG, GIF, XCF, PSD, BMP, NEF, ICO. Few others, non-image types are also recognized (e.g. MAT, ZIP, XML, ASCII). However, non-image types are not a priority and their recoginition is rather limmited. 

## Example

```C++
#include <iostream>

#include "filesignature.h"

using namespace std;

int main()
{

    string in_path {"/a/path/to/some/file"};    

    // create an impty mw::Signature object
    mw::Signature empty_signature;

    // check if a given file is an image.
    if (mw::is_image(file_path, &empty_signature))
    {
       cout << " Image type: " <<  empty_signature.img_type << endl;
    }
    else
    {
       cout << "Image type: UNKNOWN" << endl;
    }

    return 0;
}
```

