
#include "RoboCatPCH.h"

#if _WIN32


int main(int argc, const char** argv)
{
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#else
const char** __argv;
int __argc;
int main(int argc, const char** argv)
{
	__argc = argc;
	__argv = argv;
#endif

	SocketUtil::StaticInit();

	SocketAddressPtr servAddress = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:9001");
	SocketAddressPtr myAddress = SocketAddressFactory::CreateIPv4FromString("127.0.0.1:9000");

	UDPSocketPtr udpSocket = SocketUtil::CreateUDPSocket(SocketAddressFamily::INET);
	udpSocket->Bind(*myAddress);

	

	std::string msg("Hello server :>");
	if (udpSocket->SendTo(msg.c_str(), msg.length(), *servAddress))
	{
		SocketUtil::ReportError("SendTo");
	}

	SocketUtil::CleanUp();

	return 0;
}
