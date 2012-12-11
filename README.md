POLARIS-BME-DG
==============

LabVIEW LVOOP classes for Bergmann Delay Generators

The master brunch has been rebased onto DLL_20120706 brunch. (201211-02)
From now on the master brunch can be used as source for tested releases.


201212-11 The CS Framework based solution for changing channel settings was developed.
=========================
Test of current version was perfomed whit Delay Generator version SG08P2 and Bergmann DLL from 
201211-02. 
Changed: TestPC from Config File.vi
Now changes of delay occours asynchroniously, changes of output modulo counters occurs synchroniously.

CS Framework Solution:
================
CS Class for DG Server: CS POLARIS BME DG
CS Class for DG Client: CS POLARIS BME DG Client
You need one Server object for each installed Master Slave System.
You can have one or more Objects of Client class for each DG channel. Each obj must have unique name.
Only one of initiated client objects can make changes at his channel. All other channels are locked until
client object releases control.  Two modes are implemented: 
1. Simple: for asynchronious delay changes
2. Expert: for synchronious changes of output modulos 