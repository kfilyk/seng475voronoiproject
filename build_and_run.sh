cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
cmake --build tmp_cmake --clean-first --target INSTALL_DIR
cd tmp_cmake
$INSTALL_DIR/bin/demo