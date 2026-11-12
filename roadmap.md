**The pipeline**

Capture → Ethernet → IP (v4/v6) → TCP/UDP/ICMP → output/filtering


**One workable split for two people**

Person A: capture and the front of the stack. Owns libpcap setup (device selection, pcap_open_live, BPF filters, the capture loop and callback, graceful shutdown), the Ethernet header parser, and the IPv4/IPv6 parsers.

Person B: the back of the stack and presentation. Owns the transport parsers (TCP, UDP, ICMP), payload handling, and output (formatting, hex dump, CLI options, optionally pcap file writing/reading).


**Things that keep you from stepping on each other**

Separate files per layer (ethernet.cpp/.h, ip.cpp/.h, tcp.cpp/.h, capture.cpp/.h). Merge conflicts mostly vanish when people rarely touch the same file.
Test with pcap files, not live traffic. Grab a few sample captures (Wireshark’s sample captures page has plenty) or record your own. Person B can develop the TCP parser against a saved file before A’s capture loop is done. Libpcap’s pcap_open_offline makes this easy, and it avoids needing sudo every time.
Git workflow: feature branch per layer, small PRs, and the other person reviews each one. Reviewing each other’s parsers is the best collaboration point because bugs in header parsing are subtle.
Unit tests per parser (Catch2 or GoogleTest) using hand-built byte arrays, so each person can prove their layer works in isolation.
A CMake build set up early by whoever finishes first, so you both build the same way.