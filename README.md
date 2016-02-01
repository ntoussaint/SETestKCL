
# SETestKCL : <i>Negotiation Study</i>

<b>This <i> software </i> can be used to count the number of "yes" and "no" recorded during a conversation. </b>

<br>

It is based on Qt for the gui part.
<br>

### Usage  

  - type 'y' each time the negotiator says "yes"

  - type 'n' each time the negotiator says "no"

  - type 'z' to undo the last operation

  - type 's' to show the current summary

  - type 'q' to exit

  - type 'h' for a help message



## REQUIREMENTS for compilation:

There are 3 software that are required for the correct installation of this software:

 - [CMAKE](https://cmake.org/) with version > 3.0. Required for the Cross-Platform makefile creations
 - [BOOST](http://www.boost.org/) with version > 1.60.0. Required for the rapid estimation of binomial coefficients. Note that only the includes are necessary. Simply download the source code. And, during cmake configuration, point the option Boost_INCLUDE_DIR to the main root directory of the downloaded folder.
 - [QT](http://www.qt.io/) with version > 5.0. Required for the creation of the user interface. 

Once these packages have been downloaded and installed, simply configure the cmake to your convenience (be careful that the Boost_INCLUDE_DIR points to the correct directory).
After compilation, the binary should be created under the 'bin' directory of the build tree. Alternatively you can 'make install' the software for more global access.
