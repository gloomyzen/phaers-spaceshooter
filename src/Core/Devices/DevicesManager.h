#ifndef TGENGINE_DEVICESMANAGER_H
#define TGENGINE_DEVICESMANAGER_H

#include <string>
#include <vector>
#include <tuple>

#define GET_DEVICES_MANAGER() TGEngine::core::DevicesManager::getInstance()

namespace TGEngine::core {

	struct sDeviceResolution {
		std::string name;
		int width;
		int height;
		bool onlyFullscreen = true;
		sDeviceResolution(std::string _name, int _w, int _h, bool _f = false) {
			name = _name;
			width = _w;
			height = _h;
			onlyFullscreen = _f;
		}
	};

	class DevicesManager {
	public:
		DevicesManager();
		~DevicesManager();
		static DevicesManager &getInstance();

		std::vector<sDeviceResolution*> getDevicesList();

	private:
		std::vector<sDeviceResolution*> registeredDevices{};
	};

}


#endif //TGENGINE_DEVICESMANAGER_H
