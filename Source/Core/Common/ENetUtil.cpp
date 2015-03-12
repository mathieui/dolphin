#include "ENetUtil.h"

namespace ENetUtil
{
	void WakeupThread(ENetHost* host)
	{
		// Send ourselves a spurious message.  This is hackier than it should be.
		// comex reported this as https://github.com/lsalzman/enet/issues/23, so
		// hopefully there will be a better way to do it in the future.
		ENetAddress address;
		if (host->address.port != 0)
			address.port = host->address.port;
		else
			enet_socket_get_address(host->socket, &address);
		address.host = 0x0100007f; // localhost
		u8 byte = 0;
		ENetBuffer buf;
		buf.data = &byte;
		buf.dataLength = 1;
		enet_socket_send(host->socket, &address, &buf, 1);
	}
}
