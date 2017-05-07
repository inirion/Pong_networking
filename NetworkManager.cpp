#include "Helpers.h"
#include "NetworkManager.h"

NetworkManager::NetworkManager() 
{
}

AddressVectorPtr NetworkManager::getInterfaces()
{
#if PLATFORM == PLATFORM_WINDOWS
	return getInterfacesWin();
#elif 
	return getInterfacesUnix();
#endif
}

AddressVectorPtr NetworkManager::getInterfacesUnix()
{
#if PLATFORM != PLATFORM_UNIX
	return AddressVectorPtr(nullptr);
#else
	// NYI
	return AddressVectorPtr(nullptr);
#endif
}


AddressVectorPtr NetworkManager::getInterfacesWin()
{
	std::vector<AddressTuple> tmp;
#if PLATFORM != PLATFORM_WINDOWS
	return AddressVectorPtr(nullptr);
#else

	PMIB_IPADDRTABLE pIPAddrTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;
	LPVOID lpMsgBuf;

	pIPAddrTable = new MIB_IPADDRTABLE[sizeof(MIB_IPADDRTABLE)];

	if (pIPAddrTable) {
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
			delete pIPAddrTable;
			pIPAddrTable = new MIB_IPADDRTABLE[dwSize];
		}
		if (pIPAddrTable == NULL) {
			std::cout << "Memory allocation failed for GetIpAddrTable\n" << std::endl;
			return AddressVectorPtr(nullptr);
		}
	}
	
	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
		std::cout << "GetIpAddrTable failed with error: " << dwRetVal << std::endl;
		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)& lpMsgBuf, 0, NULL)) {
			std::cout << "Error: " << lpMsgBuf << std::endl;
			delete lpMsgBuf;
		}
		return AddressVectorPtr(nullptr);
	}	

	for (int i = 0; i < (int)pIPAddrTable->dwNumEntries; i++) {

		std::vector<IN_ADDR> IPAddresses = { IN_ADDR(), IN_ADDR() };

		IPAddresses[0].S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr;
		IPAddresses[1].S_un.S_addr = (u_long)pIPAddrTable->table[i].dwMask;

		tmp.push_back(makeTuple(inet_ntoa(IPAddresses[0]), inet_ntoa(IPAddresses[1])));
	}
	return std::make_shared<std::vector<AddressTuple>>(tmp);
#endif	
}

AddressTuple NetworkManager::makeTuple(const std::string & host, const std::string & mask)
{

	IN_ADDR host_addr, mask_addr, net_addr, broadcast_addr;
	AddressTuple tmpTuple;

	char net_address[INET_ADDRSTRLEN];
	char broadcast_address[INET_ADDRSTRLEN];

	char * host_ip = Helpers::immutableStringToCharPtr(host);
	char * netmask = Helpers::immutableStringToCharPtr(mask);

	InetPton(AF_INET, host_ip, &host_addr);
	InetPton(AF_INET, netmask, &mask_addr);

	net_addr.S_un.S_addr = host_addr.S_un.S_addr & mask_addr.S_un.S_addr;
	broadcast_addr.S_un.S_addr = net_addr.S_un.S_addr | ~mask_addr.S_un.S_addr;

	InetNtop(AF_INET, &net_addr, net_address, INET_ADDRSTRLEN);

	std::get<AddressTupleFields::ASSIGNED_IP>(tmpTuple) = host;
	std::get<AddressTupleFields::SUBNET>(tmpTuple) = mask;
	std::get<AddressTupleFields::BROADCAST>(tmpTuple) = inet_ntoa(broadcast_addr);
	std::get<AddressTupleFields::NET>(tmpTuple) = inet_ntoa(net_addr);

	return tmpTuple;
}


NetworkManager::~NetworkManager()
{
}

