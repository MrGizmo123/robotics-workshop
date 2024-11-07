#include <functional>

#define PORT 8000

typedef std::function<void(AsyncUDPPacket &packet)> UDPCallback;

bool connect_wifi(AsyncUDP&,char*,char*);
bool start_server(AsyncUDP&,int);
void udp_on_packet(AsyncUDP&,UDPCallback,bool);
