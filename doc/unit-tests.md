Compiling/running unit tests
------------------------------------

Unit tests will be automatically compiled if dependencies were met in configure
and tests weren't explicitly disabled.

After configuring, they can be run with 'make check'.

To run the viced tests manually, launch src/test/test_vice .

To add more viced tests, add `BOOST_AUTO_TEST_CASE` functions to the existing
.cpp files in the test/ directory or add new .cpp files that
implement new BOOST_AUTO_TEST_SUITE sections.

To run the vice-qt tests manually, launch src/qt/test/vice-qt_test

To add more vice-qt tests, add them to the `src/qt/test/` directory and
the `src/qt/test/test_main.cpp` file.
