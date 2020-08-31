#include "DevicesManager.h"

using namespace TGEngine::core;

DevicesManager *_devicesInstance = nullptr;

DevicesManager &DevicesManager::getInstance() {
	if (_devicesInstance == nullptr) {
		_devicesInstance = new DevicesManager();
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("Galaxy S5", 360, 640));
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("Pixel 2", 411, 731));
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("IPhone 6/7/8", 375, 667));
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("IPhone X", 375, 812));
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("IPad", 768, 1024));
		_devicesInstance->registeredDevices.emplace_back(new sDeviceResolution("IPad", 1024, 1366));
	}
	return *_devicesInstance;
}

DevicesManager::DevicesManager() {}

DevicesManager::~DevicesManager() {}

std::vector<sDeviceResolution *> DevicesManager::getDevicesList() {
	return registeredDevices;
}
