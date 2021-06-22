Digital Frequency Meter
=======================

Digital Frequency Meter based on ESP32-C3 chip.

## Preparing

### Obtain the source

```
git clone --recursive https://github.com/redchenjs/digital_frequency_meter_esp32c3.git
```

### Update an existing repository

```
git pull
git submodule update --init --recursive
```

### Setup the tools

```
./esp-idf/install.sh
```

## Building

### Setup the environment variables

```
export IDF_PATH=$PWD/esp-idf
source ./esp-idf/export.sh
```

### Configure

```
idf.py menuconfig
```

* All project configurations are under the `Digital Frequency Meter` menu.

### Flash & Monitor

```
idf.py flash monitor
```
