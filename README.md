# SVDCompression
The repository for COP3530 Project 3: Video Compression.

## Motivation
On some internet platforms and messaging services, there are limits to the size of photos and videos that users can send. This means users have to find ways to compress or crop media which may remove important elements or be difficult to do on some platforms. Our media compression application will provide an encoder and decoder that will compress media to a specified size. The encoder and decoder can be implemented in other applications to passively encode a sender’s compressed version of a video or image, and decompress it at the receiver’s side. This may also provide the benefit of faster transmission time and storage space savings.

## References

### In Implementing Pybind11 with numpy
- https://stackoverflow.com/questions/3654652/why-does-the-python-c-api-crash-on-pyrun-simplefile
- https://pybind11.readthedocs.io/en/stable/advanced/pycpp/utilities.html#eval
- https://github.com/pybind/pybind11/issues/1543
- https://pybind11.readthedocs.io/en/stable/advanced/cast/stl.html
- https://pybind11.readthedocs.io/en/stable/advanced/cast/overview.html
- https://github.com/aoloe/cpp-pybind11-playground/tree/master/eval-file
- https://github.com/numpy/numpy/issues/8097