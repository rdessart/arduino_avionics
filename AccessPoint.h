// AccessPoint.h

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <WiFiNINA.h>

enum class AccessPointMode {
	AP_CREATE,
	AP_CONNECT,
	AP_CONNECT_AND_CONFIGURE,
};

class AccessPoint
{
public:
  AccessPoint();
	AccessPoint(const char* ssid, const char* password);
	void setIp(IPAddress ip);
	void setSubnet(IPAddress subnet);
	void setDns(IPAddress dns);
	void setGateway(IPAddress gateway);
	void setMode(AccessPointMode mode);

	int Init();

	~AccessPoint();

protected:
	IPAddress m_ip;
	IPAddress m_subnet;
	IPAddress m_dns;
	IPAddress m_gateway;
	AccessPointMode m_mode;

	char* m_ssid;
	char* m_password;
};
