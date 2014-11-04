# libFBC
A library for applying flux balance constraint methods on SBML models. This
code was developed within the scope of the
[BioPreDyn project](http://www.biopredyn.eu/).

## Dependencies
This project uses (and distributes)
[LPsolve](http://sourceforge.net/projects/lpsolve/), a mixed integer linear
programming solver published under the LGPL 2.0 license.

It requires [libSBML](http://sbml.org/Software/libSBML) to be installed with
the FBC package.

## Installation
The library is built using [CMake](http://www.cmake.org/); open a command prompt
in the project checkout folder then type:
```
mkdir build
cd build
cmake ..
make
```

## License
This project is distributed under the terms of the
[BSD-3 clause license](http://opensource.org/licenses/BSD-3-Clause):

Copyright (c) 2014, The CoSMo Company
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors
may be used to endorse or promote products derived from this software without
specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
