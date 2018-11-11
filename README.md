placeh core integration/staging tree
=====================================


https://placeh.io

What is placeh?
----------------

placeh is an experimental digital currency artifact storage system that enables 
instant payments to anyone and transfer of arbitrary data to anyone, anywhere in the world. 

placeh uses peer-to-peer technology to operate with no central authority: managing transactions 
and issuing money are carried out collectively by the network. placeh core is the name of open source
software which enables the use of this currency. placeh is based on the cryptocurrency bitcoin 
and has not changed any of its consensus rules, coin issuance limits or blocktimes.

For more information, as well as an immediately useable, binary version of
the placeh core software, see https://placeh.io/#download, or read the
[original whitepaper](http://explore.placeh.io:8080/artifact/F9ddp3zXbNd5zwxBngvRBe4zQgmoViNuma.json).

License
-------

placeh core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Download
-------

placeh core is may be downloaded from the placeh.io website 
https://www.placeh.io/files/setup-placeh-rc2.0.26.1.exe

or directly from the executables under /src/ on the github repo.
Alternatively you can build the applicaiton from source.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/xagau/placeh/tags) are created
regularly to indicate new official, stable release versions of placeh core.

The contribution workflow is described in [CONTRIBUTING.md](CONTRIBUTING.md).

Developer Discord can be found on #placeh.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

