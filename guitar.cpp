#include <hidapi/hidapi.h>
#include <iostream>
#include <bitset>


/* https://devicehunt.com/view/type/usb/vendor/12BA/device/0100 */


// RedOctane Guitar 
// Vendor ID: 12ba
// Product ID: 100
// Path: DevSrvsID:4295009797
// Manufacturer: 0x7f838210ac30
// Product: 0x7f838210acd0
void enumerateDevs() {

    struct hid_device_info *devs, *cur_dev;
    devs = hid_enumerate(0x0, 0x0);
    cur_dev = devs;

    while (cur_dev) {
        std::cout << "Device Found:" << std::endl;
        std::cout << "  Vendor ID: " << std::hex << cur_dev->vendor_id << std::endl;
        std::cout << "  Product ID: " << std::hex << cur_dev->product_id << std::endl;
        std::cout << "  Path: " << cur_dev->path << std::endl;
        std::cout << "  Manufacturer: " << cur_dev->manufacturer_string << std::endl;
        std::cout << "  Product: " << cur_dev->product_string << std::endl;
        std::cout << "-------------------------" << std::endl;

        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

}

/* BUTTON COMBOS
    buf[0]
    GRYBO

    G - 2
    R - 4
    Y - 1
    B - 8
    O - 16

    GR - 6
    GY - 3
    GB - 10
    GO - 18
    RY - 5
    RB - 12
    RO - 20

    GRY - 7
    GRB - 14
    GYB - 11
    GRO - 22
    ...

    buf[0] value is equal to the sum of pressed buttons

    binary number:
    OBRGY

    decimal input to binary

    
    
    */
void printFretStatus(int status) {
    std::bitset<5> binary(status);
    std::string binaryString = binary.to_string();
    std::string reorderedString = "";
    reorderedString = reorderedString + binaryString[3] + binaryString[2] + binaryString[4] + binaryString[1] + binaryString[0];
    std::string fretString = "grybo";

    for (size_t i = 0; i < fretString.length(); i++) {
        if (reorderedString[i] == '1') {
            fretString[i] = std::toupper(fretString[i]);
        }
    }
    std::cout << fretString << std::endl;

    return;
}


int main() {

    int res;
    unsigned char buf[65];
    hid_device *handle;

    // set up HIDAPI
    res = hid_init();
    if (res) {
        std::cerr << "Failed to initialize HIDAPI" << std::endl;
        return 1;
    }
    std::cout << "HIDAPI initialized!" << std::endl;

    // show all connected devices
    // enumerateDevs();

    // connect to guitar
    handle = hid_open(0x12ba, 0x100, NULL);
    if (handle) {
        printf("guitar connected!\n");
    } else {
        printf("could not connect to guitar!\n");
        hid_exit();
        return 0;
    }


    // main loop
    while(true) {
        res = hid_read(handle,buf,65);
        printFretStatus(buf[0]);

    }

    hid_exit();

    return 0;
}

