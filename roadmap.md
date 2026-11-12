**The pipeline**

Capture → Ethernet → IP (v4/v6) → TCP/UDP/ICMP → output/filtering

One workable split for two people

Person A: capture and the front of the stack. Owns libpcap setup (device selection, pcap_open_live, BPF filters, the capture loop and callback, graceful shutdown), the Ethernet header parser, and the IPv4/IPv6 parsers.
Person B: the back of the stack and presentation. Owns the transport parsers (TCP, UDP, ICMP), payload handling, and output (formatting, hex dump, CLI options, optionally pcap file writing/reading).