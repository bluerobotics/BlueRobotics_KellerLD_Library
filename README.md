# BlueRobotics_KellerLD_Library

Arduino library for the Keller 4LD to 9LD I²C pressure and temperature sensors;
used in the Bar100 Sensor from Blue Robotics.

See the [Keller Communication Protocol 4LD-9LD][com] document for more details
on the I²C communication protocol, and the [Keller 4LD-9LD
Datasheet][datasheet] for sensor specification details.

[com]: http://www.keller-druck2.ch/swupdate/InstallerD-LineAddressManager/manual/Communication_Protocol_4LD-9LD_en.pdf
[datasheet]: https://download.keller-druck.com/api/download/2LfcGMzMbeHdjFbyUd5DWA/en/latest

## Changelog

* `2.0.0`
  * Allow user-defined I²C address for the sensor
  * Calibration date fields renamed to `calibration{Year,Month,Day}`
* `1.1.2` (2022-02-16)
  * Fix pressure calculation; all sensors were treated as PAA
* `1.1.1` (2021-07-01)
  * Add P-mode pressure offset handling for PR, PA and PAA type sensors,
    auto-determined based on sensor mode
  * Add support to read out the calibration date
* `1.0.0` (2017-08-31)
  * Initial release.
