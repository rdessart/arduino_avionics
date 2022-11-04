// 
// 
// 

#include "AccessPoint.h"

//int setUpAcessPoint(const char* ssid, const char* password)
//{
//	int status = WL_IDLE_STATUS;
//	IPAddress ip(192, 168, 1, 1);
//	IPAddress subnet(255, 255, 255, 0);
//	if (WiFi.status() == WL_NO_MODULE)
//	{
//		Serial.println("Communication with WiFi module failed!");
//		return WL_AP_FAILED;
//	}
//	Serial.print("Creating access point named: ");
//	Serial.println(ssid);
//	WiFi.config(ip, ip, ip, subnet);
//	status = WiFi.beginAP(ssid, password);
//	if (status != WL_AP_LISTENING)
//	{
//		Serial.println("Creating access point failed");
//		return WL_AP_FAILED;
//	}
//	return status;
//}

AccessPoint::AccessPoint()
{
}

AccessPoint::AccessPoint(const char* ssid, const char* password) : 
	m_mode(AccessPointMode::AP_CREATE),
	m_ip(IPAddress(192, 168, 1, 1)),
	m_gateway(IPAddress(192, 168, 1, 1)),
	m_dns(IPAddress(192, 168, 1, 1)),
	m_subnet(IPAddress(255, 255, 255, 0))
{
  Serial.println("CREATE");
	m_ssid = (char*)malloc(strlen(ssid) * sizeof(char));
	m_password = (char*)malloc(strlen(ssid) * sizeof(char));
	strcpy(m_ssid, ssid);
	strcpy(m_password, password);
}

void AccessPoint::setIp(IPAddress ip)
{
	IPAddress m_ip = ip;
}

void AccessPoint::setSubnet(IPAddress subnet)
{
	IPAddress m_ip = subnet;
}

void AccessPoint::setDns(IPAddress dns)
{
	IPAddress m_dns = dns;
}

void AccessPoint::setGateway(IPAddress gateway)
{
	IPAddress m_gateway = gateway;
}

void AccessPoint::setMode(AccessPointMode mode)
{
	m_mode = mode;
}

int AccessPoint::Init()
{
  Serial.println("INIT");
	int status = WL_IDLE_STATUS;
	if (WiFi.status() == WL_NO_MODULE)
	{
		Serial.println("Communication with WiFi module failed!");
		return WL_AP_FAILED;
	}
	switch (m_mode)
	{
	case AccessPointMode::AP_CREATE:
		Serial.print("Creating AP - SSID :'");
		Serial.print(m_ssid);
		Serial.print("' | Password : '");
		Serial.print(m_password);
		Serial.println("'");
		WiFi.config(m_ip, m_dns, m_gateway, m_subnet);
		status = WiFi.beginAP(m_ssid, m_password);
		if (status != WL_AP_LISTENING)
		{
			Serial.println("Creating access point failed");
			return WL_AP_FAILED;
		}
		return status;
		break;
	case AccessPointMode::AP_CONNECT:
		Serial.print("Connecting AP - SSID :'");
		Serial.print(m_ssid);
		Serial.print("' | Password : '");
		Serial.print(m_password);
		Serial.println("'");
		break;
	default:
		break;
	}

}

AccessPoint::~AccessPoint()
{
	free(m_ssid);
	free(m_password);
}
