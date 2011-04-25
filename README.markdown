chmac
=====

`chmac` is a non-interactive win32 console app that changes the given adapter's MAC by incrementing it.

Usage
-------

Running the app without arguments lists the recognized adapters.

Running the app with exactly one argument searches this list, and changes the MAC of the *first* adapter whose GUID or description contain the argument as a substring.

Note for Vista and later: You need to set the resulting executable to run with elevated privileges in its properties for this to work.

Note that only the last hex digit is ever changed (F becomes 0).

Example
-----

```
> chmac
{27A3DCC7-9216-4E07-9DF5-37E66B4362C3} 00215d0f4eff Microsoft Virtual WiFi Miniport Adapter
{24DE9034-5341-4FA9-97C9-267E7C110846} 00215d0f4efe Intel(R) WiFi Link 5100 AGN
{EB452FC0-C600-4E11-B3A1-A5295CD56716} 00235430d0b7 Realtek PCIe GBE Family Controller
```
```
> chmac Realtek
Resetting Realtek PCIe GBE Family Controller: 00235430d0b7 -> 00235430d0b8
Reset succeeded.
```

Purpose
===
The real purpose for this utility is to fool my internet provider to give me a different, MAC-dependent IP that helps me bypass their bandwidth limiter. For this, I wrap this app in a windows batch file like this:

```
ipconfig /release
start /wait chmac Realtek
ipconfig /renew
```

One day, I will write a daemon that analyzes the current bandwidth in the background and runs this script automatically :-)

Acknowledgements
===
This utility is based on [Nishant Sivakumar](http://voidnish.wordpress.com/ "Nishant Sivakumar's blog")'s excellent ["MAC Address Changer for Windows XP/2003"](http://www.codeproject.com/KB/applications/MacIdChanger.aspx "MAC Address Changer website").

License
===
[Common Development and Distribution License](http://www.opensource.org/licenses/cddl1).
