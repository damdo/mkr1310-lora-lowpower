## damdo/mkr1310-lora-lowpower

Arduino MKR WAN 1310 Low Power LoRa comms

### Motivation
The overview of the Arduino MKR WAN 1310 on the [Arduino Store](https://store.arduino.cc/mkr-wan-1310) states the following:

_"The latest modifications have considerably improved the battery life on the MKR WAN 1310. When properly configured, the power consumption is now as low as 104uA!"_.

So I've read a decent amount of blogs/forums/code on how to make Low Power LoRa comms the Arduino MKR WAN boards but either they:
- weren't performing as low as I needed them to go (<150µA during deep sleep)
- [they involved physical surgery of the board](https://forum.arduino.cc/index.php?topic=698897.0)
- [they involved the usage of Low Power Timers](https://github.com/AmedeeBulle/TTNMkrWanNode) to bring the sleep current down


After combining some findings, and testing various approaches I achieved the desired result and so I want to share how I did this, but without the above hardware compromises.

The key takeaway is that even after a `LoRa.end()` the pins used to communicate with the on-board LoRa chip are not put in low power consumption mode and they still draw a quite significant amount of current. They thus need to be manually reset to achieve power efficiency.

For now there is only an example for simple 1:1 LoRa communication but I might add one for LoRaWAN later down the line.

### Caveat
The code is compatible with both the 1300 and the 1310 boards
but I've only tested its performances with the 1310 revision.

Also the 1310 revision was born to fix the high power consumption of it's predecessor the 1300, so I wouldn't be surprised to see worse performances for the 1300.

Although that doesn't change the fact that the code should require minimal current during sleep independently of the revision.

### Performances
The measured performance of the code with the two revisions of the MKR WAN board.

| Model          | Sleep            | Transmitting |
| :------------- | :----------:     | -----------: |
| MKR 1310       | `104µA` (`0.1mA`)| `~20/30mA`   |
| MKR 1300       | untested         | untested     |

N.B. the power in the tests was provided via the battery connector, as this Arduino automatically disables the power led, when it's getting powered through that.
