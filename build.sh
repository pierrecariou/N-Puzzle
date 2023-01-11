#!/bin/bash
# File              : build.sh
# Author            : Pierre Cariou <pierrecariou@outlook.fr>
# Date              : 28.07.2022
# Last Modified Date: 28.07.2022
# Last Modified By  : Pierre Cariou <pierrecariou@outlook.fr>

rm -rf build
mkdir build
cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ..
make 
mv NPuzzle ..
