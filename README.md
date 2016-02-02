
# SETestKCL : <i>Negotiation Study</i>

<b>This <i> software </i> can be used to count the number of "yes" and "no" recorded during a negotiation. </b>

<br>

It is based on Qt for the gui part.
<br>



## REQUIREMENTS for compilation:

There are 3 pieces of software that are required for the correct installation of this software:

 - [CMAKE](https://cmake.org/) with version > 3.0. Required for the Cross-Platform makefile creations
 - [BOOST](http://www.boost.org/) with version > 1.60.0. Required for the rapid estimation of binomial coefficients. Note that only the includes are necessary. Simply download the source code. And, during cmake configuration, point the option Boost_INCLUDE_DIR to the main root directory of the downloaded folder.
 - [QT](http://www.qt.io/) with version > 5.0. Required for the creation of the user interface. 

Once these packages have been downloaded and installed, you can download the source code of SETestKCL software and start cmake configuration: 

    git clone  https://github.com/ntoussaint/SETestKCL.git

    cd SETestKCL; mkdir build; ccmake ..

Press 'c' for configuration. Simply configure the cmake to your convenience (be careful that the Boost_INCLUDE_DIR points to the correct directory). Press 'g' to generate makefiles.

After compilation, the binary (or bundle) should be created under the 'bin' directory of the build tree. Alternatively you can 'make install' the software for more global access.

Launch the application using the following commands:

For Linux:

    . bin/negotiation

For Mac:

    open -a negotiation ./bin/negotiation.app

For Windows:

    cmd ./bin/negotiation.exe

### ScreenShot

### Run Time Usage

  - type 'y' each time the negotiator says "yes"

  - type 'n' each time the negotiator says "no"

  - type 'z' to undo the last operation

  - type 's' to show (refresh) the current summary

  - type 'q' to exit
  
  - type 'r' to toggle the refresh mode



### Gallery ###

<a href="https://github.com/ntoussaint/SETestKCL/raw/master/Art/screenshot-ubuntu.png"><img src="https://github.com/ntoussaint/SETestKCL/raw/master/Art/screenshot-ubuntu.png" alt="srceenshot-ubuntu" title="screenshot-ubuntu"></a>
<br>

