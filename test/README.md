# Tests

Two kind of tests are provided:

## Unit Tests

Low level test directly built even against to internal Rates code at *rates.hpp*.

## Fake external currency server

Using the **golang** mock, this test invokes some common instructions.

# Boost libs

**Unit Test** library will be the only one [built](http://www.boost.org/doc/libs/1_64_0/libs/test/doc/html/boost_test/adv_scenarios/build_utf.html) from downloaded code in order to use its **STATIC** version with **GCC-6**:

       cd $boost_path
       ./bootstrap.sh
       ./b2 toolset=gcc-6 --with-test --prefix=$boost_installation_prefix install

## Boost libs from RPMFind

Although it seems not to properly work due to some nasty [cxx11] missing at

       00000000000008a0 T boost::unit_test::ut_detail::normalize_test_case_name[abi:cxx11](boost::unit_test::basic_cstring<char const>)

Instead of built-on-openSuse one:

       boost::unit_test::ut_detail::normalize_test_case_name(boost::unit_test::basic_cstring<char const>)
       
Maybe in the future it could be interesting to locate openSuse equivalent to the following links:

[Fedora Static](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-static-1.63.0-7.fc27.x86_64.html)

[Fedora Shared](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-devel-1.63.0-7.fc27.x86_64.html)

### Specific shared libraries from RPMFind

[Atomic](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-atomic-1.63.0-7.fc27.x86_64.html)

[Chrono](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-chrono-1.63.0-7.fc27.x86_64.html)

[Container](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/aarch64/b/boost-container-1.63.0-7.fc27.aarch64.html)

[Context](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-context-1.63.0-7.fc27.x86_64.html)

[Coroutine](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-coroutine-1.63.0-7.fc27.x86_64.html)

[DateTime](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-date-time-1.63.0-7.fc27.x86_64.html)

[Fiber](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-fiber-1.63.0-7.fc27.x86_64.html)

[Filesystem](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-filesystem-1.63.0-7.fc27.x86_64.html)

[Graph](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-graph-1.63.0-7.fc27.x86_64.html)

[Iostreams](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-iostreams-1.63.0-7.fc27.x86_64.html)

[Locale](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-locale-1.63.0-7.fc27.x86_64.html)

[Log](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-log-1.63.0-7.fc27.x86_64.html)

[Math](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-math-1.63.0-7.fc27.x86_64.html)

[ProgramOptions](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-program-options-1.63.0-7.fc27.x86_64.html)

[Python](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-python-1.63.0-7.fc27.x86_64.html)

[Random](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-random-1.63.0-7.fc27.x86_64.html)

[Regex](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-regex-1.63.0-7.fc27.x86_64.html)

[Serialization](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-serialization-1.63.0-7.fc27.x86_64.html)

[Signals](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-signals-1.63.0-7.fc27.x86_64.html)

[System](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-system-1.63.0-7.fc27.x86_64.html)

[Test](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-test-1.63.0-7.fc27.x86_64.html)

[Thread](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-thread-1.63.0-7.fc27.x86_64.html)

[Timer](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-timer-1.63.0-7.fc27.x86_64.html)

[TypeErasure](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-type_erasure-1.63.0-7.fc27.x86_64.html)

[Wave](https://www.rpmfind.net/linux/RPM/fedora/devel/rawhide/x86_64/b/boost-wave-1.63.0-7.fc27.x86_64.html)

