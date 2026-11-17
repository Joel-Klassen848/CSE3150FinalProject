#include <stdio.h>
#include <pcap.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    char *dev, errbuf[PCAP_ERRBUF_SIZE];

    // Device is automatically scanned by pcap
    dev = pcap_lookupdev(errbuf);  

    // If there is no fevice found (dev==NULL), output error message (saved in errbuf)  
    if (dev==NULL) {
        cout<<stderr<<"Couldn't find default device: "<<errbuf<<endl;
        return 2;
    }
    
    // If device successfully found, print it
    cout << "Device: " << dev << endl;
    
    // Using device dev, read BUFSIZ amt of bytes, promiscuous mode,
    // with a 1 sec timeout before sending and error msg variable.
    pcap_t *handle;
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle==NULL){
        cout<<stderr<<"Couldn't open device "<<dev<<": "<<errbuf<<endl;
        return 2;
    }
}

